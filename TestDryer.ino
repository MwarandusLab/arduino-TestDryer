#include <SoftwareSerial.h>

int Led = 4;
int Sms = 0;

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino 

void setup() {
  Serial.begin(9600);
  pinMode(Led, INPUT);

  mySerial.begin(9600);

}

void loop() {
  if(digitalRead(Led) == LOW && Sms == 0){
    Serial.println("Led Turns On");
    mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
    updateSerial();

    mySerial.println("ATD+ +254748613509;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
    updateSerial();
    delay(20000);
    Sms = 1;
  }else if(digitalRead(Led) == HIGH){
    Serial.println("Led Turns Off");
    mySerial.println("ATH"); //hang up
    updateSerial();
    Sms = 0;
    delay(1000);
  }

}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
