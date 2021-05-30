#include <Key.h>
#include <Keypad.h>

// MAPPING DEFINITIONS
const byte n_rows = 4;
const byte n_cols = 4;
char buttons[n_rows][n_cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// HARDWARE DEFINITIONS
int LED_red = 11;
int LED_green = 9;
int LED_blue = 10;
int buzzer = 8;
byte button_row[n_rows] = {13, 12, 7, 6};
byte button_col[n_cols] = {5, 4, 3, 2};

// MAPPING
Keypad customKeypad = Keypad(
  makeKeymap(buttons), button_row, button_col, n_rows, n_cols);


// PASSWORD
const byte passLength = 4;
char password[passLength] = {'0', '0', '0', '0'};


// FUNCTIONS
void RGB_color(int red_value, int green_value, int blue_value) {
  analogWrite(LED_red, red_value);
  analogWrite(LED_green, green_value);
  analogWrite(LED_blue, blue_value);
}

void playInput() {
  tone(buzzer, 880, 500);
  RGB_color(0, 0, 50);
  delay(100);
  RGB_color(0, 0, 0);
  noTone(buzzer);
}

void playError() {
  RGB_color(50, 0, 0);
  tone(buzzer, 392, 250);
  delay(250);
  tone(buzzer, 370, 250);
  delay(250);
  tone(buzzer, 349, 250);
  delay(250);
  RGB_color(0, 0, 0);
  noTone(buzzer);
}

void playSuccess() {
  RGB_color(0, 50, 0);
  tone(buzzer, 392, 250);
  delay(250);
  tone(buzzer, 587, 250);
  delay(250);
  tone(buzzer, 784, 250);
  delay(250);
  RGB_color(0, 0, 0);
  noTone(buzzer);
}

int unlockMode(){
  char customKey = customKeypad.getKey();
  
  Serial.println("Type Password to continue");
  delay(500);

  int failure_flag = 0;
  
  for(int i = 0; i < passLength; i++) {
    while(!(customKey = customKeypad.getKey())) {
       // wait infinitley for input
    }
    playInput();
    if(password[i] != customKey){
      failure_flag = 1;
    }
    Serial.print("*");
  }

  Serial.println("");
  if (failure_flag == 1) {
    Serial.println("WRONG PASSWORD");
    playError();
    return 1;
  } else {
    Serial.println("Device Successfully Unlocked!");
    playSuccess();
    return 0;
  }
}





void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
  Serial.println("System booting");
  pinMode(buzzer, OUTPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_blue, OUTPUT);

  // LIGHTING TEST
  Serial.println("RGB test");
  RGB_color(50, 0, 0);
  delay(100);
  RGB_color(0, 0, 50);
  delay(100);
  RGB_color(0, 50, 0);
  delay(100);
  RGB_color(0, 0, 0);
  delay(500);

  // TONE TEST
  Serial.println("Tone test");
  playSuccess();
  delay(500);
  playError();

  Serial.println("");
  Serial.println("Press * to set new password or # to access the system.");
}



void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey == '*'){ // button to change password
    playInput();
    Serial.println("Change Password Mode");
    int access = unlockMode();
    if(access != 0) {
      Serial.println("Access Denied. Cannot change password without the old or default.");
    } else {
      Serial.print("Welcome, authorized user. Please Enter a new password: ");
      delay(500);
      for(int i = 0; i < passLength; i++) {
        while(!(customKey = customKeypad.getKey())) {
        // wait infinitley for input
        }
        playInput();
        password[i] = customKey;
        Serial.print("*");
      }
      Serial.println("");
      playSuccess();
      Serial.println("Password Successfully Changed!");
      Serial.println("Press * to set new password or # to access the system.");
    }
  }
 
  if (customKey == '#') { // button to access system
    int access = unlockMode();
    if(access != 0) {
      Serial.println("Access Denied.");
      Serial.println("Press * to set new password or # to access the system.");
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    }
  }
 
}
