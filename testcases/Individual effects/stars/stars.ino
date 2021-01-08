#include <FastLED.h>
#include <EEPROM.h>

#define NUM_LEDS 18          // how many lights the strip has
#define DATA_PIN 7           //connected to data pin 6
CRGB leds[NUM_LEDS];         //led array

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne);
void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne);
void setPixel(int Pixel, byte red, byte green, byte blue);

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);   //adds the type/# of leds and where the data for them are stores
  fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Twinkle(0xff, 0xff, 0xff, 1, 100, false);
   TwinkleRandom(12, 100, false);

}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     FastLED.show();
     delay(SpeedDelay);
     if(OnlyOne) { 
       fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
     }
   }
}
   
void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),red,green,blue);
     FastLED.show();
     delay(SpeedDelay);
     if(OnlyOne) { 
       fill_solid(leds, NUM_LEDS, CRGB(0,0,0)); 
     }
   }
  
  delay(SpeedDelay);
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}
