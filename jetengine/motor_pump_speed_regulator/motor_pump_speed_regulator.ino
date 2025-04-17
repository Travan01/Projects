#define enA 9 
#define in1 6
#define in2 7 
#define enB 10 
#define in3 8
#define in4 12 
#define button 4 
int rotDirection = 0; 
int pressed = false; 

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(button, INPUT);
 // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  }
  
void loop() {
  int potValue = analogRead(A0);// Read potentiometer value 
  int pwmOutput = map(potValue, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
 
 // Read button - Debounce
 if (digitalRead(button) == true) {
  pressed = !pressed; 
  } 
 while (digitalRead(button) == true);
 delay(20);
 // If button is pressed - change rotation direction 
 if (pressed == true & rotDirection == 0) { 
  analogWrite(enB, pwmOutput); // Send PWM signal to L298N Enable pin
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  rotDirection = 1; 
  delay(20); }
 // If button is pressed - change rotation direction 
  if (pressed == false & rotDirection == 1) { 
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in3, LOW);
    rotDirection = 0; 
    delay(20); }
  }
