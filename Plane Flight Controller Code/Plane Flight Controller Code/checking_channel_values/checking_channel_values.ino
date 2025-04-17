#include <Servo.h>
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
int receiver_input_1, receiver_input_2, receiver_input_3, receiver_input_4;
unsigned long timer_1, timer_2, timer_3, timer_4, current_time;
int channel,a;
Servo m1;

void setup ()
{
PCICR |= (1 << PCIE0);                                                    //Set PCIE0 to enable PCMSK0 scan.
  PCMSK0 |= (1 << PCINT0);                                                  //Set PCINT0 (digital input 8) to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT1);                                                  //Set PCINT1 (digital input 9)to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT2);                                                  //Set PCINT2 (digital input 10)to trigger an interrupt on state change.
  PCMSK0 |= (1 << PCINT3);   
  Serial.begin(9600);
}

void loop()
{
  delay(250);
  print_signal();
  

}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ISR(PCINT0_vect){
  current_time = micros();
  //Channel 1=========================================
  if(PINB & B00000001){                                                     //Is input 8 high?
    if(last_channel_1 == 0){                                                //Input 8 changed from 0 to 1.
      last_channel_1 = 1;                                                   //Remember current input state.
      timer_1 = current_time;                                               //Set timer_1 to current_time.
    }
  }
  else if(last_channel_1 == 1){                                             //Input 8 is not high and changed from 1 to 0.
    last_channel_1 = 0;                                                     //Remember current input state.
    receiver_input_1 = current_time - timer_1;                             //Channel 1 is current_time - timer_1.
  }
  
  //Channel 2=========================================
  if(PINB & B00000100 ){                                                    //Is input 10 high?
    if(last_channel_3 == 0){                                                //Input 10 changed from 0 to 1.
      last_channel_3 = 1;                                                   //Remember current input state.
      timer_3 = current_time;                                               //Set timer_3 to current_time.
    }
  }
  else if(last_channel_3 == 1){                                             //Input 10 is not high and changed from 1 to 0.
    last_channel_3 = 0;                                                     //Remember current input state.
   receiver_input_3 = current_time - timer_3;                             //Channel 3 is current_time - timer_3.

  }
 
}

void print_signal()
{ 
  Serial.print(" ");
  Serial.print("Roll");
  if (receiver_input_1 - 1480 < 0)Serial.print(" -> ");
  else if (receiver_input_1 - 1520 >0)Serial.print(" -> ");
  else Serial.print(" -> ");
  Serial.print(receiver_input_1);
  Serial.print("   ");

  Serial.print("Pitch");
  if (receiver_input_3 - 1480 < 0)Serial.print(" -> ");
  else if (receiver_input_3 - 1520 >0)Serial.print(" -> ");
  else Serial.print(" -> ");
  Serial.print(receiver_input_3);

  Serial.println(" ");
}
