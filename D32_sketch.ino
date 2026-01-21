int motorPin1 = 4;
int motorPin2 = 5;
int motorPin3 = 6;
int motorPin4 = 7;
int digitalPin8=8;

int result;
int nseq = 48;
int delayTime = 50;

int Fullwave[] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
int Fullstep[] = {1,1,0,0, 0,1,1,0, 0,0,1,1, 1,0,0,1};
int Halfstep[] = {1,1,0,0,0,1,0,0, 0,1,1,0,0,0,1,0, 0,0,1,1,0,0,0,1, 1,0,0,1,1,0,0,0};
void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(digitalPin8, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  result=digitalRead(digitalPin8);
  if (result==HIGH)
    for (int j=0; j<8; j++){
      digitalWrite(motorPin4, Halfstep[4*j+0]);
      digitalWrite(motorPin3, Halfstep[4*j+1]);
      digitalWrite(motorPin2, Halfstep[4*j+2]);
      digitalWrite(motorPin1, Halfstep[4*j+3]);
      Serial.println("HIGH");
      delay(delayTime);
    }

else{
  for (int j=0; j<8; j++){
      digitalWrite(motorPin1, Fullstep[4*j+0]);
      digitalWrite(motorPin2, Fullstep[4*j+1]);
      digitalWrite(motorPin3, Fullstep[4*j+2]);
      digitalWrite(motorPin4, Fullstep[4*j+3]);
      Serial.println("LOW");
      delay(delayTime);
    }
}
}
