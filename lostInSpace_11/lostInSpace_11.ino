#include <Key.h>
#include <Keypad.h>

const byte n_rows = 4;
const byte n_cols = 4;

char buttons[n_rows][n_cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[n_rows] = {9, 8, 7, 6};
byte colPins[n_cols] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(
  makeKeymap(buttons), rowPins, colPins, n_rows, n_cols);

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  char customKey = customKeypad.getKey();

  if(customKey) {
    Serial.println(customKey);
  }
}
