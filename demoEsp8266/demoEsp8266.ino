const int triggerPin = D5; // Trigger Pin
const int echoPin = D6;   // Echo Pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int maximumRange = 400; // Maximum range needed adalah 4 meter
int minimumRange = 2; // Minimum range needed adalah 2 cm
float duration, distance; // Duration used to calculate distance

void loop() {
  //trigger pulsa ultrasonic
  digitalWrite(triggerPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(triggerPin, HIGH); //mengirim sinyal high selama 10 mikro detik ke pin Trigger
  delayMicroseconds(10); 
  digitalWrite(triggerPin, LOW); //hentikan sinyal ke pin Trigger
  
  //baca durasi pantulan ultrasonic
  duration = pulseIn(echoPin, HIGH); //baca durasi dari pin Echo (durasi dalam mikro detik)

  //hitung jarak dalam cm, lihat formulasi untuk centimeter
  distance = duration/58.2;

  if (distance >= maximumRange || distance <= minimumRange){
    Serial.println("HC-SR 04 sensor out of measurement range");
  }
  else {
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println("cm");
  }
  delay(3000); //jarak antar pengukuran diatas 60 ms, mencegah bercampurnya sinyal trigger dan echo
}
