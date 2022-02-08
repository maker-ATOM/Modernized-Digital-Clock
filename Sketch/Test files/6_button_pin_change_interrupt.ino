//pin change interrupt attached to pin A0 and driven by button of encoder

volatile byte button = 0;

void setup()
{
  PCICR |= B00000010;
  PCMSK1 |= B00000001;
  pinMode(13, OUTPUT);
}

void loop()
{


    digitalWrite(13, button);
}

ISR (PCINT1_vect)
{
  if (!digitalRead(A0))
  {
    button = !button;
  }
}
