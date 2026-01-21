int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

int buzzer = 11;
int ledPin = 12;
int buttonPin = 13;

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
  pinMode(motor1pin1, OUTPUT); //LEFT SIDE
  pinMode(motor1pin2, OUTPUT); //LEFT SIDE
  pinMode(motor2pin1, OUTPUT); //RIGHT SIDE
  pinMode(motor2pin2, OUTPUT); //RIGHT SIDE
  pinMode(11, OUTPUT);

  //(Optional)
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  //(Optional)
}

void loop() {
   // put your main code here, to run repeatedly:
  int buttonPushed = 0;
  if (digitalRead(buttonPin)==HIGH){
    buttonPushed=1;
  }
  if (buttonPushed == 1){
    digitalWrite(ledPin, HIGH); //turn on headlights
    
    delay(1000); //wait 5s
    

    // this sets the speed of the motors
    //Controlling speed (0 = off and 255 = max speed):     
    analogWrite(6, 255); //ENA pin //LUDICROUS SPEED
    analogWrite(7, 255); //ENB pin //LUDICROUS SPEED


    //turn on motors
    digitalWrite(motor1pin1, HIGH);   //LEFT SIDE MOTOR CONTROLS
    digitalWrite(motor1pin2, LOW);  //LEFT SIDE MOTOR CONTROLS
    digitalWrite(motor2pin1, HIGH);  //RIGHT SIDE MOTOR CONTROLS
    digitalWrite(motor2pin2, LOW);   //RIGHT SIDE MOTOR CONTROLS

    //song(buzzer); //start the theme song
    //delay(5000);
    //digitalWrite(motor1pin1, LOW);   //LEFT SIDE MOTOR CONTROLS
    //digitalWrite(motor1pin2, HIGH);  //LEFT SIDE MOTOR CONTROLS
    //digitalWrite(motor2pin1, LOW);  //RIGHT SIDE MOTOR CONTROLS
    //digitalWrite(motor2pin2, HIGH);   //RIGHT SIDE MOTOR CONTROLS

    //wait 10s, and turn off motors
    //delay(8000);
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);

    digitalWrite(ledPin, LOW); //turn off headlights
  }
buttonPushed = 0;
  

}
