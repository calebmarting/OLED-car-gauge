// #include <Arduino.h>

// // SPDX-FileCopyrightText: 2023 Limor Fried for Adafruit Industries
// //
// // SPDX-License-Identifier: MIT

// #include <Arduino_GFX_Library.h>
// #include "Adafruit_FT6206.h"
// /* Wio Terminal */
// #if defined(ARDUINO_ARCH_SAMD) && defined(SEEED_GROVE_UI_WIRELESS)
// #include <Seeed_FS.h>
// #include <SD/Seeed_SD.h>
// #elif defined(TARGET_RP2040)
// #include <LittleFS.h>
// #include <SD.h>
// #elif defined(ESP32)
// // #include <FFat.h>
// // #include <LittleFS.h>
// #include <SPIFFS.h>
// // #include <SD.h>
// // #include <SD_MMC.h>
// #elif defined(ESP8266)
// #include <LittleFS.h>
// #include <SD.h>
// #else
// #include <SD.h>
// #endif
// /*******************************************************************************
//  * BMP Image Viewer
//  * This is a simple BMP image viewer example
//  * Image Source: https://github.blog/2014-11-24-from-sticker-to-sculpture-the-making-of-the-octocat-figurine/
//  *
//  * BMP Class original source: https://github.com/Jaycar-Electronics/Arduino-Picture-Frame.git
//  *
//  * Setup steps:
//  * 1. Change your LCD parameters in Arduino_GFX setting
//  * 2. Upload BMP file
//  *   FFat (ESP32):
//  *     upload FFat (FatFS) data with ESP32 Sketch Data Upload:
//  *     ESP32: https://github.com/lorol/arduino-esp32fs-plugin
//  *   LittleFS (ESP32 / ESP8266 / Pico):
//  *     upload LittleFS data with ESP8266 LittleFS Data Upload:
//  *     ESP32: https://github.com/lorol/arduino-esp32fs-plugin
//  *     ESP8266: https://github.com/earlephilhower/arduino-esp8266littlefs-plugin
//  *     Pico: https://github.com/earlephilhower/arduino-pico-littlefs-plugin.git
//  *   SPIFFS (ESP32):
//  *     upload SPIFFS data with ESP32 Sketch Data Upload:
//  *     ESP32: https://github.com/lorol/arduino-esp32fs-plugin
//  *   SD:
//  *     Most Arduino system built-in support SD file system.
//  *     Wio Terminal require extra dependant Libraries:
//  *     - Seeed_Arduino_FS: https://github.com/Seeed-Studio/Seeed_Arduino_FS.git
//  *     - Seeed_Arduino_SFUD: https://github.com/Seeed-Studio/Seeed_Arduino_SFUD.git
//  ******************************************************************************/
// // #define BMP_FILENAME "/octocatS.bmp" // 243x128@IndexedColor
// //#define BMP_FILENAME "/octocatM.bmp" // 456x240@16bit
// // #define BMP_FILENAME "/octocatL.bmp" // 608x320@24bit
// #define BMP_FILENAME "/corvette.bmp" // 456x240@16bit


// Arduino_XCA9554SWSPI *expander = new Arduino_XCA9554SWSPI(
//     PCA_TFT_RESET, PCA_TFT_CS, PCA_TFT_SCK, PCA_TFT_MOSI,
//     &Wire, 0x3F);

// Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
//     TFT_DE, TFT_VSYNC, TFT_HSYNC, TFT_PCLK,
//     TFT_R1, TFT_R2, TFT_R3, TFT_R4, TFT_R5,
//     TFT_G0, TFT_G1, TFT_G2, TFT_G3, TFT_G4, TFT_G5,
//     TFT_B1, TFT_B2, TFT_B3, TFT_B4, TFT_B5,
//     1 /* hync_polarity */, 46 /* hsync_front_porch */, 2 /* hsync_pulse_width */, 44 /* hsync_back_porch */,
//     1 /* vsync_polarity */, 50 /* vsync_front_porch */, 16 /* vsync_pulse_width */, 16 /* vsync_back_porch */);

// Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
// /* 3.4" square */
// //    480 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
// //    expander, GFX_NOT_DEFINED /* RST */, tl034wvs05_b1477a_init_operations, sizeof(tl034wvs05_b1477a_init_operations));
// /* 3.2" bar */
// //    320 /* width */, 820 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
// //    expander, GFX_NOT_DEFINED /* RST */, tl032fwv01_init_operations, sizeof(tl032fwv01_init_operations));
// /* 4.0" 720x720 square */
// //    720 /* width */, 720 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
// //    expander, GFX_NOT_DEFINED /* RST */, NULL, 0);
// /* 4.0" 480x480 square */
// //    480 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
// //    expander, GFX_NOT_DEFINED /* RST */, tl040wvs03_init_operations, sizeof(tl040wvs03_init_operations));
// // 2.1" round
//     480 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
//     expander, GFX_NOT_DEFINED /* RST */, TL021WVC02_init_operations, sizeof(TL021WVC02_init_operations));

// #include "BmpClass.h"
// static BmpClass bmpClass;

// // pixel drawing callback
// static void bmpDrawCallback(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
// {
//   Serial.printf("Draw pos = %d, %d. size = %d x %d\n", x, y, w, h);
//   gfx->draw16bitRGBBitmap(x, y, bitmap, w, h);
// }

// // Adafruit_FT6206 ctp = Adafruit_FT6206();  // This library also supports FT6336U!
// // #define I2C_TOUCH_ADDR 0x15
// // bool touchOK = false;
// void setup()
// {
  
//   Serial.begin(115200);
//   Serial.setDebugOutput(true);
//   // while(!Serial);
//   Serial.println("Arduino_GFX BMP Image Viewer example");

// #ifdef GFX_EXTRA_PRE_INIT
//   GFX_EXTRA_PRE_INIT();
// #endif
//   expander->pinMode(PCA_TFT_BACKLIGHT, OUTPUT);
//   expander->digitalWrite(PCA_TFT_BACKLIGHT, HIGH);
//   // Init Display
//   if (!gfx->begin())
//   {
//     Serial.println("gfx->begin() failed!");
//   }


// #ifdef GFX_BL
//   pinMode(GFX_BL, OUTPUT);
//   digitalWrite(GFX_BL, HIGH);
// #endif

// /* Wio Terminal */
// #if defined(ARDUINO_ARCH_SAMD) && defined(SEEED_GROVE_UI_WIRELESS)
//   if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL))
// #elif defined(TARGET_RP2040)
//   if (!LittleFS.begin())
//   // if (!SD.begin(SS))
// #elif defined(ESP32)
//   // if (!FFat.begin())
//   // if (!LittleFS.begin())
//   if (!SPIFFS.begin())
//   // SPI.begin(12 /* CLK */, 13 /* D0/MISO */, 11 /* CMD/MOSI */);
//   // if (!SD.begin(10 /* CS */, SPI))
//   // pinMode(10 /* CS */, OUTPUT);
//   // digitalWrite(SD_CS, HIGH);
//   // SD_MMC.setPins(12 /* CLK */, 11 /* CMD/MOSI */, 13 /* D0/MISO */);
//   // if (!SD_MMC.begin("/root", true /* mode1bit */, false /* format_if_mount_failed */, SDMMC_FREQ_DEFAULT))
//   // SD_MMC.setPins(12 /* CLK */, 11 /* CMD/MOSI */, 13 /* D0/MISO */, 14 /* D1 */, 15 /* D2 */, 10 /* D3/CS */);
//   // if (!SD_MMC.begin("/root", false /* mode1bit */, false /* format_if_mount_failed */, SDMMC_FREQ_HIGHSPEED))
// #elif defined(ESP8266)
//   if (!LittleFS.begin())
//   // if (!SD.begin(SS))
// #else
//   if (!SD.begin())
// #endif
//   {
//     Serial.println(F("ERROR: File System Mount Failed!"));
//     gfx->println(F("ERROR: File System Mount Failed!"));
//   }
//   else
//   {
//     unsigned long start = millis();

