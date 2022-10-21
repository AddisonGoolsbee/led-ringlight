#include "FastLED.h"

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    7      // Set this to whatever Arduino pin DIN is connected to
//#define CLK_PIN   4
#define LED_TYPE    WS2812  // This is the type of chip inside of our addressable LED Strip
#define COLOR_ORDER GRB     // Neopixels apparently like commands sent in "GRB" order, so we specify this so we can still write in "RGB" order
#define NUM_LEDS    255     // Set this to the number of LED "pixels" in your strip
#define BRIGHTNESS  50      // This is the initial brightness (max value is 255)


CRGB leds[NUM_LEDS]; // this initializes the array containing all of the LEDs


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
  FastLED.clear(); // clears any previous values written to the pixels

  for (int i=0; i<NUM_LEDS; i++) { // iterate through all pixels
    leds[i] = CRGB(255, 255, 255); // full values for each will give white
  }
  
  FastLED.show();  // turns on all of the pixels with whatever settings you instructed
  
  delay(50); // Ensures that the "FastLED.show() command doesn't run too frequently
}
