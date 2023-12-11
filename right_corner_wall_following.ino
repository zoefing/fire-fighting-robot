const int m1_direction = 4;
const int m1_speed = 5;
const int m2_direction = 7;
const int m2_speed = 6;
const int touchPin = 10;
const int irSensorOne = A2;
const int irSensorTwo = A3;

// Set the desired distance from the wall
const int desiredDistance = 150;  // Adjust this value as needed

// Set the desired drop off threshold
const int dropOffThreshold = 100;  // Adjust this value as needed

// Speed for adjusting robot position
const int adjustSpeed = 25;

void setup() {
  pinMode(m1_direction, OUTPUT);
  pinMode(m1_speed, OUTPUT);
  pinMode(m2_direction, OUTPUT);
  pinMode(m2_speed, OUTPUT);
  pinMode(touchPin, INPUT);
  pinMode(irSensorOne, INPUT);
  pinMode(irSensorTwo, INPUT);
  pinMode(13, OUTPUT);

  // pause briefly when the robot is turned on
  delay(2000); // pause for 2 seconds
}

void loop() {
  bool touchValue = digitalRead(touchPin);
  float distanceRight = getDistance(irSensorOne);

  if (touchValue == LOW) {
    // obstacle detected, stop both motors
    stopMotors();
    delay(1000); // pause for 1 second

    // back up
    backup();
    // rotate counterclockwise
    rotateCounterClockwise();
  } else {
    if (distanceRight < dropOffThreshold) {
      // Detects drop-off; wall "disappears"
      stopMotors();
      moveForward();
      delay(1500); // pause for 1.5 seconds
      rotateCounterClockwise();
    } else {

    // No obstacle detected, follow the wall
    if (distanceRight > desiredDistance) {
      // Too far from the wall, adjust to the right
      adjustRight();
    } else if (distanceRight < desiredDistance) {
      // Too close to the wall, adjust to the left
      adjustLeft();
    } else {
      // Maintain the desired distance, move forward
      moveForward();
    }
    }
  }
}

// Function to get distance from Sharp IR sensor
float getDistance(int irSensorOne) {
  // Read the analog value from the sensor
  int sensorValue = analogRead(irSensorOne);
  return sensorValue;
}

// Function to stop both motors
void stopMotors() {
  digitalWrite(m1_direction, HIGH);
  digitalWrite(m2_direction, HIGH);
  analogWrite(m1_speed, 0);
  analogWrite(m2_speed, 0);
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(m1_direction, LOW);
  digitalWrite(m2_direction, LOW);
  analogWrite(m1_speed, 75);
  analogWrite(m2_speed, 75);
}

// Function to adjust the robot position to the right
void adjustRight() {
  digitalWrite(m1_direction, LOW);
  digitalWrite(m2_direction, LOW);
  analogWrite(m1_speed, adjustSpeed);
  analogWrite(m2_speed, 75);
}

// Function to adjust the robot position to the left
void adjustLeft() {
  digitalWrite(m1_direction, LOW);
  digitalWrite(m2_direction, LOW);
  analogWrite(m1_speed, 75);
  analogWrite(m2_speed, adjustSpeed);
}

// Function to make the robot back up
void backup() {
  digitalWrite(m1_direction, HIGH);
  digitalWrite(m2_direction, HIGH);
  analogWrite(m1_speed, 75);
  analogWrite(m2_speed, 75);
  delay(1000); // back up for 1 second
}

// Function to rotate the robot counterclockwise
void rotateCounterClockwise() {
  digitalWrite(m1_direction, LOW);
  digitalWrite(m2_direction, HIGH);
  analogWrite(m1_speed, 75);
  analogWrite(m2_speed, 50);
  delay(1000); // rotate for 1 second
}