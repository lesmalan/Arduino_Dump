#include <arduinoFFT.h>        // Include the correct FFT library for frequency analysis
//#include <LiquidCrystal.h> // Include the LiquidCrystal I2C library for displaying on an LCD

// Define constants for the FFT
#define SAMPLES 64              // Number of samples for FFT, must be a power of 2
#define SAMPLING_FREQUENCY 682  // Sampling frequency in Hz (adjust to match the expected frequency range)
#define SIGNAL_PIN A0           // Pin where the guitar signal (analog) is read
#define POT_PIN A1              // Pin where the potentiometer is connected (analog input)
#define LED_PIN 13              // Pin for the LED output (digital pin)

// Arrays to hold real and imaginary components for the FFT calculation
double vReal[SAMPLES];  // Real part of the FFT input data (will hold the signal values)
double vImag[SAMPLES];  // Imaginary part of the FFT input data (will be zeroed out for real signals)

// Create an FFT object with the real and imaginary arrays, sample size, and sampling frequency
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

// Initialize the LCD with I2C address, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  lcd.begin(0x27, 16, 2);                 // Initialize the LCD display
  lcd.backlight();             // Turn on the backlight of the LCD
  Serial.begin(115200);        // Start serial communication for debugging
  Serial.println("Guitar Frequency Detector Started...");  // Inform the user that the program has started

  pinMode(POT_PIN, INPUT);     // Set the potentiometer pin as an input
  pinMode(LED_PIN, OUTPUT);    // Set the LED pin as an output

  lcd.setCursor(0, 0);         // Set the cursor at the beginning of the first row
  lcd.print("Potentiometer");  // Display the label on the first row of the LCD
  lcd.setCursor(0, 1);         // Move the cursor to the second row of the LCD
  lcd.print("Freq: 0 Hz");     // Display initial frequency value (0 Hz)
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
  
  // Check if the detected frequency is above a threshold to avoid noise detection
  if (peakFrequency > 50) {  // Only display frequencies above 50 Hz to avoid noise
    Serial.print("Detected Frequency: ");
    Serial.print(peakFrequency);  // Print the detected frequency to the serial monitor
    Serial.println(" Hz");
  } else {
    // Print a message when no valid frequency is detected (likely noise or signal issues)
    Serial.println("No valid frequency detected.");
  }

  // Read the potentiometer value (0-1023) and map it to LED brightness (0-255)
  int potValue = analogRead(POT_PIN);          // Read the potentiometer value
  int mappedValue = map(potValue, 0, 1023, 0, 255); // Map to LED brightness range
  
  analogWrite(LED_PIN, mappedValue);  // Control the brightness of the LED based on potentiometer value

  // Update the LCD with the detected frequency and potentiometer value
  lcd.setCursor(7, 1);                // Set the cursor on the second row after the "Freq: " label
  lcd.print(peakFrequency);           // Display the detected frequency (from FFT) on the LCD
  lcd.setCursor(0, 1);                // Move the cursor to the start of the second row
  lcd.print("Value: ");               // Label for the potentiometer value
  lcd.print(mappedValue);             // Display the mapped potentiometer value (LED brightness)

  delay(100);  // Wait for 100 milliseconds before updating the display again
}
