//Eingabe vink Pototyp

int potPin1 = 1;            //Potentiometer1 an Pin A1
int potPin2 = 2;            //Potentiometer2 an Pin A2
int eingabewert1 = 0;       // Variable für den durch das Potentiometer1 eingegebenen Wert
int eingabewert2 = 0;       // Variable für den durch das Potentiometer2 eingegebenen Wert
int r1 = 0;                 // Variable für Rot-Wert der zu errechnenden Farbe1
int g1 = 0;                 // Variable für Grün-Wert der zu errechnenden Farbe1
int b1 = 0;                 // Variable für Blau-Wert der zu errechnenden Farbe1
int r2 = 0;                 // Variable für Rot-Wert der zu errechnenden Farbe2
int g2 = 0;                 // Variable für Grün-Wert der zu errechnenden Farbe2
int b2 = 0;                 // Variable für Blau-Wert der zu errechnenden Farbe2
String farbe1 = "keine";    // Variable für die Bennenung der errechneten Farbe1
String farbe2 = "keine";    // Variable für die Bennenung der errechneten Farbe2
int multi1 = 0;             // Variable zur Multipilizierung der Farbschritte
int multi2 = 0;             // Variable zur Multipilizierung der Farbschritte

void setup() {
  Serial.begin(9600); // Starte Serialmonitor
}

void loop() {
  eingabewert1 = analogRead(potPin1)/ 4;    // Eingabewert vm Potentiometer erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  eingabewert2 = analogRead(potPin2)/ 4;    // Eingabewert vm Potentiometer erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
  multi1 = eingabewert1 - 1;                  // Die Variable multi wird benutzt, um die Anzahl der Annäherungsschritte an die nächste Farbe zu bestimmen
  multi2 = eingabewert2 - 1;                  // Die Variable multi wird benutzt, um die Anzahl der Annäherungsschritte an die nächste Farbe zu bestimmen
if(eingabewert1 == 0){
   r1 = 0;
   g1 = 0;
   b1 = 0;
   farbe1 = "keine";
  }
  if(eingabewert1 == 1){
   r1 = 151;
   g1 = 201;
   b1 = 124;
   farbe1 = "gruen";
  }
  if(eingabewert1 > 1 && eingabewert1 < 128){
   r1 = 151 + (multi1 * 0.832);                  // Die Faktoren, die mit multi multipliziert werden wurden errechnet: Farbwertabstand = (Farbwert der nächsten Farbe - Farbe der vorangegangenen Farbe); Faktor = (Farbwertabstand / 125)
   g1 = 201 + (multi1 * 0.088);
   b1 = 124 + (multi1 * 0.6);
   farbe1 = "zwischen gruen und gelb";
  }
  if(eingabewert1 == 128){
   r1 = 255;
   g1 = 212;
   b1 = 199;
   farbe1 = "gelb";
  }
   if(eingabewert1 > 128 && eingabewert1 < 255){
   r1 = 255;
   g1 = 212 - (multi1 * 0.552);
   b1 = 199 - (multi1 * 0.704);
   farbe1 = "zwischen gelb und rot";
  }
  if(eingabewert1 == 255){
   r1 = 255;
   g1 = 143;
   b1 = 111;
   farbe1 = "rot";
  }

   if(eingabewert2 == 0){
   r2 = 0;
   g2 = 0;
   b2 = 0;
   farbe2 = "keine";
  }
  if(eingabewert2 == 1){
   r2 = 151;
   g2 = 201;
   b2 = 124;
   farbe2 = "gruen";
  }
  if(eingabewert2 > 1 && eingabewert2 < 128){
   r2 = 151 + (multi2 * 0.832);                  // Die Faktoren, die mit multi multipliziert werden wurden errechnet: Farbwertabstand = (Farbwert der nächsten Farbe - Farbe der vorangegangenen Farbe); Faktor = (Farbwertabstand / 125)
   g2 = 201 + (multi2 * 0.088);
   b2 = 124 + (multi2 * 0.6);
   farbe2 = "zwischen gruen und gelb";
  }
  if(eingabewert2 == 128){
   r2 = 255;
   g2 = 212;
   b2 = 199;
   farbe2 = "gelb";
  }
   if(eingabewert2 > 128 && eingabewert2 < 255){
   r2 = 255;
   g2 = 212 - (multi2 * 0.552);
   b2 = 199 - (multi2 * 0.704);
   farbe2 = "zwischen gelb und rot";
  }
  if(eingabewert2 == 255){
   r2 = 255;
   g2 = 143;
   b2 = 111;
   farbe2 = "rot";
  }

 // Ausgabe des Eingabewertes des Potentiometers, der Farbbezeichnung und errechneten Farbwerts (rgb) im Serialmonitor
  Serial.print("Eingabewert1: ");
  Serial.println(eingabewert1);
  Serial.print("Farbe1: ");
  Serial.println(farbe1);
  Serial.print("Farbwert1: rgb(");
  Serial.print(r1);
  Serial.print(",");
  Serial.print(g1);
  Serial.print(",");
  Serial.print(b1);
  Serial.println(")");
  Serial.println("---");
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
 
