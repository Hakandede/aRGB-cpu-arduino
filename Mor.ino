#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    15

#define BRIGHTNESS  0
#define FRAMES_PER_SECOND 20

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];

CRGBPalette16 gPal;

void setup() {
  delay(3000);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

 
    gPal = CRGBPalette16( CRGB(110, 5, 133), CRGB(61, 0, 104), CRGB(79, 0, 135), CRGB(155, 43, 172));

}

void loop()
{
  random16_add_entropy( random());

  Fire2012WithPalette(); 
  
  FastLED.show(); 
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}



#define COOLING  20

.
#define SPARKING 50


void Fire2012WithPalette()
{
  static uint8_t heat[NUM_LEDS];

 
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
  
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
  
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }


    for( int j = 0; j < NUM_LEDS; j++) {
    
      uint8_t colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
