#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <Firebase.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "smarthome-5d11a.firebaseio.com"
#define FIREBASE_AUTH "uTP6tlP930oA1s9zuwGIZvrz1ef8ZjVLegROgNN0"

ESP8266WebServer server(80);

const char* ssid = "test";
const char* passphrase = "test";
String st;
String content;
int statusCode;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  delay(10);
  
  String esid;
  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }

  String epass = "";
  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
    
  if ( esid.length() > 1 ) {
      WiFi.begin(esid.c_str(), epass.c_str());
      if (testWifi()) {
        launchWeb();
        return;
      } 
  }
 
  setupAP();
}

bool testWifi() {
  int c = 0;
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) {
        pinMode(D0, OUTPUT);
      return true; 
      } 
    delay(500);
    Serial.print(WiFi.status());    
    c++;
  }
  return false;
} 

void launchWeb() {
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
 
  server.begin();
}

void setupAP(void) {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();

  if (n == 0)
  {
    
  }
 
  else
  {
 
    for (int i = 0; i < n; ++i)
     {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
     }
  }
  Serial.println(""); 
  st = "<ol>";
  for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      st += "<li>";
      st += WiFi.SSID(i);
      st += " (";
      st += WiFi.RSSI(i);
      st += ")";
      st += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
      st += "</li>";
    }
  st += "</ol>";
  delay(100);
  WiFi.softAP("okhttp","khangit");
  launchWeb();
}

void createWebServer()
{
  //Trang chủ
    server.on("/", []() {
        IPAddress ip = WiFi.softAPIP();
        String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
        content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
        content += ipStr;
        content += "<p>";
        content += st;
        content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
        content += "</html>";
        server.send(200, "text/html", content);  
    });

    //Cấu hình wifi
    server.on("/setting", []() {
        String qsid = server.arg("ssid");
        String qpass = server.arg("pass");
        if (qsid.length() > 0 && qpass.length() > 0) {
          Serial.println("clearing eeprom");
          for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
          Serial.println(qsid);
          Serial.println("");
          Serial.println(qpass);
          Serial.println("");
            
          Serial.println("writing eeprom ssid:");
          for (int i = 0; i < qsid.length(); ++i)
            {
              EEPROM.write(i, qsid[i]);
              Serial.print("Wrote: ");
              Serial.println(qsid[i]); 
            }
          Serial.println("writing eeprom pass:"); 
          for (int i = 0; i < qpass.length(); ++i)
            {
              EEPROM.write(32+i, qpass[i]);
              Serial.print("Wrote: ");
              Serial.println(qpass[i]); 
            }    
          EEPROM.commit();
          content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
          statusCode = 200;
        } else {
          content = "{\"Error\":\"404 not found\"}";
          statusCode = 404;
          Serial.println("Sending 404");
        }
        server.send(statusCode, "application/json", content);
    });

    //Điều khiển
        server.on("/controls", []() {
        String para = server.arg("para");
        if(para=="batDen")
          {
            Serial.println(para);
          }
        else if(para=="tatDen")
        {
          
        }
        else if(para=="batOCamDien")
        {
          
        }
        else if(para=="tatOCamDien")
        {
          
        }
        
     
        server.send(statusCode, "application/json", "{\"Success\":\"\"}");
    });
}

void loop() {
  server.handleClient();

  if(WiFi.status()== WL_CONNECTED){

    }
}
