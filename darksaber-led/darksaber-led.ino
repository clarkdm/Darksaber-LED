#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#define Button_PIN     4
#define LED_PIN     7
#define NUM_LEDS    65
//CRGB leds[NUM_LEDS];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


int x = 1;

int buttonState;             
int lastButtonState = LOW; 
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 

// FOR rainbow
  byte *c;
  uint16_t i, j = 0;

  
void setup() {
//  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
 
pinMode(Button_PIN,INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
}




//void loop() {
//
//
////rainbow()
//FastLED.show();
//
//FadeInOut(0xff, 0x00, 0x00); // red
//  FadeInOut(0xff, 0xff, 0xff); // white
//  FadeInOut(0x00, 0x00, 0xff); // blue
//
//
////  for (int i = 0; i <= NUM_LEDS; i++) {
////    leds[i] = CRGB (204, 102, 255 );
////    FastLED.show();
////  }
////  for (int i = NUM_LEDS; i >= 0; i--) {
////    leds[i] = CRGB ( 102, 255, 255);
////    FastLED.show();
////  }
//}
//
//
//void rainbow(){
//  fill_rainbow (leds ,90 ,0, 8);
//}



//void loop() {
// 
//  int reading = digitalRead(Button_PIN);
//
// Serial.println(reading);
//  if (reading != lastButtonState) {
//    
//    lastDebounceTime = millis();
//  }
//
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//   
//    if (reading != buttonState) {
//      buttonState = reading;
//
//      
//      if (buttonState == HIGH) {
//        x = x + 1;
//        if (x > 6){
//          x = 1;
//        }
//      }
//    }
//  }
//
// 
//  ledState();
//
// 
//  lastButtonState = reading;
//}


//
void loop() { 
  
  if(digitalRead(Button_PIN)== 0){
    
//    Blue();
    delay(50);
    if(digitalRead(Button_PIN)== 1){
//      red();
x = x + 1;
    }
  }
  if (x == 7){
    x = 1;
  }
  ledState();
 }
  
 void ledState(){
  Serial.println(x);
  switch (x) {
          case 1:
          Serial.println("Blue");
              Blue();
              break;
          case 2:
          Serial.println("red");
              red();
              break;
          case 3:
          Serial.println("Green");
              Green();
              break;
          case 4:
          Serial.println("purple");
              purple();
              break;
          case 5:
          Serial.println("purple2");
              Fire(55,120,15);
              break;
          default:
          Serial.println("purple3");
              rainbowCycle(15);
              break;
      }
  
 }

void red() {
  strip.fill(strip.Color(255, 0, 0));
  showStrip();
}

void Green() {
  strip.fill(strip.Color(0, 255, 0));
  showStrip();
}

void Blue() {
  strip.fill(strip.Color(0, 0, 255));
  showStrip();
}

void purple() {
  strip.fill(strip.Color(128,0,128));
  showStrip();
}

void rainbowCycle(int SpeedDelay) {
if(j>256*5){
  j = 0;
  }
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  j++;
  
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
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}


void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}
