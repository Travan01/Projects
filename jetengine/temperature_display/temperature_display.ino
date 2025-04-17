#include "max6675.h" 
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_Sensor.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 // Use K type Thermocouple
#define OLED_RESET -1
 Adafruit_SH1106 display(OLED_RESET);
 
// Temperature Sensor1
int thermo1D0 = 4; // so
int thermo1CS = 5; 
int thermo1CLK = 6; // sck
float temp1 = 0; 
MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1D0); 
 
 
// Temperature Sensor2
int thermo2D0 = 8; // so
int thermo2CS = 9; 
int thermo2CLK = 10; // sck
float temp2 = 0; 
MAX6675 thermocouple2(thermo2CLK, thermo2CS, thermo2D0); 
 
 
// Temperature Sensor3
int thermo3D0 = 11; // so
int thermo3CS = 12; 
int thermo3CLK = 13; // sck
float temp3 = 0; 
MAX6675 thermocouple3(thermo3CLK, thermo3CS, thermo3D0);
 
void setup()
{
  Serial.begin(9600); 
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(2000);
    display.clearDisplay();
  display.setTextColor(WHITE);
}
 
void loop()
{
  temp1 = thermocouple1.readCelsius(); 
  delay(100);
  temp2 = thermocouple2.readCelsius();
  delay(100);
  temp3 = thermocouple3.readCelsius();
  delay(100);
    //clear display
  display.clearDisplay();
 
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Inlet: ");
  display.setTextSize(2);
  display.setCursor(38,0);
  display.print(temp1);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
 
// temperature sensor 2
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("C.Ch : ");
  display.setTextSize(2);
  display.setCursor(38,20);
  display.print(temp2);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
 
 
  // temperature sensor 3
  display.setTextSize(1);
  display.setCursor(0,40);
  display.print("Exit: ");
  display.setTextSize(2);
  display.setCursor(38,40);
  display.print(temp3);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
 
 
  display.setTextSize(1);
  display.setCursor(0,57);
  display.print(" Travan Systems ");
 display.display();
  
}
