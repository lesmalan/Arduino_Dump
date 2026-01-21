// Define LED pins
const int LEDA = 2;
const int LEDB = 3;
const int LEDC = 9;
const int LEDD = 10;

void setup() {
  // put your setup code here, to run once:
  // Set LED pins as output
  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDC, OUTPUT);
  pinMode(LEDD, OUTPUT);

}

void loop() {
  // LEDA ON
  digitalWrite(LEDA, HIGH);
  delay(500); // 500 ms delay
  digitalWrite(LEDA, LOW);
  delay(1000); // 1000 ms delay before LEDC turns ON
  // LEDC ON
  digitalWrite(LEDC, LOW);
  delay(500); // 500 ms delay
  digitalWrite(LEDC, LOW);
  delay(1500); // 1500 ms delay before LEDB turns ON
  // LEDB ON
  digitalWrite(LEDB, LOW);
  delay(500); // 500 ms delay
  digitalWrite(LEDB, LOW);
  delay(2000); // 2000 ms delay before LEDD turns ON
  digitalWrite(LEDD, LOW);
  delay(500); // 500 ms delay
  digitalWrite(LEDD, LOW);
}
