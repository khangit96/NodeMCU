#include <Ultrasonic.h>
Ultrasonic ultrasonic(5, 4); // (Trig PIN,Echo PIN) D1(GPIO5) and D2(GPIO4) in Nodemcu 1.0
long distance;
void setup() {
   Serial.begin(9600);

}

void loop() {
 distance = ultrasonic.Ranging(CM);// CM or INC
  Serial.print("Distance:" );
  Serial.print(distance);
  Serial.println(" cm" );
  delay(1000);

}
