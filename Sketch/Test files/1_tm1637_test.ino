//increments data after every 500ms and displays on TM1637
//each digit of the data is stored in different variable

#include <TM1637Display.h>

#define CLK 5
#define DIO 4

TM1637Display display = TM1637Display(CLK, DIO);

int i = 0, j = 0, k = 0, l = 0;

void setup()
{

}

void loop()
{
  display.setBrightness(0x0a);

  for (l = 0; l < 9; l++)
  {
    for (k = 0; k <  9; k++ )
    {
      for (j = 0; j < 9; j++)
      {
        for (i = 0; i <= 9; i++)
        {
          display.showNumberDecEx(l * 1000 + k * 100 + j * 10 + i, B01000000, true, 4, 0);
          delay(500);
        }
      }
    }
  }
}
