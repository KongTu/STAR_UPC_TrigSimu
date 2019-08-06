#include "Board.hh"
#include "bits.hh"
#include "fms_fm103_2015_a.hh"

void fms_fm103_2015_a(Board& fm103)
{
  int fm005 = fm103.channels[0] | fm103.channels[1] << 16; //Top/Side
  int fm006 = fm103.channels[2] | fm103.channels[3] << 16; //Top
  int fm007 = fm103.channels[4] | fm103.channels[5] << 16; //Bottom/Side
  int fm008 = fm103.channels[6] | fm103.channels[7] << 16; //Bottom


  const int R0 = fm103.registers[0]; //FMSsmall-BS-th1
  const int R1 = fm103.registers[1]; //FMSsmall-BS-th2
  const int R2 = fm103.registers[2]; //FMSsmall-BS-th3
  //DD Board Sum
  int T_JJ = getbits(fm005, 4, 12);
  int B_JJ = getbits(fm007, 4, 12);

  int BS_JJ = T_JJ + B_JJ;
  //overlapping jet patches
  int T_JP_EF = getbits(fm006, 16, 8);

  int T_JP_GH = getbits(fm005, 16, 8);
  int T_JP_IJ = getbits(fm005, 24, 8);

  int B_JP_EF = getbits(fm008, 16, 8);

  int B_JP_GH = getbits(fm007, 16, 8);
  int B_JP_IJ = getbits(fm007, 24, 8);

  int JP_T = T_JP_EF + T_JP_GH + T_JP_IJ;
  if(JP_T > 0xff) JP_T = 0xff;
  int JP_M = T_JP_IJ + B_JP_IJ;
  if(JP_M > 0xff) JP_M = 0xff;
  int JP_B = B_JP_EF + B_JP_GH + B_JP_IJ;
  if(JP_B > 0xff) JP_B = 0xff;
  //
  int bs3 = (BS_JJ > R2) || btest(fm005, 0) || btest(fm006, 0) || btest(fm007, 0) || btest(fm008, 0);
  int bs2 = (BS_JJ > R1) || btest(fm005, 1) || btest(fm006, 1) || btest(fm007, 1) || btest(fm008, 1);;
//  int bs1_t = (BS_JJ > R0) || btest(fm006, 2);
  int bs1_t = btest(fm006, 2);
  int bs1_m = (BS_JJ > R0) || btest(fm005, 2) || btest(fm006, 3) || btest(fm007, 2) || btest(fm008, 3);
//  int bs1_b = (BS_JJ > R0) || btest(fm008, 2);
  int bs1_b = btest(fm008, 2);

  fm103.output = 0;
  fm103.output = 
    bs3 |
    bs2 << 1 |
    bs1_t << 2 |
    bs1_m << 3 |
    bs1_b << 4 |
    JP_T << 5 |
    JP_M << 16 |
    JP_B << 24;
}
