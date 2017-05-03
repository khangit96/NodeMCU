
#include <ESP8266WiFi.h>
#include <Firebase.h>
#include <FirebaseArduino.h>

// Firebase Config.
#define FIREBASE_HOST "smarthome-5d11a.firebaseio.com"
#define FIREBASE_AUTH "uTP6tlP930oA1s9zuwGIZvrz1ef8ZjVLegROgNN0"
#define WIFI_SSID "SaKuRa"
#define WIFI_PASSWORD "hoilamgita"
String key="1";
int BAT_DEN=12;
int BAT_O_CAM_DIEN=13;

/*Function setup*/
void setup()
{
    Serial.begin(9600);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    pinMode(BAT_DEN, OUTPUT);//đèn
    pinMode(BAT_O_CAM_DIEN, OUTPUT);//ổ cắm điện
  
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
}


/*Main */
void loop()
{
  
 
      if(Firebase.getBool(key+"/DieuKhien/tinhTrang"))
      {
         Firebase.setBool(key+"/DieuKhien/tinhTrang",false);
          //Điều khiển đèn
         if( Firebase.getBool(key+"/DieuKhien/batDen"))// bật đèn
           {
             digitalWrite(BAT_DEN,HIGH);
           }
          else //tắt đèn
          {
              digitalWrite(BAT_DEN,LOW);
          }

      // Điều khiển ổ cắm điện
          if( Firebase.getBool(key+"/DieuKhien/oCamDien"))// bật ổ cắm điện
           {
              digitalWrite(BAT_O_CAM_DIEN,HIGH);
           }
          else // tắt ổ cắm điện
          {
            digitalWrite(BAT_O_CAM_DIEN,LOW);
          }
      }
}

