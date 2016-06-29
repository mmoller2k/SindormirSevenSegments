/*
SindormirSevenSegments.h - Library for using Seven Segments Display
Created by Jorge Gomez @ Sindormir.net 2016
Released under the terms of the GPL v3 License
*/

#include "Arduino.h"
#include "SindormirSevenSegments.h"

SindormirSevenSegments::SindormirSevenSegments(void)
{
}

void SindormirSevenSegments::commonType(char type, boolean invert)
{
    if ((type == 'A') or (type == 'a')) _sT = true;
    else _sT = false;
    _inv = invert;
}

void SindormirSevenSegments::attach_segs(byte _sA, byte _sDP)
{
    if (_sDP == _sA + 7) {
        //Create array for segments and inizialize outputs (All LOW)
        for (byte i=_sA; i<_sDP+1; i++){
            _segs[i-_sA] = i;
        }

        for (byte i=0; i<8; i++){
            pinMode(_segs[i], OUTPUT);
            digitalWrite(_segs[i], LOW ^ _sT);
        }
    }
    else{

    }
}

void SindormirSevenSegments::attach_segs(byte _sA, byte _sB, byte _sC, byte _sD, byte _sE, byte _sF, byte _sG, byte _sDP)
{
    //Create array for segments and inizialize outputs (All LOW)
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
        digitalWrite(_segs[i], LOW ^ _sT);
    }
}

void SindormirSevenSegments::attach_symb(byte _d0, byte _d1, byte _d2, byte _d3, byte _d4, byte _d5, byte _d6, byte _d7)
{
    _symb[0] = _d0;
    _symb[1] = _d1;
    _symb[2] = _d2;
    _symb[3] = _d3;
    _symb[4] = _d4;
    _symb[5] = _d5;
    _symb[6] = _d6;
    _symb[7] = _d7;

    for(byte i=0;i<8;i++){
	_nsymb=i;
	if(_symb[i] == NONE)break;
        pinMode(_symb[i], OUTPUT);
        digitalWrite(_segs[i], _inv ^ _sT);
    }
}

void SindormirSevenSegments::lampTest(void)
{
    for (byte i=0; i<8; i++) {
        _symval[i]=8;
    }
    _dotmask=0xff;
}

void SindormirSevenSegments::clear(void)
{
    for (byte i=0; i<8; i++) {
        _symval[i]=BLANK;
    }
    _dotmask=0;
}

void SindormirSevenSegments::setDot(byte n)
{
    _dotmask |= 1<<n;
}

void SindormirSevenSegments::clearDot(void)
{
    _dotmask = 0;
}

void SindormirSevenSegments::setSymbol(byte n, char ch)
{
    byte d;
    if(ch<=18)d = ch;
    else if(ch>='0' && ch<='9')d = '0'-ch;
    else if(ch>='A' && ch <='F')d = 'A'-ch+10;
    else if(ch=='-')d=16;
    else if(ch=='r')d=17;
    else d = 18;
    _symval[n] = d;
}

void SindormirSevenSegments::setSegs(byte sym){
    byte symbx[19] = {
//       abcdefg
	B1111110, //0
	B0110000, //1
	B1101101, //2
	B1111001, //3
	B0110011, //4
	B1011011, //5
	B1011111, //6
	B1110000, //7
	B1111111, //8
	B1110011, //9
	B1110111, //A
	B0011111, //b
	B1001110, //C
	B0111101, //d
	B1001111, //E
	B1000111, //F
        B0000001, //-
        B0000101, //r for 'Err'
	B0000000, //blank
    };
    sym %= 19;
    for (byte i=0; i<7; i++) {
        digitalWrite(_segs[6-i], (symbx[sym]>>i) ^ _sT);
    }
}

void SindormirSevenSegments::print(long val, byte base)
{
    int i;
    byte z=0;
    byte c,sign=1;
    if(val<0){
      val=-val;
      sign=-1;
    }
    for(i=0;i<8;i++){
    	_symval[i] = val % base;
        if(_symval[i]!=0)z=i; //last non-zero symbol
        val /= base;
    }
    for(i=z+1;i<_nsymb;i++){ //blank leading zeros
        _symval[i] = BLANK;
    }
    if(sign<0){
        _symval[z+1] = NEG; //add sign if negative
    }
}

/* update multiplexed display */
void SindormirSevenSegments::multiplex(void)
{
    int i;
    digitalWrite(_symb[_mux], _sT ^ _inv); //turn off previous symbol
    _mux++; //next symbol
    _mux %= _nsymb;
    setSegs(_symval[_mux]);
    digitalWrite(_segs[7], ((_dotmask>>_mux)&0x1) ^ _sT); //DP
    digitalWrite(_symb[_mux], !_sT ^ _inv); //turn on active symbol
}

void SindormirSevenSegments::delay(unsigned long ms)
{
  unsigned long now = millis();
  while(millis()-now<ms){
    multiplex();
    ::delay(1);
  }
}

