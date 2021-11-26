
 
#define LED_BUILTIN 2
boolean BT_cnx = false;

 
void setup() {
  // initialize digital pin 2 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the serial communication:
  Serial.begin(9600);
  Serial.println(); // blank line in serial ...
  pinMode(41, INPUT); // Setup for leads off detection LO +
  pinMode(40, INPUT); // Setup for leads off detection LO -
  // initialize the serial BT communication:
}
 
void loop() {
  if((digitalRead(40) == 1)||(digitalRead(41) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0 to serial:
    Serial.println(analogRead(A0));
  //Wait a little to keep serial data from saturating
  delay(20);
}
}
