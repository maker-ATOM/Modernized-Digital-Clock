byte a;

void setup()
{
  pinMode(9, OUTPUT);
  Serial.begin(9600);
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
