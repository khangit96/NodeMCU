#include <DHT.h>


#include <ESP8266WiFi.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#include "DHT.h"

#define DHTPIN 12 
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21 
DHT dht(DHTPIN, DHTTYPE);

// Firebase Config.
#define FIREBASE_HOST "smartgardening-3d2d2.firebaseio.com"
#define FIREBASE_AUTH "pJ5LGq1SIudyXT28vhPojt0LtWmgodB1sIkc1JDv"
#define WIFI_SSID "Open IT LAB"
#define WIFI_PASSWORD "sharetobeshare"
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
     dht.begin();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    pinMode(led, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(0, OUTPUT);
    digitalWrite(5,LOW);
    digitalWrite(4,LOW);
    digitalWrite(0,LOW);
  
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

/*Funtion receive data from Atemga8*/
void receiveDataFromAtmga8()
{
     float h = dht.readHumidity();
     float t = dht.readTemperature();
     Firebase.setFloat(key+"/DuLieu/DoAmKhongKhi",h);
     Firebase.setFloat(key+"/DuLieu/NhietDo",t);
   
     if (Serial.available() >= 4) 
     {
          char abc[4]= {};
           Serial.readBytes(abc,4);
     
            /*if (abc[0] == '1') {
                Firebase.setString(key+"/DuLieu/NhietDo",abc);
               Serial.println(abc);
            }*/

            if (abc[0] == '2') {
                Firebase.setString(key+"/DuLieu/DoAm1", abc);
                 Serial.println(abc);
            }

            else if (abc[0] == '3') {
                Firebase.setString(key+"/DuLieu/DoAm2", abc);
                Serial.println(abc);
            }

            else if (abc[0] == '4') {
                Firebase.setString(key+"/DuLieu/DoAm3", abc);
                Serial.println(abc);
            }
    }
   
}

/*Receive data from Firebase*/
void receiveDataFromFirebase(){

  //Điều khiển từng hệ thống
   if (Firebase.getBool(key+"/DieuKhien/tinhTrang")) {
      Firebase.setBool(key+"/DieuKhien/tinhTrang",false);
        //Bật máy bơm/phun sương
        if (Firebase.getBool(key+"/DieuKhien/batMayBom")) {
           digitalWrite(5,HIGH);
        }
        else {
          digitalWrite(5,LOW);
        }

        //Bật đèn
        if (Firebase.getBool(key+"/DieuKhien/batDen")) {
           digitalWrite(4,HIGH);
        
        }
        else {
          digitalWrite(4,LOW);
           
        }

        //Kéo màng
        if (Firebase.getBool(key+"/DieuKhien/keoMang")) {
           digitalWrite(0,HIGH);
        }
        else {
          digitalWrite(0,LOW);
        }
    }

  /*  //Điều khiển chung
    if (Firebase.getBool("DieuKhienChung/tinhTrang")) {
          Firebase.setBool("DieuKhienChung/tinhTrang",false);
        //Bật máy bơm
        if (Firebase.getBool("DieuKhienChung/batMayBom")) {
           digitalWrite(5,HIGH);
        }
        else {
          digitalWrite(5,LOW);
        }

        //Bật đèn
        if (Firebase.getBool("DieuKhienChung/batDen")) {
             digitalWrite(4,HIGH);
        }
        else {
          digitalWrite(4,LOW);
        }

        //Kéo màng
        if (Firebase.getBool("DieuKhienChung/keoMang")) {
            digitalWrite(0,HIGH);
        }
        else {
          digitalWrite(0,LOW);
        }
     }*/
}

/*Main */
void loop()
{
    receiveDataFromAtmga8();
    receiveDataFromFirebase();
      
}

