/*
||  Demonstrates the simple use of the matrix Keypad library.
The LED circuit:
 * + pin of Red LED - to digital Pin 10
 * + pin of Green LED - to digital Pin 11
 * Ground pin - GND pin of arduino

**********************************
The Keypad circuit:
 * Row-1 pin to digital pin 0
 * Row-2 pin to digital pin 1
 * Row-3 pin to digital pin 2
 * Row-4 pin to digital pin 3
 * Column-1 pin to digital pin 4
 * Column-2 pin to digital pin 5
 * Column-3 pin to digital pin 6
 * Column-4 pin to digital pin 7
***********************************
*/
#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h>   //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

Password password = Password( "1602" );  //THE PASSWORD DECLARATION LINE-------------------------------------//

char PASS = 10;  //Green LED as 'PASS'
char FAIL = 11;  //Red LED as 'FAIL'
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','C'},          //keypad's first Row key names
  {'4','5','6','L'},          //keypad's second Row key names
  {'7','8','9','M'},          //keypad's third Row key names
  {'*','0','#','E'}           //keypad's fourth Row key names
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Keypad

//=======================end of declarations======================// 

void setup(){
  keypad.addEventListener(keypadEvent); //add an event listener for the keypad
  pinMode(PASS,OUTPUT); // GreenLED
  pinMode(FAIL,OUTPUT); // RedLED
  Serial.begin(9600);   
  delay(10);            //wait 10ms for initiating Serial module
  digitalWrite(PASS,LOW);  //Initially OFF the PASS LED
  digitalWrite(FAIL,HIGH);  //Initially ON the FAIL LED
  Serial.print("Welcome Instructables!...|");            //Print text
  Serial.println("Keypad project by:- Sensational_Leo"); //print text
  Serial.println("Keypad test- ENTER THE PASSWORD");    //print text
}
//======================end of setup======================//

void loop(){
  keypad.getKey(); //Get updated with the keys pressed
}

//=======================end of loop======================//

void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
  Serial.println("PASSWORD: ");
  Serial.print(eKey);
  switch (eKey){
    case 'L': checkPassword(); break;
    case 'C': password.reset(); break;
    default: password.append(eKey);
     }
  }
}
//========================end of Password enter=================//

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success...| you are welcome!");
    //Add code to run if the password works
    digitalWrite(PASS,HIGH);  //Green LED ON
    digitalWrite(FAIL,LOW);   //Red LED OFF
   }
  else{
    Serial.println("Wrong");
    //add code to run if the password did not work
    Serial.println("Sorry I could not Recognize you...");
    digitalWrite(PASS,LOW);    //Green LED OFF
    digitalWrite(FAIL,HIGH);   //Red LED ON
  }
}
//=========================end of password validation================//
//=================***========||==END OF PROJECT==||======***========//
