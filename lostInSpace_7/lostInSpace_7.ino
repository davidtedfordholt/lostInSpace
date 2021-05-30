int sensorPin = A0;
int sensorValue = 0;
int onboardLED = 13;
unsigned int batteryCapacity = 1000;
unsigned int batteryLevel = 0;
bool wasAlreadyCharged = false;

void PrintBatteryPercentage() {
  Serial.print((double)batteryLevel/ (double)batteryCapacity*100);
  Serial.println("%");
}

void setup() {
  pinMode(onboardLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  sensorValue = min(sensorValue, 100);
  batteryLevel += sensorValue;
  
  if (batteryLevel >= batteryCapacity) {
    if (wasAlreadyCharged == false) {
      Serial.println("FULLY CHARGED");
      batteryLevel = batteryCapacity;
      wasAlreadyCharged = true;
      digitalWrite(onboardLED, HIGH);
      delay(100);
    }
  } else {
    digitalWrite(onboardLED, HIGH);
    delay(110 - sensorValue);
    digitalWrite(onboardLED, LOW);
    delay(110 - sensorValue);
    PrintBatteryPercentage();
    delay(500);
  }

}
