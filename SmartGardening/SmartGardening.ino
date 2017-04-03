
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
    pinMode(5, OUTPUT);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/*Funtion receive data from Atemga8*/
void receiveDataFromAtmga8()
{
     if (Serial.available() >= 4) 
     {
          char abc[4]= {};
           Serial.readBytes(abc,4);
     
            if (abc[0] == '1') {
                Firebase.setString(key+"/DuLieu/NhietDo",abc);
            }

            else if (abc[0] == '2') {
                Firebase.setString(key+"/DuLieu/DoAm1", abc);
            }

            else if (abc[0] == '3') {
                Firebase.setString(key+"/DuLieu/DoAm2", abc);
            }

            else if (abc[0] == '4') {
                Firebase.setString(key+"/DuLieu/DoAm3", abc);
            }
    }
   
}

/*Receive data from Firebase*/
void receiveDataFromFirebase(){

  //Điều khiển từng hệ thống
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
        
         digitalWrite(5,HIGH);
        }
        else {
       
           digitalWrite(5,LOW);
        }

        //Kéo màng
        if (Firebase.getBool(key+"/DieuKhien/keoMang")) {
          //Serial.println("Bat keo mang");
        }
        else {
          //Serial.println("Tắt keo mang");
        }
    }

    //Điều khiển chung
    if (Firebase.getBool("DieuKhienChung/tinhTrang")) {
           Firebase.setBool("DieuKhienChung/tinhTrang",false);
        //Bật máy bơm
        if (Firebase.getBool("DieuKhienChung/batMayBom")) {
          Serial.println("1");
        }
        else {
           Serial.println("0");
        }

        //Bật đèn
        if (Firebase.getBool("DieuKhienChung/batDen")) {
           digitalWrite(5,HIGH);
        }
        else {
          digitalWrite(5,LOW);
        }

        //Kéo màng
        if (Firebase.getBool("DieuKhienChung/keoMang")) {
          //Serial.println("Bat keo mang");
        }
        else {
        //  Serial.println("Tắt keo mang");
        }
     }
}

/*Main */
void loop()
{
    receiveDataFromAtmga8();
    receiveDataFromFirebase();
      
}

