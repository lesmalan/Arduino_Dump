#include <arduinoFFT.h>        // Include the correct FFT library for frequency analysis
 #include <LiquidCrystal.h>


// Define constants for the FFT
#define SAMPLES 64              // Number of samples for FFT, must be a power of 2
#define SAMPLING_FREQUENCY 682  // Sampling frequency in Hz (adjust to match the expected frequency range)
#define SIGNAL_PIN A0           // Pin where the guitar signal (analog) is read


// Arrays to hold real and imaginary components for the FFT calculation
double vReal[SAMPLES];  // Real part of the FFT input data (will hold the signal values)
double vImag[SAMPLES];  // Imaginary part of the FFT input data (will be zeroed out for real signals)

// Create an FFT object with the real and imaginary arrays, sample size, and sampling frequency
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

 //LCD Display
const byte LCD_D7 = 2; 
const byte LCD_D6 = 3; 
const byte LCD_D5 = 4; 
const byte LCD_D4 = 5; 
const byte LCD_E = 11; 
const byte LCD_RS = 12 ; 
 
LiquidCrystal Lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
const byte LCD_WIDTH = 16;
const byte LCD_HEIGHT = 2;

void setup() {
  Serial.begin(115200);        // Start serial communication for debugging
   //LCD
  Lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  Lcd.print("Starting...");
  delay(2500);
  Lcd.clear();
  
}

void loop() {
  // Collect 'SAMPLES' number of data points from the analog input (signal pin)
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(SIGNAL_PIN);  // Read the analog input (guitar signal)
    vImag[i] = 0;                       // Set the imaginary part to 0 (since we're working with real data)
    delayMicroseconds(1000000 / SAMPLING_FREQUENCY);  // Delay to match the desired sampling frequency
  }

  // Apply a Hamming window function to the real input data to reduce spectral leakage
  FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);

  // Compute the FFT on the real and imaginary data
  FFT.compute(FFT_FORWARD);  // Perform the FFT calculation

  // Convert the complex FFT result to magnitude (real signal information)
  FFT.complexToMagnitude();

  // Identify the frequency of the peak in the spectrum
  double peakFrequency = FFT.majorPeak();  // Get the frequency corresponding to the peak value in the FFT output
  
 //LOW E STRING 
    if(peakFrequency>83.5 && peakFrequency<92) {
    Lcd.print("Your E string is too high.");
    delay (2000);
    Lcd.clear(); 
    }
    
    if(peakFrequency<82){
    Lcd.print("Your E string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
      if(peakFrequency<=83 && peakFrequency>=82){
    Lcd.print("E string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
  //A STRING
  if(peakFrequency>110.5 && peakFrequency<128){
  Lcd.print("Your A string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peakFrequency<109.5 && peakFrequency>93){
    Lcd.print("Your A string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peakFrequency<=110 && peakFrequency>=109){
    Lcd.print("A string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
      //D STRING
      if(peakFrequency>147.5 && peakFrequency<170){
    Lcd.print("Your D string is too high.");
    delay (2000);
    Lcd.clear(); 
      }
      
        if(peakFrequency<145 && peakFrequency>128.5){
    Lcd.print("Your D string is too low");
    delay (2000);
    Lcd.clear(); 
      }
      
        if(peakFrequency<=146 && peakFrequency>=147){
    Lcd.print("D string is in tune.");
    delay (2000);
    Lcd.clear(); 
       }
         //G STRING
      if(peakFrequency>197 && peakFrequency<222){
  Lcd.print("Your G string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peakFrequency<196 && peakFrequency>171){
    Lcd.print("Your G string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peakFrequency<=197 && peakFrequency>=196){
    Lcd.print("G string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
   //B STRING
       if(peakFrequency>248 && peakFrequency<288){
  Lcd.print("Your B string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peakFrequency<247 && peakFrequency>223){
    Lcd.print("Your B string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peakFrequency<= 248 && peakFrequency>= 247){
    Lcd.print("B string in tune.");
    delay (2000);
    Lcd.clear(); 
      }
      
   //HIGH E STRING
   if(peakFrequency>331.5 && peakFrequency< 400){
  Lcd.print("Your high E string is too high.");
    delay (2000);
    Lcd.clear(); 
  }
  
     if(peakFrequency<329 && peakFrequency>289){
    Lcd.print("Your high E string is too low.");
    delay (2000);
    Lcd.clear(); 
      }
      
   if(peakFrequency<=331  && peakFrequency>=330 ){
    Lcd.print("Your high E string is in tune.");
    delay (2000);
    Lcd.clear(); 
      }


  delay(100);  // Wait for 100 milliseconds before updating the display again
}
