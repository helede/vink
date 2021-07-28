//Eingabe vink Pototyp

int potPin = 2;            //Potentiometer an Pin A2
int eingabewert = 0;       // Variable für den durch das Potentiometer eingegebenen Wert
int r = 0;                 // Variable für Rot-Wert der zu errechnenden Farbe
int g = 0;                 // Variable für Grün-Wert der zu errechnenden Farbe
int b = 0;                 // Variable für Blau-Wert der zu errechnenden Farbe
String farbe = "keine";    // Variable für die Bennenung der errechneten Farbe

void setup() {
  Serial.begin(9600); // Starte Serialmonitor
}

void loop() {
  eingabewert = analogRead(potPin)/ 4;    // Eingabewert vm Potentiometer erfassen und diesen durch folgende Bedingungen in einen Farbwert umwandeln
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

 // Ausgabe des Eingabewertes des Potentiometers, der Farbbezeichnung und errechneten Farbwerts (rgb) im Serialmonitor
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
 


