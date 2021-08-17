/*
 * Prototyp des Bachelorprojektes vink
 * 
 * von Helene Antonia Lehmann und Isabel Mahnken
 * Sommersemester 2021
 * Interactive Media Design
 * Mediencampus Dieburg der Hochschule Darmstadt
 * 18.08.2021
 */

#include <FastLED.h>        //Library Import

#define PIN1     5          // Eingabeanhänger1
#define PIN2     6          // Eingabeanhänger2
#define PIN3     7          // Ausgabeleuchte

const int POTPIN1 = 1;      //Potentiometer1 an Pin A1
const int POTPIN2 = 2;      //Potentiometer2 an Pin A2

#define NUM_LEDS1und2    10 //Anzahl der anzusteuernden LEDs im Eingabeanhänger1/2
#define NUM_LEDS3        70 //Anzahl der anzusteuernden LEDs in Ausgabeleuchte
#define LED_TYPE    WS2811 
#define COLOR_ORDER GRB

//Zuweisung der anzusteuernden LEDs pro LEDStripe
CRGB leds1[NUM_LEDS1und2]; //Eingabeanhänger1
CRGB leds2[NUM_LEDS1und2]; //Eingabeanhänger2
CRGB leds3[NUM_LEDS3];     //Ausgabeleuchte
CRGBPalette16 farbpalette; 

float eingabewert1 = 0;    // Variable für den durch das Potentiometer1 eingegebenen Wert
float eingabewert2 = 0;    // Variable für den durch das Potentiometer2 eingegebenen Wert
float eingabewertd = 0;    // Variable für den zu errechnenden Durchschnittswert
int r1 = 0;                // Variable für Rot-Wert der zu errechnenden Farbe1
int g1 = 0;                // Variable für Grün-Wert der zu errechnenden Farbe1
int b1 = 0;                // Variable für Blau-Wert der zu errechnenden Farbe1
int r2 = 0;                // Variable für Rot-Wert der zu errechnenden Farbe2
int g2 = 0;                // Variable für Grün-Wert der zu errechnenden Farbe2
int b2 = 0;                // Variable für Blau-Wert der zu errechnenden Farbe2
int rd = 0;                // Variable für Rot-Wert der zu errechnenden Farbed
int gd = 0;                // Variable für Grün-Wert der zu errechnenden Farbed
int bd = 0;                // Variable für Blau-Wert der zu errechnenden Farbed
int multi1 = 0;            // Variable zur Multipilizierung der Farbschritte
int multi2 = 0;            // Variable zur Multipilizierung der Farbschritte
int multid = 0;            // Variable zur Multipilizierung der Farbschritte
float multiFarbIndex;      // Variable zur Multipilizierung des Farbindex
float multiSchattierung;   // Variable zur Abdunklung der Farben für den Welleneffekt
  


void setup() {
    Serial.begin(9600);
    FastLED.clear();
    delay( 1000 );
    FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds1, NUM_LEDS1und2).setCorrection( TypicalLEDStrip );  //Zuordnungen für den Eingabeanhänger1
    FastLED.addLeds<LED_TYPE, PIN2, COLOR_ORDER>(leds2, NUM_LEDS1und2).setCorrection( TypicalLEDStrip );  //Zuordnungen für den Eingabeanhänger2
    FastLED.addLeds<LED_TYPE, PIN3, COLOR_ORDER>(leds3, NUM_LEDS3).setCorrection( TypicalLEDStrip );      //Zuordnungen für die Ausgabeleuchte
    FastLED.setBrightness(255);
    pinMode(POTPIN1, INPUT);                                                                              //Deklarierung des Eingabepotentiometers1 als analogen Input
    pinMode(POTPIN2, INPUT);                                                                              //Deklarierung des Eingabepotentiometers2 als analogen Input
    farbpalette = RainbowStripeColors_p;                                                                  //Farbpalette aus der Library
}


void loop()
{    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;                          //Geschwindigkeit der Bewegung, bzw. Start-LED + 1
    EingabeAuslesen();                                    //Funktionsaufruf zum Auslesen der Eingabe über die Potentiometer in den Eingabeanhängern1/2
    FarbwertErrechnen();                                  //Funktionsaufruf zum Errechnen der anzuzeigenden Farben auf den Eingabeanhängern1/2 und der Ausgabeleuchte
    AnhaengerAnzeige();                                     //Funktionsaufruf zum Anzeigen der errechneten Farben auf den Eingabeanhängern1/2
    if(eingabewertd >2.5){                                
       AusgabeleuchteAnzeige(startIndex);                 //Funktionsaufruf zum Anzeigen der errechneten Farben auf den Eingabeanhängern1/2 (nur wenn mindestens ein Potentiometer auf die ON-Position gedreht wurde
    }
    else{
       FastLED.clear();   
    }
   
    FastLED.show();
    FastLED.delay(800/ eingabewertd);                     //Geschwindigkeit der Bewegung; abh. von dem errechneten Durchschnittswert
}


