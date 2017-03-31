
#include <ESP8266WiFi.h>
#include <Firebase.h>
#include <FirebaseArduino.h>

// Firebase Config.
#define FIREBASE_HOST "smartgardening-3d2d2.firebaseio.com"
#define FIREBASE_AUTH "pJ5LGq1SIudyXT28vhPojt0LtWmgodB1sIkc1JDv"
#define WIFI_SSID "okhttp"
#define WIFI_PASSWORD "1234567890"
#define led D0
String test = "";
int count = 0;
char command;
char firstChar;
String key="1";

/*Function setup*/
void setup()
{
    Serial.begin(9600);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    pinMode(led, OUTPUT);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/*Funtion receive data from Atemga8*/
void receiveDataFromAtmga8()
{
    if (Serial.available()) {
        count++;
        command = ((byte)Serial.read());
        test += command;

        if (count == 1) {
            firstChar = command;
        }

        if (count == 4) {

            if (firstChar == '1') {
                Firebase.pushString(key+"/DuLieu/NhietDo", test);
            }

            else if (firstChar == '2') {
                Firebase.pushString(key+"/DuLieu/DoAm1", test);
            }

            else if (firstChar == '3') {
                Firebase.pushString(key+"/DuLieu/DoAm2", test);
            }

            else if (firstChar == '4') {
                Firebase.pushString(key+"/DuLieu/DoAm3", test);
            }
            test = "";
            count = 0;
        }
    }
}

/*Receive data from Firebase*/
void receiveDataFromFirebase(){
   if (Firebase.getBool(key+"/DieuKhien/tinhTrang")) {
      Firebase.setBool(key+"/DieuKhien/tinhTrang",false);
        //Bật máy bơm
        if (Firebase.getBool(key+"/DieuKhien/batMayBom")) {
          Serial.println("1");
        }
        else {
           Serial.println("0");
        }

        //Bật đèn
        if (Firebase.getBool(key+"/DieuKhien/batDen")) {
         //  Serial.println("Bat den");
        }
        else {
         // Serial.println("Tat den");
        }

        //Kéo màng
        if (Firebase.getBool(key+"/DieuKhien/keoMang")) {
          //Serial.println("Bat keo mang");
        }
        else {
          //Serial.println("Tắt keo mang");
        }
    }
}

/*Main */
void loop()
{
    receiveDataFromAtmga8();
    receiveDataFromFirebase();
    
    delay(20);
}

