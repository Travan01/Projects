const int injectorPin = 2; // Pin connected to the fuel injector
const int sparkPlugPin = 3; // Pin connected to the spark plug
# define potpin A0
# define highms 500
# define lowms 20
float pot=0;
float total=0;
float ondelay=0;
float offdelay=0;

void setup() {
  pinMode(injectorPin, OUTPUT);
  pinMode(sparkPlugPin, OUTPUT);
  pinMode(potpin, INPUT);
  total= highms-lowms;
}

void loop() {
  pot= analogRead(potpin);
  pot/=50.0;
  if(pot>1) pot=1;
  if (pot<0.04) pot=0.04;
  offdelay= total*pot*pot;
  ondelay= total*pot - offdelay;
  digitalWrite(injectorPin, HIGH); // Activate the fuel injector
  delay(ondelay); // Wait for the specified delay time
  digitalWrite(sparkPlugPin, HIGH); // Activate the spark plug
  delay(ondelay); // Wait for the specified delay time
  digitalWrite(injectorPin, LOW); // Deactivate the fuel injector
  digitalWrite(sparkPlugPin, LOW); // Deactivate the spark plug
  delay(offdelay); // Wait for the specified delay time
}
