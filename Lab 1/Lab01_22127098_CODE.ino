const int buttonPin = 8;	// Button pin
const int led1 = 13;        // Led 1: Yellow
const int led2 = 12;        // Led 2: Orange
const int led3 = 11;        // Led 3: Blue
const int led4 = 4;         // Led 4: White
const int led5 = 3;         // Led 5: Red
const int led6 = 2;         // Led 6: Green

int buttonState = LOW;         	// Current state of button
int lastButtonState = LOW;     	// Previous state of button

unsigned long pressedTime = 0;  	 // Time the button was pressed
unsigned long releasedTime = 0; 	 // Time the button was released

bool isMode1 = true;         		 // Current mode (Mode 1 is default)
unsigned long lastSwitchTime = 0;    // Time for led change color in Mode 2
int mode2State = 0;          		 // Current led status in Mode 2 (0: Led 4, 1: Led 5, 2: Led 6)

void setup() {
  // Set up button as input
  pinMode(buttonPin, INPUT); 
  
  // Set up leds as outputs
  pinMode(led1, OUTPUT);      
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  // Default mode
  mode1();
}

void loop() {
  buttonState = digitalRead(buttonPin); // Read the button state
  
  // Check if the button is pressed
  if (buttonState == HIGH && lastButtonState == LOW) {
    pressedTime = millis(); // Save button pressed time
  }

  // Check if the button is released
  if (buttonState == LOW && lastButtonState == HIGH) {
    releasedTime = millis(); // Save button released time
    
    if (releasedTime - pressedTime >= 4000) {
      // If button is held >= 4s, switch to Mode 2
      isMode1 = false;
      
      // Reset time and index for mode 2 
      lastSwitchTime = millis(); 
      mode2State =  0;
    } else {
      // If button is held < 4s, switch to Mode 1
      isMode1 = true;
      mode1();
    }
  }

  // If in Mode 2, led 4,5, 6 light up alternately
  if (!isMode1) {
    mode2();
  }

  // Save the current button state for the next loop
  lastButtonState = buttonState;
}


void mode1() {
  // Turn led 1, 2, 3 up
  digitalWrite(led1, HIGH);  
  digitalWrite(led2, HIGH);  
  digitalWrite(led3, HIGH); 
  
  // Turn led 4, 5, 6 off
  digitalWrite(led4, LOW);   
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
}

void mode2() {
  unsigned long currentMillis = millis();

  // State change every 1s
  if (currentMillis - lastSwitchTime >= 1000) {
    lastSwitchTime = currentMillis; //Update last switch time

    // Led 4, 5, 6 light up alternately
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    
    switch (mode2State) {
      case 0:
      	digitalWrite(led4, HIGH);
      	mode2State = 1;
      	break;
      case 1:
      	digitalWrite(led5, HIGH);
      	mode2State = 2;
      	break;
      case 2: 
      	digitalWrite(led6, HIGH);
      	mode2State = 0;
      	break;
    }
  }
}
