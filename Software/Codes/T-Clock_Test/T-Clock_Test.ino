#include <Arduino.h>
#include <U8g2lib.h>

#include <RTClib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


//      Arduino   - OLED
#define SCLK  7  //D0
#define SDIN  6  //D1
#define RST   5   //RES
#define DC    4   //DC
#define CS    3  //CS


U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI OLED(U8G2_R0, SCLK, SDIN, CS, DC, RST);
RTC_DS1307 RTC; //RTC按照IIC接线

String thisMonth = "";
String thisTime = "";
String thisDay = "";
//用于定义表盘的中心
int clockCentreX = 64;
int clockCentreY = 32;
void draw(void)
{
  OLED.setFont(u8g_font_profont15);
  DateTime now = RTC.now();
  
  //数字时间
  thisTime = thisTime + String(now.minute()) ;
  const char* newTime = (const char*) thisTime.c_str();
  OLED.drawStr(10, 10, newTime);
  
}


void setup(void) {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  OLED.begin();
}

void loop(void) {

  OLED.clearBuffer();         // clear the internal memory
  draw();
  OLED.sendBuffer();          // transfer internal memory to the display
  delay(10);
}
