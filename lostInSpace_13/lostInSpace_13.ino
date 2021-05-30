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
int buzzer = 10;
byte rowPins[n_rows] = {9, 8, 7, 6};
byte colPins[n_cols] = {5, 4, 3, 2};

// MAPPING
Keypad customKeypad = Keypad(
  makeKeymap(buttons), rowPins, colPins, n_rows, n_cols);


// PASSWORD
const byte passLength = 4;
char password[passLength] = {'0', '0', '0', '0'};


// UNLOCK FUNCTION
int unlockMode(){
  char customKey = customKeypad.getKey();
  
  Serial.println("Type Password to continue");
  delay(500);

  int failure_flag = 0;
  
  for(int i = 0; i < passLength; i++) {
    while(!(customKey = customKeypad.getKey())) {
       // wait infinitley for input
    }
    if(password[i] != customKey){
      failure_flag = 1;
    }
    Serial.print("*");
  }

  Serial.println("");
  if (failure_flag == 1) {
    Serial.println("WRONG PASSWORD");
    return 1;
  } else {
    Serial.println("Device Successfully Unlocked!");
    return 0;
  }
}



void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
  Serial.println("Press * to set new password or # to access the system.");
}



void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey == '*'){ // button to change password
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
        password[i] = customKey;
        Serial.print("*");
      }
      Serial.println("");
      Serial.println("Password Successfully Changed!");
      Serial.println("Press * to set new password or # to access the system.");
    }
  }
 
  if (customKey == '#') { // button to access system
    int access = unlockMode();
    if(access != 0) {
      Serial.println("Access Denied.");
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    }
  }
 
}
