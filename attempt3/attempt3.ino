#include "FastLED.h"
#include "elapsedMillis.h"

/*
 * This program linearly maps the range of possible hues (0-255) 
 * onto your neopixel strip.
 */

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    2      // Set this to whatever Arduino pin DIN is connected to
//#define CLK_PIN   4
#define LED_TYPE    WS2812  // This is the type of chip inside of our addressable LED Strip
#define COLOR_ORDER GRB     // Neopixels apparently like commands sent in "GRB" order, so we specify this so we can still write in "RGB" order
#define NUM_LEDS    11   // Set this to the number of LED "pixels" in your strip
#define BRIGHTNESS  100      // This is the initial brightness (max value is 255)


CRGB leds[NUM_LEDS]; // this initializes the array containing all of the LEDs

elapsedMillis timer0; // declare timer variable for loop timing
int tempHue = 0; 

void setup() { // setup code should be the same for nearly every FastLED program
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
  timer0 = 0;
  FastLED.clear(); // clears any previous values written to the pixels

  for (int i=0; i<NUM_LEDS; i+=2) { // iterate through all pixels
    leds[i] = CHSV(tempHue, 255, 255); // CHSV(hue, saturation, value)
  }
  for (int i=1; i<NUM_LEDS; i+=2) { // iterate through all pixels
    leds[i] = CHSV((tempHue + 127) % 255, 255, 255); // CHSV(hue, saturation, value)
  }

  tempHue++;
  if (tempHue >= 256) { // keep tempHue within the range 0-255
    tempHue = 0;       // however, a hue value of 256 is equivalent to a value of 0
  }
  
  FastLED.show();  // turns on all of the pixels with whatever settings you instructed
  while(timer0 < 1) {} // different way of doing a 50 ms delay
}