// /* Wio Terminal */
// #if defined(ARDUINO_ARCH_SAMD) && defined(SEEED_GROVE_UI_WIRELESS)
//     File bmpFile = SD.open(BMP_FILENAME, "r");
// #elif defined(TARGET_RP2040)
//     File bmpFile = LittleFS.open(BMP_FILENAME, "r");
//     // File bmpFile = SD.open(BMP_FILENAME, "r");
// #elif defined(ESP32)
//     // File bmpFile = FFat.open(BMP_FILENAME, "r");
//     // File bmpFile = LittleFS.open(BMP_FILENAME, "r");
    
//     // File bmpFile = SD.open(BMP_FILENAME, "r");
// #elif defined(ESP8266)
//     File bmpFile = LittleFS.open(BMP_FILENAME, "r");
//     // File bmpFile = SD.open(BMP_FILENAME, "r");
// #else
//     File bmpFile = SD.open(BMP_FILENAME, FILE_READ);
// #endif
//     gfx->fillScreen(BLACK);
//     File bmpFile = SPIFFS.open(BMP_FILENAME, "r");
//     // read BMP file header
//     bmpClass.draw(
//         &bmpFile, bmpDrawCallback, false /* useBigEndian */,
//         0 /* x */, 0 /* y */, gfx->width() /* widthLimit */, gfx->height() /* heightLimit */);

//     bmpFile.close();

//     Serial.print("Time used: ");
//     Serial.println(millis() - start);
//   }

// }

// void loop()
// {

// }

// // void setup(void)
// // {
// //   //while (!Serial) delay(100);

// // #ifdef GFX_EXTRA_PRE_INIT
// //   GFX_EXTRA_PRE_INIT();
// // #endif
// //   Serial.begin(115200);
  
// //   Serial.println("Starting touch paint");

// //   // Init Display
// //   Wire.setClock(400000); // speed up I2C
// //   if (!gfx->begin()) {
// //     Serial.println("gfx->begin() failed!");
// //     while (1) yield();
// //   }

// //   gfx->fillScreen(BLACK);

// //   expander->pinMode(PCA_TFT_BACKLIGHT, OUTPUT);
// //   expander->digitalWrite(PCA_TFT_BACKLIGHT, HIGH);

// //   Serial.println("Hello!");
// //   gfx->fillScreen(BLACK);
// //   gfx->setCursor(100, gfx->height() / 2 - 75);
// //   gfx->setTextSize(5);
// //   gfx->setTextColor(WHITE);
// //   gfx->println("Hello World!");

// //   gfx->setCursor(100, gfx->height() / 2 - 25);
// //   gfx->setTextColor(RED);
// //   gfx->println("RED");

// //   gfx->setCursor(100, gfx->height() / 2 + 25);
// //   gfx->setTextColor(GREEN);
// //   gfx->println("GREEN");

// //   gfx->setCursor(100, gfx->height() / 2 + 75);
// //   gfx->setTextColor(BLUE);
// //   gfx->println("BLUE");

// //   if (!ctp.begin(0, &Wire, I2C_TOUCH_ADDR)) {
// //     //gfx->setTextColor(RED);
// //     //gfx->println("\nTouch not found");
// //     Serial.println("No touchscreen found");
// //     touchOK = false;
// //   } else {
// //     gfx->setTextColor(WHITE);
// //     gfx->println("\nTouch found");
// //     Serial.println("Touchscreen found");
// //     touchOK = true;
// //   }

// //   expander->pinMode(PCA_BUTTON_UP, INPUT);
// //   expander->pinMode(PCA_BUTTON_DOWN, INPUT);
// // }

// // void loop()
// // {
// //   if (touchOK && ctp.touched()) {
// //     TS_Point p = ctp.getPoint(0);
// //     Serial.printf("(%d, %d)\n", p.x, p.y);
// //     gfx->fillRect(p.x, p.y, 5, 5, WHITE);
// //   }

// //   // use the buttons to turn off
// //   if (! expander->digitalRead(PCA_BUTTON_DOWN)) {
// //     expander->digitalWrite(PCA_TFT_BACKLIGHT, LOW);
// //   }
// //   // and on the backlight
// //   if (! expander->digitalRead(PCA_BUTTON_UP)) {
// //     expander->digitalWrite(PCA_TFT_BACKLIGHT, HIGH);
// //   }

// // }