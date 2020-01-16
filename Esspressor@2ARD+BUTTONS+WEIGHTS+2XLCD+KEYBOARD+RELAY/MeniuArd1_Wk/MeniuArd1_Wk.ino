#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <EEPROM.h>




// define pins for weight counters (DT & SCK) x 4 in total 8 pins
#define DT 10
#define SCK 11
#define DTA 9
#define SCKA 12
#define DT2 A2
#define SCK2 A3
#define DT3 A6
#define SCK3 A7

LiquidCrystal_I2C lcd(0x27, 20, 4);

int servoPin = 3;

Servo Servo1;



// ======================================================= readcounter =========================================================================================
unsigned long readCount(int DTX, int SCKX)
{
  unsigned long count;
  unsigned char i;
  pinMode(DTX, OUTPUT);
  digitalWrite(DTX,HIGH);
  digitalWrite(SCKX,LOW);
  count=0;
  pinMode(DTX, INPUT);
  while(digitalRead(DTX));
  for (i=0;i<24;i++)
  {
    digitalWrite(SCKX,HIGH);
    count=count<<1;
    digitalWrite(SCKX,LOW);
    if(digitalRead(DTX)) 
    count++;
  }
  digitalWrite(SCKX,HIGH);
  count=count^0x800000;
  digitalWrite(SCKX,LOW);
  return(count);
}

//============================ end of counter =======================================



//================================= Calibration function ============================================================================================================================
void calibrate(int memcount, int memval, int memsample, int DTX, int SCKX, float valx, long samplex, long countx)
{

  valx = 0;
  samplex = 0;
  countx = 0;

  
  lcd.clear();
  lcd.print("Calibrating...");
  lcd.setCursor(0,1);
  lcd.print("Please Wait...");
  for(int i=0;i<100;i++)
  {
    countx=readCount(DTX,SCKX);
    samplex+=countx;   
  }
  samplex/=100;
  lcd.clear();
  lcd.print("Put 100g & wait");
  countx=0;
  delay(3000);
  while(countx > 1000)
  {
    countx=readCount(DTX,SCKX);
    countx=samplex-countx;
  
  }
  lcd.clear();
  lcd.print("Please Wait....");
  delay(2000);
  for(int i=0;i<100;i++)
  {
    countx=readCount(DTX,SCKX);
    valx+=samplex-countx;
  
  }
  valx=valx/100.0;
  valx=valx/100.0;        // put here your calibrating weight
  lcd.clear();
  

 
   EEPROM_writeAnything(memval, valx);
   EEPROM_writeAnything(memsample, samplex);
   EEPROM_writeAnything(memcount,countx);
  
 


}
// End of calibration function ++++++++++++++++++++===========================================================================================



//define variables for weight counter
//weight counter1
long count2;
float val;
long sample;

//weight counter2
long count1;
float val1;
long sample1;

//weight counter3
long count3;
float val3;
long sample3;

//weight counter4
long count4;
float val4;
long sample4;



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

void working() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Order in progress");
  loop();

}




//SETUP FUNCTION <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void setup() {
  // put your setup code here, to run once:

  //define serial communication and baud rate
  Serial.begin(9600);
  Servo1.attach(servoPin);
  Servo1.write(0);


  //weight counter define pins
  pinMode (SCK, OUTPUT);
  pinMode (SCKA, OUTPUT);
  pinMode(SCK2, OUTPUT);
  pinMode(SCK3, OUTPUT);


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
  EEPROM_readAnything(10, val);
  EEPROM_readAnything (25, sample);
  EEPROM_readAnything (34, count2);
  EEPROM_readAnything (50, val1);
  EEPROM_readAnything (80, sample1);
  EEPROM_readAnything(94, count1);
  EEPROM_readAnything(104, count3);
  EEPROM_readAnything(110, val3);
  EEPROM_readAnything(115, sample3);
  EEPROM_readAnything(125, count4);
  EEPROM_readAnything(130, val4);
  EEPROM_readAnything(140, sample4);


}

// END SETUP<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// START LOOP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void loop() {
  // put your main code here, to run repeatedly:/
  lcd.clear();

  //buttons
  int button1 = digitalRead(2);
  int button2 = digitalRead(4);
  int button3 = digitalRead(5);
  int button4 = digitalRead(6);
  int button5 = digitalRead(7);
  int button6 = digitalRead(8);

