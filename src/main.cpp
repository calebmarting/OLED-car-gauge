// SPDX-FileCopyrightText: 2023 Limor Fried for Adafruit Industries
//
// SPDX-License-Identifier: MIT

#include <Arduino_GFX_Library.h>
#include "Adafruit_FT6206.h"

Arduino_XCA9554SWSPI *expander = new Arduino_XCA9554SWSPI(
    PCA_TFT_RESET, PCA_TFT_CS, PCA_TFT_SCK, PCA_TFT_MOSI,
    &Wire, 0x3F);

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    TFT_DE, TFT_VSYNC, TFT_HSYNC, TFT_PCLK,
    TFT_R1, TFT_R2, TFT_R3, TFT_R4, TFT_R5,
    TFT_G0, TFT_G1, TFT_G2, TFT_G3, TFT_G4, TFT_G5,
    TFT_B1, TFT_B2, TFT_B3, TFT_B4, TFT_B5,
    1 /* hync_polarity */, 46 /* hsync_front_porch */, 2 /* hsync_pulse_width */, 44 /* hsync_back_porch */,
    1 /* vsync_polarity */, 50 /* vsync_front_porch */, 16 /* vsync_pulse_width */, 16 /* vsync_back_porch */);

Arduino_RGB_Display *display = new Arduino_RGB_Display(
    // 2.1" round
    480 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, false /* auto_flush */,
    expander, GFX_NOT_DEFINED /* RST */, TL021WVC02_init_operations, sizeof(TL021WVC02_init_operations));

Arduino_GFX *gfx = new Arduino_Canvas_3bit(480 /* width */, 480 /* height */, display);

uint16_t backgroundColor = BLACK;

void setup(void)
{
#ifdef GFX_EXTRA_PRE_INIT
    GFX_EXTRA_PRE_INIT();
#endif
    Serial.begin(115200);
    // while (!Serial) delay(100);
    Serial.println("Starting touch paint");

    // Init Display
    Wire.setClock(400000); // speed up I2C
    if (!gfx->begin())
    {
        Serial.println("gfx->begin() failed!");
        while (1)
            yield();
    }

    expander->pinMode(PCA_TFT_BACKLIGHT, OUTPUT);
    expander->digitalWrite(PCA_TFT_BACKLIGHT, HIGH);

    // Serial.println("Hello!");
    // gfx->fillScreen(BLACK);
    // gfx->setCursor(100, gfx->height() / 2 - 75);
    // gfx->setTextSize(5);
    // gfx->setTextColor(WHITE);
    // gfx->println("Hello World!");

    // gfx->setCursor(100, gfx->height() / 2 - 25);
    // gfx->setTextColor(RED);
    // gfx->println("RED");

    // gfx->setCursor(100, gfx->height() / 2 + 25);
    // gfx->setTextColor(GREEN);
    // gfx->println("GREEN");

    // gfx->setCursor(100, gfx->height() / 2 + 75);
    // gfx->setTextColor(BLUE);
    // gfx->println("BLUE");

    expander->pinMode(PCA_BUTTON_UP, INPUT);
    expander->pinMode(PCA_BUTTON_DOWN, INPUT);

    gfx->fillScreen(backgroundColor);
}

struct Point2d{
    int x;
    int y;
};

Point2d polarToXY(float r, float theta){
    theta = radians(theta);
    float x = r * cos(theta);
    float y = r * sin(theta);
    return Point2d{(int)round(x) + (gfx->width()/2), (int)round(y) + (gfx->height()/2)};
}

void drawMarkings(int16_t radius, int16_t thickness){

    // Warning Spot
    gfx -> fillArc(gfx->width()/2,gfx->height()/2,radius+thickness,radius,-45-9,-45+9,RED);
    gfx -> fillArc(gfx->width()/2,gfx->height()/2,radius+thickness,radius,-135-3,-135+3,WHITE);
    gfx -> fillArc(gfx->width()/2,gfx->height()/2,radius+thickness,radius,-90-3,-90+3,WHITE);
    gfx -> fillArc(gfx->width()/2,gfx->height()/2,radius+thickness,radius,-90-22-1,-90-22,WHITE);
    gfx -> fillArc(gfx->width()/2,gfx->height()/2,radius+thickness,radius,-90+22,-90+22+1,WHITE);
}

