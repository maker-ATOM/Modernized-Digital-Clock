#include <TM1637Display.h>

#define TM_CLK 5
#define TM_DIO 4


TM1637Display display = TM1637Display(TM_CLK, TM_DIO);

void setup()
{

  display.setBrightness(0x0a);

  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setSegments(blank);

  delay(1000);
  display.showNumberDec(9,false,1,1);
}

void loop()
{
}
