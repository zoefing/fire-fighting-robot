// Connect a start switch/touch sensor to digital port 10
// Use analog port 3 for Sharp sensor 1

// Global variables
int Sharp1 = 3; //use analog port 2 for Sharp sensor 1 (left)
int start_sw = 10; //digital port ID, start switch
int interval = 250; //interval between sensor readings

void start_press(int sw)
{
//sw represents the digital port number that’s connected to the switch
//function waits for switch to be pressed and released
while(digitalRead(sw) == HIGH){} //exit when switch pressed
while(digitalRead(sw) == LOW) {} // continue when switch released
}

void setup()
{
pinMode(start_sw, INPUT);
// initialize the Serial monitor
Serial.begin(9600);
Serial.println("Hit Start Button");
start_press(start_sw);
}

void loop()
{
int Reading_1;
Reading_1 = analogRead(Sharp1);
//print the sensor reading
Serial.println(Reading_1);
delay(interval);
}