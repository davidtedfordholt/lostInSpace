int blue = 9;
int green = 10;
int red = 11;

void RBGcolor(int red_value, int green_value, int blue_value) {
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
  delay(500);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  RBGcolor(5, 0, 0); // red
  RBGcolor(0, 5, 0); // green
  RBGcolor(0, 0, 5); // blue
  RBGcolor(5, 0, 5); // purple
  RBGcolor(0, 5, 5); // aqua?
  RBGcolor(5, 5, 0); // yellow
  RBGcolor(5, 5, 5); // white
}
