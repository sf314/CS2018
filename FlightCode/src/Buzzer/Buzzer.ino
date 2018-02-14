// Test CSBuzzer class
// Stephen Flores

#include "CSBuzzer.h"

CSBuzzer buzzer;

void setup() {
    Serial.begin(9600);
    
    // buzzer.config(20);
    // buzzer.setDebugMode(true);
    // 
    // delay(300);
    // noTone(20);
    // buzzer.playStartup();
    // delay(300);
    
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);
    delay(500);
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case 'b':
                buzzer.toggle();
                break;
            case 'p':
                buzzer.playSong();
                break;
            case 's':
                buzzer.playStartup();
                break;
            case 'e':
                Serial.println("on");
                digitalWrite(20, HIGH);
                digitalWrite(21, LOW);
                break;
            case 'r':
                Serial.println("off");
                digitalWrite(20, LOW);
                digitalWrite(21, LOW);
                break;
            default:
                Serial.println("Invalid command");
        }
    }
    
    // Buzzer runs infinitely in the background
    // buzzer.main();
}


// void setup() {
//     Serial.begin(9600);
//     pinMode(23, OUTPUT);
// }
// int isOn = false;
// void loop() {
//     if (Serial.available()) {
//         isOn = !isOn;
//         
//         if (isOn) {
//             digitalWrite(23, HIGH);
//         } else {
//             digitalWrite(23, LOW);
//         }
//     }
// }