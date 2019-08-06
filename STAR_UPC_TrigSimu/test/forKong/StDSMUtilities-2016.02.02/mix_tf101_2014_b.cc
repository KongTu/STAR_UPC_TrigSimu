#include "bits.hh"
#include "Board.hh"
#include "mix_tf101_2014_b.hh"
//#include <stdio.h>

void mix_tf101_2014_b(Board& tf101)
{
  const int R0 = tf101.registers[0]; //TOF-sector-th(10)
  const int R1 = tf101.registers[1]; //TOF_upc_East_mask(12)
  const int R2 = tf101.registers[2]; //TOF_upc_West_mask(12)
  //(0:9) TOF multiplicity
  //(10:13) UPC threshold bits
  //(14:15) Unused
  int upce[12]; //start from 12 o'clock
  int upcw[12];
  for(int ichn = 0; ichn < 6; ichn++){
    upce[(2*ichn+9)%12] = btest(tf101.channels[ichn], 12);
    upce[(2*ichn+10)%12] = btest(tf101.channels[ichn], 13);
    upcw[(2*ichn+9)%12] = btest(tf101.channels[ichn], 10);
    upcw[(2*ichn+10)%12] = btest(tf101.channels[ichn], 11);
  }

  int sum0 = getbits(tf101.channels[0], 0, 10) + getbits(tf101.channels[1], 0, 10);
  int sum2 = getbits(tf101.channels[2], 0, 10) + getbits(tf101.channels[3], 0, 10);
  int sum4 = getbits(tf101.channels[4], 0, 10) + getbits(tf101.channels[5], 0, 10);

  int goodmult[6];
  for(int ichn = 0; ichn < 6; ichn++){
    int mult = getbits(tf101.channels[ichn], 0, 10);
    goodmult[ichn] = mult > R0;
  }

  int sum03 = sum0 + sum2;
  for(int iclk = 0; iclk < 12; iclk++){
    if(!((R1 >> iclk) & 0x1))
      upce[iclk] = 0;
    if(!((R2 >> iclk) & 0x1))
      upcw[iclk] = 0;
  }

  int upc[12];
  for(int iclk = 0; iclk < 12; iclk++){
    upc[iclk] = upce[iclk] || upcw[iclk];
//    printf("upc_%d=%d ", iclk, upc[iclk]);
  }
//  printf("\n");

  int tofupc = 0;
  for(int iclk = 0; iclk < 12; iclk++)
    {
      tofupc |= upc[iclk] && upc[(iclk+4)%12];
    }
//  printf("tofupc=%d\n", tofupc);
  int sum = sum03 + sum4;
  tf101.output = 0;
  tf101.output =
    sum   |
    goodmult[0] << 16 |
    goodmult[1] << 17 |
    goodmult[2] << 18 |
    goodmult[3] << 19 |
    goodmult[4] << 20 |
    goodmult[5] << 21 |
    tofupc << 22;
}
