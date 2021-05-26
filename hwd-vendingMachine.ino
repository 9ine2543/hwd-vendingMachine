#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <qrcode.h>

//Network
#include <WiFi.h>
#include <ESPmDNS.h>
const char *c_html = "<!DOCTYPE html>\r\n"
                     "<html>\r\n\r\n"
                     "<head>\r\n"
                     "    <title>JIDO</tit"
                     "le>\r\n"
                     "    <meta charset=\'"
                     "UTF-8\'>\r\n"
                     "    <script src=\'ht"
                     "tps://unpkg.com/axio"
                     "s/dist/axios.min.js"
                     "\'></script>\r\n"
                     "    <link rel=\'prec"
                     "onnect\' href=\'http"
                     "s://fonts.gstatic.co"
                     "m\'>\r\n"
                     "    <link href=\'htt"
                     "ps://fonts.googleapi"
                     "s.com/css2?family=Sa"
                     "rabun:wght@300;400;5"
                     "00;600;700&display=s"
                     "wap\'\r\n"
                     "        rel=\'styles"
                     "heet\'>\r\n"
                     "</head>\r\n\r\n"
                     "<body>\r\n"
                     "    <header>\r\n"
                     "        <h1>\r\n"
                     "            JIDO\r\n"
                     "        </h1>\r\n"
                     "    </header>\r\n"
                     "    <section>\r\n"
                     "        <div class="
                     "\'bar ready\'>พร้อม<"
                     "/div>\r\n"
                     "        <div class="
                     "\'zone\'>\r\n"
                     "            <div cla"
                     "ss=\'item-btn\' oncl"
                     "ick=\'itemSelect1(th"
                     "is)\'>\r\n"
                     "                <img"
                     " src=\'https://backe"
                     "nd.tops.co.th/media/"
                     "catalog/product/8/8/"
                     "8858998581153_1.jpg"
                     "\' alt=\'pepsi\'>\r"
                     "\n"
                     "                <div"
                     ">Pepsi</div>\r\n"
                     "            </div>\r"
                     "\n"
                     "            <div cla"
                     "ss=\'item-btn\' oncl"
                     "ick=\'itemSelect2(th"
                     "is)\'>\r\n"
                     "                <img"
                     " src=\'https://backe"
                     "nd.tops.co.th/media/"
                     "catalog/product/8/8/"
                     "8851959132074_1.jpg"
                     "\' alt=\'coke\'>\r\n"
                     "                <div"
                     ">Coca-Cola</div>\r\n"
                     "            </div>\r"
                     "\n"
                     "        </div>\r\n"
                     "    </section>\r\n"
                     "    <footer>\r\n"
                     "        <div>Compute"
                     "r Hardware Design</d"
                     "iv>\r\n"
                     "        <div>Compute"
                     "r Engineering KMITL "
                     "2021</div>\r\n"
                     "    </footer>\r\n"
                     "</body>\r\n\r\n"
                     "<script>\r\n"
                     "    function setRead"
                     "y() {\r\n"
                     "        let noti = d"
                     "ocument.querySelecto"
                     "r(\'.bar\')\r\n"
                     "        if (noti) {"
                     "\r\n"
                     "            noti.cla"
                     "ssList.remove(\'occu"
                     "py\')\r\n"
                     "            noti.cla"
                     "ssList.remove(\'deli"
                     "vering\')\r\n"
                     "            noti.cla"
                     "ssList.add(\'ready\'"
                     ")\r\n"
                     "            noti.inn"
                     "erHTML = \'พร้อม\'\r"
                     "\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    function setOccu"
                     "py() {\r\n"
                     "        let noti = d"
                     "ocument.querySelecto"
                     "r(\'.bar\')\r\n"
                     "        if (noti) {"
                     "\r\n"
                     "            noti.cla"
                     "ssList.remove(\'read"
                     "y\')\r\n"
                     "            noti.cla"
                     "ssList.remove(\'deli"
                     "vering\')\r\n"
                     "            noti.cla"
                     "ssList.add(\'occupy"
                     "\')\r\n"
                     "            noti.inn"
                     "erHTML = \'เครื่องไม"
                     "่ว่าง\'\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    function setNoIt"
                     "em() {\r\n"
                     "        let noti = d"
                     "ocument.querySelecto"
                     "r(\'.bar\')\r\n"
                     "        if (noti) {"
                     "\r\n"
                     "            noti.cla"
                     "ssList.remove(\'read"
                     "y\')\r\n"
                     "            noti.cla"
                     "ssList.remove(\'deli"
                     "vering\')\r\n"
                     "            noti.cla"
                     "ssList.add(\'occupy"
                     "\')\r\n"
                     "            noti.inn"
                     "erHTML = \'ไม่มีของ"
                     "\'\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    function setErro"
                     "r() {\r\n"
                     "        let noti = d"
                     "ocument.querySelecto"
                     "r(\'.bar\')\r\n"
                     "        if (noti) {"
                     "\r\n"
                     "            noti.cla"
                     "ssList.remove(\'read"
                     "y\')\r\n"
                     "            noti.cla"
                     "ssList.remove(\'deli"
                     "vering\')\r\n"
                     "            noti.cla"
                     "ssList.add(\'occupy"
                     "\')\r\n"
                     "            noti.inn"
                     "erHTML = \'เครื่องมี"
                     "ปัญหา\'\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    function setDeli"
                     "vering() {\r\n"
                     "        let noti = d"
                     "ocument.querySelecto"
                     "r(\'.bar\')\r\n"
                     "        if (noti) {"
                     "\r\n"
                     "            noti.cla"
                     "ssList.remove(\'occu"
                     "py\')\r\n"
                     "            noti.cla"
                     "ssList.remove(\'read"
                     "y\')\r\n"
                     "            noti.cla"
                     "ssList.add(\'deliver"
                     "ing\')\r\n"
                     "            noti.inn"
                     "erHTML = \'กำลังจ่าย"
                     "สินค้า\'\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    function isReady"
                     "() {\r\n"
                     "        let noti = d"
                     "ocument.querySelecto"
                     "r(\'.bar\')\r\n"
                     "        if (noti && "
                     "noti.classList.conta"
                     "ins(\'ready\')) {\r"
                     "\n"
                     "            return t"
                     "rue\r\n"
                     "        } else retur"
                     "n false\r\n"
                     "    }\r\n"
                     "    function setDisa"
                     "ble(id, state = true"
                     ") {\r\n"
                     "        let items = "
                     "document.querySelect"
                     "orAll(\'.item-btn\')"
                     "\r\n"
                     "        if (items.le"
                     "ngth !== 0) {\r\n"
                     "            let item"
                     " = items[id - 1]\r\n"
                     "            if (item"
                     ") {\r\n"
                     "                if ("
                     "state === true) item"
                     ".classList.add(\'dis"
                     "able\')\r\n"
                     "                else"
                     " item.classList.remo"
                     "ve(\'disable\')\r\n"
                     "            }\r\n"
                     "        }\r\n"
                     "    }\r\n\r\n"
                     "    async function g"
                     "etStatus() {\r\n"
                     "        try {\r\n"
                     "            await fe"
                     "tch(\'http://STEALUR"
                     "IP/status\')\r\n"
                     "            await fe"
                     "tch(\'http://STEALUR"
                     "IP/status\')\r\n"
                     "            const re"
                     "s = await fetch(\'ht"
                     "tp://STEALURIP/statu"
                     "s\')\r\n"
                     "            const da"
                     "ta = await res.json("
                     ")\r\n"
                     "            if (data"
                     "[0] === \'ready\') {"
                     "\r\n"
                     "                setR"
                     "eady()\r\n"
                     "            } else i"
                     "f (data[0] === \'pen"
                     "ding\') {\r\n"
                     "                setO"
                     "ccupy()\r\n"
                     "            } else i"
                     "f (data[0] === \'err"
                     "or\') {\r\n"
                     "                setE"
                     "rror()\r\n"
                     "                retu"
                     "rn data[0];\r\n\r\n"
                     "            }\r\n"
                     "        } catch {\r"
                     "\n"
                     "            setError"
                     "()\r\n"
                     "            return "
                     "\"error\"\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    async function s"
                     "electItem(num) {\r\n"
                     "        try {\r\n"
                     "            const re"
                     "s = await fetch(`htt"
                     "p://STEALURIP/take/$"
                     "{num}`)\r\n"
                     "            const da"
                     "ta = await res.json("
                     ")\r\n"
                     "            if (data"
                     "[0] === \'started\')"
                     " {\r\n"
                     "                setD"
                     "elivering()\r\n"
                     "            } else i"
                     "f (data[0] === \'err"
                     "or\') {\r\n"
                     "                setE"
                     "rror()\r\n"
                     "            }\r\n"
                     "            return d"
                     "ata[0];\r\n"
                     "        } catch {\r"
                     "\n"
                     "            setError"
                     "()\r\n"
                     "            return "
                     "\"error\";\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    async function i"
                     "temSelect1(e) {\r\n"
                     "        if (!e.class"
                     "List.contains(\'disa"
                     "ble\')) {\r\n"
                     "            console."
                     "log(\'select 1\')\r"
                     "\n"
                     "            setDisab"
                     "le(1)\r\n"
                     "            setDisab"
                     "le(2)\r\n"
                     "            let stat"
                     "us = await getStatus"
                     "()\r\n"
                     "            if (stat"
                     "us === \'ready\') {"
                     "\r\n"
                     "                setR"
                     "eady()\r\n"
                     "                stat"
                     "us = await selectIte"
                     "m(1)\r\n"
                     "            } else i"
                     "f (status === \'pend"
                     "ing\') {\r\n"
                     "                setO"
                     "ccupy()\r\n"
                     "                stat"
                     "us = await getStatus"
                     "()\r\n"
                     "            } else i"
                     "f (status === \'erro"
                     "r\') {\r\n"
                     "                setE"
                     "rror()\r\n"
                     "            }\r\n"
                     "            setDisab"
                     "le(1, false)\r\n"
                     "            setDisab"
                     "le(2, false)\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "    async function i"
                     "temSelect2(e) {\r\n"
                     "        if (!e.class"
                     "List.contains(\'disa"
                     "ble\')) {\r\n"
                     "            console."
                     "log(\'select 2\')\r"
                     "\n"
                     "            setDisab"
                     "le(1)\r\n"
                     "            setDisab"
                     "le(2)\r\n"
                     "            let stat"
                     "us = await getStatus"
                     "()\r\n"
                     "            if (stat"
                     "us === \'ready\') {"
                     "\r\n"
                     "                setR"
                     "eady()\r\n"
                     "                stat"
                     "us = await selectIte"
                     "m(2)\r\n"
                     "            } else i"
                     "f (status === \'pend"
                     "ing\') {\r\n"
                     "                setO"
                     "ccupy()\r\n"
                     "            } else i"
                     "f (status === \'erro"
                     "r\') {\r\n"
                     "                setE"
                     "rror()\r\n"
                     "            }\r\n"
                     "            setDisab"
                     "le(1, false)\r\n"
                     "            setDisab"
                     "le(2, false)\r\n"
                     "        }\r\n"
                     "    }\r\n"
                     "</script>\r\n"
                     "<style>\r\n"
                     "    * {\r\n"
                     "        margin: 0;\r"
                     "\n"
                     "        padding: 0;"
                     "\r\n"
                     "        font-family:"
                     " \'Sarabun\', sans-s"
                     "erif !important;\r\n"
                     "        font-weight:"
                     " 500;\r\n"
                     "        color: #2929"
                     "29;\r\n"
                     "        font-size: 4"
                     "0px;\r\n"
                     "    }\r\n\r\n"
                     "    body {\r\n"
                     "        height: 100v"
                     "h;\r\n"
                     "        width: 100vw"
                     ";\r\n"
                     "        padding: 0;"
                     "\r\n"
                     "        margin: 0;\r"
                     "\n"
                     "        display: fle"
                     "x;\r\n"
                     "        flex-flow: c"
                     "olumn;\r\n"
                     "    }\r\n\r\n"
                     "    header {\r\n"
                     "        height: 7%;"
                     "\r\n"
                     "        width: 100%;"
                     "\r\n"
                     "        background: "
                     "#ffe4bb;\r\n"
                     "        display: fle"
                     "x;\r\n"
                     "        justify-cont"
                     "ent: center;\r\n"
                     "        align-items:"
                     " center;\r\n"
                     "    }\r\n\r\n"
                     "    header h1 {\r\n"
                     "        font-size: 5"
                     "0px;\r\n"
                     "        color: #ff6d"
                     "49;\r\n"
                     "    }\r\n\r\n"
                     "    section {\r\n"
                     "        width: 100%;"
                     "\r\n"
                     "        flex: 1;\r\n"
                     "        background: "
                     "#fffaf7;\r\n"
                     "        display: fle"
                     "x;\r\n"
                     "        flex-flow: c"
                     "olumn;\r\n"
                     "    }\r\n\r\n"
                     "    footer {\r\n"
                     "        margin-top: "
                     "auto;\r\n"
                     "        display: fle"
                     "x;\r\n"
                     "        justify-cont"
                     "ent: center;\r\n"
                     "        align-items:"
                     " center;\r\n"
                     "        flex-flow: c"
                     "olumn;\r\n"
                     "        padding: 40p"
                     "x;\r\n"
                     "        background: "
                     "#ffe4bb;\r\n"
                     "    }\r\n\r\n"
                     "    footer div:last-"
                     "child {\r\n"
                     "        font-size: 3"
                     "0px;\r\n"
                     "        color: #ff4c"
                     "15;\r\n"
                     "    }\r\n\r\n"
                     "    .bar {\r\n"
                     "        display: fle"
                     "x;\r\n"
                     "        justify-cont"
                     "ent: center;\r\n"
                     "        padding: 20p"
                     "x;\r\n"
                     "    }\r\n\r\n"
                     "    .bar.occupy {\r"
                     "\n"
                     "        background: "
                     "rgb(247, 90, 90);\r"
                     "\n"
                     "        color: rgb(2"
                     "53, 218, 218);\r\n"
                     "    }\r\n\r\n"
                     "    .bar.ready {\r\n"
                     "        background: "
                     "rgb(32, 165, 54);\r"
                     "\n"
                     "        color: rgb(2"
                     "30, 255, 218);\r\n"
                     "    }\r\n\r\n"
                     "    .bar.delivering "
                     "{\r\n"
                     "        background: "
                     "rgb(255, 198, 93);\r"
                     "\n"
                     "        color: rgb(1"
                     "60, 72, 0);\r\n"
                     "    }\r\n\r\n"
                     "    .zone {\r\n"
                     "        display: fle"
                     "x;\r\n"
                     "        flex-flow: c"
                     "olumn;\r\n"
                     "        align-items:"
                     " center;\r\n"
                     "    }\r\n\r\n"
                     "    .item-btn {\r\n"
                     "        width: 80%;"
                     "\r\n"
                     "        background: "
                     "#ffffff;\r\n"
                     "        border-radiu"
                     "s: 40px;\r\n"
                     "        border: 2px "
                     "solid #ff4c15;\r\n"
                     "        padding: 20p"
                     "x;\r\n"
                     "        margin-top: "
                     "70px;\r\n"
                     "        display: fle"
                     "x;\r\n"
                     "        flex-flow: c"
                     "olumn;\r\n"
                     "        align-items:"
                     " center;\r\n"
                     "    }\r\n\r\n"
                     "    .item-btn>img {"
                     "\r\n"
                     "        height: 500p"
                     "x;\r\n"
                     "        margin-botto"
                     "m: 15px;\r\n"
                     "    }\r\n\r\n"
                     "    .disable {\r\n"
                     "        filter: blur"
                     "(4px);\r\n"
                     "    }\r\n"
                     "</style>\r\n\r\n"
                     "</html>";
