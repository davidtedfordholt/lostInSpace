// VARIABLES  -------------------------

// pins
int sensorLight_pin = A0;
int switch_1 = 4;
int RGB_blue = 9;
int RGB_green = 10;
int RGB_red = 11;

// spaceship constants
int powerDraw = 20;
unsigned int batteryCapacity = 2000;
int delayStdValue = 500;

// variables
int lightLevel = 0;
unsigned int batteryLevel = 0;
double batteryPercentage = 0;
double powerChange = 0;
bool wasAlreadyCharged = false;
bool wasDebug = false;


// FUNCTIONS --------------------------

void printBatteryPercentage(bool debug = false) {
  if (debug == true) {
    if (wasDebug == false) {
      Serial.println("DEBUG MODE ON");
      wasDebug = true;
    }
    Serial.print("Battery Level: ");
    Serial.print(batteryPercentage);
    Serial.println("%"); 
    Serial.print("  lightLevel: ");
    Serial.println(lightLevel);
    Serial.print("  powerDraw: ");
    Serial.println(powerDraw);
    Serial.print("  batteryLevel value: ");
    Serial.println(batteryLevel);
    Serial.print("  wasAlreadyCharged value: ");
    Serial.println(wasAlreadyCharged);
  } else {
    if (wasDebug == true) {
      Serial.println("DEBUG MODE OFF");
      wasDebug = false;
    }
    Serial.print("Battery Level: ");
    Serial.print(batteryPercentage);
    Serial.println("%");    
  }
}

double calcBatteryPercentage() {
  return((double)batteryLevel/ (double)batteryCapacity * 100);
}

void RGBcolor(int red_value, int green_value, int blue_value, bool blinking = true) {
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
  delay(delayStdValue);
  if (blinking == true) {
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    delay(delayStdValue);
  } else {
    delay(delayStdValue);
  }
}


// SETUP -------------------------------

void setup() {
  pinMode(switch_1, INPUT);
  Serial.begin(9600);

  printBatteryPercentage();
}


// LOOP --------------------------------

void loop() {
  
  // STARTING STATE
  lightLevel = analogRead(sensorLight_pin);
  powerChange = (double)lightLevel - (double)powerDraw;

  // RESOLVE CHANGE
  
    // constrain batteryLevel to between 0 and batteryCapacity
  if (powerChange < 0 & abs(powerChange) >= batteryLevel) {
    batteryLevel = 0;
  } else if (powerChange > 0 & (batteryLevel + powerChange) >= batteryCapacity) {
    batteryLevel = batteryCapacity;
  } else {
    batteryLevel += powerChange;
  }

  batteryPercentage = calcBatteryPercentage();

  if (wasAlreadyCharged == false) {
    if (digitalRead(switch_1) == 1) {
      printBatteryPercentage(true);
    } else {
      printBatteryPercentage(false);
    }
  }

  // BATTERY CHARGE INDICATOR
  
                                    
  if (wasAlreadyCharged == true) {  // if the battery was already full - no change
    if (batteryPercentage < 100) {
      wasAlreadyCharged = false;
    }
  } else if (batteryPercentage >= 100) {   // if the battery is full - solid green
    Serial.println("FULLY CHARGED"); 
    wasAlreadyCharged = true;
    RGBcolor(0, 10, 0, false);
  } else if (batteryPercentage >= 75) {  // if the battery is above 75% - blink green
    RGBcolor(0, 10, 0);
  } else if (batteryPercentage >= 50) {  // if the battery is above 50% - blink yellow
    RGBcolor(10, 10, 0);
  } else if (batteryPercentage >= 25) {  // if the battery is above 25% - blink red
    RGBcolor(10, 0, 0);
  } else if (batteryPercentage > 0) {  // if the battery is below 25% - solid red
    RGBcolor(10, 0, 0, false);
  } else {                             // if the battery is dead - nothing
    RGBcolor(0, 0, 0, false);
  }

}
