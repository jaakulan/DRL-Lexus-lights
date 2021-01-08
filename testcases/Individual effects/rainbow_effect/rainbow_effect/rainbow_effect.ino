#include "FastLED.h"
#include <EEPROM.h>
#define NUM_LEDS 18          // how many lights the strip has
#define DATA_PIN1 7
#define DATA_PIN2 4//connected to data pin 6
CRGB leds1[NUM_LEDS];         //led array
CRGB leds2[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN1, GRB>(leds1, NUM_LEDS);   //adds the type/# of leds and where the data for them are stores
  FastLED.addLeds<WS2812B, DATA_PIN2, GRB>(leds2, NUM_LEDS);
  fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
  FastLED.show();

}

void loop() {
   rainbowCycle(20);
}

void showStrip() {
   FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   leds1[Pixel].r = red;
   leds1[Pixel].g = green;
   leds1[Pixel].b = blue;
   leds2[Pixel].r = red;
   leds2[Pixel].g = green;
   leds2[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}
