int led1 = 8;			// Led 1: Blue
int led2 = 7;			// Led 2: Red
int led3 = 6;			// Led 3: Green
int trig_pin = 3;		// Trig pin
int echo_pin = 2;		// Echo pin
int buzzer_pin = 13;	// Buzzer pin
int distanceCm = 0;		// Car's current distance

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set leds, trig pin, buzzer pin as outputs and echo pin as input
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  // Get the current distance (centimeter)
  distanceCm = getDistance();
  
  // If the distance is bigger than 150cm, the car is in area 1
  if (distanceCm >= 150) {
    Serial.println("Your car is in area 1");
    area1();
  }  
  // If the distance is between 50cm and 150cm, the car is in area 2
  else if (distanceCm > 50 && distanceCm < 150) { //
    Serial.println("Your car is in area 2");
    area2();
  } 
  // If the distance is smaller than 50cm, the car is in area 3
  else {
    Serial.println("Your car is in area 3");
    area3();
  }
}

long getDistance() {
  // Set the trig pin to LOW for 2 microseconds to ensure a clean pulse start
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  // Then set it to HIGH for 10 microseconds to trigger the ultrasonic sensor
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  // Set it backs to LOW to end the pulse
  digitalWrite(trig_pin, LOW);
  
  // Measure the time it takes for the echo to be received back on echo pin
  long duration = pulseIn(echo_pin, HIGH);
  
  // Compute the distance in centimeter
  long distanceCm = duration * 0.034 / 2;
  
  return distanceCm;
}

void area1() {
  // Turn led 1 on and turn led 2, led 3, buzzer pin off
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  noTone(buzzer_pin);
}

void area2() {
  // Turn led 1 and led 3 off
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  
  // Led 2 blinks and buzzer sounds beep-pause-beep
  digitalWrite(led2, HIGH);
  tone(buzzer_pin, 300);
  delay(300);
  
  digitalWrite(led2, LOW);
  noTone(buzzer_pin);
  delay(300);
}

void area3() {
  // Map the distance to a delay value: closer distance results in a shorter delay and beep frequency
  unsigned int time = map(distanceCm, 0, 50, 100, 500); 
  unsigned int beepFrequency = map(distanceCm, 0, 50, 2000, 500);
  
  // All leds blink and buzzer sounds beep-pause-beep
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  tone(buzzer_pin, beepFrequency);
  delay(time);
 
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  noTone(buzzer_pin);
  delay(time);
}
