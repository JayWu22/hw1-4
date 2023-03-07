#include "mbed.h"
#include "string"
#include "map"
#include <cstdio>

BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
DigitalIn mypin(BUTTON1);
DigitalOut myled(LED1);

map<std::string, char> letter = {
    {"00001", 0x77},
    {"01100", 0x7C},
    {"01101", 0x39},
    {"01111", 0x5E},
    {"00010", 0x79},
    {"01110", 0x71},
    {"01010", 0x3D},
    {"01011", 0x76}, 
    {"00110", 0x30}, 
    {"01001", 0x1E}, 
    {"11001", 0x75}, 
    {"11011", 0x38}, 
    {"11010", 0x55}, 
    {"11110", 0x54}, 
    {"00111", 0x5C}, 
    {"11111", 0x73}, 
    {"11101", 0x67}, 
    {"11100", 0x50}, 
    {"10100", 0x6D},
    {"10101", 0x78}, 
    {"00101", 0x3E}, 
    {"10111", 0x1C}, 
    {"10110", 0x1D}, 
    {"10010", 0x64}, 
    {"00100", 0x6E}, 
    {"10011", 0x5B}
};

map<std::string, char> figure = {
    {"01111", 0x3F}, {"00001", 0x06}, {"00010", 0x5B}, {"00100", 0x4F}, {"00101", 0x66}, {"00111", 0x6D}, 
    {"01001", 0x7D}, {"01010", 0x07}, {"01100", 0x7F}, {"01101", 0x6F}
};

// main() runs in its own thread in the OS
int main()
{
    mypin.mode(PullNone);
    char show[3];
    int let = 1; 
    for (int i=0; i < 3; i++) {
        std::string re;
        myled=1;
        ThisThread::sleep_for(500ms);
        re = to_string(!mypin);
        myled.write(0);
        ThisThread::sleep_for(500ms);
        for (int j=0; j < 4; j++) {
            myled=1;
            ThisThread::sleep_for(500ms);
            re = re + to_string(!mypin);
            myled.write(0);
            ThisThread::sleep_for(500ms);
        }
        printf("%s\n,", re.c_str());
        if (let == 1 && re != "01000" && re != "10000") {
            show[i] = letter[re];
        } else if (let == 0 && re != "01000" && re != "10000") {
            show[i] = figure[re];
        } else if (re == "01000") {
            let = 0;
            i--;
        } else if (re == "10000") {
            let = 1;
            i--;
        }
    }
    int i = 0;
    while (1) {
        display = show[i % 3];
        ThisThread::sleep_for(1s);
        i++;
    }
}

