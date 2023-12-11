const int fanOne = 2;
const int fanTwo = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(fanOne, OUTPUT);
  pinMode(fanTwo, OUTPUT);
}

void loop() {
  digitalWrite(fanOne, HIGH);
  digitalWrite(fanTwo, HIGH);
}