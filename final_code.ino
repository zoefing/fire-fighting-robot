const int m1_direction = 4;
const int m1_speed = 5;
const int m2_direction = 7;
const int m2_speed = 6;
const int touchPin = 10;
const int irSensorOne = A2;
const int irSensorTwo = A3;
const int flameSensorOne = A4;
const int flameSensorTwo = A5;
const int fanOnePin = 2;
const int fanTwoPin = 0;
const int stripeSensor = A0;

// Set the desired distance from the wall
const int desiredDistance = 150;  // Adjust this value as needed

// Set the desired drop off threshold
const int dropOffThreshold = 100;  // Adjust this value as needed

// Threshold for flame detection
int flameThreshold = 900; 

// Threshold value for white vs. black
int lightThreshold = 500;

// Speed for adjusting robot position
const int adjustSpeed = 25;

// Initialize variables for white line detection
int whiteLineCount = 0;

bool isFollowingLeftWall = false; // Assume robot starts by following right wall

bool pastStripeValueWasBlack = true;
bool currentStripeValueIsBlack = true;
bool w2b = false;
bool b2w = false;

int stripeSensorValue = analogRead(stripeSensor);

void setup() {
  Serial.begin(9600); // Initialize serial communication

  pinMode(m1_direction, OUTPUT);
  pinMode(m1_speed, OUTPUT);
  pinMode(m2_direction, OUTPUT);
  pinMode(m2_speed, OUTPUT);
  pinMode(touchPin, INPUT);
  pinMode(irSensorOne, INPUT);
  pinMode(irSensorTwo, INPUT);
  pinMode(13, OUTPUT);
  pinMode(flameSensorOne, INPUT);
  pinMode(flameSensorTwo, INPUT);
  pinMode(fanOnePin, OUTPUT);
  pinMode(fanTwoPin, OUTPUT);
  pinMode(stripeSensor, INPUT);

  // pause briefly when the robot is turned on
  delay(2000); // pause for 2 seconds
}

void loop() {
  bool touchValue = digitalRead(touchPin);
  int flameOneValue = analogRead(flameSensorOne);
  int flameTwoValue = analogRead(flameSensorTwo);

  currentStripe();  

  if (flameOneValue < flameThreshold) {
    Serial.println("Flame detected!");
    digitalWrite(LED_BUILTIN, HIGH);
    stopMotors();
    delay(1000);
    digitalWrite(fanOnePin, HIGH);
    delay(2000);
    digitalWrite(fanOnePin, LOW);
    digitalWrite(LED_BUILTIN, LOW);

  } else if (flameTwoValue < flameThreshold) {
    Serial.println("Flame detected!");
    digitalWrite(LED_BUILTIN, HIGH);
    stopMotors();
    delay(1000);
    digitalWrite(fanTwoPin, HIGH);
    delay(2000);
    digitalWrite(fanTwoPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);

  } else if (touchValue == LOW) {

    // obstacle detected, stop both motors
    stopMotors();
    delay(1000); // pause for 1 second

    // back up
    backup();

    if (isFollowingLeftWall) {
      // Following left wall
      rotateCounterClockwise();

    } else if (!isFollowingLeftWall) { // 
      // Following right wall
      rotateClockwise();
    }
  } else {
    if (whiteLineCount >= 0) {
      if (whiteLineCount == 0) {
        Serial.println("count = 0");
        isFollowingLeftWall = false; // Right wall following
      } 
      if (whiteLineCount == 1) {
        Serial.println("count = 1");
        isFollowingLeftWall = false; // Right wall following
      } 
      if (whiteLineCount == 2) {
        Serial.println("count = 2");   
        isFollowingLeftWall = false; // Right wall following  
      } 
      if (whiteLineCount == 3) {
        Serial.println("count = 3");
        isFollowingLeftWall = false; // Right wall following
      } 
      if (whiteLineCount == 4) {
        Serial.println("count = 4");
        isFollowingLeftWall = true; // Switch to left wall following
      } 
      if (whiteLineCount == 5) {
        Serial.println("count = 5");
        isFollowingLeftWall = false; // Switch to right wall following
      } 
      if (whiteLineCount == 6) {
        Serial.println("count = 6");
        isFollowingLeftWall = true; // Switch to left wall following
      } 
      if (whiteLineCount == 7) {
        Serial.println("count = 7");
        isFollowingLeftWall = false; // Switch to right wall following
      }
    } if (isFollowingLeftWall) {
      // Following left wall
      leftWallFollowing();
    } else if (!isFollowingLeftWall) { // 
      // Following right wall
        rightWallFollowing();
      }   
  }
}

// Function to get distance from Sharp IR sensor
float getDistance(int sensorPin) {
  // Read the analog value from the sensor
  int sensorValue = analogRead(sensorPin);
  return sensorValue;
}

