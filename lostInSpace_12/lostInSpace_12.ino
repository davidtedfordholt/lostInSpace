#include <Key.h>
#include <Keypad.h>

int buzzer = 10;
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

int tones[n_rows][n_cols] = {
  {31, 93, 147, 208},
  {247, 311, 370, 440},
  {523, 587, 698, 880},
  {1397, 2637, 3729, 4978}
};

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {

  int toneFreq = 0;
  char customKey = customKeypad.getKey();
  
  if(customKey) {
    Serial.print(customKey);
    Serial.print(": ");
    for (byte j=0; j<n_rows; j++) {
      for (byte i=0; i<n_cols; i++) {
        if (customKey == buttons[j][i]) {
          toneFreq = tones[j][i];
          break;
        }
      }
    }

    tone(buzzer, toneFreq, 500);
    delay(500);
    noTone(buzzer);
  }
}