void EingabeAuslesen(){                                   //Funktion zum Auslesen der Eingabe über die Potentiometer in den Eingabeanhängern1/2
  eingabewert1 = analogRead(POTPIN1)/ 4;                  //Eingabewert vom Potentiometer1 erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  eingabewert2 = analogRead(POTPIN2)/ 4;                  //Eingabewert vom Potentiometer2 erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  eingabewertd = (eingabewert1 + eingabewert2) / 2;       //Berechnung des durchschnittlichen und momentanen Eingabewertes
  multiFarbIndex = eingabewertd / 85;                     //Umrechnung dieses Durchschnittes in die Werte 1-3 für die Wellenfunktion
  multiSchattierung = multiFarbIndex * 10;                //Umrechnung dieses Wertes für die Abdunklungsstärke der Wellen (je abgedunkelter, desto sichtbarer die Wellen)

}

void FarbwertErrechnen(){                                 //Funktion zum Errechnen der anzuzeigenden Farben auf den Eingabeanhängern1/2 und der Ausgabeleuchte
  multi1 = eingabewert1 - 1;                              //Variable zur Multipilizierung der Farbschritte ist eins kleiner als der Eingabewert
  multi2 = eingabewert2 - 1;
  multid = eingabewertd - 1;

  if(eingabewert1 < 5){                                   //Solange der Eingabewert unter 5 liegt, wird keine Farbe angezeigt und der AUS-Zustand simuliert
   r1 = 0;
   g1 = 0;
   b1 = 0;
  }
  if(eingabewert2 < 5){
   r2 = 0;
   g2 = 0;
   b2 = 0;
  }
  if(eingabewert1 == 5){                                  //Sobald der Eingabewert über 5 liegt, wird die Farbe errechnet
   r1 = 100;                                              //Dabei gibt es zwei feste Farbwerte, die festen Eingabewerten zugeordnet sind
   g1 = 155;                                              //Zwischen diesen zwei Eingabewerten, wird die Differenz aus den einzelnen r-g-b-Werten mit dem Eingabewert-1 multipliziert
   b1 = 0;
  }
  if(eingabewert2 == 5){
   r2 = 100;
   g2 = 155;
   b2 = 0;
  }
  if(eingabewertd == 5){
   rd = 100;
   gd = 155;
   bd = 0;
  }
  if(eingabewert1 > 5 && eingabewert1 < 255){
   r1 = 100 + (multi1 * 0.57312253);                  
   g1 = 155 - (multi1 * 0.57312253);
   b1 = 0;
  }
  if(eingabewert2 > 5 && eingabewert2 < 255){
   r2 = 100 + (multi2 * 0.57312253);                  
   g2 = 155 - (multi2 * 0.57312253);
   b2 = 0;
  }
  if(eingabewertd > 5 && eingabewertd < 255){
   rd = 100 + (multid * 0.57312253);                  
   gd = 155 - (multid * 0.57312253);
   bd = 0;
  }
  if(eingabewert1 == 255){
   r1 = 245;
   g1 = 10;
   b1 = 0;
  }
  if(eingabewert2 == 255){
   r2 = 245;
   g2 = 10;
   b2 = 0;
  }
  if(eingabewertd == 255){
   rd = 245;
   gd = 10;
   bd = 0;
  }
}

void AnhaengerAnzeige(){                                    //Funktionsaufruf zum Anzeigen der errechneten Farben auf den Eingabeanhängern1/2
  for( int j = 0; j < NUM_LEDS1und2; j++) {
    leds1[j] = CRGB(r1, g1, b1);
    leds2[j] = CRGB(r2, g2, b2);

  }
}

void AusgabeleuchteAnzeige( float farbIndex)                //Funktionsaufruf zum Anzeigen der errechneten Farben auf der Ausgabeleuchte
{    
    for( int i = 0; i < NUM_LEDS3; i++) {
      Wellen();
        {leds3[i] = ColorFromPalette(farbpalette, farbIndex, 255, LINEARBLEND);  
        farbIndex += multiFarbIndex;}
    }
}

void Wellen()                                               //Funktionsaufruf zum Anzeigen der simulierten Wellen durch Abdunklung bestimmter Stellen, deren Abstand von den Eingabewerten abhängen 
{
    fill_solid( farbpalette, 16, CRGB(rd/multiSchattierung, gd/multiSchattierung, bd/multiSchattierung)); //Abdunklung (abh. von Eingabewerten) 
    for(int k=0; k<16; k=k+2){                                                                            //Farbe anzeigen an bestimmten Stellen
      farbpalette[k] = CRGB(rd, gd, bd);
    }    
}
