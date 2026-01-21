const int photoPin=A0;
const int buzzerPin=9;
const int laserOutputPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(laserOutputPin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(laserOutputPin, HIGH);
  int light=analogRead(photoPin);
  int freq=light+50;
  Serial.print("Light value: ");
  Serial.println(light);
  Serial.print("Frequency: ");
  Serial.println(freq);
  tone(buzzerPin, freq);
  delay(50);
}
