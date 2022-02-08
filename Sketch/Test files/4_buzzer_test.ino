//outputs a PWM on pin 9 for buzzer

byte a;

void setup()
{
  pinMode(9, OUTPUT);
}

void loop()
{
  tone(9 ,1000);
  delay(200);
  noTone(9);
  tone(9, 1000);
  delay(200);
  noTone(9);
  pinMode(9, INPUT);
  delay(1250);
}
