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
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(255,102,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(255,102,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
}
