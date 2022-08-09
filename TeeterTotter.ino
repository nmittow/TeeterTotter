#include <FastLED.h>

#define NUM_LEDS 146

#define DATA_PIN 13
#define CLOCK_PIN 11
#define WIDTH 10

#define BACKGROUND CRGB::Blue;
#define FOREGROUND CRGB::Red;

#define CALLIBRATION_DURATION_SECONDS 15

unsigned POT_LOW  = 1023;
unsigned POT_HIGH = 0;

CRGB leds[NUM_LEDS];

int pot = A0;
int rawpos = 0;
int pos = NUM_LEDS/2;

bool tickTock = LOW;

void strip_digitalWrite(bool val) {
  CRGB color = CRGB::Black;
  if (val) color = CRGB::White;
  for(unsigned i=0;i<NUM_LEDS;i++){
    leds[i] = color;
  }
  FastLED.show();
  return;
}

void tock() {
  tickTock = !tickTock;
  strip_digitalWrite(tickTock);
  return;
}

void callibrate() {
  int tick = 0;
  unsigned long last = millis();
  unsigned cal = 0;
  unsigned long current = 0;
  while (tick < CALLIBRATION_DURATION_SECONDS) {
    cal = analogRead(pot);
    if (cal < POT_LOW) POT_LOW = cal;
    if (cal > POT_HIGH) POT_HIGH = cal;
    current = millis();
    if ((current - last) > 1000) {
      tick++;
      tock();
      last = current;
    }
  }
  return;
}

void setup() {
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  Serial.begin(115200);
  callibrate();

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
