
#include <Wire.h>
#include<EEPROM.h>
#include <SoftwareSerial.h>
//SoftwareSerial SIM900( RX , TX);



//------------------
#include <Arduino.h>
//#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <ESP8266WiFi.h>


// This call example is for test only, do not use in the production due to quota limit of calls.

const int buzzerPin = D2;
const int captgaz = A0  ;
int S0 = D3;
int ledred = D0;
int gaz;
int Gaz;
int count = 0;

unsigned long sendDataPrevMillis = 0;


//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
//#include <NTPClient.h>
//#include <WiFiUdp.h>
//#include <FirebaseESP32.h>
// Provide the token generation process info.
//#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
//#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "KALANSO_Telefilani"
#define WIFI_PASSWORD "Iw2GgsF8Y0@Z"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAWQCp_oriy9ViN_-waFOW-FvR94l-gNs8"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "thiamfatim7010@gmail.com"
#define USER_PASSWORD "F701058t"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://demosogaz-default-rtdb.firebaseio.com"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config; 

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}



void setup() {

  pinMode(captgaz, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(S0, INPUT);


  Serial.begin(115200);
  //Serial.begin(19200);
  delay(1000);
  // passer l'appel telephonique
  //callSomeone();
  initWiFi();
  //timeClient.begin();

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  //fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */


  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);


}

void loop() {

  //Gaz = digitalRead(S0);
  gaz = analogRead(captgaz);
  Serial.print("Analog :");
  Serial.println(gaz);
  // Serial.print("D :");
  //Serial.println(Gaz);
  delay(100);

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 10000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "Dispositif-1/float", count)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;

    // Write an Float number on the database path test/float
    //  if (Firebase.RTDB.setFloat(&fbdo, "Dispositif-1/float", 0.01 + random(0,100))){

    if (Firebase.RTDB.setFloat(&fbdo, "Dispositif-1/Concentration", gaz)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }


  //DECLENCHEMENT DES ACTIONS///////////////////////

  if (gaz < 150) // PAs de detection de gaz
  {
    noTone(buzzerPin);

    digitalWrite(ledred, LOW);
    delay(100);
  }
  else
  { // Cas d'une detection de gaz

    // 1 ER CAS
    if (gaz >= 170) {
      tone(buzzerPin, 1000 );
      digitalWrite(ledred, HIGH);
      Serial.println("le gaz est detecté");

      //1er SMS


      Serial.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1 second
      Serial.println("AT+CMGS=\"+22370897181\""); // Replace x with mobile number
      delay(100);
      Serial.println("ATTENTION IL Y'A FUITE DE GAZ");// The SMS text you want to send
      delay(100);
      Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
      delay(100);
      Serial.println();
      delay(5000);
      //delay(100);
    }

    // 2 eme Cas
    if (gaz >= 200) {

      //2eme SMS


      Serial.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
      delay(100);  // Delay of 1 second
      Serial.println("AT+CMGS=\"+22370897181\""); // Replace x with mobile number
      delay(100);
      Serial.println("ATTENTION IL Y'A FUITE DE GAZ.");// The SMS text you want to send
      delay(100);
      Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
      delay(100);
      Serial.println();
      delay(5000);
      //delay(100);
    }

    // 3 eme Cas
    if (gaz >= 220) {

      //3 eme SMS

      Serial.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1 second
      Serial.println("AT+CMGS=\"+22370897181\""); // Replace x with mobile number
      delay(100);
      Serial.println("ATTENTION IL Y'A FUITE DE GAZ");// The SMS text you want to send
      delay(100);
      Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
      delay(100);
      Serial.println();
      delay(5000);
      delay(10000);

      //PASSER APPEL

      Serial.println("ATD +22370897181;");
      delay(100);
      Serial.println();

      // Lappel ne peut durer que 30 secondes
      // Vous pouvez modifier la durée de l'appel téléphonique dans le délai

      delay(30000);
      // commande dangerous gaz pour raccrocher
      Serial.println("Dangerous gaz"); // hang up

    }

  }
}





