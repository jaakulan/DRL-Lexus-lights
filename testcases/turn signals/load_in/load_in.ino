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

void loop(){

  sequential();
}

void sequential(){
  
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(40);
  for(int i=19;i>=0;i--){
    for(int j=0;j<i;j++){
    leds1[j] = CRGB(255,102,0);
    leds2[j] = CRGB(255,102,0);
    FastLED.show();
    delay(10);
    leds1[j] = CRGB(0,0,0);
    leds2[j] = CRGB(0,0,0);
    }
    leds1[i] = CRGB(255,102,0);
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(10);
  }
  delay(40);
  
}
