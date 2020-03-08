 
#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Keypad.h> // load keypad library

#include <EEPROM.h>

#define relay  A0
#define relay1 A1
#define relay2 A2
#define relay3 A3
#define relay4 A6
#define relay5 3
#define relay6 2




//butons state & counter -  variables for state of the button
int buttonPushCounter1 = 0;
int buttonPushCounter2 = 0;
int lastButtonState1 = 0;
int lastButtonState2 = 0;
int previousButtonCounter1 = 0;
int previousButtonCounter2 = 0;
int machineState = 0;
int x = 0;
int relayState = 0;


//servo flag
int myservo = 0;


//millis count  important for time count when button is pressed and send the signal
unsigned long previousMillis1 = 0;
unsigned long interval = 0;
unsigned long currentmillis = 0;
unsigned long previousMillis2 = 0;



// Menu control variables

int itemNo = 0;

int cursorPosition = 0;

String menuItems[] = {"CafeLatte", "Cappucino", "CleaningTime", "Bidon 1", "Bidon 2", "Bidon 3", "Bidon 4", "Recipient6", "Recipient7", "Recipient8", "Setari", "Despre"};

// submenu 1 control variables

//String SubmenuItem1 [] = {"Pump On", "Pump Off"};

//int subitemNo = 0;

//int subcursorPosition = 1;

// Creates 3 custom characters for the menu display

byte downArrow[8] = {

0b00100, // *

0b00100, // *

0b00100, // *

0b00100, // *

0b00100, // *

0b10101, // * * *

0b01110, // ***

0b00100 // *

};

byte upArrow[8] = {

0b00100, // *

0b01110, // ***

0b10101, // * * *

0b00100, // *

0b00100, // *

0b00100, // *

0b00100, // *

0b00100 // *

};

byte menuCursor[8] = {

B01000, // *

B00100, // *

B00010, // *

B00001, // *

B00010, // *

B00100, // *

B01000, // *

B00000 //

};

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Defining keypad

const byte ROWS = 4; //four rows

const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {

{'1','2','3','A'},

{'4','5','6','B'},

{'7','8','9','C'},

{'*','0','#','D'}

};

// Defining keypad pins on arduino
byte rowPins[ROWS] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



//variables for relay times
int digitCaffeLatte;
int digitCappucino;
int CleaningTime;
int digitSiropBidon1;
int digitSiropBidon2;
int digitSiropBidon3;
int digitSiropBidon4;
int digitSiropBidon5;
int digitSiropBidon6;


void setup() {

// Initializes serial communication
lcd.backlight();
lcd.init();
Serial.begin(9600);


// Initializes and clears the LCD screen
lcd.backlight();

lcd.begin(16, 4);

lcd.clear();

//initialize the relay
pinMode(relay,  OUTPUT);
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
pinMode(relay5, OUTPUT);
pinMode(relay6, OUTPUT);
//pinMode(relay7, OUTPUT);
//pinMode(relay8, OUTPUT);
//pinMode(relay9, OUTPUT);


// Creates the byte for the 3 custom characters

lcd.createChar(0, menuCursor);

lcd.createChar(1, upArrow);

lcd.createChar(2, downArrow);


//reads from EEPROM the value of the caffe latte relay
float f = EEPROM.read(0);
float y = EEPROM.read(85);
float z = EEPROM.read(98);
float u = EEPROM.read(80);
float k = EEPROM.read(105);
float p = EEPROM.read(115);



digitCappucino = (int) y;
digitCaffeLatte = (int) f;
digitSiropBidon1 = (int) z;
digitSiropBidon2 = (int) u;
digitSiropBidon3 = (int) k;
digitSiropBidon4 = (int) p;


//Read from EEPROM the value of the cleaning variable this is the time the servo start, holds and comesback -------!!!!!--------------------------
float m = EEPROM.read(5);
CleaningTime = (int) m;


}

void loop() {





    //Serial.println (subcursorPosition);
        mainMenuDraw();

        drawCursor();

        operateMainMenu();

        


}

// This function will generate the 4 menu items that can fit on the screen. They will change as you scroll through your menu.

//Up and down arrows will indicate your current menu position.

