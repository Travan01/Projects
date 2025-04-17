#include "Adafruit_FONA.h"
#include <TinyGPS++.h>
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
#define FONA_RX 8
#define FONA_TX 7
#define FONA_RST 11
// this is a large buffer for replies
char replybuffer[255];
char message[141];
String commands="";
String  YourArduinoData="";
#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
// HardwareSerial *fonaSerial = &Serial;

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
// Use this one for FONA 3G
//Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

void setup() {

  Serial.begin(GPSBaud);
  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  pinMode(13,1);
  // make it slow so its easy to read!
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));

  // Print SIM card IMEI number.
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("SIM card IMEI: "); Serial.println(imei);
  }

  fonaSerial->print("AT+CNMI=2,1\r\n");  //set up the FONA to send a +CMTI notification when an SMS is received

  Serial.println("FONA Ready");
}

  
char fonaNotificationBuffer[64];          //for notifications from the FONA
char smsBuffer[250];

void loop() {
    getloc();
    
  char* bufPtr = fonaNotificationBuffer;  
  
  if (fona.available())     
  {
    int slot = 0;          
    int charCount = 0;
    //Read the notification into fonaInBuffer
    do  {
      *bufPtr = fona.read();
      Serial.write(*bufPtr);
      delay(1);
    } while ((*bufPtr++ != '\n') && (fona.available()) && (++charCount < (sizeof(fonaNotificationBuffer)-1)));
    
    *bufPtr = 0;

   
    if (1 == sscanf(fonaNotificationBuffer, "+CMTI: " FONA_PREF_SMS_STORAGE ",%d", &slot)) {
      Serial.print("slot: "); Serial.println(slot);
      
      char callerIDbuffer[32];  //we'll store the SMS sender number in here
      
   
      if (! fona.getSMSSender(slot, callerIDbuffer, 31)) {
        Serial.println("Didn't find SMS message in slot!");
      }
      Serial.print(F("FROM: ")); Serial.println(callerIDbuffer);

        // Retrieve SMS value.
        uint16_t smslen;
        if (fona.readSMS(slot, smsBuffer, 250, &smslen)) { // pass in buffer and max len!
          Serial.println(smsBuffer);
          commands=smsBuffer;
          Serial.println(commands);
          if(commands=="get loc"){
            digitalWrite(13,1);
          
             if (!fona.sendSMS(callerIDbuffer, message)) {
                Serial.println(F("Failed"));
                } else {
             Serial.println(F("Sent!"));
               digitalWrite(13,0);
                 }
          
            
          }
          if (fona.deleteSMS(slot)) {

       Serial.println(F("OK!"));
      }
      else {
      Serial.println("Deleting Smas from devvice");
      
      Serial.print(F("Couldn't delete SMS in slot ")); Serial.println(slot);
        fona.print(F("AT+CMGD=?\r\n"));
      }
            
          }
            if (fona.deleteSMS(slot)) {

       Serial.println(F("OK!"));
      }
      else {
      Serial.println("Deleting Smas from devvice");
      
      Serial.print(F("Couldn't delete SMS in slot ")); Serial.println(slot);
        fona.print(F("AT+CMGD=?\r\n"));
      }
          
        }

      
    }
  }

  void getloc(){
     // This sketch displays information every time a new sentence is correctly encoded.
  if (Serial.available() > 0)
    if (gps.encode(Serial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
    
 
    
   
  }
  void  displayInfo(){
    Serial.println("Location");
    
    Serial.print(F("_Location---"));
    Serial.print(gps.location.lat(), 10);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 10);
    Serial.print(F("_______Date"));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
    Serial.print(F("--------"));
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.println();
    
//   char TempString[10];  //  Hold The Convert Data
//   double val=gps.location.lat();
//    dtostrf(val,3,10,TempString);
// // dtostrf( [doubleVar] , [sizeBeforePoint] , [sizeAfterPoint] , [WhereToStoreIt] )
//String    YourArduinoData = String(TempString); 
//Serial.println(YourArduinoData);
   char latitude[18];
   char longitude[18];
   dtostrf(gps.location.lat(),8,7,latitude);
   dtostrf(gps.location.lng(),8,7,longitude);
   YourArduinoData = ("https://www.google.com/maps/place/"+ String(latitude) + "," + String(longitude)); 
   YourArduinoData.toCharArray(message, 141);
   
   
  }
