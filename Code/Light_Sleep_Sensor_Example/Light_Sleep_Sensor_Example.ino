//
//

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHTC3.h"
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

#define SPI_EPD_CLK     37
#define SPI_EPD_MOSI    35
#define SPI_EPD_MISO    40  //Not used
#define SPI_EPD_CS      34
#define SPI_EPD_BUSY    4
#define SPI_EPD_RST     3
#define SPI_EPD_DC      33
#define BATTERY_PIN     5

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>  
#include "GxEPD2_display_selection_new_style.h"


float get_battery_voltage()
{
  return float (analogRead(BATTERY_PIN) / 4096.0 * 5.6761);  //2841 / 4096 * 7.23 = x  (3.937)
  //return float (analogRead(BATTERY_PIN)); 
}

void setup()
{
  pinMode(BATTERY_PIN, INPUT);
  analogReadResolution(12); 
 
  Serial.begin(115200);
  Wire.begin(8,9); 
  delay(100);
  SPI.end(); 
  SPI.begin(SPI_EPD_CLK, SPI_EPD_MISO, SPI_EPD_MOSI, SPI_EPD_CS); 
  display.init();
  display.setRotation(3);
  shtc3.begin();
}

void loop() 
{
  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp); //fresh data
  Serial.println("Sensor Test");
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow(); 
  // DO NOT display.fillScreen(GxEPD_WHITE); keep current content!
  // display.fillRect(0, 0, 10, 10, GxEPD_BLACK); // clear rect instead
  
  display.fillScreen(GxEPD_WHITE);
  
  display.setCursor(10,80);
  display.setFont(&FreeSansBold24pt7b);
  display.print((temp.temperature),1);//One decimal point

  display.drawCircle(120,65,4,GxEPD_BLACK);  //over,down 120,60
  display.setFont(&FreeSansBold12pt7b);
  
  display.setCursor(130,80);
  display.setFont(&FreeSansBold12pt7b);
  display.print("C");

  display.drawLine(25,95,175,95,GxEPD_BLACK);
  display.drawLine(0,100,200,100,GxEPD_BLACK);
  display.drawLine(25,105,175,105,GxEPD_BLACK);

  display.setCursor(10,150);
  display.setFont(&FreeSansBold24pt7b);
  display.print((humidity.relative_humidity),1);//One decimal point

  display.setCursor(120,150);
  display.setFont(&FreeSansBold12pt7b);
  display.print("%H");
  
  display.setCursor(165,15);
  display.setFont(&FreeSansBold9pt7b);
  display.print(get_battery_voltage(),1);
  display.print("v");
  
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(50,15);  //50,15
  display.setFont(&FreeSansBold9pt7b);
  display.print("ESP32-S2");
 

  display.display();
  //delay(2000);
  esp_sleep_enable_timer_wakeup(600000000);  //10 minutes
  //esp_sleep_enable_timer_wakeup(30000000);  //30 seconds
  //esp_light_sleep_start();  //works on the S2
  esp_deep_sleep_start();  //deep sleep works on the S2
}