void mainMenuDraw() {

lcd.clear();

lcd.setCursor(1, 0);

lcd.print(menuItems[itemNo]);

lcd.setCursor(1, 1);

lcd.print(menuItems[itemNo + 1 ]);

if (cursorPosition >= 0 and cursorPosition <= 1) {

lcd.setCursor(14, 1);

lcd.print ("D");
lcd.write(byte(2));

}

else if (cursorPosition > 1 and cursorPosition < 10) {

lcd.setCursor(14, 1);
lcd.print ("D");
lcd.write(byte(2));

lcd.setCursor(14, 0);

lcd.print("A");
lcd.write(byte(1));

}

else if (cursorPosition >= 10) {

lcd.setCursor(14, 0);

lcd.print("A");
lcd.write(byte(1));

}

}

// When called, this function will erase the current cursor and redraw it based on the cursorPosition and itemNo variables.

void drawCursor() {

for (int x = 0; x < 1; x++) { // Erases current cursor

lcd.setCursor(0, x);

lcd.print(" ");

}

// When called, this function will determine where the cursor should be
if (cursorPosition == 0 || cursorPosition == 2 || cursorPosition == 4 || cursorPosition == 6 || cursorPosition == 8 || cursorPosition == 10 || cursorPosition == 12 ){

lcd.setCursor (0,0);

lcd.write(byte(0));

}

if (cursorPosition == 1 || cursorPosition == 3 || cursorPosition == 5 || cursorPosition == 7 || cursorPosition == 9 || cursorPosition == 11 ){

lcd.setCursor (0,1);

lcd.write(byte(0));

}


}

