// Team NEXUS - Smart Safety Keychain
// Members: Amullya, Roshni, Yankamma, Likitha
// Components: ESP32-C3, Tactile Button, Active Buzzer

// Pin Configuration
const int buttonPin = 2; // The pin where your button is connected
const int buzzerPin = 3; // The pin where your buzzer is connected

// Timing for the 3-second long-press logic
unsigned long pressStartTime = 0;
const int longPressDuration = 3000; // 3000 milliseconds = 3 seconds

void setup() {
  // Initialize the pins
  pinMode(buttonPin, INPUT_PULLUP); // Using internal pullup for the button
  pinMode(buzzerPin, OUTPUT);       // Setting buzzer as output
  
  Serial.begin(115200);
  Serial.println("System Initialized: Nexus SOS Active.");
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // If button is pressed (LOW because of INPUT_PULLUP)
  if (buttonState == LOW) {
    if (pressStartTime == 0) {
      pressStartTime = millis(); // Start the timer
    }
    
    // If held for 3 seconds, trigger the SOS
    if (millis() - pressStartTime >= longPressDuration) {
      triggerSOS();
    }
  } 
  else {
    // If button is released, reset the timer and turn off buzzer
    pressStartTime = 0;
    digitalWrite(buzzerPin, LOW);
  }
}

void triggerSOS() {
  Serial.println("EMERGENCY! Sending Location via Bluetooth...");
  
  // Make the buzzer beep in a loud pattern
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}
