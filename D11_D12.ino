int A=3;
int B=4;
int C=5;

void setup() {
  Serial.begin(9600);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<2; i++){
    for (int j=0; j<2; j++){
      for (int k=0; k<2; k++){
        digitalWrite(A,i);
        digitalWrite(B,j);
        digitalWrite(C,k);
        Serial.print(i);
        Serial.print(j);
        Serial.print(k);
        Serial.println();
        delay(1000);
      }
    }
  }
}
