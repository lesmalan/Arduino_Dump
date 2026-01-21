#define BUTTON 3
#define MOTOR 9


void setup() {
  // put your setup code here, to run once:
pinMode(BUTTON, INPUT);
pinMode(MOTOR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int val;
val=digitalRead(BUTTON);
if(val==HIGH){
  digitalWrite(MOTOR,HIGH);
}
else{
  digitalWrite(MOTOR,LOW);
}
}
