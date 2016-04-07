/*
SindormirSevenSegments.h - Library for using Seven Segments Display
Created by Jorge Gomez @ Sindormir.net 2016
Released under the terms of the GPL v3 License
*/

#include "Arduino.h"
#include "SindormirSevenSegments.h"

SindormirSevenSegments::SindormirSevenSegments(byte _sA, byte _sB, byte _sC, byte _sD, byte _sE, byte _sF, byte _sG, byte _sDP){

    //Create array for segments and inizialize outputs (All HIGH)
    _segs[0] = _sA;
    _segs[1] = _sB;
    _segs[2] = _sC;
    _segs[3] = _sD;
    _segs[4] = _sE;
    _segs[5] = _sF;
    _segs[6] = _sG;
    _segs[7] = _sDP;

    for (byte i=0; i<8; i++){
        pinMode(_segs[i], OUTPUT);
        digitalWrite(_segs[i], HIGH);
    }
}

void SindormirSevenSegments::commonType(char type){
    if ((type == 'A') or (type == 'a')) _sT = true;
    else _sT = false;
}

void SindormirSevenSegments::print(char num){
    //                      A, B, C, D, E, F, G, DP
    byte symbols[17][8]= { {1, 1, 1, 1, 1, 1, 0, 0}, //0
                           {0, 1, 1, 0, 0, 0, 0, 0}, //1
                           {1, 1, 0, 1, 1, 0, 1, 0}, //2
                           {1, 1, 1, 1, 0, 0, 1, 0}, //3
                           {0, 1, 1, 0, 0, 1, 1, 0}, //4
                           {1, 0, 1, 1, 0, 1, 1, 0}, //5
                           {1, 0, 1, 1, 1, 1, 1, 0}, //6
                           {1, 1, 1, 0, 0, 0, 0, 0}, //7
                           {1, 1, 1, 1, 1, 1, 1, 0}, //8
                           {1, 1, 1, 0, 0, 1, 1, 0}, //9
                           {1, 1, 1, 0, 1, 1, 1, 0}, //A
                           {0, 0, 1, 1, 1, 1, 1, 0}, //b
                           {1, 0, 0, 1, 1, 1, 0, 0}, //C
                           {0, 1, 1, 1, 1, 0, 1, 0}, //d
                           {1, 0, 0, 1, 1, 1, 1, 0}, //E
                           {1, 0, 0, 0, 1, 1, 1, 0}, //F
                           {0, 0, 0, 0, 0, 0, 0, 0}  //BLANK
    };
    char d;

    if ((num == 0) || (num == '0')) d = 0;
    else if ((num == 1) || (num == '1')) d = 1;
    else if ((num == 2) || (num == '2')) d = 2;
    else if ((num == 3) || (num == '3')) d = 3;
    else if ((num == 4) || (num == '4')) d = 4;
    else if ((num == 5) || (num == '5')) d = 5;
    else if ((num == 6) || (num == '6')) d = 6;
    else if ((num == 7) || (num == '7')) d = 7;
    else if ((num == 8) || (num == '8')) d = 8;
    else if ((num == 9) || (num == '9')) d = 9;
    else if ((num == 10) || (num == 'A') || (num == 'a')) d = 10;
    else if ((num == 11) || (num == 'B') || (num == 'b')) d = 11;
    else if ((num == 12) || (num == 'C') || (num == 'c')) d = 12;
    else if ((num == 13) || (num == 'D') || (num == 'd')) d = 13;
    else if ((num == 14) || (num == 'E') || (num == 'e')) d = 14;
    else if ((num == 15) || (num == 'F') || (num == 'f')) d = 15;
    else d = 16;

    for (byte i=0; i<8; i++) {
        digitalWrite(_segs[i], symbols[d][i] ^ _sT);
    }
}
