#define INPUT_PIN 2
#define led D0
int counter = 0;
int previousReading = LOW;

void setup() {
 Serial.begin(9600);
 pinMode(INPUT_PIN, INPUT);
 // digitalWrite(INPUT_PIN, LOW);
// pinMode(led,OUTPUT);

}

void loop() {
 int value=digitalRead(INPUT_PIN);
 Serial.println(value);
 delay(1000);
}
