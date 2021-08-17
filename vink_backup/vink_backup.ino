#include <FastLED.h>

#define PIN1     5  // Eingabe1
#define PIN2     6  // Eingabe2
#define PIN3     7  // Ausgabe

const int POTPIN1 = 1;  //Potentiometer1 an Pin A1
const int POTPIN2 = 2;  //Potentiometer2 an Pin A2

#define NUM_LEDS1und2    10
#define NUM_LEDS3        70

#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS1und2];
CRGB leds2[NUM_LEDS1und2];
CRGB leds3[NUM_LEDS3];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int eingabewert1 = 0;       // Variable für den durch das Potentiometer1 eingegebenen Wert
int eingabewert2 = 0;       // Variable für den durch das Potentiometer2 eingegebenen Wert
int eingabewertd = 0;
int r1 = 0;                 // Variable für Rot-Wert der zu errechnenden Farbe1
int g1 = 0;                 // Variable für Grün-Wert der zu errechnenden Farbe1
int b1 = 0;                 // Variable für Blau-Wert der zu errechnenden Farbe1
int r2 = 0;                 // Variable für Rot-Wert der zu errechnenden Farbe2
int g2 = 0;                 // Variable für Grün-Wert der zu errechnenden Farbe2
int b2 = 0;                 // Variable für Blau-Wert der zu errechnenden Farbe2
int rd = 0;                 // Variable für Rot-Wert der zu errechnenden Farbed
int gd = 0;                 // Variable für Grün-Wert der zu errechnenden Farbed
int bd = 0;                 // Variable für Blau-Wert der zu errechnenden Farbed
String farbe1 = "keine";    // Variable für die Bennenung der errechneten Farbe
String farbe2 = "keine";    // Variable für die Bennenung der errechneten Farbe
String farbed = "keine";    // Variable für die Bennenung der errechneten Farbe
uint32_t farbwert1;    
uint32_t farbwert2;    
uint32_t farbwertd; 
int multi1 = 0;             // Variable zur Multipilizierung der Farbschritte
int multi2 = 0;             // Variable zur Multipilizierung der Farbschritte
int multid = 0;             // Variable zur Multipilizierung der Farbschritte



void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1und2).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, PIN2, COLOR_ORDER>(leds2, NUM_LEDS1und2).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, PIN3, COLOR_ORDER>(leds3, NUM_LEDS3).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    pinMode(POTPIN1, INPUT);  
    pinMode(POTPIN2, INPUT);
    currentPalette = RainbowStripeColors_p;
    currentBlending = LINEARBLEND;
    Serial.begin(9600);
}


void loop()
{    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    EingabeAuslesen();
    FarbwertErrechnen();
    FarbenAnzeigen();
    FillLEDsFromPaletteColors(startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS3; i++) {
      SetupBlackAndWhiteStripedPalette();
        {leds3[i] = ColorFromPalette( currentPalette, colorIndex, brightness, LINEARBLEND);
        colorIndex += 3;}
    }
    
}

void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB(rd, gd, bd);
    currentPalette[4] = CRGB(rd, gd, bd);
    currentPalette[8] = CRGB(rd, gd, bd);
    currentPalette[12] = CRGB(rd, gd, bd);
    
}

void EingabeAuslesen(){
  eingabewert1 = analogRead(POTPIN1)/ 4;    // Eingabewert vm Potentiometer erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  eingabewert2 = analogRead(POTPIN2)/ 4;    // Eingabewert vm Potentiometer erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  eingabewertd = (eingabewert1 + eingabewert2) / 2;
  Serial.println(eingabewert1);
}

void FarbwertErrechnen(){
  multi1 = eingabewert1 - 1;
  multi2 = eingabewert2 - 1;
  multid = eingabewertd - 1;

  if(eingabewert1 < 5){
   r1 = 0;
   g1 = 0;
   b1 = 0;
  }
  if(eingabewert2 < 5){
   r2 = 0;
   g2 = 0;
   b2 = 0;
  }
  if(eingabewertd < 5){
   rd = 0;
   gd = 0;
   bd = 0;
  }
  if(eingabewert1 == 5){
   r1 = 100;
   g1 = 155;
   b1 = 0;
   farbe1 = "gruen";
  }
  if(eingabewert2 == 5){
   r2 = 100;
   g2 = 155;
   b2 = 0;
   farbe2 = "gruen";
  }
  if(eingabewertd == 5){
   rd = 100;
   gd = 155;
   bd = 0;
   farbed = "gruen";
  }
  if(eingabewert1 > 5 && eingabewert1 < 255){
   r1 = 100 + (multi1 * 0.57312253);                  
   g1 = 155 - (multi1 * 0.57312253);
   b1 = 0;
   farbe1 = "irgendetwas zwischen gruen und rot";
  }
  if(eingabewert2 > 5 && eingabewert2 < 255){
   r2 = 100 + (multi2 * 0.57312253);                  
   g2 = 155 - (multi2 * 0.57312253);
   b2 = 0;
   farbe2 = "irgendetwas zwischen gruen und rot";
  }
  if(eingabewertd > 5 && eingabewertd < 255){
   rd = 100 + (multid * 0.57312253);                  
   gd = 155 - (multid * 0.57312253);
   bd = 0;
   farbed = "irgendetwas zwischen gruen und rot";
  }
  if(eingabewert1 == 255){
   r1 = 245;
   g1 = 10;
   b1 = 0;
   farbe1 = "rot";
  }
  if(eingabewert2 == 255){
   r2 = 245;
   g2 = 10;
   b2 = 0;
   farbe2 = "rot";
  }
  if(eingabewertd == 255){
   rd = 245;
   gd = 10;
   bd = 0;
   farbed = "rot";
  }

}

void FarbenAnzeigen(){
  
  //farbwert1 = CRGB(r1, g1, b1);
  Serial.print(r1);
  Serial.print(g1);
  Serial.println(b1);

  
  farbwert2 = CRGB(r2, g2, b2);
  farbwertd = CRGB(rd, gd, bd);

  for( int j = 0; j < NUM_LEDS1und2; j++) {
    leds1[j] = CRGB(r1, g1, b1);
    leds2[j] = CRGB(r2, g2, b2);
 
  }
 // leds1 = fill(farbwert1);
//  strip1.fill(farbwert1);
//  strip2.fill(farbwert2);
//  strip3.fill(farbwertd);
//  strip1.show();
//  strip2.show();
//  strip3.show();
}
