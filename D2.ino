int J=3;
int K=4;
int CLK=5;
int PRE=6;
int CLR=7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(J,OUTPUT);
  pinMode(K,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(PRE,OUTPUT);
  pinMode(CLR,OUTPUT);
  digitalWrite(CLK,0);
  digitalWrite(PRE,0);
  digitalWrite(CLR,0);
  digitalWrite(J,0);
  digitalWrite(K,0);


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PRE,1);
  digitalWrite(CLR,1);
  for (int i=0;i<2; i++){
    for (int j=0;j<2;j++){
      digitalWrite(J,i);
      digitalWrite(K,j);
      digitalWrite(CLK,1);
      delay(10);
      digitalWrite(CLK,0);
      delay(1000);
    }
  }

}