/* if (gaz < 150) // PAs de detection de gaz
  {
   if (Firebase.ready())
   {
     Firebase.RTDB.setInt(&fbdo, "demosogaz/table/concentration",150);

   }
   noTone(buzzerPin);


   digitalWrite(ledred, LOW);
   delay(100);
  }
  else {
   // Cas d'une detection de gaz

   if (Firebase.ready())
   {
     Firebase.RTDB.setInt(&fbdo, "demosogaz/table/concentration",156);
     //Firebase.RTDB.setString(&fbdo, "myparking/place1/time",t);
   }
   //lcd.print("1LB");
  // S1 = 0;
   //analogWrite(led1, 0);
   if (gaz >= 200) {
     if (Firebase.ready())
   {
     Firebase.RTDB.setInt(&fbdo, "demosogaz/table1/concentration",200);
   }
    tone(buzzerPin, 1000 );
     digitalWrite(ledred, HIGH);
     Serial.println("le gaz est detecté");

     //1er SMS


     Serial.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     Serial.println("AT+CMGS=\"+22376299710\""); // Replace x with mobile number
     delay(100);
     Serial.println("ATTENTION IL Y'A FUITE DE GAZ");// The SMS text you want to send
     delay(100);
     Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
     delay(100);
     Serial.println();
     delay(5000);
     //delay(100);

  }
  // 2 eme Cas
      if (gaz >= 250) {
       if (Firebase.ready())
   {
     Firebase.RTDB.setInt(&fbdo, "demosogaz/table2/concentration",250);
   }



     Serial.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
     delay(100);  // Delay of 1 second
     Serial.println("AT+CMGS=\"+22375710051\""); // Replace x with mobile number
     delay(100);
     Serial.println("ATTENTION IL Y'A FUITE DE GAZ.");// The SMS text you want to send
     delay(100);
     Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
     delay(100);
     Serial.println();
     delay(5000);
     //delay(100);
     }

     // 3 eme Cas
     if (gaz >= 275) {
        if (Firebase.ready())
   {
     Firebase.RTDB.setInt(&fbdo, "demosogaz/table3/concentration",275);
   }
   //3 eme SMS

         Serial.print("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     Serial.println("AT+CMGS=\"+22371883108\""); // Replace x with mobile number
     delay(100);
     Serial.println("ATTENTION IL Y'A FUITE DE GAZ");// The SMS text you want to send
     delay(100);
     Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
     delay(100);
     Serial.println();
     delay(5000);
     delay(10000);

     //PASSER APPEL

     Serial.println("ATD +22376299710;");
     delay(100);
     Serial.println();

     // Lappel ne peut durer que 30 secondes
     // Vous pouvez modifier la durée de l'appel téléphonique dans le délai

     delay(30000);
     // commande dangerous gaz pour raccrocher
     Serial.println("Dangerous gaz"); // hang up


     }



  }*/



/*----------------------t----------------------
  void incremente_horloge(struct Horloge *horloge)
  {
  (*horloge).secondes++;
  }
  void stop_horloge(struct Horloge *horloge)
  {
  (*horloge).secondes = 0;
  }
  void save_horloge(struct Horloge h)
  {
  EEPROM.put(adresse_horloge, h);
  }
  void print_horloge(struct Horloge horloge)
  {
  t = horloge.secondes;
  Serial.println(horloge.secondes);
  }
  ISR(TIMER2_OVF_vect)
  {
  if (compteur++ == 125)
  {
    incremente_horloge(&horloge);
    compteur = 0;
  }
  if (compteur2++ == 125)
  {
    incremente_horloge2(&horloge2);
    compteur2 = 0;
  }
  if (compteur3++ == 125)
  {
    incremente_horloge3(&horloge3);
    compteur3 = 0;
  }
  if (compteur4++ == 125)
  {
    incremente_horloge4(&horloge4);
    compteur4 = 0;
  }
  if (timer_5s++ == 125)
  {
    synchronisation = true;
    synchronisation2 = true;
    synchronisation3 = true;
    synchronisation4 = true;
    timer_5s = 0;
  }
  TCNT2 = 6; //réarmement  dans 4ms
  }
  /----------------------t2----------------------
  void incremente_horloge2(struct Horloge2 *horloge2)
  {
  (*horloge2).secondes2++;
  }
  void stop_horloge2(struct Horloge2 *horloge2)
  {
  (*horloge2).secondes2 = 0;
  }
  void save_horloge2(struct Horloge2 h2)
  {
  EEPROM.put(adresse_horloge2, h2);
  }
  void print_horloge2(struct Horloge2 horloge2)
  {
  t2 = horloge2.secondes2;
  Serial.print("la valeur de t2 est : ");
  Serial.println(horloge2.secondes2);
  }
  ----------------------t3----------------------
  void incremente_horloge3(struct Horloge3 *horloge3)
  {
  (*horloge3).secondes3++;
  }
  void stop_horloge3(struct Horloge3 *horloge3)
  {
  (*horloge3).secondes3 = 0;
  }
  void save_horloge3(struct Horloge3 h3)
  {
  EEPROM.put(adresse_horloge3, h3);
  }
  void print_horloge3(struct Horloge3 horloge3)
  {
  t3 = horloge3.secondes3;
  Serial.print("la valeur de t3 est : ");
  Serial.println(horloge3.secondes3);
  }
  //----------------------t4----------------------
  void incremente_horloge4(struct Horloge4 *horloge4)
  {
  (*horloge4).secondes4++;
  }
  void stop_horloge4(struct Horloge4 *horloge4)
  {
  (*horloge4).secondes4 = 0;
  }
  void save_horloge4(struct Horloge4 h4)
  {
  EEPROM.put(adresse_horloge4, h4);
  }
  void print_horloge4(struct Horloge4 horloge4)
  {
  t4 = horloge4.secondes4;
  Serial.print("la valeur de t4 est : ");
  Serial.println(horloge4.secondes4);
  }
*/