void drawNeedle(float angle, int16_t color){
    Point2d topLeft = polarToXY(180, angle - .5f);
    Point2d topRight = polarToXY(180, angle + .5f);
    Point2d botLeft = polarToXY(40, angle - 180 + 15);
    Point2d botRight = polarToXY(40, angle -180 - 15);
    // gfx -> getTextBounds
    gfx->fillTriangle(topLeft.x,topLeft.y,topRight.x,topRight.y,botRight.x,botRight.y,color);
    gfx->fillTriangle(topLeft.x,topLeft.y,botLeft.x,botLeft.y,botRight.x,botRight.y,color);
}

void drawCenteredText(const char* str, int16_t x, int16_t y){
    int16_t x1,y1;
    uint16_t w,h;
    gfx->getTextBounds(str, x,y,&x1,&y1,&w,&h, true);
    gfx->setCursor(x-w/2, y-h/2);
    gfx->print(str);
}

void drawText(int16_t color){
    gfx->setTextColor(color); 
    gfx->setTextSize(5);
    Point2d p = polarToXY(100,-90);
    drawCenteredText("250", p.x, p.y);
    p = polarToXY(130,-90-68);
    drawCenteredText("100", p.x, p.y);    
    p = polarToXY(130,-90+68);
    drawCenteredText("320", p.x, p.y);
    gfx->setTextSize(4);
    p = polarToXY(90,90);
    drawCenteredText("OIL", p.x, p.y);
    p = polarToXY(125,90);
    drawCenteredText("TEMP", p.x, p.y);    
}


// void clearNeedle(float angle, int16_t color){
//     Point2d topLeft = polarToXY(180, angle - .5f);
//     Point2d topRight = polarToXY(180, angle + .5f);
//     Point2d botLeft = polarToXY(40, angle - 180 + 15);
//     Point2d botRight = polarToXY(40, angle -180 - 15);
//     // gfx -> getTextBounds
//     gfx->fillTriangle(topLeft.x,topLeft.y,topRight.x,topRight.y,botRight.x,botRight.y,Black);
//     gfx->fillTriangle(topLeft.x,topLeft.y,botLeft.x,botLeft.y,botRight.x,botRight.y,Black);
// }

float a = 0;
unsigned long start;
void loop()
{   

    start = millis();
    drawNeedle(a, backgroundColor);
    float prev = a;
    a = (a+1);
    if(a < 0){
        a+=360;
    }
    if (a>=360){
        a-=360;
    }

    if(a>360-45-9 && backgroundColor==BLACK){
        backgroundColor = RED;
        gfx->fillScreen(backgroundColor);
    }else if(a<360-45-9 && backgroundColor==RED){
        backgroundColor = BLACK;
        gfx->fillScreen(backgroundColor);
    }

    drawMarkings(135, 30);
    drawText(WHITE);
    drawNeedle(a, WHITE);

    gfx->flush();
    delay(min((unsigned long)0,30-(millis()-start)));
    // gfx->fillScreen(BLACK);
    // gfx->setCursor(100, gfx->height() / 2 - 75);
    // gfx->setTextSize(5);
    // gfx->setTextColor(WHITE);
    // gfx->println("Hello World!");

    // gfx->setCursor(100, gfx->height() / 2 - 25);
    // gfx->setTextColor(RED);
    // gfx->println("RED");

    // gfx->setCursor(100, gfx->height() / 2 + 25);
    // gfx->setTextColor(GREEN);
    // gfx->println("GREEN");

    // gfx->setCursor(100, gfx->height() / 2 + 75);
    // gfx->setTextColor(BLUE);
    // gfx->println("BLUE");
    
    

    // use the buttons to turn off
    if (!expander->digitalRead(PCA_BUTTON_DOWN))
    {
        expander->digitalWrite(PCA_TFT_BACKLIGHT, LOW);
    }
    // and on the backlight
    if (!expander->digitalRead(PCA_BUTTON_UP))
    {
        expander->digitalWrite(PCA_TFT_BACKLIGHT, HIGH);
    }
}
