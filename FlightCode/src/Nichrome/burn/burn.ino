

/*
Test Nichrome wire with keyboard control
*/

// Vars
int nichromePin = 23;
bool active = false;

void setup() {
    Serial.begin(9600);
    
    pinMode(23, OUTPUT);
    Serial.println("Starting...");
}

void loop() {
    // Check for serial commands constantly
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case 'x':
                active = !active; // Switch mode each time
                break;
            default:
                Serial.println("Unknown command!");
        }
    }
    
    
    // Continuous
    if (active) {
        digitalWrite(nichromePin, HIGH);
    } else {
        digitalWrite(nichromePin, LOW);
    }
}