#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// LCD setup: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Servo setup
Servo myServo;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};     // Keypad row pins → UNO
byte colPins[COLS] = {13, A0, A1, A2}; // Keypad col pins → UNO

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password variables
String password = "12434";
String inputPassword = "";

void setup() {
  lcd.begin(16, 2);          // 16x2 LCD
  myServo.attach(10);        // Servo signal → pin 10
  myServo.write(0);          // Start at 0°
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey(); // read one key

  if (key) {
    if (key == '#') {  // Enter key
      if (inputPassword == password) {
        lcd.clear();
        lcd.print("Access Granted");
        myServo.write(90);   // Servo rotates 90°
      } else {
        lcd.clear();
        lcd.print("Password Error");
        myServo.write(0);    // Reset servo
      }
      delay(2000);           // Show message for 2 sec
      lcd.clear();
      lcd.print("Enter Password:");
      inputPassword = "";    // Reset input
    }
    else if (key == '*') {  // Clear input
      inputPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else {  // Add typed digit/char
      inputPassword += key;
      lcd.setCursor(0, 1);    // Line 2
      lcd.print(inputPassword);
    }
  }
}
