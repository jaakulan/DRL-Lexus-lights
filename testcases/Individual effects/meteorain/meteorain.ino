#include <FastLED.h>
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
  // put your main code here, to run repeatedly:
  meteorRain(0xff,0xff,0xff,10, 64, true, 50);

}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
   fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
   fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    FastLED.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds1[ledNo].fadeToBlackBy( fadeValue );
   leds2[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds1[Pixel].r = red;
   leds1[Pixel].g = green;
   leds1[Pixel].b = blue;
   leds2[Pixel].r = red;
   leds2[Pixel].g = green;
   leds2[Pixel].b = blue;
 #endif
}
