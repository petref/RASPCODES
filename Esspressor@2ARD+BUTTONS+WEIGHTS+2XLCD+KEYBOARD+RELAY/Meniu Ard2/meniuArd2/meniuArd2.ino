#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Keypad.h> // load keypad library

// Menu control variables

int itemNo = 0;

int cursorPosition = 0;

String menuItems[] = {"ITEM 1", "ITEM 2", "ITEM 3", "ITEM 4", "ITEM 5", "ITEM 6", "ITEM 7", "ITEM 8", "ITEM 9", "ITEM 10", "ITEM 11", "ITEM 12"};

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

void setup() {

// Initializes serial communication


lcd.backlight();
lcd.init();
Serial.begin(9600);

// Initializes and clears the LCD screen
lcd.backlight();


lcd.begin(16, 4);

lcd.clear();

// Creates the byte for the 3 custom characters

lcd.createChar(0, menuCursor);

lcd.createChar(1, upArrow);

lcd.createChar(2, downArrow);

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

//lcd.setCursor(1, 2);

//lcd.print(menuItems[itemNo +2 ]);

//lcd.setCursor(1, 3);

//lcd.print(menuItems[itemNo + 3]);

if (cursorPosition >= 0 and cursorPosition <= 1) {

lcd.setCursor(15, 1);

lcd.write(byte(2));

}

else if (cursorPosition > 1 and cursorPosition < 10) {

lcd.setCursor(15, 1);

lcd.write(byte(2));

lcd.setCursor(15, 0);

lcd.write(byte(1));

}

else if (cursorPosition >= 10) {

lcd.setCursor(15, 0);

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

//if (cursorPosition == 2 || cursorPosition == 6 || cursorPosition == 10 ){

//lcd.setCursor (0,2);

//lcd.write(byte(0));

//}

//if (cursorPosition == 3 || cursorPosition == 7 || cursorPosition == 11){

//lcd.setCursor (0,3);

//lcd.write(byte(0));

//}

}

void operateMainMenu() {

int activeButton = 0;

while (activeButton == 0) {

int button;

button = evaluateButton();

switch (button) {

case 0: // When button returns as 0 there is no action taken i.e no button pressed.

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

void menuItem1() { // caffelatte Function executes when you select the 2nd item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("CaffeLatte");

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

void menuItem2() { // Function executes when you select the 2nd item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 2");

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

void menuItem3() { // Function executes when you select the 3rd item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 3");

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

void menuItem4() { // Function executes when you select the 4th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 4");

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

void menuItem5() { // Function executes when you select the 5th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 5");

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

void menuItem6() { // Function executes when you select the 6th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 6");

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

void menuItem7() { // Function executes when you select the 7th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 7");

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

void menuItem8() { // Function executes when you select the 8th item from main menu

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

void menuItem9() { // Function executes when you select the 9th item from main menu

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

void menuItem10() { // Function executes when you select the 10th item from main menu

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

void menuItem11() { // Function executes when you select the 10th item from main menu

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

void menuItem12() { // Function executes when you select the 10th item from main menu

int activeButton = 0;

lcd.clear();

lcd.setCursor(3, 0);

lcd.print("Sub Menu 12");

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
