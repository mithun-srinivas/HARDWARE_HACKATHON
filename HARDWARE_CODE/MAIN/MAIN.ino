#define LED_BUILTIN 2
boolean BT_cnx = false;
#include <Wire.h>
#include <Adafruit_MLX90614.h>
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

 
void setup() {
  // initialize digital pin 2 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the serial communication:
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");
 
  mlx.begin();
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
    //Serial.print("Ambient = ");
//    Serial.print(mlx.readAmbientTempC());
//    Serial.print("*C\tObject = ");
//    Serial.print(mlx.readObjectTempC()); Serial.println("*C");
//    Serial.print("Ambient = ");
//    Serial.print(mlx.readAmbientTempF());
//    Serial.print("*F\tObject = ");
//    Serial.print(mlx.readObjectTempF()); Serial.println("*F");
//     
    Serial.println();
    delay(20);
}
}
