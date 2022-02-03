//libraries
#include <TM1637Display.h>
#include <DS1302.h>

//macros
#define TM_CLK 5
#define TM_DIO 4

#define RE_CLK 3
#define RE_DT 2

#define RTC_CLK 6
#define RTC_DIO 7
#define RTC_CE 8

#define buzzer 9

//varibles
volatile byte nowRE_DT = 1;
volatile byte prevRE_DT = 1;

volatile byte button = 0;
byte buttonPressed = false;

volatile byte counter = 0;
byte prevcounter = 0;

byte td1 = 0, td2 = 0, td3 = 0, td4 = 0;
byte ad1 = 0, ad2 = 0, ad3 = 0, ad4 = 0;

byte digichange = 0;
int gettime = 0;

byte brightness = 4;

int setalarm = 0;
byte alarmFlag = false;

//array to display words
uint8_t full[] = {0xff, 0x0ff, 0xff, 0xff};
uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
uint8_t bright[] = {0x7c, 0xd0, 0x6f, 0x31};
uint8_t set[] = {0x6d, 0x79, 0x31, 0x00};
uint8_t timearr[] = {0x31, 0x30, 0x52, 0x79};
uint8_t dipy[] = {0x5e, 0x30, 0x73, 0x66};
uint8_t alarm[] = {0x77, 0x38, 0x50, 0x52};
uint8_t on[] = {0x00, 0x3f, 0x54, 0x00};
uint8_t off[] = {0x3f, 0x71, 0x71, 0x00};

TM1637Display display = TM1637Display(TM_CLK, TM_DIO);

DS1302 rtc(RTC_CE, RTC_DIO, RTC_CLK);

Time t;

//---------------------------------------------------------------------------------//

void setup()
{
  //register maipulation to set pin change interrupt on A0 pin
  PCICR |= B00000010;
  PCMSK1 |= B00000001;

  pinMode(RE_CLK, INPUT);
  pinMode(RE_DT, INPUT);

  //set the pin to high impedance so humming is inherted
  pinMode(buzzer, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), updateEncoder, CHANGE);

  display.setBrightness(brightness);

  rtc.halt(false);
  rtc.writeProtect(false);
}

//---------------------------------------------------------------------------------//

void loop()
{

  switch (button)
  {

    case 1: //show time
      display.setSegments(dipy);
      delay(1500);
      display.setSegments(timearr);
      delay(1500);
      while (!buttonPressed)
      {
        t = rtc.getTime();
        gettime = t.min;
        gettime = gettime + (t.hour * 100);
        display.showNumberDecEx(gettime, B01000000, true, 4, 0);

        if ((setalarm == gettime) && (alarmFlag))
        {
          prevcounter = counter;
          while (prevcounter == counter)
          {
            alarmSound();
          }
          alarmFlag = false;
          buttonPressed = false;
        }
        delay(2000);
      }
      break;



    case 2: //change time
      beep();
      display.setSegments(set);
      delay(1500);
      display.setSegments(timearr);
      delay(1500);
      while (!buttonPressed)
      {
        buttonPressed = false;
        if (counter != prevcounter)
        {
          display.setSegments(blank);
          if (counter > prevcounter)
          {
            digichange = (digichange + 1) % 4;
          }
          else
          {
            switch (digichange)
            {
              case 0:
                td4 = (td4 + 1) % 10;
                break;
              case 1:
                td3 = (td3 + 1) % 10;
                break;
              case 2:
                td2 = (td2 + 1) % 10;
                break;
              case 3:
                td1 = (td1 + 1) % 10;
                break;
            }
            rtc.setTime(td4 * 10 + td3, td2 * 10 + td1, 00);
          }
          switch (digichange)
          {
            case 0:
              display.showNumberDec(td4, false, 1, 0);
              break;
            case 1:
              display.showNumberDec(td3, false, 1, 1);
              break;
            case 2:
              display.showNumberDec(td2, false, 1, 2);
              break;
            case 3:
              display.showNumberDec(td1, false, 1, 3);
              break;
          }
          beep();
          prevcounter = counter;
        }
        delay(5);
      }
      break;

    case 3: //change brightness
      beep();
      display.setSegments(set);
      delay(1500);
      display.setSegments(bright);
      delay(1500);
      while (!buttonPressed)
      {
        buttonPressed = false;
        display.setSegments(full);
        if (counter != prevcounter)
        {
          if (brightness > 7)
          {
            brightness = 0;
          }
          brightness++;
          display.setBrightness(brightness);
          prevcounter = counter;
          beep();
        }
        delay(5);
      }
      break;

    case 4: //set alarm
      beep();
      display.setSegments(set);
      delay(1500);
      display.setSegments(alarm);
      delay(1500);
      while (!buttonPressed)
      {

        if (counter != prevcounter)
        {

          alarmFlag = !alarmFlag;
          if (alarmFlag)
          {
            display.setSegments(on);
            beep();
            delay(2000);
            while (!buttonPressed)
            {
              if (counter != prevcounter)
              {
                beep();
                display.setSegments(blank);
                if (counter > prevcounter)
                {
                  digichange = (digichange + 1) % 4;
                }
                else
                {
                  switch (digichange)
                  {
                    case 0:
                      ad4 = (ad4 + 1) % 10;
                      break;
                    case 1:
                      ad3 = (ad3 + 1) % 10;
                      break;
                    case 2:
                      ad2 = (ad2 + 1) % 10;
                      break;
                    case 3:
                      ad1 = (ad1 + 1) % 10;
                      break;
                  }
                  setalarm = (ad4 * 1000) + (ad3 * 100) + (ad2 * 10) + ad1;
                }
                switch (digichange)
                {
                  case 0:
                    display.showNumberDec(ad4, false, 1, 0);
                    break;
                  case 1:
                    display.showNumberDec(ad3, false, 1, 1);
                    break;
                  case 2:
                    display.showNumberDec(ad2, false, 1, 2);
                    break;
                  case 3:
                    display.showNumberDec(ad1, false, 1, 3);
                    break;
                }

                prevcounter = counter;
              }
              delay(5);
            }

          }
          else
          {
            display.setSegments(off);
          }
          prevcounter = counter;
          beep();
        }
        delay(5);
      }
      break;
    default:
      button = 1;
  }

  buttonPressed = false;

}

//---------------------------------------------------------------------------------//

ISR (PCINT1_vect)
{
  if (!digitalRead(A0))
  {
    button++;
    buttonPressed = true;
  }
  delay(1);
}

//---------------------------------------------------------------------------------//

void updateEncoder()
{
  nowRE_DT = digitalRead(3);
  if ((nowRE_DT != prevRE_DT) && digitalRead(2))
  {
    if (nowRE_DT)
    {
      counter--;
    }
    else
    {
      counter++;
    }
  }
  prevRE_DT = nowRE_DT;
}

//---------------------------------------------------------------------------------//

void beep()
{
  tone(buzzer, 1500);
  delay(50);
  noTone(buzzer);
  pinMode(buzzer, INPUT);
}

//---------------------------------------------------------------------------------//

void alarmSound()
{
  tone(buzzer , 1000);
  delay(200);
  noTone(buzzer);
  tone(buzzer, 1000);
  delay(200);
  noTone(buzzer);
  delay(1250);
}

//---------------------------------------------------------------------------------//
