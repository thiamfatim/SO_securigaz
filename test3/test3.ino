 #include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);
 const int buzzerPin = 11;
const int captgaz = A2;
int D0 = 9;
int ledred = 2;
int gaz;
int Gaz;
void setup() 
{
  pinMode(captgaz, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(D0, INPUT);

  pinMode(captgaz, INPUT);
  Serial.begin(9600);
  SIM900.begin(9600);
  delay(1000);
}

void loop() 
{
  Gaz=digitalRead(D0);
  gaz=analogRead(captgaz);
  Serial.print("A :");
  Serial.println(gaz);
  Serial.print("D :");
  Serial.println(Gaz);
  delay(100);

  if (gaz>100)
  {
    delay(1000);
    if(gaz>=200){
    
      SIM900.println("ATDxxxxxxxxx;"); // ATDxxxxxxxxxx; semicolon should be at the last ;AT command that follows UART protocol;
   tone(buzzerPin,1000 );
    digitalWrite(ledred, HIGH);
    Serial.print("le gaz est detecté");
    
       SIM900.println("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     SIM900.print("AT+CMGS=\"+22370105882,\"+22370105882\\"""); // Replace x with mobile number
     delay(100);
     SIM900.println("ATTENTION IL Y'A FUITE DE GAZ");// The SMS text you want to send
     delay(100);
     SIM900.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
     delay(100); 
     SIM900.println();
    delay(5000); 
     //delay(100);
     
    
  }
  else
  {

    noTone(buzzerPin);
  
    digitalWrite(ledred, LOW);
  }
}
}
