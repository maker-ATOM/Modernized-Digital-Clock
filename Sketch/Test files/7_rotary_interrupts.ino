// Rotary Encoder Inputs
#define CLK 2
#define DT 4

volatile int counter = 0;
volatile int currentStateCLK;
volatile int lastStateCLK;
String currentDir ="";

void setup() {
  
  // Set encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
  
  // Call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(digitalPinToInterrupt(2), updateEncoder, CHANGE);
 // attachInterrupt(digitalPinToInterrupt(3), updateEncoder, CHANGE);
}

void loop() {

/*    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
  */  Serial.println(counter);
}

void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir ="CW";
    }

  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}
