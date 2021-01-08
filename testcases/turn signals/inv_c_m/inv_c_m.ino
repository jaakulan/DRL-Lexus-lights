#include <FastLED.h>

#define LED_PIN1 7
#define LED_PIN2 4

#define NUM_LEDS 20

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN1, GRB>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN2, GRB>(leds2, NUM_LEDS);
}

void loop() {
  CRGB temp;
  int i;
  for(i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(0,0,0);
    leds2[i] = CRGB(0,0,0);
    FastLED.show();
  }
  
  for(i=0;i<5;i++){
    leds1[i] = CRGB(255,102,0);
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(70);
  }
  
  for(int j=0;j<NUM_LEDS-4;j++){
    temp=leds1[NUM_LEDS-1];
    for(i=NUM_LEDS-1;i>0;i--)
    {
        leds1[i]=leds1[i-1];
        leds2[i]=leds1[i-1];
    }
   leds1[0]=temp;
   leds2[0]=temp;
   FastLED.show();
   delay(70);
  }
  
  
}
