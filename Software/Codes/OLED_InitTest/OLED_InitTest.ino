#include <Arduino.h>
#include <U8g2lib.h>

#include <SPI.h>



/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphiCS, 8x8 Text only.
*/

/*
  //      Arduino   - OLED
  #define SCLK  7  //D0
  #define SDIN  6  //D1
  #define RST   5   //RES
  #define DC    4   //DC
  #define CS    3  //CS
*/

//      NodeMCU   - OLED
#define SCLK  2  //D0
#define SDIN  0  //D1
#define RST   4   //RES
#define DC    5   //DC
#define CS    16  //CS


U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI OLED(U8G2_R0, SCLK, SDIN, CS, DC, RST);

void setup(void) {
  OLED.begin();
}

void loop(void) {
  OLED.clearBuffer();         // clear the internal memory
  OLED.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  OLED.drawStr(0, 10, "Hello  World!"); // write something to the internal memory
  OLED.drawStr(0, 20, "wiki-power.com"); // write something to the internal memory
  OLED.sendBuffer();          // transfer internal memory to the display

  delay(1000);
}
