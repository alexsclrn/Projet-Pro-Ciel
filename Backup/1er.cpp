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
  client.println("<button class=\"button boutton-phare\">❌</button>");
  client.println("<button class=\"button boutton-phare\">🔦</button>");
  client.println("</div>");
  client.println("<div class=\"center-align buttons-row\">");
  client.println("<button class=\"button boutton-cligno\">⬅</button>");
  client.println("<button class=\"button boutton-cligno\">🔺</button>");
  client.println("<button class=\"button boutton-cligno\">➡</button>");
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
  client.println("psp.x = coords.x;");
  client.println("psp.y = coords.y;");
  // client.println("psp.alpha = 0.5;");
  client.println("});");

  client.println()

  

  client.println("mc.on(\"panend\", function () {");
  client.println("psp.alpha = 0.25;");
  client.println("createjs.Tween.get(psp)");
  client.println(".to({ x: xCenter, y: yCenter }, 750, createjs.Ease.elasticOut);");
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
