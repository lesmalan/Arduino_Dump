
void song(int buzzerPin){
  
  tone(buzzerPin, 659);
  delay(203);
  noTone(buzzerPin);

  tone(buzzerPin, 659);
  delay(203);
  noTone(buzzerPin);

  tone(buzzerPin, 587);
  delay(203);
  noTone(buzzerPin);

  tone(buzzerPin, 587);
  delay(203);
  noTone(buzzerPin);

  tone(buzzerPin, 523);
  delay(617);
  noTone(buzzerPin);

  tone(buzzerPin, 587);
  delay(203);
  noTone(buzzerPin);

  tone(buzzerPin, 698);
  delay(410);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(617);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(203);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(410);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(410);
  noTone(buzzerPin);

  tone(buzzerPin, 659);
  delay(410);
  noTone(buzzerPin);

  tone(buzzerPin, 659);
  delay(203);
  noTone(buzzerPin);

  tone(buzzerPin, 587);
  delay(410);
  noTone(buzzerPin);

  tone(buzzerPin, 523);
  delay(617);
  noTone(buzzerPin);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  // call the song function with digital pin
  song(11);
}

void loop() {
  // put your main code here, to run repeatedly:
}
