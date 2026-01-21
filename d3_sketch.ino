// Mechatronics Lab - Activity 403 Part D-3
// 02/06/13
// Les Malan w/assistance from M. Akour, G. Valois, J. Taylor

int led[3]={3,5,7}; //declare variable for LED pins
int delayA = 0; //declare variable for delay timer


void setup() {
pinMode(led[0], OUTPUT); // set pin mode
pinMode(led[1], OUTPUT);
pinMode(led[2], OUTPUT);
}
void loop() { // loops through all combinations of integer values 1-3, ie 111, 112, 113, etc
  for(int i = 1; i < 4; i++){ //integer position 1
    for(int j = 1; j < 4; j++){ //integer position 2
      for(int k = 1; k < 4; k++){ //integer position 3
        
        digitalWrite(led[i-1],HIGH); //cycles through turning LED pins on/off
        delay(150);
        digitalWrite(led[i-1],LOW);
        delay(150);
        digitalWrite(led[j-1],HIGH);
        delay(150);
        digitalWrite(led[j-1],LOW);
        delay(150);
        digitalWrite(led[k-1],HIGH);
        delay(150);
        digitalWrite(led[k-1],LOW);
        delay(delayA);
        
        if((i+j+k)%2==0){ // checks even or odd value. If even, delay is 250ms, otherwise it is 500 ms
          delayA=(i+j+k)*250;
        }
        else{
          delayA=500;
        }
 }
 }
}
}
