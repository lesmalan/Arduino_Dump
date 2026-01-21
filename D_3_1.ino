// Variable declaration
int CS = 10;
int CLK = 13;
int D0 = 12;
float result;

// Setup function
void setup()
{
    pinMode(CS, OUTPUT);
    pinMode(CLK, OUTPUT);
    pinMode(D0, INPUT);
    digitalWrite(CS, HIGH);
    digitalWrite(CLK, LOW);
  Serial.begin(9600);
}

//Loop function
void loop()
{
  result=ADCread();
  Serial.println(result*5.0/255);
  delay(1000);
}

//Other function
byte ADCread()
{
  int array[8];
    digitalWrite(CS, LOW);
      digitalWrite(CLK, HIGH);
      delayMicroseconds(2);
      digitalWrite(CLK, LOW);
      delayMicroseconds(2);
  for (int i=7; i>=0; i--)
      {
     digitalWrite(CLK, HIGH);
     delayMicroseconds(2);
     digitalWrite(CLK, LOW);
     delayMicroseconds(2);
     array[i]=digitalRead(D0);
      }
  int val=array[7]*128+array[6]*64+
            array[5]*32+array[4]*16+array[3]*8+array[2]*4+array[1]*2+array[0];
  digitalWrite(CS, HIGH);
  return val ;    }