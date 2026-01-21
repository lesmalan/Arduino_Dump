int motorPin1 = 4;
int motorPin2 = 5;
int motorPin3 = 6;
int motorPin4 = 7;
int nseq = 48;
int delay1 = 25;
int delay2 = 25;
int delay3 = 25;
int Fullwave[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
int Fullstep[] = {1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,1};
int Halfstep[] = {1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0};


void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i<nseq/8; i++){
    for(int j = 0; j<4; j++){                 
      digitalWrite(motorPin4, Fullwave[4*j+0]);
      digitalWrite(motorPin3, Fullwave[4*j+1]);
      digitalWrite(motorPin2, Fullwave[4*j+2]);
      digitalWrite(motorPin1, Fullwave[4*j+3]);
      delay(delay1);
    }
  }

delay(500);

  for(int i = 0; i<nseq/16; i++){
    for(int j = 0; j<8; j++){                 
      digitalWrite(motorPin1, Halfstep[4*j+0]);
      digitalWrite(motorPin2, Halfstep[4*j+1]);
      digitalWrite(motorPin3, Halfstep[4*j+2]);
      digitalWrite(motorPin4, Halfstep[4*j+3]);
      delay(delay2);
    }
  }

delay(250);

  for(int i = 0; i<nseq/6; i++){
    for(int j = 0; j<6; j++){                 
      digitalWrite(motorPin4, Fullstep[4*j+0]);
      digitalWrite(motorPin3, Fullstep[4*j+1]);
      digitalWrite(motorPin2, Fullstep[4*j+2]);
      digitalWrite(motorPin1, Fullstep[4*j+3]);
      delay(delay3);
    }
  }
delay(750);
}

