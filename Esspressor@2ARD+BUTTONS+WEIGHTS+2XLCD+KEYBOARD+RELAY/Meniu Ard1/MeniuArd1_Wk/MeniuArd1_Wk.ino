#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>



// define pins for weight counters (DT & SCK) x 4 in total 8 pins
#define DT 10
#define SCK 11
#define DT1 9
#define SCK1 12
#define DT2 A2
#define SCK2 A3
#define DT3 A6
#define SCK3 A7



LiquidCrystal_I2C lcd(0x27, 20, 4);

int servoPin = 3;

Servo Servo1;

//define variables for weight counter
long count = 0;
float val = 0;
long sample = 0;
long count1 = 0;
float val1 = 0;
long sample1 = 0;




//functions for storing in memory the scale factors
template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  int i;
  for (i = 0; i < sizeof(value); i++)
    EEPROM.write(ee++, *p++);
  //return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
  byte* p = (byte*)(void*)&value;
  int i;
  for (i = 0; i < sizeof(value); i++)
    *p++ = EEPROM.read(ee++);
  return value;
}



// define variables for buttons HIGH and LOW


//flags

void working() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Order in progress");
  loop();

}





void setup() {
  // put your setup code here, to run once:

  //define serial communication and baud rate
  Serial.begin(9600);
  Servo1.attach(servoPin);
  Servo1.write(0);


  //weight counter define pins
  pinMode (SCK, OUTPUT);



  //initiate lcd screen
  lcd.backlight();
  lcd.init();


  // define charachteristics of the variables
  pinMode (2, INPUT_PULLUP);
  pinMode (4, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  pinMode (6, INPUT_PULLUP);
  pinMode (7, INPUT_PULLUP);
  pinMode (8, INPUT_PULLUP);

  // read values for counter weights last calibration:
  val = EEPROM_readAnything(10, val);
  sample = EEPROM_readAnything (25, sample);
  count = EEPROM_readAnything (34, count);
  val1 = EEPROM_readAnything (50, val1);
  sample1 = EEPROM_readAnything (80, sample1);
  count1 = EEPROM_readAnything(94, count1);



}


void loop() {
  // put your main code here, to run repeatedly:/
  //lcd.clear();
  //  count=readCount(DT,SCK);
  //  int w=(((count-sample)/val)-2*((count-sample)/val));
  //  lcd.print (w);


  //buttons
  int button1 = digitalRead(2);
  int button2 = digitalRead(4);
  int button3 = digitalRead(5);
  int button4 = digitalRead(6);
  int button5 = digitalRead(7);
  int button6 = digitalRead(8);



  /*

    //read counter weights
    count= readCount();
    int w=(((count-sample)/val)-2*((count-sample)/val));
    //Serial.print("weight:");
    //Serial.print((int)w);
    //Serial.println("g");
    lcd.setCursor(0,0);
    lcd.print("Weight            ");
    lcd.setCursor(0,1);
    lcd.print(w);
    lcd.print("g             ");

  */


  if (button1 == LOW  && button3 == HIGH && button4 == HIGH) {

    delay (500);
    int x = 1;
    char str[1];
    itoa(x, str, 10);
    Serial.write(str, 1);
    //Serial.print(x);
    working();

  }


  if (button2 == LOW) {


    delay (50);
    int x = 2;
    char str[1];
    itoa(x, str, 10);
    Serial.write(str, 1);
    working();

  }

  if (button3 == LOW && button1 == HIGH) {

    //read counter
    count = readCount(DT, SCK);
    int w = (((count - sample) / val) - 2 * ((count - sample) / val));
    lcd.clear();
    lcd.print("Counter:");
    lcd.print(w);
    delay(3000);
    if ( w > 50) {



      delay (500);
      int x = 3;
      char str[2];
      itoa(x, str, 10);
      Serial.write(str, 2);
      working();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Adauga sirop Button3");
      delay(4000);
    }
  }

  if (button4 == LOW && button1 == HIGH) {
    count1 = readCount(DT1, SCK1);
    int w = (((count1 - sample1) / val1) - 2 * ((count1 - sample1) / val1));
    lcd.print(w);
    delay(3000);
    delay(3000);
    if ( w > 20) {
      lcd.print(w);
      delay (500);
      int x = 4;
      char str[1];
      itoa(x, str, 10);
      Serial.write(str, 1);
      working();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Adauga sirop Buton4");
      delay(4000);
    }
  }




  //serial commands for servo which are universal for all


  if (Serial.available() > 0) {
    int  y = Serial.read();
    //Serial.flush();
    if ( y == 48 ) {
      Servo1.write(180);
      delay(1000);
      //Serial.print("Am1 primit:  ");
      //Serial.print(y);
      y = 0;

    } else if (y == 57) {
      Servo1.write(0);
      delay(1000);
      //Serial.print("Am5 primit:  ");
      //Serial.print(y);


    }
  }

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>calibrate each weigth counter
  if (button1 == LOW && button3 == LOW) {
    calibrate(34, 10, 25, DT, SCK, val, sample, count);
  }

  if (button1 == LOW && button4 == LOW) {
    calibrate(94, 50, 80, DT1, SCK1, val1, sample1, count1);
  }




}
