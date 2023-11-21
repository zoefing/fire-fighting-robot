const int m1_direction = 4; // digital pin 4 controls M1 direction
const int m1_speed = 5; // analog pin 5 controls M1 speed
const int m2_direction = 7; // digital pin 7 controls M2 direction
const int m2_speed = 6; // analog pin 6 controls M2 speed
const int touchPin = 10; // analog pin 10 for touch sensor


void setup() {
  pinMode(m1_direction, OUTPUT);
  pinMode(m1_speed, OUTPUT);
  pinMode(m2_direction, OUTPUT);
  pinMode(m2_speed, OUTPUT);
  pinMode(touchPin, INPUT);

  // pause briefly when the robot is turned on
  delay(2000); // pause for 2 seconds
}

void loop() {
  bool touchValue = digitalRead(touchPin);

  if (touchValue == LOW) {
    // obstacle detected, stop both motors
    digitalWrite(m1_direction, HIGH);
    digitalWrite(m2_direction, HIGH);
    analogWrite(m1_speed, 0);
    analogWrite(m2_speed, 0);
    delay(1000); // pause for 1 second

    // back up
    digitalWrite(m1_direction, HIGH);  // M1 backward
    digitalWrite(m2_direction, HIGH);  // M2 backward
    analogWrite(m1_speed, 75);      // moderately low speed for M1 (backward)
    analogWrite(m2_speed, 75);      // moderately low speed for M2 (backward)
    delay(1000); // back up for 1 second

    // rotate clockwise
    digitalWrite(m1_direction, HIGH);  // M1 backward
    digitalWrite(m2_direction, LOW); // M2 forward
    analogWrite(m1_speed, 50);      // low speed for M1 (backward)
    analogWrite(m2_speed, 75);      // slower speed for M2 (forward)
    delay(1000); // rotate for 1 second
  } else {
    // no obstacle detected, continue forward
    digitalWrite(m1_direction, LOW); // M1 forward
    digitalWrite(m2_direction, LOW); // M2 forward
    analogWrite(m1_speed, 75);     // higher speed for M1
    analogWrite(m2_speed, 75);     // high speed for M2
  }
}