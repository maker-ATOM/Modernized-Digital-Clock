//gets the data from RTC and displays on TM1637

#include <DS1302.h>
#include <TM1637Display.h>

#define CLK 5
#define DIO 4

// Init the DS1302
DS1302 rtc(8, 7, 6);

// Init a Time-data structure
Time t;

TM1637Display display = TM1637Display(CLK, DIO);
int i =0;

void setup()
{
  
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // Setup Serial connection
  Serial.begin(9600);

  // The following lines can be commented out to use the values already stored in the DS1302
  //rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  //rtc.setTime(14, 27, 10);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(6, 8, 2010);   // Set the date to August 6th, 2010
  display.setBrightness(0x02);
}

void loop()
{
  
  
  // Get data from the DS1302
  t = rtc.getTime();

  i = t.min;
  i = i + (t.hour * 100);

  Serial.println(i);
  display.showNumberDecEx(i, B11100000, true,4,0);


  // Wait one second before repeating :)
  delay (1000);
}
