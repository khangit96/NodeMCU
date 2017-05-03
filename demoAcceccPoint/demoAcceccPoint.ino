
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
int stateLED = LOW;

ESP8266WebServer server(80);

void handleRoot() {
    response();
}

void handleLedOn() {
  stateLED = LOW;
  digitalWrite(LED_BUILTIN, stateLED);
  response();
}

void handleLedOff() {
  stateLED = HIGH;
  digitalWrite(LED_BUILTIN, stateLED);
  response();
}

void handleSubmit(){
 String wifiName = server.arg("wifiName");
 Serial.println(wifiName);
 
 String wifiPass = server.arg("wifiPass");
 Serial.println(wifiPass);
 delay(1000);
 //server.stop();
// setUpWifi();
}

void response(){
const char INDEX_HTML[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>ESP8266 Web Form Demo</title>"
"<style>"
"\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
"</style>"
"</head>"
"<body>"
"<h1>ESP8266 Web Form Demo</h1>"
"<FORM action=\"/\" method=\"post\">"
"<P>"
"LED<br>"
"<INPUT type=\"text\" name=\"wifiName\" value=\"Tên wifi\">On<BR>"
"<INPUT type=\"text\" name=\"wifiPass\" value=\"Mật khẩu\">Off<BR>"
"<INPUT type=\"submit\" value=\"Send\"> <INPUT type=\"reset\">"
"</P>"
"</FORM>"
"</body>"
"</html>";

  server.send(200, "text/html", INDEX_HTML);
  handleSubmit();
}


void setUpAccessPoint(){
    const char *ssid = "smarthome";
    const char *password = "khang1234";
    
    delay(1000);
    Serial.begin(9600);
    Serial.println();

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server beginned");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, stateLED);
}

void setUpWifi(){
  WiFi.mode(WIFI_OFF);
  WiFi.begin("SakuRa","hoilamgita");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.println("Wifi start");
}

void setup() {
    if(!digitalRead(14)){
      setUpAccessPoint();
    }
    Serial.println("ok");
}

void loop() {
    server.handleClient();
    
    if(WiFi.status()== WL_CONNECTED){
      
    }
}
