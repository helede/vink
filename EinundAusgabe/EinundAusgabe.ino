//Ausgabe vink Pototyp

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN1        5       // Eingabe1
#define PIN2        6       // Eingabe2
#define PIN3        7       // Ausgabe 

int potPin1 = 1;            //Potentiometer an Pin A1
int potPin2 = 2;            //Potentiometer2 an Pin A2
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

#define NUMPIXELS 50 

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel strip1(6, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(6, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.


  Serial.begin(9600); // Starte Serialmonitor
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.show();
  strip3.show();
}

void loop() {
  strip1.clear(); // Set all pixel colors to 'off'
  strip2.clear();
  strip3.clear();

  eingabewert1 = analogRead(potPin1)/ 4;    // Eingabewert vm Potentiometer erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  eingabewert2 = analogRead(potPin2)/ 4;    // Eingabewert vm Potentiometer erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  eingabewertd = (eingabewert1 + eingabewert2) / 2;
  multi1 = eingabewert1 - 1;
  multi2 = eingabewert2 - 1;
  multid = eingabewertd - 1;

  if(eingabewert1 == 0){
   r1 = 0;
   g1 = 0;
   b1 = 0;
  }
  if(eingabewert2 == 0){
   r2 = 0;
   g2 = 0;
   b2 = 0;
  }
  if(eingabewertd == 0){
   rd = 0;
   gd = 0;
   bd = 0;
  }
  if(eingabewert1 == 1){
   r1 = 100;
   g1 = 155;
   b1 = 0;
   farbe1 = "gruen";
  }
  if(eingabewert2 == 1){
   r2 = 100;
   g2 = 155;
   b2 = 0;
   farbe2 = "gruen";
  }
  if(eingabewertd == 1){
   rd = 100;
   gd = 155;
   bd = 0;
   farbed = "gruen";
  }
  if(eingabewert1 > 1 && eingabewert1 < 255){
   r1 = 100 + (multi1 * 0.57312253);                  
   g1 = 155 - (multi1 * 0.57312253);
   b1 = 0;
   farbe1 = "irgendetwas zwischen gruen und rot";
  }
  if(eingabewert2 > 1 && eingabewert2 < 255){
   r2 = 100 + (multi2 * 0.57312253);                  
   g2 = 155 - (multi2 * 0.57312253);
   b2 = 0;
   farbe2 = "irgendetwas zwischen gruen und rot";
  }
  if(eingabewertd > 1 && eingabewertd < 255){
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

  farbwert1 = strip1.Color(r1, g1, b1);
  farbwert2 = strip2.Color(r2, g2, b2);
  farbwertd = strip3.Color(rd, gd, bd);
  
 
  
strip1.fill(farbwert1);
strip2.fill(farbwert2);
strip3.fill(farbwertd);
strip1.show();
strip2.show();
strip3.show();

 // Ausgabe des Eingabewertes des Potentiometers, der Farbbezeichnung und errechneten Farbwerts (rgb) im Serialmonitor
  Serial.print("Eingabewert1: ");
  Serial.println(eingabewert1);
  Serial.print("Farbe1: ");
  Serial.println(farbe1);
  Serial.print("Farbwert: rgb(");
  Serial.print(r1);
  Serial.print(",");
  Serial.print(g1);
  Serial.print(",");
  Serial.print(b1);
  Serial.println(")");
  Serial.println("----"); 
  Serial.print("Eingabewert2: ");
  Serial.println(eingabewert2);
  Serial.print("Farbe2: ");
  Serial.println(farbe2);
  Serial.print("Farbwert2: rgb(");
  Serial.print(r2);
  Serial.print(",");
  Serial.print(g2);
  Serial.print(",");
  Serial.print(b2);
  Serial.println(")");
  Serial.println("----"); 
  Serial.print("Eingabewertd: ");
  Serial.println(eingabewertd);
  Serial.print("Farbed: ");
  Serial.println(farbed);
  Serial.print("Farbwertd: rgb(");
  Serial.print(rd);
  Serial.print(",");
  Serial.print(gd);
  Serial.print(",");
  Serial.print(bd);
  Serial.println(")");
  Serial.println("-------------");
  
 
//  
//  Serial.println("Eingabewert: "+ eingabewert);
//  Serial.println("Farbe: " + farbe);
//  Serial.print("Farbwert: rgb(" + r);
//  Serial.print(g);
//  Serial.print(b +")");


//  digitalWrite(ledPin, HIGH);  // turn the ledPin on
//  delay(val);                  // stop the program for some time
//  digitalWrite(ledPin, LOW);   // turn the ledPin off
//  delay(val);                  // stop the program for some time
}
 
