#include <FastLED.h>

#define NUM_LEDS 146

#define DATA_PIN 13
#define CLOCK_PIN 11
#define WIDTH 10

#define POT_LOW 817
#define POT_HIGH 982

#define BACKGROUND CRGB::Blue;
#define FOREGROUND CRGB::Red;


CRGB leds[NUM_LEDS];

int pot = A0;
int rawpos = 0;
int pos = NUM_LEDS/2;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);  // BGR ordering is typical
  Serial.begin(115200);

}

void loop() {
  rawpos = analogRead(pot);
  Serial.println(rawpos);
  pos = map(rawpos, POT_LOW, POT_HIGH, 0, NUM_LEDS - 1);

  
  int lower = pos - (WIDTH/2);
  if (lower < 0) {
    lower = 0;
  }
  int upper = pos + (WIDTH/2);
  if (upper > NUM_LEDS) {
    upper = NUM_LEDS-1;
  }
  for (int i=0;i<NUM_LEDS; i++) {
    if ((i >= lower) && (i <= upper)) { 
      leds[i] = FOREGROUND;
    }
    else {
      leds[i] = BACKGROUND; 
    }
  }
  FastLED.show();
  

}
