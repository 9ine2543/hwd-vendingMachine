#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <qrcode.h>

//Network
#include <WiFi.h>
#include <ESPmDNS.h>

const char *ssid = "Haruk";
const char *password = "10001000";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
String output2State = "off";
const int output2 = 2;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 5000;

const int led = 2;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define OLED_SDA 21
#define OLED_SCL 22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

QRCode qrcode;

String text[] = {"Welcome <3", "Delivering...", "Select your item", "Item delivered!", "Temp. Closed"};

void setup()
{
  Serial.begin(115200);

  pinMode(output2, OUTPUT);
  digitalWrite(output2, LOW);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.display();
  delay(1000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // initialize LCD
  lcd.init();

  // display.display();
  // Serial.println(display.height());
  // turn on LCD backlight
  lcd.backlight();

  // Clear the buffer
  // display.clearDisplay();

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  uint8_t qrcodeBytes[qrcode_getBufferSize(2)];
  qrcode_initText(&qrcode, qrcodeBytes, 2, ECC_LOW, ("http://" + WiFi.localIP().toString()).c_str());

  display.clearDisplay();
  /*
         * QR-code ต้องมีพื้นที่สีสว่างกว่าตัว block ของ code เลยต้องถม background 
         * ส่วนที่จะแสดง QR-code ให้เป็นสีขาว (หน้าจอจะออกเป็นสีตามเม็ดสีบน oled ซึ่งคือสีฟ้า)
         */
  display.fillRect(0, 0, 128, 64, WHITE);
  for (uint8_t y = 0; y < qrcode.size; y++)
  {
    for (uint8_t x = 0; x < qrcode.size; x++)
    {
      if (qrcode_getModule(&qrcode, x, y))
      {
        /*
               * วาด Rectangle ขนาด 2x2 ในแต่ละตำแหน่งของ qrcode บนหน้าจอ 
                โดยวางมุมซ้ายบนสุดของ QR-Code ไว้ที่พิกัด (39, 18)
                */
        display.fillRect(x * 2 + 39, y * 2 + 7, 2, 2, BLACK);
      }
    }
    Serial.print("\n");
  }

  display.display();
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  { // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);
        delay(1); // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");

            // turns the GPIOs on and off
            if (header.indexOf("/status") >= 0)
            {
              client.println("Content-type:application/json");
              client.println("Connection: close");
              client.println();
              Serial.print(0b00001000); //check status
              delay(300);
              if (Serial.available())
              {
                int status = Serial.read();
                if (status == (int)0b00011001) // ready
                {
                  client.println("{\"status\" : \"ready\" }");
                  client.println();
                }
                else if (status == (int)0b01000000) // occupy
                {
                  client.println("{\"status\" : \"pending\" }");
                  client.println();
                }
                else // error
                {
                  client.println("{\"status\" : \"error\" }");
                  client.println();
                }
              }
            }
            if (header.indexOf("/take") >= 0)
            {
              client.println("Content-type:application/json");
              client.println("Connection: close");
              Serial.print(0b00001000); //check status
              delay(300);
              if (Serial.available())
              {
                /* code */
                int status = Serial.read();
                if (status == (int)0b00011001) // ready
                {
                  if (header.indexOf("/take/1") >= 0) // get item 1
                  {
                    Serial.print(0b10001000);
                  }
                  else if (header.indexOf("/take/2") >= 0) // get item 2
                  {
                    Serial.print(0b10010000);
                  }
                  delay(300);
                  int response = Serial.read();
                  if (response == (int)0b10000000) //started
                  {
                    client.println("{\"status\" : \"started\" }");
                    client.println();
                  }
                  else // error
                  {
                    client.println("{\"status\" : \"error\" }");
                    client.println();
                  }
                }
                else if (status == (int)0b01000000) // occupy
                {
                  client.println("{\"status\" : \"pending\" }");
                  client.println();
                }
                else // error
                {
                  client.println("{\"status\" : \"error\" }");
                  client.println();
                }
              }
            }
            else
            {
              String html = String("<!DOCTYPE html>\n<html>\n\n<head>\n    <title>JIDO</title>\n    <meta charset='UTF-8'>\n    <script src='https://unpkg.com/axios/dist/axios.min.js'></script>\n    <link rel='preconnect' href='https://fonts.gstatic.com'>\n    <link href='https://fonts.googleapis.com/css2?family=Sarabun:wght@300;400;500;600;700&display=swap'\n        rel='stylesheet'>\n</head>\n\n<body>\n    <header>\n        <h1>\n            JIDO\n        </h1>\n    </header>\n    <section>\n        <div class='bar occupy'>\u0e40\u0e04\u0e23\u0e37\u0e48\u0e2d\u0e07\u0e44\u0e21\u0e48\u0e27\u0e48\u0e32\u0e07</div>\n        <div class='zone'>\n            <div class='item-btn' onclick='itemSelect1(this)'>\n                <img src='https://backend.tops.co.th/media/catalog/product/8/8/8858998581153_1.jpg' alt='pepsi'>\n                <div>Pepsi</div>\n            </div>\n            <div class='item-btn' onclick='itemSelect2(this)'>\n                <img src='https://backend.tops.co.th/media/catalog/product/8/8/8851959132074_1.jpg' alt='coke'>\n                <div>Coca-Cola</div>\n            </div>\n        </div>\n    </section>\n    <footer>\n        <div>Computer Hardware Design</div>\n        <div>Computer Engineering KMITL 2021</div>\n    </footer>\n</body>\n\n<script>\n    function setReady() {\n        let noti = document.querySelector('.bar')\n        if (noti) {\n            noti.classList.remove('occupy')\n            noti.classList.remove('delivering')\n            noti.classList.add('ready')\n            noti.innerHTML = '\u0e1e\u0e23\u0e49\u0e2d\u0e21'\n        }\n    }\n    function setOccupy() {\n        let noti = document.querySelector('.bar')\n        if (noti) {\n            noti.classList.remove('ready')\n            noti.classList.remove('delivering')\n            noti.classList.add('occupy')\n            noti.innerHTML = '\u0e40\u0e04\u0e23\u0e37\u0e48\u0e2d\u0e07\u0e44\u0e21\u0e48\u0e27\u0e48\u0e32\u0e07'\n        }\n    }\n    function setError() {\n        let noti = document.querySelector('.bar')\n        if (noti) {\n            noti.classList.remove('ready')\n            noti.classList.remove('delivering')\n            noti.classList.add('occupy')\n            noti.innerHTML = '\u0e40\u0e04\u0e23\u0e37\u0e48\u0e2d\u0e07\u0e21\u0e35\u0e1b\u0e31\u0e0d\u0e2b\u0e32'\n        }\n    }\n    function setDelivering() {\n        let noti = document.querySelector('.bar')\n        if (noti) {\n            noti.classList.remove('occupy')\n            noti.classList.remove('ready')\n            noti.classList.add('delivering')\n            noti.innerHTML = '\u0e01\u0e33\u0e25\u0e31\u0e07\u0e08\u0e48\u0e32\u0e22\u0e2a\u0e34\u0e19\u0e04\u0e49\u0e32'\n        }\n    }\n    function isReady() {\n        let noti = document.querySelector('.bar')\n        if (noti && noti.classList.contains('ready')) {\n            return true\n        } else return false\n    }\n    function setDisable(id, state = true) {\n        let items = document.querySelectorAll('.item-btn')\n        if (items.length !== 0) {\n            let item = items[id - 1]\n            if (item) {\n                if (state === true) item.classList.add('disable')\n                else item.classList.remove('disable')\n            }\n        }\n    }\n\n    async function getStatus() {\n        const res = await fetch('http://STEALURIP/status')\n        const data = await res.json()\n        if (data.status === 'ready') {\n            setReady()\n        } else if (data.status === 'pending') {\n            setOccupy()\n        } else if (data.status === 'error') {\n            setError()\n        }\n        return data.status;\n    }\n    async function selectItem(num) {\n        const res = await fetch(`http://STEALURIP/take/${num}`)\n        const data = await res.json()\n        if (data.status === 'started') {\n            setDelivering()\n        } else if (data.status === 'pending') {\n            setOccupy()\n        } else if (data.status === 'error') {\n            setError()\n        }\n        return data.status;\n    }\n    async function itemSelect1(e) {\n        if (!e.classList.contains('disable')) {\n            console.log('select 1')\n            setDisable(1)\n            setDisable(2)\n            let status = await getStatus()\n            if (status === 'ready') {\n                setReady()\n                status = await selectItem(1)\n            } else if (status === 'pending') {\n                setOccupy()\n                status = await getStatus()\n            } else if (status === 'error') {\n                setError()\n            }\n            setDisable(1, false)\n            setDisable(2, false)\n        }\n    }\n    async function itemSelect2(e) {\n        if (!e.classList.contains('disable')) {\n            console.log('select 2')\n            setDisable(1)\n            setDisable(2)\n            let status = await getStatus()\n            if (status === 'ready') {\n                setReady()\n                status = await selectItem(2)\n            } else if (status === 'pending') {\n                setOccupy()\n            } else if (status === 'error') {\n                setError()\n            }\n            setDisable(1, false)\n            setDisable(2, false)\n        }\n    }\n</script>\n<style>\n    * {\n        margin: 0;\n        padding: 0;\n        font-family: 'Sarabun', sans-serif !important;\n        font-weight: 500;\n        color: #292929;\n        font-size: 40px;\n    }\n\n    body {\n        height: 100vh;\n        width: 100vw;\n        padding: 0;\n        margin: 0;\n        display: flex;\n        flex-flow: column;\n    }\n\n    header {\n        height: 7%;\n        width: 100%;\n        background: #ffe4bb;\n        display: flex;\n        justify-content: center;\n        align-items: center;\n    }\n\n    header h1 {\n        font-size: 50px;\n        color: #ff6d49;\n    }\n\n    section {\n        width: 100%;\n        flex: 1;\n        background: #fffaf7;\n        display: flex;\n        flex-flow: column;\n    }\n\n    footer {\n        margin-top: auto;\n        display: flex;\n        justify-content: center;\n        align-items: center;\n        flex-flow: column;\n        padding: 40px;\n        background: #ffe4bb;\n    }\n\n    footer div:last-child {\n        font-size: 30px;\n        color: #ff4c15;\n    }\n\n    .bar {\n        display: flex;\n        justify-content: center;\n        padding: 20px;\n    }\n\n    .bar.occupy {\n        background: rgb(247, 90, 90);\n        color: rgb(253, 218, 218);\n    }\n\n    .bar.ready {\n        background: rgb(32, 165, 54);\n        color: rgb(230, 255, 218);\n    }\n\n    .bar.delivering {\n        background: rgb(255, 198, 93);\n        color: rgb(160, 72, 0);\n    }\n\n    .zone {\n        display: flex;\n        flex-flow: column;\n        align-items: center;\n    }\n\n    .item-btn {\n        width: 80%;\n        background: #ffffff;\n        border-radius: 40px;\n        border: 2px solid #ff4c15;\n        padding: 20px;\n        margin-top: 70px;\n        display: flex;\n        flex-flow: column;\n        align-items: center;\n    }\n\n    .item-btn>img {\n        height: 500px;\n        margin-bottom: 15px;\n    }\n\n    .disable {\n        filter: blur(4px);\n    }\n</style>\n\n</html>");
              html.replace("STEALURIP",WiFi.localIP().toString()).c_str());
              // display page
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();

              client.println(html);

              client.println();
            }
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

  for (int i; i < 5; i++)
  {
    showText(text[i]);
  }
}

void showText(String text)
{
  lcd.setCursor(0, 0);

  lcd.print(text);

  delay(1000);
  lcd.clear();
}
