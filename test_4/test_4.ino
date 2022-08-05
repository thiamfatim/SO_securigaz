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
  Serial.begin(19200);
  SIM900.begin(19200);
  delay(1000);
  // passer l'appel telephonique
  //callSomeone();
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

 if (gaz<150) // PAs de detection de gaz
  {
    noTone(buzzerPin);
  
    digitalWrite(ledred, LOW);
  delay(100);
  }
  else 
  { // Cas d'une detection de gaz 
    
      // 1 ER CAS 
      if(gaz>=200){ 
      tone(buzzerPin,1000 );
      digitalWrite(ledred, HIGH);
      Serial.println("le gaz est detecté");
 
    //1er SMS
    
 
      SIM900.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1 second
      SIM900.println("AT+CMGS=\"+22374053304\""); // Replace x with mobile number
      delay(100);
      SIM900.println("ATTENTION IL Y'A FUITE DE GAZ");// The SMS text you want to send
      delay(100);
      SIM900.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
      delay(100); 
      SIM900.println();
      delay(5000); 
      //delay(100);
      }

      // 2 eme Cas 
      if(gaz>=250){
      
      //2eme SMS
      
    
       SIM900.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
     delay(100);  // Delay of 1 second
     SIM900.println("AT+CMGS=\"+22370897181\""); // Replace x with mobile number
     delay(100);
     SIM900.println("ATTENTION IL Y'A FUITE DE GAZ.");// The SMS text you want to send
     delay(100);
     SIM900.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
     delay(100); 
     SIM900.println();
    delay(5000); 
     //delay(100);
  }

   // 3 eme Cas 
   if (gaz>=275){
      
      //3 eme SMS

       SIM900.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
       delay(1000);  // Delay of 1 second
     SIM900.println("AT+CMGS=\"+22373451676\""); // Replace x with mobile number
     delay(100);
     SIM900.println("ATTENTION IL Y'A FUITE DE GAZ");// The SMS text you want to send
     delay(100);
     SIM900.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
     delay(100); 
     SIM900.println();
    delay(5000); 
     delay(10000);
     
    //PASSER APPEL

     SIM900.println("ATD +22370897181;");
     delay(100);
    SIM900.println();
  
 // Lappel ne peut durer que 30 secondes
 // Vous pouvez modifier la durée de l'appel téléphonique dans le délai

  delay(30000);
  // commande dangerous gaz pour raccrocher
  SIM900.println("Dangerous gaz"); // hang up
      
     }
     
    }
   
  
  
        
}