// Button 1 :

  if (button1 == LOW  && button3 == HIGH && button4 == HIGH && button5 == HIGH && button6 == HIGH) {

    delay (500);
    int x = 1;
    char str[1];
    itoa(x, str, 10);
    Serial.write(str, 1);
    //Serial.print(x);
    working();

  }

// Button 2:
  if (button2 == LOW) {


    delay (50);
    int x = 2;
    char str[1];
    itoa(x, str, 10);
    Serial.write(str, 1);
    working();

  }

//Button 3 :
  if (button3 == LOW && button1 == HIGH) {

    //read counter
    count2 = readCount(DT, SCK);
    int w = (((count2 - sample) / val) - 2 * ((count2 - sample) / val));
    lcd.clear();
    lcd.print("Counter:");
    lcd.print(w);
    lcd.print("g  ");
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
      lcd.print("Adauga sirop cantar 1");
      delay(4000);
      w = 0;
      count1 = readCount(DTA, SCKA);
      int w = (((count1 - sample1) / val1) - 2 * ((count1 - sample1) / val1));
    }
  }

//Button4 :
  if (button4 == LOW && button1 == HIGH) {
    count1 = readCount(DTA, SCKA);
    int w = (((count1 - sample1) / val1) - 2 * ((count1 - sample1) / val1));
    lcd.clear();
    lcd.print(w);
    lcd.print("g  ");
    delay(3000);
    if ( w > 50) {
      delay (500);
      int x = 4;
      char str[1];
      itoa(x, str, 10);
      Serial.write(str, 1);
      working();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Adauga sirop cantar 2");
      delay(4000);
      w=0;
      count1 = readCount(DTA, SCKA);
      int w = (((count1 - sample1) / val1) - 2 * ((count1 - sample1) / val1));
      
    }
  }


// Button 5:
  if (button5 == LOW && button1 == HIGH) {
    count1 = readCount(DT2, SCK2);
    int w = (((count3 - sample3) / val3) - 2 * ((count3 - sample3) / val3));
    lcd.clear();
    lcd.print(w);
    lcd.print("g  ");
    delay(3000);
    if ( w > 50) {
      delay (500);
      int x = 5;
      char str[1];
      itoa(x, str, 10);
      Serial.write(str, 1);
      working();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Adauga sirop cantar3");
      delay(4000);
      w=0;
      count1 = readCount(DT2, SCK2);
      int w = (((count3 - sample3) / val3) - 2 * ((count3 - sample3) / val3));
      
    }
  }



  //Button 6:

  
  if (button6 == LOW && button1 == HIGH) {
    count1 = readCount(DT3, SCK3);
    int w = (((count4 - sample4) / val4) - 2 * ((count4 - sample4) / val4));
    lcd.clear();
    lcd.print(w);
    lcd.print("g  ");
    delay(3000);
    if ( w > 50) {
      delay (500);
      int x = 6;
      char str[1];
      itoa(x, str, 10);
      Serial.write(str, 1);
      working();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Adauga sirop cantar4");
      delay(4000);
      w=0;
      count1 = readCount(DT3, SCK3);
      int w = (((count4 - sample4) / val4) - 2 * ((count4 - sample4) / val4));
      
    }
  }



  //serial commands for servo which are universal for all


  if (Serial.available() > 0) {
    int  y = Serial.read();
    //Serial.flush();
    if ( y == 48 ) {
      Servo1.write(180);
      delay(1000);
      y = 0;

    } else if (y == 57) {
      Servo1.write(0);
      delay(1000);
      

    }
  }

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>calibrate each weigth counter
  //calibrate counter1
  if (button1 == LOW && button3 == LOW) {
    calibrate(34, 10, 25, DT, SCK, val, sample, count2);
  }

  //calibrate counter2
  if (button1 == LOW && button4 == LOW) {
    calibrate(94, 50, 80, DTA, SCKA, val1, sample1, count1);
  }

  //calibrate counter3
  if (button1 == LOW && button5 == LOW) {
    calibrate(104, 110, 115, DT2, SCK2, val3, sample3, count3);
  }

  //calibrate counter4
  if (button1 == LOW && button6 == LOW) {
    calibrate(125, 130, 140, DT3, SCK3, val4, sample4, count4);
  }




}
