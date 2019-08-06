#include "Board.hh"
#include "bits.hh"
#include "bbc_vp101_2009_a.hh"
//#include "stdio.h"

void bbc_vp101_2009_a(Board& vp101)
{
  //registers
  const int R0 = vp101.registers[0];
  const int R1 = vp101.registers[1];

  //input
  const int vp003 = (vp101.channels[4] & 0xffff) | vp101.channels[5] << 16;
  const int vp004 = (vp101.channels[6] & 0xffff) | vp101.channels[7] << 16;

  //algo

  int vp003adc = getbits(vp003, 0, 16);
  int vp004adc = getbits(vp004, 0, 16);

  int vp003adcth = vp003adc > R0;
  int vp004adcth = vp004adc > R1;

  int vp003tac = getbits(vp003, 16, 12);
  int vp004tac = getbits(vp004, 16, 12);

  int tacdiff = 4096 + vp003tac - vp004tac;
  int vp003goodtac = vp003tac > 0;
  int vp004goodtac = vp004tac > 0;
  if(! vp003goodtac || ! vp004goodtac) tacdiff = 0;

  vp101.output = 0x0;
  vp101.output = (tacdiff << 0 |
		  vp003adcth << 14 |
		  vp004adcth << 15
		  );		       
}