void currentStripe() {
  // lightThreshold established earlier in code

  // the idea is that if the past robot goes from the black floor to passing over a white stripe, the past value = black and the current value = white so b2w is true and the count is incremented

  int stripeSensorValue = analogRead(stripeSensor);

  if (stripeSensorValue < lightThreshold) { // white detected
    currentStripeValueIsBlack = false;
  } else if (stripeSensorValue > lightThreshold) { // black detected
    currentStripeValueIsBlack = true;
  } if (pastStripeValueWasBlack && !currentStripeValueIsBlack) { // if the robot went from black floor to white stripe (b2w = true)
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); // hold light for a second
    whiteLineCount++; //Increment count on white line detection
    digitalWrite(LED_BUILTIN, LOW);
  } if (!pastStripeValueWasBlack && currentStripeValueIsBlack) { // w2b = true
    w2b = true;
  }
  pastStripeValueWasBlack = currentStripeValueIsBlack;
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
void rotateClockwise() {
  stripeSensorValue = analogRead(stripeSensor);
  digitalWrite(m1_direction, LOW);
  digitalWrite(m2_direction, LOW);
  analogWrite(m1_speed, 0);
  analogWrite(m2_speed, 85);
  for (int i=0; i <=1400; i++)
  {
    stripeSensorValue = analogRead(stripeSensor);
    delay(1);

    if (stripeSensorValue < lightThreshold) { // white detected
    currentStripeValueIsBlack = false;
   } else if (stripeSensorValue > lightThreshold) { // black detected
    currentStripeValueIsBlack = true;
  } if (pastStripeValueWasBlack && !currentStripeValueIsBlack) { // if the robot went from black floor to white stripe (b2w = true)
    digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000); // hold light for a second
    whiteLineCount++; //Increment count on white line detection
    digitalWrite(LED_BUILTIN, LOW);
    pastStripeValueWasBlack = currentStripeValueIsBlack;
  } if (!pastStripeValueWasBlack && currentStripeValueIsBlack) { // w2b = true
    w2b = true;
  }
  pastStripeValueWasBlack = currentStripeValueIsBlack;
  }
}

// Function to rotate the robot counterclockwise
void rotateCounterClockwise() {
  stripeSensorValue = analogRead(stripeSensor);
  digitalWrite(m1_direction, LOW);
  digitalWrite(m2_direction, LOW);
  analogWrite(m1_speed, 82.5);
  analogWrite(m2_speed, 0);
  for (int i=0; i <=1400; i++)
  {
    stripeSensorValue = analogRead(stripeSensor);
    delay(1);

    if (stripeSensorValue < lightThreshold) { // white detected
    currentStripeValueIsBlack = false;
   } else if (stripeSensorValue > lightThreshold) { // black detected
    currentStripeValueIsBlack = true;
  } if (pastStripeValueWasBlack && !currentStripeValueIsBlack) { // if the robot went from black floor to white stripe (b2w = true)
    digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000); // hold light for a second
    whiteLineCount++; //Increment count on white line detection
    digitalWrite(LED_BUILTIN, LOW);
    pastStripeValueWasBlack = currentStripeValueIsBlack;
  } if (!pastStripeValueWasBlack && currentStripeValueIsBlack) { // w2b = true
    w2b = true;
  }
  pastStripeValueWasBlack = currentStripeValueIsBlack;
  }
}

// Following left wall
void leftWallFollowing() {
  float distanceLeft = getDistance(irSensorTwo);

  if (distanceLeft < dropOffThreshold) {
  // Detects drop-off; wall "disappears"
  stopMotors();
  moveForward();

  for (int i=0; i <=1500; i++) // continue for 1.4 seconds
  {
    stripeSensorValue = analogRead(stripeSensor);
    delay(1);

    if (stripeSensorValue < lightThreshold) { // white detected
    currentStripeValueIsBlack = false;
   } else if (stripeSensorValue > lightThreshold) { // black detected
    currentStripeValueIsBlack = true;
    
  } if (pastStripeValueWasBlack && !currentStripeValueIsBlack) { // if the robot went from black floor to white stripe (b2w = true)
    digitalWrite(LED_BUILTIN, HIGH);
    //delay(1000); // hold light for a second
    whiteLineCount++; //Increment count on white line detection
    digitalWrite(LED_BUILTIN, LOW);
    pastStripeValueWasBlack = currentStripeValueIsBlack;
    break;
  } if (!pastStripeValueWasBlack && currentStripeValueIsBlack) { // w2b = true
    w2b = true;
  }
  pastStripeValueWasBlack = currentStripeValueIsBlack;
  }

  rotateClockwise();

  } else {
  // No obstacle detected, follow the wall
  if (distanceLeft > desiredDistance) {
  // Too far from the wall, adjust to the left
  adjustLeft();
  
  } else if (distanceLeft < desiredDistance) {
  // Too close to the wall, adjust to the right
  adjustRight();
  
  } else {
  // Maintain the desired distance, move forward
  moveForward();
  }
 }
}

// Following right wall
void rightWallFollowing() {
  float distanceRight = getDistance(irSensorOne);

  if (distanceRight < dropOffThreshold) {
  // Detects drop-off; wall "disappears"
  stopMotors();
  moveForward();
  for (int i=0; i <=1500; i++) // continue
  {
    stripeSensorValue = analogRead(stripeSensor);
    delay(1);

    if (stripeSensorValue < lightThreshold) { // white detected
    currentStripeValueIsBlack = false;
   } else if (stripeSensorValue > lightThreshold) { // black detected
    currentStripeValueIsBlack = true;
    
  } if (pastStripeValueWasBlack && !currentStripeValueIsBlack) { // if the robot went from black floor to white stripe (b2w = true)
    digitalWrite(LED_BUILTIN, HIGH);
    //delay(1000); // hold light for a second
    whiteLineCount++; //Increment count on white line detection
    digitalWrite(LED_BUILTIN, LOW);
    pastStripeValueWasBlack = currentStripeValueIsBlack;
    break;
  } if (!pastStripeValueWasBlack && currentStripeValueIsBlack) { // w2b = true
    w2b = true;
  }
  pastStripeValueWasBlack = currentStripeValueIsBlack;
  }

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