void operateMainMenu() {

int activeButton = 0;

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 0: // When button returns as 0 there is no action taken i.e no button pressed.

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HERE WORK WITH SERIAL COM AND RELAYS AND SERVO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




//millis count update:
currentmillis = millis(); //get the current time

if(Serial.available() > 0) {
  x = Serial.read();
  Serial.flush();

  }


relayState = digitalRead(relay);

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> This part starts the first pump, when the button 1 is pressed  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
if (( x == 49 ) && ( relayState == LOW ) && buttonPushCounter1 == previousButtonCounter1)
    {
      buttonPushCounter1++;
      previousMillis1 = currentmillis;
      //Serial.print("  Amajuns ");
      machineState = 1;
  

} else if ( buttonPushCounter1 - previousButtonCounter1 == 1 && (currentmillis - previousMillis1 < (digitCaffeLatte*1000) && machineState == 1)) 
    {
      digitalWrite(relay, HIGH);
      myservo = 1;
   
      x = 0;  // make the serial read variable back to 0 so it will not reset the previous if --- !!!! VERRY VERRY IMPORTANT STUPID!
  //Serial.print("  Primul Else  ");
  



} else if(( currentmillis - previousMillis1 < digitCaffeLatte*1005)  && ( myservo == 1 ) && machineState == 1)
    {
      int y = 0;
      char str1[1];
      itoa(y, str1, 10);
      Serial.write(str1,1);
      Serial.flush();
      delay(CleaningTime * 1000);
      myservo = 2;
      

      
      
} else if (machineState == 1 && (currentmillis - previousMillis1 < digitCaffeLatte * 1010 + (CleaningTime * 1000)))  
    {
      digitalWrite(relay, LOW);    
      myservo=0;
      
      
} else if (machineState == 1 && (currentmillis - previousMillis1 < digitCaffeLatte * 1012 + (CleaningTime * 1000 + 2000)))  
    {      
      int z = 9;
      char str1[1];
      itoa(z,str1,10);
      Serial.write(str1,1);
      previousButtonCounter1 = buttonPushCounter1;
      machineState = 0;
 
       
  loop();


}


// this is for button2
relayState = digitalRead(relay1);

if (( x == 50 ) && ( relayState == LOW ) && buttonPushCounter1 == previousButtonCounter1)
    {
      buttonPushCounter1++;
      previousMillis1 = currentmillis;
      machineState = 2;
  

} else if ( buttonPushCounter1 - previousButtonCounter1 == 1 && (currentmillis - previousMillis1 < (digitCappucino*1000) && machineState == 2)) 
    {
      digitalWrite(relay1, HIGH);
      myservo = 1;
   
      x = 0;  // make the serial read variable back to 0 so it will not reset the previous if --- !!!! VERRY VERRY IMPORTANT STUPID!
 
  



} else if(( currentmillis - previousMillis1 < digitCappucino*1005)  && ( myservo == 1 ) && machineState == 2)
    {
      //open servo start cleaning == asume position 160degrees
      int y = 0;
      char str1[1];
      itoa(y, str1, 10);
      Serial.write(str1,1);
      Serial.flush();
      delay(CleaningTime * 1000);
      myservo = 2;
      

      
      
} else if (machineState == 2 && (currentmillis - previousMillis1 < digitCappucino * 1010 + (CleaningTime * 1000)))  
    {
      digitalWrite(relay1, LOW);    
      myservo=0;
      
      
} else if (machineState == 2 && (currentmillis - previousMillis1 < digitCappucino * 1012 + (CleaningTime * 1000 + 2000)))  
    {      
      //close servo ==== asume position 0
      int z = 9;
      
      char str1[1];
      itoa(z,str1,10);
      Serial.write(str1,1);
      previousButtonCounter1 = buttonPushCounter1;
      machineState = 0;
 
       
  loop();


}



// this is for button3

relayState = digitalRead(relay2);

if (( x == 51 ) && ( relayState == LOW ) && buttonPushCounter1 == previousButtonCounter1)
    {
      buttonPushCounter1++;
      previousMillis1 = currentmillis;
      machineState = 3;
  

} else if ( buttonPushCounter1 - previousButtonCounter1 == 1 && (currentmillis - previousMillis1 < (digitSiropBidon1*1000) && machineState == 3)) 
    {
      digitalWrite(relay2, HIGH);
      myservo = 1;
   
      x = 0;  // make the serial read variable back to 0 so it will not reset the previous if --- !!!! VERRY VERRY IMPORTANT STUPID!
  //Serial.print("  Primul Else  ");
  



} else if (machineState == 3 && (currentmillis - previousMillis1 < digitSiropBidon1 * 1010))  
    {
      digitalWrite(relay2, LOW);    
      myservo=0;
      previousButtonCounter1 = buttonPushCounter1;
      machineState = 0;
 
      loop();    
} 

// this is for button4 =====================================================================

relayState = digitalRead(relay3);

if (( x == 52 ) && ( relayState == LOW ) && buttonPushCounter1 == previousButtonCounter1)
    {
      buttonPushCounter1++;
      previousMillis1 = currentmillis;
      machineState = 4;
  

} else if ( buttonPushCounter1 - previousButtonCounter1 == 1 && (currentmillis - previousMillis1 < (digitSiropBidon2*1000) && machineState == 4)) 
    {
      digitalWrite(relay3, HIGH);
      myservo = 1;
   
      x = 0;  // make the serial read variable back to 0 so it will not reset the previous if --- !!!! VERRY VERRY IMPORTANT STUPID!
  //Serial.print("  Primul Else  ");
  



} else if (machineState == 4 && (currentmillis - previousMillis1 < (digitSiropBidon2 * 1010)))  
    {
      digitalWrite(relay3, LOW);    
      previousButtonCounter1 = buttonPushCounter1;
      machineState = 0;
 
       
  loop();
      
}


// this is for button5 =====================================================================

relayState = digitalRead(relay5);

if (( x == 54 ) && ( relayState == LOW ) && buttonPushCounter1 == previousButtonCounter1)
    {
      buttonPushCounter1++;
      previousMillis1 = currentmillis;
      machineState = 5;
  

} else if ( buttonPushCounter1 - previousButtonCounter1 == 1 && (currentmillis - previousMillis1 < (digitSiropBidon3*1000) && machineState == 5)) 
    {
      digitalWrite(relay5, HIGH);
      
   
      x = 0;  // make the serial read variable back to 0 so it will not activate the previous condition --- !!!! VERRY VERRY IMPORTANT STUPID!
  //Serial.print("  Primul Else  ");
  



} else if (machineState == 5 && (currentmillis - previousMillis1 < (digitSiropBidon3 * 1010)))  
    {
      digitalWrite(relay5, LOW);    
      previousButtonCounter1 = buttonPushCounter1;
      machineState = 0;
 
       
  loop();
      
} 



// this is for button6 =====================================================================

relayState = digitalRead(relay6);

if (( x == 55 ) && ( relayState == LOW ) && buttonPushCounter1 == previousButtonCounter1)
    {
      buttonPushCounter1++;
      previousMillis1 = currentmillis;
      machineState = 6;
  

} else if ( buttonPushCounter1 - previousButtonCounter1 == 1 && (currentmillis - previousMillis1 < (digitSiropBidon4*1000) && machineState == 6)) 
    {
      digitalWrite(relay5, HIGH);
      
   
      x = 0;  // make the serial read variable back to 0 so it will not activate the previous condition --- !!!! VERRY VERRY IMPORTANT STUPID!
  //Serial.print("  Primul Else  ");
  



} else if (machineState == 6 && (currentmillis - previousMillis1 < (digitSiropBidon4 * 1010)))  
    {
      digitalWrite(relay6, LOW);    
      previousButtonCounter1 = buttonPushCounter1;
      machineState = 0;
 
       
  loop();
      
}


  
/*  
  switch(x) {

    case 49:
    lcd.clear();
    lcd.print("CaffeLatte");
    digitalWrite (relay, HIGH);
    delay(3000);
    lcd.print("am terminat");
    digitalWrite (relay, LOW);
    lcd.clear();
    
    loop();
    

    
    default:
    //digitalWrite (relay,HIGH);

  break;
  
}
*/  



break;

case 1: // This case will execute if the "right" button is pressed

button = 0;

switch (cursorPosition) { // The case that is selected here is dependent on which menu page you are on and where the cursor is.

case 0:

menuItem1();

break;

case 1:

menuItem2();

break;

case 2:

menuItem3();

break;

case 3:

menuItem4();

break;

case 4:

menuItem5();

break;

case 5:

menuItem6();

break;

case 6:

menuItem7();

break;

case 7:

menuItem8();

break;

case 8:

menuItem9();

break;

case 9:

menuItem10();

break;

case 10:

menuItem11();

break;

case 11:

menuItem12();

break;

}

activeButton = 1;

mainMenuDraw();

drawCursor();

break;

case 2: // This case will execute if the "up" button is pressed

button = 0;

if (cursorPosition == 2 || cursorPosition == 4 || cursorPosition == 6 || cursorPosition == 8 || cursorPosition == 10 ){

itemNo = itemNo - 2;

}

if (cursorPosition != 0){

cursorPosition = cursorPosition - 1 ;

}

mainMenuDraw();

drawCursor();

activeButton = 1;

break;

case 3: // This case will execute if the "down" button is pressed

button = 0;

//if (cursorPosition != 11){

//}

if (cursorPosition == 1 || cursorPosition == 3 || cursorPosition == 5 || cursorPosition == 7 || cursorPosition == 9  ){

itemNo = itemNo + 2 ;

}

cursorPosition = cursorPosition + 1 ;

if (cursorPosition >= 11){

cursorPosition = 11;

}

mainMenuDraw();

drawCursor();

activeButton = 1;

break;

}

}

}

