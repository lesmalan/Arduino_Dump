#include <NewPing.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 


#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 400 // Maximum distance we want to measure (in centimeters).


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
void setup() {
  //Serial.begin(9600);
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display }
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
 
  

}

void loop() {
 delay(50);                    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

 int distance = sonar.ping_cm(); // Send ping, get distance in cm and print result (0 = outside set distance range)
 lcd.setCursor(0,1);
 lcd.print(distance);
 lcd.setCursor(0,1);
 delay(500);
 lcd.print("   ");
}
