// Test CSBuzzer class
// Stephen Flores

#include "CSBuzzer.h"

CSBuzzer buzzer;

void setup() {
    Serial.begin(9600);
    buzzer.config(23);
    buzzer.setDebugMode(true);
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
            default:
                Seria.println("Invalid command");
        }
    }
    
    // Buzzer runs infinitely in the background
    buzzer.main();
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