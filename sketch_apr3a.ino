int motorPin1=4;
int motorPin2=5;
int motorPin3=6;
int motorPin4=7;
int nseq=2048/4;
int delayTime=5000;
int Fullwave[]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
void setup() {
pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);
pinMode(motorPin3, OUTPUT);
pinMode(motorPin4, OUTPUT);

}

void loop() 
{
for(int i=0; i<nseq; i++)
  {
  for(int j=0; j<4; j++)
    {
    digitalWrite(motorPin1, Fullwave[4*j+0]);
    digitalWrite(motorPin2, Fullwave[4*j+1]);
    digitalWrite(motorPin3, Fullwave[4*j+2]);
    digitalWrite(motorPin4, Fullwave[4*j+3]);
    delay(delayTime);
    }
  }
}
