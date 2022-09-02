
//Solution: Keep Serial Monitor closed while programming. 
//Serial Monitor. Serial output works as expected.

#include <Arduino.h>
#include <Wire.h>

#define SPI_EPD_CLK     37  //4
#define SPI_EPD_MOSI    35  //6
#define SPI_EPD_MISO    40  //5
#define SPI_EPD_CS      34  //7
#define SPI_EPD_BUSY    4  //1
#define SPI_EPD_RST     3 //10
#define SPI_EPD_DC      33  //3

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "GxEPD2_display_selection_new_style.h"

const char HelloWorld[] = "TEST";

void helloWorld()
{
  
  
}


void setup()
{
  Serial.begin(115200);
  SPI.end(); // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  SPI.begin(SPI_EPD_CLK, SPI_EPD_MISO, SPI_EPD_MOSI, SPI_EPD_CS); // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)
  display.init();
  display.setRotation(2);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  helloWorld();

  // display.hibernate();
}



const char HelloEpaper[] = "ESP32-C3 eInk!";

void loop() 
{
  
  Serial.println("Testing");
  display.setRotation(2);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  // align with centered HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  // height might be different
  display.getTextBounds(HelloEpaper, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t y = (display.height() * 3 / 4) + tbh / 2; // y is base line!
  // make the window big enough to cover (overwrite) descenders of previous text
  uint16_t wh = FreeMonoBold9pt7b.yAdvance;
  uint16_t wy = (display.height() * 3 / 4) - wh / 2;
  // full window mode is the initial mode, set it anyway
  display.setFullWindow();
  // DO NOT display.fillScreen(GxEPD_WHITE); keep current content!
  // display.fillRect(0, wy, display.width(), wh, GxEPD_WHITE); // clear rect instead
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(random(0,30), random(20,display.height()));
  display.print(HelloEpaper);
  display.display();

  display.drawRect(0, 0, 28, 12, GxEPD_BLACK);
  
  
  delay(5000);
};
