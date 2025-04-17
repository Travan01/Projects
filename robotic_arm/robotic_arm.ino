#include <Servo.h>

Servo base;  
Servo link1;
Servo link2;
Servo claw;
void setup() {
 base.attach(4);
 link1.attach(5);
 link2.attach(6);
 claw.attach(7);
}

void loop() {
  link1.write(30);//first arm down
  link2.write(30);// second arm down
  delay(100);
  claw.write(180);// open the claw
  delay(1000);
  claw.write(-180);//close claw
  delay(500);
  link1.write(-30);// first arm up to original position
  base.write(90); //rotate the whole arm 90 degrees
  delay(500);
  link1.write(30);// first arm down
  claw.write(180);// open the claw
  delay(1000);
  claw.write(-180);// close the claw
  delay(500);
  link1.write(-30);//first arm up
  link2.write(-30);// second arm up
  delay(500);
  base.write(-90);//rotate the whole arm bark to original position
  
}
