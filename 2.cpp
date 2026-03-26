#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "Voiture";
const char* password = "123456";

int ledPin = 2;
uint8_t oled_addr = 0x3C;

WiFiServer server(80);

void setup() {

  Serial.begin(74880);
  delay(100);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, oled_addr)) {
    Serial.println("Euh marche pas");
    while(true);
  }

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  // oled.println("Connexion a ");
  // oled.println(ssid);
  oled.display();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  WiFi.softAP(ssid, password);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   oled.print(".");
  //   oled.display();
  // }

  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.println("WiFi OK");
  oled.println("Server OK");
  oled.println("SSID: Voiture");
  oled.print("http://");
  oled.println(WiFi.softAPIP());
  oled.display();

  server.begin();
}

void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("New client");

  while (!client.available()) {
    delay(1);
  }

  while (client.available()) {
    client.read();
  }

  client.flush();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=UTF-8");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html lang=\"fr\">");
  client.println("<head>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<title>Telecommande</title>");
  client.println("<script src=\"http://code.jquery.com/jquery-3.6.0.min.js\"></script>");
  client.println("<script src=\"http://code.createjs.com/1.0.0/createjs.min.js\"></script>");
  client.println("<script src=\"http://hammerjs.github.io/dist/hammer.min.js\"></script>");
  client.println("<style>");
  client.println("body {height:100%;width:100%;background-color:#30814f;margin:0;font-family:Arial, Helvetica, sans-serif;}");
  client.println(".space-top {padding-top:200px;}");
  client.println(".center {text-align:center;}");
  client.println(".center-align {display:flex;justify-content:center;}");
  client.println(".thin {font-weight:300;}");
  client.println(".light {font-weight:400;text-align:center;color:white;font-family:Arial Black;}");
  client.println("#joystick {height:300px;width:300px;border-radius:300px;background-color:#ffffff;cursor:all-scroll;user-select:none;}");
  client.println(".button {background-color:white;border:none;color:black;padding:5px 15px;text-align:center;text-decoration:none;display:inline-block;font-size:16px;margin:4px 2px;transition-duration:0.4s;cursor:pointer;}");
  client.println(".buttons-row {margin-top:10px;gap:3px;}");
  client.println(".boutton-phare {border-radius:8px;}");
  client.println(".boutton-phare:hover {background-color:#ffee00;color:white;}");
  client.println(".boutton-cligno {border-radius:8px;}");
  client.println(".boutton-cligno:hover {background-color:#e45f22;color:white;}");
  client.println(".noselect {-webkit-touch-callout:none;-webkit-user-select:none;-khtml-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none;}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body class=\"noselect\" onload=\"init();\">");
  client.println("<div class=\"container space-top\">");
  client.println("<div class=\"center-align\">");
  client.println("<canvas id=\"joystick\" width=\"300\" height=\"300\"></canvas>");
  client.println("</div>");
  client.println("<p id=\"Vitesse\" class=\"light\">Vitesse : 0kmh</p>");
  client.println("<div class=\"center-align buttons-row\">");
  client.println("<button class=\"button boutton-phare\">"
    "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 256 256' width='32' height='32' fill='black'>"
    "<path d='M140,64V192a12.01343,12.01343,0,0,1-12,12H88A76.00037,76.00037,0,0,1,12.002,127.4248C12.31055,85.835,46.80859,52,88.90381,52H128A12.01343,12.01343,0,0,1,140,64Zm-8,0a4.00427,4.00427,0,0,0-4-4H88.90381C51.187,60,20.27783,90.27344,20.002,127.4834A68.00056,68.00056,0,0,0,88,196h40a4.00427,4.00427,0,0,0,4-4Z'/>"
    "<path d='M168 84 L240 156 M240 84 L168 156' stroke='black' stroke-width='12' stroke-linecap='round'/>"
    "</svg>"
    "</button>");
  client.println("<button class=\"button boutton-phare\">"
    "<svg fill='black' width='32' height='32' viewBox='0 0 256 256' xmlns='http://www.w3.org/2000/svg'>"
    "<path d='M164,80a4.0002,4.0002,0,0,1,4-4h72a4,4,0,0,1,0,8H168A4.0002,4.0002,0,0,1,164,80Zm76,92H168a4,4,0,0,0,0,8h72a4,4,0,0,0,0-8Zm0-64H168a4,4,0,0,0,0,8h72a4,4,0,0,0,0-8Zm0,32H168a4,4,0,0,0,0,8h72a4,4,0,0,0,0-8ZM140,64V192a12.01343,12.01343,0,0,1-12,12H88A76.00037,76.00037,0,0,1,12.002,127.4248C12.31055,85.835,46.80859,52,88.90381,52H128A12.01343,12.01343,0,0,1,140,64Zm-8,0a4.00427,4.00427,0,0,0-4-4H88.90381C51.187,60,20.27783,90.27344,20.002,127.4834A68.00056,68.00056,0,0,0,88,196h40a4.00427,4.00427,0,0,0,4-4Z'/>"
    "</svg>"
    "</button>");
  client.println("</div>");
  client.println("<div class=\"center-align buttons-row\">");
  client.println("<button class=\"button boutton-cligno\">"
    "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 286 286' width='32' height='32' fill='black'>"
    "<path d='M129.352,102.748H81.408l-0.002-26.155c0-3.033-1.827-5.768-4.63-6.929"
    "c-2.804-1.161-6.027-0.519-8.174,1.626L2.196,137.696C0.79,139.102,0,141.01,0,142.999"
    "s0.79,3.897,2.197,5.303l66.408,66.406c1.435,1.435,3.353,2.197,5.305,2.197"
    "c0.966,0,1.94-0.187,2.868-0.571c2.803-1.161,4.63-3.896,4.63-6.929v-26.155h47.943"
    "c4.143,0,7.5-3.358,7.5-7.5v-65.503C136.852,106.106,133.494,102.748,129.352,102.748z"
    "M121.852,168.251H73.908c-4.143,0-7.5,3.358-7.5,7.5v15.548l-48.302-48.3l48.301-48.301"
    "l0.001,15.55c0,4.142,3.358,7.5,7.5,7.5h47.943V168.251z'/>"
    "</svg>"
    "</button>");
  client.println("<button class=\"button boutton-cligno\">"
    "<svg fill='black' width='32' height='32' viewBox='0 0 36 36' xmlns='http://www.w3.org/2000/svg'>"
    "<path d='M18,21.32a1.3,1.3,0,0,0,1.3-1.3V14a1.3,1.3,0,1,0-2.6,0v6A1.3,1.3,0,0,0,18,21.32Z'></path>"
    "<circle cx='17.95' cy='24.27' r='1.5'></circle>"
    "<path d='M30.33,25.54,20.59,7.6a3,3,0,0,0-5.27,0L5.57,25.54A3,3,0,0,0,8.21,30H27.69a3,3,0,0,0,2.64-4.43Zm-1.78,1.94a1,1,0,0,1-.86.49H8.21a1,1,0,0,1-.88-1.48L17.07,8.55a1,1,0,0,1,1.76,0l9.74,17.94A1,1,0,0,1,28.55,27.48Z'></path>"
    "<rect x='0' y='0' width='36' height='36' fill-opacity='0'/>"
    "</svg>"
    "</button>");
  client.println("<button class=\"button boutton-cligno\">"
    "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 286 286' width='32' height='32' fill='black'>"
    "<path d='M283.801,137.696L217.393,71.29c-2.145-2.146-5.371-2.788-8.173-1.626"
    "c-2.803,1.161-4.63,3.896-4.63,6.929v26.155h-47.943c-4.143,0-7.5,3.358-7.5,7.5v65.503"
    "c0,4.142,3.357,7.5,7.5,7.5h47.943l0.002,26.155c0,3.033,1.827,5.768,4.63,6.929"
    "c0.928,0.384,1.902,0.571,2.868,0.571c1.952,0,3.87-0.762,5.306-2.197l66.406-66.406"
    "c1.406-1.406,2.196-3.314,2.196-5.303S285.208,139.102,283.801,137.696z"
    "M219.591,191.3l-0.001-15.55c0-4.142-3.358-7.5-7.5-7.5h-47.943v-50.503h47.943"
    "c4.143,0,7.5-3.358,7.5-7.5V94.7l48.302,48.3L219.591,191.3z'/>"
    "</svg>"
    "</button>");
  client.println("</div>");
  client.println("</div>");
  client.println("<script>");
  client.println("function init() {");
  client.println("var xCenter = 150;");
  client.println("var yCenter = 150;");
  client.println("var stage = new createjs.Stage('joystick');");
  client.println("var psp = new createjs.Shape();");
  client.println("psp.graphics.beginFill('#333333').drawCircle(xCenter, yCenter, 50);");
  client.println("psp.alpha = 0.25;");
  client.println("var vertical = new createjs.Shape();");
  client.println("var horizontal = new createjs.Shape();");
  client.println("stage.addChild(psp, vertical, horizontal);");
  client.println("createjs.Ticker.framerate = 60;");
  client.println("createjs.Ticker.addEventListener('tick', stage);");
  client.println("var myElement = document.getElementById('joystick');");
  client.println("var mc = new Hammer(myElement);");
  client.println("mc.on(\"panstart\", function () {");
  client.println("xCenter = psp.x;");
  client.println("yCenter = psp.y;");
  client.println("psp.alpha = 0.5;");
  client.println("});");
  client.println("mc.on(\"panmove\", function (ev) {");
  client.println("var pos = $('#joystick').position();");
  client.println("var x = ev.center.x - pos.left - 150;");
  client.println("var y = ev.center.y - pos.top - 150;");
  client.println("console.log('y: ' + Math.round(y));");
  client.println("console.log('X: ' + Math.round(x));");
  client.println("var coords = calculateCoords(ev.angle, ev.distance);");
  client.println("psp.x = xCenter + coords.x;");
  client.println("psp.y = yCenter + coords.y;");
  client.println("stage.update();");
  client.println("});");
  client.println("mc.on(\"panend\", function () {");
  client.println("psp.alpha = 0.25;");
  client.println("createjs.Tween.get(psp)");
  client.println(".to({ x: xCenter, y: yCenter }, 750, createjs.Ease.elasticOut);");
  client.println("stage.update();");
  client.println("});");
  client.println("}");
  client.println("function calculateCoords(angle, distance) {");
  client.println("distance = Math.min(distance, 100);");
  client.println("var rads = (angle * Math.PI) / 180;");
  client.println("return {");
  client.println("x: distance * Math.cos(rads),");
  client.println("y: distance * Math.sin(rads)");
  client.println("};");
  client.println("}");
  client.println("</script>");
  client.println("</body>");
  client.println("</html>");


  delay(1);
  client.stop();

  Serial.println("Client disconnected");
}
