//sets the DS3231 RTC, gets the time in single variable and displays on the serial monitor

#include <DS1302.h>

// Init the DS1302
DS1302 rtc(8, 7, 6);

// Init a Time-data structure
Time t;

int i =0;

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // Setup Serial connection
  Serial.begin(9600);

  // The following lines can be commented out to use the values already stored in the DS1302
  //rtc.setDOW(FRIDAY);        // S et Day-of-Week to FRIDAY
  rtc.setTime(12, 34, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(6, 8, 2010);   // Set the date to August 6th, 2010
}

void loop()
{
  // Get data from the DS1302
  t = rtc.getTime();

  i = t.min;
  i = i + (t.hour * 100);

  Serial.println(i);

  // Wait one second before repeating :)
  delay (1000);
}
