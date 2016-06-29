/*
SindormirSevenSegments.h - Library for using Seven Segments Display
Created by Jorge Gomez @ Sindormir.net
Released under the terms of the GPL v3 License
*/

#ifndef SindormirSevenSegments_h
#define SindormirSevenSegments_h

#define Sindormir7segs SindormirSevenSegments
#define LED7seg SindormirSevenSegments
#define A 'a'
#define ANODO 'a'
#define ANODE 'a'
#define C 'k'
#define K 'k'
#define CATODO 'k'
#define CATHODE 'k'
#define NEG 16
#define BLANK 18
#define NONE 255

#include "Arduino.h"

class SindormirSevenSegments {
    public:
        SindormirSevenSegments(void);
        void attach_segs(byte _sA, byte _sB, byte _sC, byte _sD, byte _sE, byte _sF, byte _sG, byte _sDP);
        void attach_segs(byte _sA, byte _sDP);
        void attach_symb(byte _d0, byte _d1, byte _d2, byte _d3, byte _d4, byte _d5, byte _d6, byte _d7);
        void attach_symb(byte _d0, byte _d1){attach_symb(_d0,_d1,NONE,NONE,NONE,NONE,NONE,NONE);}
        void attach_symb(byte _d0, byte _d1, byte _d2){attach_symb(_d0,_d1,_d2,NONE,NONE,NONE,NONE,NONE);}
        void attach_symb(byte _d0, byte _d1, byte _d2, byte _d3){attach_symb(_d0,_d1,_d2,_d3,NONE,NONE,NONE,NONE);}
        void commonType(char t, boolean invert);
        void lampTest(void);
        void clear(void);
        void setSymbol(byte n, char ch);
        void setDot(byte n);
        void clearDot(void);
        void multiplex(void);
        void setSegs(byte sym);
        void print(long n, byte base);
        void print(long n){print(n,10);}
        void delayms(unsigned long ms);

    private:
        byte _nsymb;
	byte _mux;
        byte _segs[8];
        byte _symb[8];
        byte _symval[8];
        byte _dotmask;

	boolean _sT;
        boolean _inv;
	long _longval;
};

#endif
