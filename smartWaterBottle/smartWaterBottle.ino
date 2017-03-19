
#include <ESP8266WiFi.h>
#include <Firebase.h>
#include <FirebaseArduino.h>

// Firebase Config.
#define FIREBASE_HOST "demonodemcu.firebaseio.com"
#define FIREBASE_AUTH "fNDh456Nv6xtdBPqJtwcXHEN7JfMCWYs44LozYeb"
#define WIFI_SSID "Du Du Duc"
#define WIFI_PASSWORD "0985589587"
#define led D0
#define sound

//Hsrf04 measure distance of water
const int triggerPin = D5; // Trigger Pin
const int echoPin = D6; // Echo Pin
int maximumRange = 400; // Maximum range needed adalah 4 meter
int minimumRange = 2; // Minimum range needed adalah 2 cm
float duration;
float distance; // Duration used to calculate distance
float distanceBefore=100;
int count=0;

/*Setup*/
void setup()
{
    Serial.begin(9600);

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    // connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("Server started");
    Serial.println(WiFi.localIP());
    pinMode(led, OUTPUT);
    pinMode(4, OUTPUT);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/*Function Put value int to Firebase Server*/
void putFloat(float value)
{
    Firebase.pushFloat("value", value);

    if (Firebase.failed()) {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());
        return;
    }
}
void configWifi(char  tenWifi[100],char matKhau[100])
{    
    int count=0;
    WiFi.mode(WIFI_OFF);
    WiFi.begin(tenWifi,matKhau);
    Serial.print("Reconnecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
        
        count++;
        if(count==20)
        {
          ReConfigWifi();
          Serial.print("Connect Failed");
          Firebase.pushBool("wifiSuccess",false);
          return; 
        }
    }
      Serial.print("Connect Success");
      digitalWrite(led,HIGH);
      delay(1000);
      digitalWrite(led,LOW);
      delay(1000);
      digitalWrite(led,HIGH);
      delay(1000);
      digitalWrite(led,LOW);
      delay(1000);
      digitalWrite(led,HIGH);
      delay(1000);
      digitalWrite(led,LOW);
      delay(1000);
      digitalWrite(led,HIGH);
      delay(1000);
      Firebase.pushBool("wifiSuccess",true);
}
void ReConfigWifi()
{    
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("Server started");
    Serial.println(WiFi.localIP());
  
}

/*Function measure distance of water*/
void measureDistance(){
   
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(1000); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW); 
  
  duration = pulseIn(echoPin, HIGH);

  distance = duration/58.2;

  if (distance >= maximumRange || distance <= minimumRange){
    Serial.println("HC-SR 04 sensor out of measurement range");
  }
 else {
  
       Serial.print("Distance:");
       Serial.print(distance);
       Serial.println("cm");
       putFloat(distance);
  }

}

/*Function Loop*/
void loop()
{
  if(Firebase.getBool("status"))
  {
        digitalWrite(led,LOW);
        if (Firebase.getBool("WifiChange"))
        { 
          Firebase.setBool("WifiChange",false);
          
          String str_MatKhau=Firebase.getString("Wifi/matKhau");
          String str_TenWifi=Firebase.getString("Wifi/tenWifi");
           
          char tenWifi[100];
          char matKhau[100];
          str_MatKhau.toCharArray(matKhau, 100) ;
          str_TenWifi.toCharArray(tenWifi, 100) ;
          
         configWifi(tenWifi,matKhau);
         }

    //Nếu người dùng hẹn giờ
      if(Firebase.getBool("Alarm")
      {
        Firebase.setBool("Alarm",false);
         digitalWrite(4,HIGH);
      }
  }
  else
  {
       digitalWrite(led,HIGH);
  }

 delay(2000);
}
