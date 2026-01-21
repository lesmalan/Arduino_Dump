#include <arduinoFFT.h>  // Include the correct FFT library

#define SAMPLES 64             // Must be a power of 2
#define SAMPLING_FREQUENCY 726  // Adjust based on expected frequencies
#define SIGNAL_PIN A0           // Analog input

double vReal[SAMPLES];  // Real part of FFT
double vImag[SAMPLES];  // Imaginary part

// ✅ Corrected FFT object declaration with explicit template type
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

void setup() {
  Serial.begin(115200);
  Serial.println("Guitar Frequency Detector Started...");
}

void loop() {
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(SIGNAL_PIN);  // Read signal
    vImag[i] = 0;
    delayMicroseconds(1000000 / SAMPLING_FREQUENCY);
  }

  FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); // ✅ Fix: Lowercase function names
  FFT.compute(FFT_FORWARD);                        // ✅ Fix
  FFT.complexToMagnitude();                        // ✅ Fix

  double peakFrequency = FFT.majorPeak();          // ✅ Fix
  if (peakFrequency > 50) {  // Ignore noise
    Serial.print("Detected Frequency: ");
    Serial.print(peakFrequency);
    Serial.println(" Hz");
  } else {
    Serial.println("No valid frequency detected.");
  }

  delay(500);
}