#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Firebase.h>
// Set these to run example.
#define FIREBASE_HOST "demonodemcu.firebaseio.com"
#define FIREBASE_AUTH "fNDh456Nv6xtdBPqJtwcXHEN7JfMCWYs44LozYeb"
#define WIFI_SSID "VNPT_Khong Cho"
#define WIFI_PASSWORD "khongcho"

FirebaseArduino FirebaseStream;
void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  FirebaseStream.begin(FIREBASE_HOST, FIREBASE_AUTH);
  FirebaseStream.stream("/data");
}

//Pust some String
void putStr()
{
    Firebase.pushString("value","khang");
    
      if (Firebase.failed()) {
          Serial.print("setting /message failed:");
          Serial.println(Firebase.error());  
          return;
      }
      
}
void listenDataChangeFirebase()
{
    
    if (FirebaseStream.available()) {
     //   FirebaseObject event = FirebaseStream.readEvent();
       /* Serial.print("event: ");
        Serial.println(event.getString("event"));
        Serial.print("path: ");
        Serial.println(event.getString("path"));
        Serial.print("data: ");
        Serial.println(event.getInt("data"));*/
  }
    
}
void loop() { 
  if (FirebaseStream.available()) {
        FirebaseObject event = FirebaseStream.readEvent();
       /* Serial.print("event: ");
        Serial.println(event.getString("event"));
        Serial.print("path: ");
        Serial.println(event.getString("path"));
        Serial.print("data: ");
        Serial.println(event.getInt("data"));*/
  }
 delay(1000);
  
}
