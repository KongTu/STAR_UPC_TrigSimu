#include "Board.hh"
#include "bits.hh"
#include "bbc_bb101_2016_a.hh"
//#include <stdio.h>

void bbc_bb101_2016_a(Board& bb101)
{
  //registers
  const int R0 = bb101.registers[0];
  const int R1 = bb101.registers[1];
  const int R2 = bb101.registers[2];
  const int R3 = bb101.registers[3];

  //input
  const int bb001 = (bb101.channels[0] & 0xffff) | bb101.channels[1] << 16;
  const int bb002 = (bb101.channels[2] & 0xffff) | bb101.channels[3] << 16;

  //algo

  int bb001adc = getbits(bb001, 0, 16);
  int bb002adc = getbits(bb002, 0, 16);

  int bb001adcth = bb001adc > R0;
  int bb002adcth = bb002adc > R1;

  int bb001tac = getbits(bb001, 16, 12);
  int bb002tac = getbits(bb002, 16, 12);

  int tacdiff = 4096 + bb001tac - bb002tac;
  int bb001goodtac = bb001tac > 0;
  int bb002goodtac = bb002tac > 0;
  if(! bb001goodtac || ! bb002goodtac) tacdiff = 0;

 // printf("simu: tac1=%d, tac2=%d diff=%d\n", bb001tac, bb002tac, tacdiff);

//  int bb001tac_sel = getbits(bb001tac, R2, 6) & 0x7f;
//  if(bb001tac >> (R2+7)) bb001tac_sel = 0x7f;

//  int bb002tac_sel = getbits(bb002tac, R3, 6) & 0x7f;
//  if(bb002tac >> (R3+7)) bb002tac_sel = 0x7f;
  int tacsum = bb001tac + bb002tac;
  int tacwin = tacsum > R2 && tacsum < R3 && bb001goodtac && bb002goodtac;
  bb101.output = 0x0;
  bb101.output = (tacdiff |
		  tacwin << 13 |
		  bb001adcth << 14 |
		  bb002adcth << 15
		  );		       
}
