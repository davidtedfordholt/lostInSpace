int sensorPin = A0;
int sensorValue = 0;
int onboardLED = 13;
unsigned int batteryCapacity = 1000;
unsigned int batteryLevel = 0;

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
  batteryLevel += sensorValue;

  if (batteryLevel >= batteryCapacity) {
    Serial.println("FULLY CHARGED");
    batteryLevel = batteryCapacity;
    digitalWrite(onboardLED, HIGH);
    delay(10000);
  } else {
    //digitalWrite(onboardLED, HIGH);
    //delay(sensorValue);
    //digitalWrite(onboardLED, LOW);
    //delay(sensorValue);
    PrintBatteryPercentage();
    delay(500);
  }

}
