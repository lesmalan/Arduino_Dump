//_______________________________________
//Arduino Sketch for blinking an LED
//_______________________________________
//defining variables
const int led=10; // constant referring to pin 10
// set up block
void setup() 
{
pinMode(led, OUTPUT);
}
//recuring block

void loop() 
{
digitalWrite(led, LOW);
delay(1000); //delay 1000 milliseconds
digitalWrite(led,HIGH);
delay(500); //delay 500 milliseconds
}