const char *ssid = "N19EENIN";
const char *password = "Nine06012000";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
String output2State = "off";
const int output2 = 2;
WiFiClient *temp_client;
String action = "";
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
  Serial1.begin(10000);
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
        // delay(1); // print it out the serial monitor
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
              Serial1.write(0b00001000); //check status
              temp_client = &client;
              action = "check";
            }
            else if (header.indexOf("/take/1") >= 0) // get item 1
            {
              client.println("Content-type:application/json");
              client.println("Connection: close");
              client.println();
              Serial1.write(0b10001000);
              temp_client = &client;
              action = "take";
            }
            else if (header.indexOf("/take/2") >= 0) // get item 2
            {
              client.println("Content-type:application/json");
              client.println("Connection: close");
              client.println();
              Serial1.write(0b10010000);
              temp_client = &client;
              action = "take";
            }
            else
            {
              String html = String(c_html);
              html.replace("STEALURIP", WiFi.localIP().toString().c_str());
              // display page
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();

              client.println(html.c_str());

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

    if (temp_client == NULL)
    {
      client.stop();
      Serial.println("Client disconnected.");
      Serial.println("");
    }
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

void serialEvent()
{
  while (Serial1.available() && temp_client != NULL)
  {
    int status = Serial1.read();
    Serial.println(status, 2);
    if (action == "check")
    {
      if ((status >> 6) == 0) // ready
      {
        int item_1 = (int)status & 0b0111;
        int item_2 = ((int)status & 0b111000) >> 3;
        String response = "[\"ready\",11item_111,11item_211]";
        response.replace("11item_111", String(item_1));
        response.replace("11item_211", String(item_2));
        temp_client->println(response.c_str());
        temp_client->println();
      }
      else if ((status >> 6) == 1) // occupy
      {
        int item_1 = (int)status & 0b0111;
        int item_2 = ((int)status & 0b111000) >> 3;
        String response = "[\"pending\",11item_111,11item_211]";
        response.replace("11item_111", String(item_1));
        response.replace("11item_211", String(item_2));
        temp_client->println(response.c_str());
        temp_client->println();
      }
      else // error
      {
        temp_client->println("[\"error\",0,0]");
        temp_client->println();
      }
    }
    else if (action == "take")
    {
      if (status == (int)0b10000000) // ready
      {
        temp_client->println("[\"ready\",0,0]");
        temp_client->println();
      }
      else // error
      {
        temp_client->println("[\"error\",0,0]");
        temp_client->println();
      }
    }
    temp_client->stop();
    temp_client = NULL;
  }
}