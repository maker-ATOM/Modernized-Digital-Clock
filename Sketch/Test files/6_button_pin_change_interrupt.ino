volatile byte button = 0;
byte a = 0;

void setup()
{
  PCICR |= B00000010;
  PCMSK1 |= B00000001;
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (button == 2)
  {
    a = !a;
    digitalWrite(13, a);
    button = 3;
  }
  Serial.print(digitalRead(2));
  Serial.print(" ");
  Serial.print(digitalRead(3));
  Serial.print(" ");
  Serial.println(button);
}

ISR (PCINT1_vect)
{
  if (!digitalRead(A0))
  {
    button = 2;
  }
}
