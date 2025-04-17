#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Servo.h>
Servo myservo;
int pos = 0;
int basic;
int c;
Adafruit_BMP280 bmp;
void setup() {
  Serial.begin(9600);
  myservo.attach(9); 
  //while ( !Serial ) delay(100);   // wait for native usb
  //Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
   
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    
}

void loop() {
    /*Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");*/

    /*Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");*/
    
    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.15)); // Adjusted to local forecast!
    Serial.println(" m");
   
    //Serial.println();
    delay(2000);
   while (Serial.available()>0){
      //read altitude value from serial monitor 
      Serial.setTimeout(1500);
     basic = round ( Serial.parseInt());
    }
    delay(250);
    c = floor( bmp.readAltitude(1013.15));
    delay(250);
      // check if the read value is greater than than the current sensor reading
  if(c >= basic ){//if it is, deploy servo
      for (pos = 0; pos <= 180; pos += 180) { 
    myservo.write(pos);              
    delay(500); 
      }
    } 
  //  else{for (pos = 0; pos <= 0; pos += 0){myservo.write(pos); delay(500);}}
}
