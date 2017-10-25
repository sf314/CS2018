

void setup() {
    Serial.begin(9600);
    pinMode(23, OUTPUT);
}
int isOn = false;
void loop() {
    if (Serial.available()) {
        isOn = !isOn;
        
        if (isOn) {
            digitalWrite(23, HIGH);
        } else {
            digitalWrite(23, LOW);
        }
    }
}