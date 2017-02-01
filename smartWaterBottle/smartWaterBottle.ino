
#include <ESP8266WiFi.h>
#include <Firebase.h>
#include <FirebaseArduino.h>

// Firebase Config.
#define FIREBASE_HOST "demonodemcu.firebaseio.com"
#define FIREBASE_AUTH "fNDh456Nv6xtdBPqJtwcXHEN7JfMCWYs44LozYeb"
#define WIFI_SSID "VNPT_Khong Cho"
#define WIFI_PASSWORD "khongcho"

//Hsrf04 measure distance of water
const int triggerPin = D5; // Trigger Pin
const int echoPin = D6; // Echo Pin
int maximumRange = 400; // Maximum range needed adalah 4 meter
int minimumRange = 2; // Minimum range needed adalah 2 cm
float duration, distance; // Duration used to calculate distance
bool check=false;

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

/*Function measure distance of water*/
void measureDistance(){
   
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW); 
  
  duration = pulseIn(echoPin, HIGH);

  //distance = duration/58.2;
 distance= 0.0344*(duration/2);

//  if (distance >= maximumRange || distance <= minimumRange){
    //Serial.println("HC-SR 04 sensor out of measurement range");
 // }
 // else {
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println("cm");
   //  putFloat(distance);
  //}

}

/*Function Loop*/
void loop(){
 //check=Firebase.getBool("state");
 //Serial.println(check);
  measureDistance();
 //if(check==true){
 // measureDistance();
 //}
 
 delay(2000);
}
