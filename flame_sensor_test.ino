const int flameSensorOne = A4;
const int flameSensorTwo = A5;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(flameSensorOne, INPUT);
  pinMode(flameSensorTwo, INPUT);
}

void loop() {
  int flameOneValue = analogRead(flameSensorOne); 
  int flameTwoValue = analogRead(flameSensorTwo); 

  // You may need to adjust this threshold based on your sensor and environment
  int flameThreshold = 900;  // Adjust this threshold value as needed

  if (flameOneValue < flameThreshold || flameTwoValue < flameThreshold) {
    if (flameOneValue < flameThreshold) {
    Serial.println("Flame detected!");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); // pause for 1 second
    digitalWrite(LED_BUILTIN, LOW);

    } else if (flameTwoValue < flameThreshold) {
    Serial.println("Flame detected!");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); // pause for 1 second
    digitalWrite(LED_BUILTIN, LOW);
   } else {
    // No flame detected, turn off the fan
    Serial.println("No flame detected");
    digitalWrite(LED_BUILTIN, LOW);
  }
 }
}