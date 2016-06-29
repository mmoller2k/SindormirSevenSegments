#include <SindormirSevenSegments.h>

#define tDelay 250

unsigned long t0=0;
int count = -99;

LED7seg x7seg;

void setup()
{
  x7seg.commonType(CATHODE,true); //inverted cathode drivers
  x7seg.attach_segs(0,1,2,3,4,5,6,7); //segment drivers
  x7seg.attach_symb(8,9,10); //three digits
}

void loop()
{
  unsigned long now = millis();
  if(now-t0 >= tDelay){
    t0 = now;
    x7seg.print(count);
    if(count>199)count=-99;
    else count++;
  }
  x7seg.multiplex();
}
