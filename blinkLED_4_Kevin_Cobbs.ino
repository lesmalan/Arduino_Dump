//_______________________________________
//Arduino Sketch for blinking an LED
//_______________________________________
//defining variables
const int led=10; // constant referring to pin 10
// set up block
void setup() 
{
Serial.begin(9600); // setup of serial communication
pinMode(led, OUTPUT);
}
//recuring block

void loop() 
{
digitalWrite(led, HIGH);
Serial.println("HIGH");
delay(500); //delay 500 milliseconds
digitalWrite(led,LOW);
Serial.println("LOW");
delay(500); //delay 500 milliseconds
}
