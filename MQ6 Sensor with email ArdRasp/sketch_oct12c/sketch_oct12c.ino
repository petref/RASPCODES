#define MQ6pin (0)

int sensorValue;  //variable to store sensor value

void setup()
{
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // allow the MQ-6 to warm up
}

void loop()
{
  sensorValue = analogRead(MQ6pin); // read analog input pin 0
  
  
  Serial.write(sensorValue);
  

  
 
  delay(2000); // wait 2s for next reading
}
