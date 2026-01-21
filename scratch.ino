#include <Servo.h>
Servo myservo;

int globalPos=0;
char appCommand;

int incPos(int localPos){
  localPos+=1;
  return localPos;
}

int decPos(int localPos){
  localPos-=1;
  return localPos;
}

void elevationUp(int localPos){
  myservo.write(incPos(localPos));
  globalPos=localPos;
}

void elevationDown(int localPos){
  myservo.write(decPos(localPos));
  globalPos=localPos;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial started...");
  myservo.attach(8);


}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()){ 
    appCommand = Serial.read();
    Serial.println(appCommand);
 }

 switch (appCommand){
        case 'U':
        elevationUp(globalPos);
        Serial.println("Command received: UP");

            
        break;

        case 'D':
        elevationDown(globalPos);
        Serial.println("Command received: DOWN");

        break;

        case 'S':
        //stopAll();
        Serial.println("Command received: STOP");
      }
}