int evaluateButton() {

int result = 0;

char key = keypad.getKey();

if (key == 'A') {

result = 2; // up

}

if (key == 'D') {

result = 3; // down

}

if (key == 'C') {

result = 4; // left

}

if (key == 'B') {

result = 1; // right

}

if (key == '*') {

result = 5; // select

}

return result;

}

// If there are common usage instructions on more than 1 of your menu items you can call this function from the sub

// menus to make things a little more simplified. If you don't have common instructions or verbage on multiple menus

// I would just delete this void. You must also delete the drawInstructions()function calls from your sub menu functions.

void drawInstructions() {

lcd.setCursor(0, 1); // Set cursor to the bottom line

lcd.print("Use ");

lcd.write(byte(1)); // Up arrow

lcd.print("/");

lcd.write(byte(2)); // Down arrow

lcd.print(" buttons");

}

void menuItem1() { // CaffeLatte  -  Function executes when you select the 2nd item from main menu

int activeButton = 0;


lcd.clear();

lcd.setCursor(3, 0);
lcd.print("Caffe Latte");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.print(digitCaffeLatte);
lcd.print ("C-Inapoi");

digitCaffeLatte = GetDigit();
EEPROM.update(0,digitCaffeLatte);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Caffe Latte");
lcd.setCursor(0,1);
lcd.print("T[s]:");
lcd.println (digitCaffeLatte);
lcd.print ("C-Inapoi");
  


while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

loop();


}

}

}

void menuItem2() { // Cappucino - Function executes when you select the 2nd item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);
lcd.print("Cappucino");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.print(digitCappucino);
lcd.print (" C-Inapoi");




digitCappucino = GetDigit();
EEPROM.update(85,digitCappucino);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Cappucino");
lcd.setCursor(0,1);
lcd.print("T[s]:");
lcd.println (digitCappucino);
lcd.print ("C-Inapoi");

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

loop();

break;

}

}

}

