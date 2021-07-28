
/* Analog Read to LED
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The amount of time the LED will be on and off depends on
 * the value obtained by analogRead(). In the easiest case we connect
 * a potentiometer to analog pin 2.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */

int potPin = 2;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int eingabewert = 0;       // variable to store the value coming from the sensor
int r = 0;
int g = 0;
int b = 0;
String farbe = "keine";

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600); // Starte Serialmonitor
}

void loop() {
  eingabewert = analogRead(potPin)/ 4;    // read the value from the sensor
  if(eingabewert == 0){
   r = 0;
   g = 0;
   b = 0;
   farbe = "keine";
  }
  if(eingabewert == 1){
   r = 151;
   g = 201;
   b = 124;
   farbe = "gruen";
  }
  if(eingabewert > 1 && eingabewert < 128){
   r = 151;
   g = 201;
   b = 124;
   farbe = "zwischen gruen und gelb";
  }
  if(eingabewert == 128){
   r = 255;
   g = 212;
   b = 199;
   farbe = "gelb";
  }
   if(eingabewert > 128 && eingabewert < 255){
   r = 151;
   g = 201;
   b = 124;
   farbe = "zwischen gelb und rot";
  }
  if(eingabewert == 255){
   r = 255;
   g = 143;
   b = 111;
   farbe = "rot";
  }

 
  Serial.print("Eingabewert: ");
  Serial.println(eingabewert);
  Serial.print("Farbe: ");
  Serial.println(farbe);
  Serial.print("Farbwert: rgb(");
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.print(b);
  Serial.println(")");
  Serial.println("-------------");
  delay(1000);
 
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
 


