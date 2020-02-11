/**The MIT License (MIT)

  Copyright (c) 2018 by Daniel Eichhorn - ThingPulse

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  See more at https://thingpulse.com
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Ticker.h>
#include <JsonListener.h>
#include <OLEDDisplayUi.h>
#include <WorldClockClient.h>
#include "icons.h"
#include "fonts.h"



/***************************
   Begin Settings
 **************************/
// WIFI
const char* WIFI_SSID = "6001";
const char* WIFI_PWD = "82467627171982547";

// Setup
const int UPDATE_INTERVAL_SECS = 10 * 60; // Update every 10 minutes

//      NodeMCU   - OLED
#define SCLK  2  //D0
#define SDIN  0  //D1
#define RST   4   //RES
#define DC    5   //DC
#define CS    16  //CS


U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI OLED(U8G2_R0, SCLK, SDIN, CS, DC, RST);


// TimeClient settings


// Initialize the oled display for address 0x3c
// sda-pin=14 and sdc-pin=12



/***************************
   End Settings
 **************************/

// flag changed in the ticker function every 10 minutes
bool readyForUpdate = false;

String lastUpdate = "--";

Ticker ticker;

/*
void updateData(OLEDDisplay *display) {
  drawProgress(display, 50, "Updating Time...");
  worldClockClient.updateTime();
  drawProgress(display, 100, "Done...");
  readyForUpdate = false;
  delay(1000);
}

void drawProgress(OLEDDisplay *display, int percentage, String label) {
  display->clear();
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(64, 10, label);
  display->drawProgressBar(10, 28, 108, 12, percentage);
  display->display();
}
*/

void drawClock(OLEDDisplay *display, int x, int y, int timeZoneIndex, String city, const uint8_t* icon) {

  OLED.setFont(u8g2_font_ncenB10_tr);
  OLED.drawStr(x + 60, y + 5, "city");
  OLED.setFont(u8g2_font_ncenB10_tr); //36
  OLED.drawXBM(x, y, 60, 60, icon);
  OLED.drawStr(x + 60, y + 15, worldClockClient.getHours(timeZoneIndex) + ":" + worldClockClient.getMinutes(timeZoneIndex));

}




void setReadyForWeatherUpdate() {
  Serial.println("Setting readyForUpdate to true");
  readyForUpdate = true;
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // initialize dispaly
  //display.init();
  //display.clear();
  //display.display();
  OLED.begin();
  OLED.clearBuffer();
  //display.setTextAlignment(TEXT_ALIGN_CENTER);
  OLED.setContrast(255);

  WiFi.begin(WIFI_SSID, WIFI_PWD);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    OLED.clearBuffer();
    OLED.drawString(64, 10, "Connecting to WiFi");
    OLED.sendBuffer();
    counter++;
  }

  Serial.println("");

  updateData(&display);

  ticker.attach(UPDATE_INTERVAL_SECS, setReadyForWeatherUpdate);

}

void loop() {


}
