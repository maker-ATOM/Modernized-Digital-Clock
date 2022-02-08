#include <TM1637Display.h>

#define TM_CLK 5
#define TM_DIO 4

#define RE_CLK 2
#define RE_DT 4
#define RE_SW 3

volatile bool direc = false;
volatile byte nowRE_DT = 1;
volatile byte prevRE_DT = 1;
volatile byte counter = 0;
byte prevcounter = 0;


TM1637Display display = TM1637Display(TM_CLK, TM_DIO);

void setup()
{
  pinMode(RE_CLK, INPUT);
  pinMode(RE_DT, INPUT);
  pinMode(RE_SW, INPUT);


  attachInterrupt(digitalPinToInterrupt(2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), updateEncoder, CHANGE);

  display.setBrightness(0x0a);
}


void loop()
{
  if (counter != prevcounter)
  {
    display.showNumberDecEx(counter, B01000000, true, 4, 0);
    prevcounter = counter;
    prevRE_DT = 1;
  }
}


void updateEncoder()
{
  nowRE_DT = digitalRead(3);
  if ((nowRE_DT != prevRE_DT) && digitalRead(2))
  {
    if (nowRE_DT)
    {
      direc = false;
      counter--;
    }
    else
    {
      direc = true;
      counter++;
    }
  }
  prevRE_DT = nowRE_DT;
}
