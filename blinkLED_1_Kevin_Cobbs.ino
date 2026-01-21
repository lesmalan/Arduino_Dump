//_______________________________________
//Arduino Sketch for blinking an LED
//_______________________________________
//defining variables
const int led=3; // constant referring to pin 10
// set up block
void setup() 
{
pinMode(led, OUTPUT);
}
//recuring block

void loop() 
{
digitalWrite(led, LOW);
delay(1000); //delay 500 milliseconds
digitalWrite(led,HIGH);
delay(500); //delay 500 milliseconds
}
