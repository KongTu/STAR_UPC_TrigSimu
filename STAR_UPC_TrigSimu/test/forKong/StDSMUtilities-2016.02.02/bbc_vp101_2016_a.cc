#include "Board.hh"
#include "bits.hh"
#include "bbc_vp101_2016_a.hh"
//#include "stdio.h"

void bbc_vp101_2016_a(Board& vp101)
{
  //registers
  //R0 VPD-EastADCsum_th (12)
  //R1 VPD-WestADCsum_th (12)
  //R2 VPD-meanDiff-window1 (12)
  //R3 VPD-meanDiff-window2 (12)
  //R4 VPD-meanDiff-window3 (12)
  const int R0 = vp101.registers[0];
  const int R1 = vp101.registers[1];
  const int R2 = vp101.registers[2];
  const int R3 = vp101.registers[3];
  const int R4 = vp101.registers[4];
  //printf("R0=%d, R1=%d, R2=%d, R3=%d, R4=%d\n", R0, R1, R2, R3, R4);
  //input
  const int vp003 = (vp101.channels[4] & 0xffff) | vp101.channels[5] << 16;
  const int vp004 = (vp101.channels[6] & 0xffff) | vp101.channels[7] << 16;

  //algo

  int vp003adc = getbits(vp003, 0, 12);
  int vp004adc = getbits(vp004, 0, 12);

  int vp003adcth = vp003adc > R0;
  int vp004adcth = vp004adc > R1;

  int vp003tac = getbits(vp003, 16, 16);
  int vp004tac = getbits(vp004, 16, 16);

  int vp003nhits = getbits(vp003, 12, 4);
  int vp004nhits = getbits(vp004, 12, 4);
  //printf("vp003tac=%d, vp003nhits=%d, vp004tac=%d, vp004nhits=%d\n", 
  //	vp003tac, vp003nhits, vp004tac, vp004nhits);

  int tacdiff = vp003tac*vp004nhits - vp004tac*vp003nhits;
  if(tacdiff < 0) tacdiff = -1 * tacdiff;
  //printf("tacdiff=%d, vp003nhits*vp004nhits=%d\n", tacdiff, vp003nhits*vp004nhits);
     int tacw1 = 0;
     if(tacdiff < R2*vp003nhits*vp004nhits) tacw1 = 1;
     int tacw2 = 0;
     if(tacdiff < R3*vp003nhits*vp004nhits) tacw2 = 1;
     int tacw3 = 0;
     if(tacdiff < R4*vp003nhits*vp004nhits) tacw3 = 1;
     
     
  vp101.output = 0x0;
  vp101.output = (tacw1 << 0 |
		  tacw2 << 1 |
		  tacw3 << 2 |
		  vp003adcth << 14 |
		  vp004adcth << 15
		  );		       
}
