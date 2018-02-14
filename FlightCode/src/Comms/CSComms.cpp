// CSComms


#include "CSComms.h"

CSComms::CSComms(SoftwareSerial* s) {
    ss = s;
}

void CSComms::config() {
    
}

void CSComms::begin(int x) {
    ss->begin(x);
}

void CSComms::print(String s) {
    ss->print(s);
}
void CSComms::println(String s) {
    ss->println(s);
}

bool CSComms::available() {
    return ss->available();
}

char CSComms::read() {
    return ss->read();
}