#include "arduinoFFT.h"
 
#define SAMPLES 128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2048 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.

arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
 
 //LCD Display
 #include <LiquidCrystal.h>
  const byte LCD_D7 = 2; 
	const byte LCD_D6 = 3; 
	const byte LCD_D5 = 4; 
	const byte LCD_D4 = 5; 
	const byte LCD_E = 11; 
	const byte LCD_RS = 12 ; 
 
LiquidCrystal Lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
const byte LCD_WIDTH = 16;
const byte LCD_HEIGHT = 2;
void setup() 
{
    Serial.begin(115200); //Baud rate for the Serial Monitor
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
  //LCD
  Lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  Lcd.print("Starting...");
  delay(2500);
  Lcd.clear();
}

void loop() 
{  
    /*Sample SAMPLES times*/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
/*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

/*Find peak frequency and print peak*/
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    Serial.println(peak);     //Print out the most dominant frequency.

/*Script stops here. Hardware reset required.*/
    while (1); //do one time


 //LOW E STRING 
    if(peak>83.5 && peak<92) {
    Lcd.print("Your E string is too high.");
    delay (2000);
    Lcd.clear(); 
    }
    
    if(peak<82){
    Lcd.print("Your E string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
      if(peak<=83 && peak>=82){
    Lcd.print("E string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
  //A STRING
  if(peak>110.5 && peak<128){
  Lcd.print("Your A string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peak<109.5 && peak>93){
    Lcd.print("Your A string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peak<=110 && peak>=109){
    Lcd.print("A string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
      //D STRING
      if(peak>147.5 && peak<170){
    Lcd.print("Your D string is too high.");
    delay (2000);
    Lcd.clear(); 
      }
      
        if(peak<145 && peak>128.5){
    Lcd.print("Your D string is too low");
    delay (2000);
    Lcd.clear(); 
      }
      
        if(peak<=146 && peak>=147){
    Lcd.print("D string is in tune.");
    delay (2000);
    Lcd.clear(); 
       }
         //G STRING
      if(peak>197 && peak<222){
  Lcd.print("Your G string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peak<196 && peak>171){
    Lcd.print("Your G string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peak<=197 && peak>=196){
    Lcd.print("G string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
   //B STRING
       if(peak>248 && peak<288){
  Lcd.print("Your B string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peak<247 && peak>223){
    Lcd.print("Your B string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peak<= 248 && peak>= 247){
    Lcd.print("B string in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
   //HIGH E STRING
   if(peak>331.5 && peak< 400){
  Lcd.print("Your high E string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peak<329 && peak>289){
    Lcd.print("Your high E string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peak<=331  && peak>=330 ){
    Lcd.print("Your high E string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }
}