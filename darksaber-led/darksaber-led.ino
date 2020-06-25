#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    299
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}
void loop() {
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB (204, 102, 255 );
    FastLED.show();
  }
  for (int i = NUM_LEDS; i >= 0; i--) {
    leds[i] = CRGB ( 102, 255, 255);
    FastLED.show();
  }
}
