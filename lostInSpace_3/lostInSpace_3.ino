int Switch1 = 2;
int LED = 12;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Switch1, INPUT);
}

void loop() {
  if (digitalRead(Switch1) == 1){
    digitalWrite(LED, HIGH); // 5V
  }
  else {
    digitalWrite(LED, LOW); // ground
  }
}
