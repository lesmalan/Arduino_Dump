/******************************************************************************************************************************************
Set Up
Ardiuno UNO
Seven Segment Display
A = pin 2
B = pin 3
C = pin 4
D = pin 5
E = pin 6
F = pin 7
G = pin 8


Button = pin 9

Stepper Motor
10,11

*******************************************************************************************************************************************/
#include <arduinoFFT.h>  // Include the correct FFT library for frequency analysis

#define BUTTON_PIN 9 // Define the pin for the button to switch strings

// Define pin connections & motor's steps per revolution
const int dirPin = 10;
const int stepPin = 11;
const int stepsPerRevolution = 200;

// Seven-segment display pins (assume common cathode setup)
#define SEG_A 2
#define SEG_B 3
#define SEG_C 4
#define SEG_D 5
#define SEG_E 6
#define SEG_F 7
#define SEG_G 8

#define SAMPLES 64             // Number of samples to be taken (must be a power of 2 for FFT)
#define SAMPLING_FREQUENCY 726  // Sampling frequency (Hz) to capture expected guitar frequencies
//#define SAMPLING_FREQUENCY 10000
#define SIGNAL_PIN A0           // Analog input pin to read the guitar string vibrations

// Arrays to store real and imaginary parts of FFT computation
double vReal[SAMPLES];  // Real part of the FFT
double vImag[SAMPLES];  // Imaginary part (initialized to 0)

// Instantiate the FFT object with the required template type and parameters
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

int stringNote = 6; // Start with the 6th string (Low E)

// 7-segment display letter mappings
const byte segmentMap[6] = {
  0b00000110, // '1' 'E'
  0b01011011, // '2' 'B'
  0b01001111, // '3' 'G'
  0b01100110, // '4' 'D'
  0b01101101, // '5' 'A'
  0b01111101  // '6' 'e'
};

void displayCharacter(byte character) {
  digitalWrite(SEG_A, (character >> 0) & 1);
  digitalWrite(SEG_B, (character >> 1) & 1);
  digitalWrite(SEG_C, (character >> 2) & 1);
  digitalWrite(SEG_D, (character >> 3) & 1);
  digitalWrite(SEG_E, (character >> 4) & 1);
  digitalWrite(SEG_F, (character >> 5) & 1);
  digitalWrite(SEG_G, (character >> 6) & 1);
}

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate for debugging
  delay(3000);
  Serial.println("Guitar Frequency Detector Started...");
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set button pin as input with pull-up resistor

  // Set seven-segment display pins as output
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);

  	// Declare pins as Outputs
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
}

void loop() {
 // Check if button is pressed to cycle through strings
  if (digitalRead(BUTTON_PIN) == LOW) {
    stringNote--; // Move to the next string
    if (stringNote < 1) {
      stringNote = 6; // Loop back to the 6th string if below 1
    }
    displayCharacter(segmentMap[stringNote - 1]); // Display number 1-6
    delay(300); // Debounce delay
    Serial.print("Switched to string: ");
    Serial.println(stringNote);
  }

  // Read SAMPLES number of data points from the analog input
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(SIGNAL_PIN);  // Read the signal from the guitar string
    vImag[i] = 0;  // Set imaginary part to zero (FFT requires complex input)
    delayMicroseconds(1000000 / SAMPLING_FREQUENCY); // Control sampling rate
  }

  // Apply a Hamming window function to smooth the signal before FFT computation
  FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);

  // Perform the Fast Fourier Transform (FFT)
  FFT.compute(FFT_FORWARD);

  // Convert the complex output of FFT to magnitude spectrum
  FFT.complexToMagnitude();

  // Identify the dominant frequency in the signal
  double peakFrequency = FFT.majorPeak();
  double adjustedFrequency = peakFrequency;  // Store adjusted frequency after correction

   // Ignore frequencies below 50 Hz (to filter out noise)
  if (peakFrequency > 50) {

  // Manually adjust detected frequency based on the specific guitar string
  if (stringNote == 6) {
    adjustedFrequency = peakFrequency - 9;  // Low E string correction
    if (adjustedFrequency < 80.00) { // If frequency is too low, tighten the string
      tuneUp();  // rotate stepper counter clockwise
    }
    if (adjustedFrequency > 84.00) { // If frequency is too high loosen the string
      tuneDown(); //rotate stepper clockwise
    }
  }
  if (stringNote == 5) {
    adjustedFrequency = peakFrequency - 12; // A string correction
        // Simple tuning logic: move stepper motor based on frequency range
    if (adjustedFrequency < 108) { // If frequency is too low, tighten the string
      tuneUp();  // rotate stepper counter clockwise
    }
    if (adjustedFrequency > 112) { // If frequency is too high, loosen the string
      tuneDown(); //rotate stepper clockwise
    }
  }
  if (stringNote == 4) {
    adjustedFrequency = peakFrequency - 15; // D string correction
    if (adjustedFrequency < 144) { // If frequency is too low, tighten the string
      tuneUp();  // rotate stepper counter clockwise
    }
    if (adjustedFrequency > 148) { // If frequency is too high, loosen the string
      tuneDown(); //rotate stepper clockwise
    }
  }
  if (stringNote == 3) {
    adjustedFrequency = peakFrequency - 21.4; // G string correction
    if (adjustedFrequency < 194) { // If frequency is too low, tighten the string
      tuneUp();  // rotate stepper counter clockwise
    }
    if (adjustedFrequency > 198) { // If frequency is too high, loosen the string
      tuneDown(); //rotate stepper clockwise
    }
  }
  if (stringNote == 2) {
    adjustedFrequency = peakFrequency - 27; // B string correction
    if (adjustedFrequency < 244) { // If frequency is too low, tighten the string
      tuneUp();  // rotate stepper counter clockwise
    }
    if (adjustedFrequency > 248) { // If frequency is too high, loosen the string
      tuneDown(); //rotate stepper clockwise
    }
  }
  if (stringNote == 1) {
    adjustedFrequency = peakFrequency - 32; // High E string correction
    if (adjustedFrequency < 328) { // If frequency is too low, tighten the string
      tuneUp();  // rotate stepper counter clockwise
    }
    if (adjustedFrequency > 332) { // If frequency is too high, loosen the string
      tuneDown(); //rotate stepper clockwise
    }
  }

    // Print detected frequency to serial monitor
    Serial.print("Detected Frequency: ");
    Serial.print(adjustedFrequency);
    Serial.println(" Hz");
  } else {
    // If no valid frequency is detected, print a message
    Serial.println("No valid frequency detected.");
  }

  delay(500); // Wait before next sampling cycle to avoid excessive tuning attempts
}

void tuneUp(){
  digitalWrite(dirPin, HIGH);
  for(int x = 0; x < stepsPerRevolution/10; x++)
	  {
		  digitalWrite(stepPin, HIGH);
		  delayMicroseconds(2000);
		  digitalWrite(stepPin, LOW);
		  delayMicroseconds(2000);
	  }
  delay(500);
}

void tuneDown(){
  digitalWrite(dirPin, LOW);
  for(int x = 0; x < stepsPerRevolution/10; x++)
	  {
		  digitalWrite(stepPin, HIGH);
		  delayMicroseconds(2000);
		  digitalWrite(stepPin, LOW);
		  delayMicroseconds(2000);
	  }
  delay(500);
}