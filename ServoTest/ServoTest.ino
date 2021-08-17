    /*
      Servosteuerung ohne Library
    */
    const int potiPin = A2;
    const int servoPin = 8;
    // linker und rechter Anschlag in Grad
    const int minValue = 0;
    const int maxValue = 180;
    void setup()
    {
      pinMode(servoPin,OUTPUT);  
    }
    int getPotiValue() {
      return map(analogRead(potiPin),0,1023,minValue,maxValue);
    }
    void setServo(int pos) {
      int puls = map(pos,minValue,maxValue,400,2400);
      digitalWrite(servoPin,HIGH);
      delayMicroseconds(puls);
      digitalWrite(servoPin,LOW);
      delay(19);
    }
    void loop() 
    { 
      setServo(getPotiValue());
    } 
