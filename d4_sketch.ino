// Mechatronics Lab - Activity 403 Part D-4
// 02/06/13
// Les Malan w/assistance from M. Akour, G. Valois, J. Taylor

#include<LCD.h> //add relevant libraries
#include<liquidCrystal_I2C.h>

//Declare variables for keypad, LCD, and dates
const byte ROWS = 4;
const byte COLS = 4;
int rowstate[ROWS];
int colstate[COLS];
int rowval;
int colval;
char weekdays[7]={'M', 'T', 'W', 'R', 'F', 'S', 'U'};
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int DD = 0;
int MM = 0;
int YYYY = 0;
int dow = 0;

int ncentury = 0;
int YYYY100 = 0;

//Initialize pins for keypad and Zeller algorithm
int rowPins[ROWS] = {9, 8, 7, 6};
int colPins[COLS] = {5, 4, 3, 2};
char hexaKeys[ROWS][COLS] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
int n=0;
int zeller[8];
char zellerint[8];

void setup() { // set conditions for serial monitoring, LCD cursor position
Serial.begin(9600);
lcd.begin (16, 2);
lcd.home();
lcd.print("Input MM/DD/YYYY**********");
lcd.setCursor(0,1);
}
void loop() {
  rowval = 32;
  do{
  for(int i = 0; i<4; i++){
    pinMode(colPins[i], INPUT_PULLUP);
    pinMode(rowPins[i], INPUT);
    }
    for(int i =0; i<4; i++){
      pinMode(rowPins[i], OUTPUT);
      for(int j=0; j<4; j++){
        colstate[j] = digitalRead(colPins[j]);
        if (colstate[j]==0){
          rowval = i;
          colval=j;
          pinMode(rowPins[i], INPUT);
        }
      }
    }delay(190);
  }while(rowval ==32);
  if(rowval !=32){

    lcd.print(hexaKeys[rowval][colval]);
  }
 
  zellerint[n]=hexaKeys[rowval][colval];
  zeller[n]=zellerint[n]-'0';
  Serial.println(n);
 
  if(n>=7){
    lcd.clear();
    DD = 10*zeller[2] + zeller[3];
    MM = 10*zeller[0] + zeller[1];
    YYYY = 1000*zeller[4] + 100* zeller[5] + 10*zeller[6] + zeller[7];
    Serial.println(DD);
    Serial.println(MM);
    Serial.println(YYYY);
   
    if (MM >= 4) {
      MM -= 2;
    }
    else{
      MM+=10;
    }

    if (MM> 10) {
      YYYY -= 2;}
      ncentury = int(YYYY/100);
      YYYY100 = YYYY%100;
      dow = (DD + int(13*MM /5-0.2) +int(YYYY100) + int(YYYY100 / 4)
       + int(ncentury/4)-(2*ncentury))%7;
      if (YYYY >=1700 and YYYY <= 1751) {
        dow -= 3;}
        if (YYYY <= 1699){
          dow -= 4;
        }
        if (dow < 0){
          dow += 7;
          }

          lcd.print(weekdays[dow]);
          Serial.println(weekdays[dow]);
          n=0;
          }
          n += 1;
}