void menuItem3() { //  CleaningTime - ServoFunctioningTime - Function executes when you select the 3rd item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);
lcd.print("Timp Curatare");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.print(CleaningTime);
lcd.print (" C-Inapoi");




CleaningTime = GetDigit();

// Set the minimum cleaning time to 3 sec----- impossible to set below 3 seconds ------------------!!!!!!!!!!!!!!!!!!!!!!------------------------------------

if (CleaningTime < 3) {
  CleaningTime = 3;
}

EEPROM.update(5
,CleaningTime);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Timp Curatare");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.println (CleaningTime);
lcd.print ("C-Inapoi");

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;
loop();

break;

}

}

}

void menuItem4() { // Recipient 2 Function executes when you select the 4th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);
lcd.print("SiropBidon1");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.print(digitSiropBidon1);
lcd.print (" C-Inapoi");




digitSiropBidon1 = GetDigit();
EEPROM.update(80,digitSiropBidon1);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("SiropBidon1");
lcd.setCursor(0,1);
lcd.print("T[s]:");
lcd.println (digitSiropBidon1);
lcd.print ("C-Inapoi");


while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem5() { // Recipient 3 Function executes when you select the 5th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);
lcd.print("SiropBidon2");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.print(digitSiropBidon2);
lcd.print (" C-Inapoi");




digitSiropBidon2 = GetDigit();
EEPROM.update(98,digitSiropBidon2);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("SiropBidon2");
lcd.setCursor(0,1);
lcd.print("T[s]:");
lcd.println (digitSiropBidon2);
lcd.print ("C-Inapoi");


while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem6() { // Recipient 4 - Function executes when you select the 6th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);
lcd.print("SiropBidon3");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.print(digitSiropBidon3);
lcd.print (" C-Inapoi");




digitSiropBidon3 = GetDigit();
EEPROM.update(105, digitSiropBidon3);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("SiropBidon3");
lcd.setCursor(0,1);
lcd.print("T[s]:");
lcd.println (digitSiropBidon3);
lcd.print ("C-Inapoi");



while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem7() { // Recipient 5 - Function executes when you select the 7th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);
lcd.print("SiropBidon4");
lcd.setCursor(0,1);
lcd.print("T[s]");
lcd.print(digitSiropBidon4);
lcd.print (" C-Inapoi");




digitSiropBidon4 = GetDigit();
EEPROM.update(115,digitSiropBidon4);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("SiropBidon4");
lcd.setCursor(0,1);
lcd.print("T[s]:");
lcd.println (digitSiropBidon4);
lcd.print ("C-Inapoi");


while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem8() { // Recipient 6 - Function executes when you select the 8th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 8");

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem9() { // Recipient 7 - Function executes when you select the 9th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 9");

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem10() { // Recipient 8 - Function executes when you select the 10th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 10");

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem11() { // Setari - Function executes when you select the 10th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 11");

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back or left" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

void menuItem12() { // Despre -  Function executes when you select the 10th item from main menu

int activeButton = 0;

lcd.clear();

char text[]="www.petrefl.com";  // text to be printed
unsigned int i = 0;
lcd.setCursor(0,0);
while(text[i]!='\0'){
  lcd.print(text[i]);
  if (i>14){
    lcd.command(0x18); //Scrolling text to Right
  }

  delay(400);
  i++;
}
 lcd.clear(); 
 lcd.print (text);
 lcd.setCursor(4,1);
 lcd.print ("vers. 1");

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 4: // This case will execute if the "back or left" button is pressed

button = 0;

activeButton = 1;

break;

}

}

}

int GetDigit()
{
   unsigned long num = 0;
   
   char key4 = keypad.getKey();
   
   while(key4 != '*')
   
   {  
      switch (key4)
      {
         case NO_KEY:
            break;

         case '0': case '1': case '2': case '3': case '4':
         case '5': case '6': case '7': case '8': case '9':
            
                                
            num = num *10 + (key4-'0'); 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Set Timp");
            lcd.setCursor(0,1);
            lcd.print("T[s]: ");
            lcd.print(num);
            lcd.print("   [*]OK");
            break;

         case 'C':
            num = digitCaffeLatte;
           
            goto Loop1;
            
    

        
      }

     key4 = keypad.getKey();

    
   }

   Loop1:
    return num;

      loop();
         

}
