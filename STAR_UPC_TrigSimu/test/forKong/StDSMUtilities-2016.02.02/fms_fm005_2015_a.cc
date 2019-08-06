#include "Board.hh"
#include "bits.hh"
//#include "qt32b_fms_2009_a.hh"
#include "fms_fm005_2015_a.hh"

void fms_fm005_2015_a(Board& fm005)
{
  const int R0 = fm005.registers[0]; //FMSsmall-BS-th1 (13)
  const int R1 = fm005.registers[1]; //FMSsmall-BS-th2 (13)
  const int R2 = fm005.registers[2]; //FMSsmall-BS-th3 (13)
  const int R3 = fm005.registers[3]; //FMSsmall-BitSelect (3)

  int J = fm005.channels[0] | fm005.channels[1] << 16;
  int I = fm005.channels[2] | fm005.channels[3] << 16;
  int H = fm005.channels[4] | fm005.channels[5] << 16;
  int G = fm005.channels[6] | fm005.channels[7] << 16;

  int Gsum01 = getbits(G, 0, 12);
  int Gsum23 = getbits(G, 16, 12);

  int Hsum01 = getbits(H, 0, 12);
  int Hsum23 = getbits(H, 16, 12);

  int Isum01 = getbits(I, 0, 12);
  int Isum23 = getbits(I, 16, 12);

  int Jsum01 = getbits(J, 0, 12);
  int Jsum23 = getbits(J, 16, 12);

  //BS Sum
  int BS_G = Gsum01 + Gsum23;
  int BS_GH = Gsum23 + Hsum01;
  int BS_H = Hsum01 + Hsum23;
  int BS_HI = Hsum23 + Isum01;
  int BS_I = Isum01 + Isum23;
  int BS_IJ = Isum23 + Jsum01;
  int BS_J = Jsum01 + Jsum23;
  //JP Sum
  int JP_GH = BS_G + BS_H;
  int JP_IJ = BS_I + BS_J;
  //BS threshold bit
  int bs3 = (BS_G > R2) || (BS_GH > R2) || (BS_H > R2) || (BS_HI > R2) || (BS_I > R2) || (BS_IJ > R2) || (BS_J > R2);
  int bs2 = (BS_G > R1) || (BS_GH > R1) || (BS_H > R1) || (BS_HI > R1) || (BS_I > R1) || (BS_IJ > R1) || (BS_J > R1);
  int bs1 = (BS_G > R0) || (BS_GH > R0) || (BS_H > R0) || (BS_HI > R0) || (BS_I > R0) || (BS_IJ > R0) || (BS_J > R0);

  //JP bits
  int jp_gh = getbits(JP_GH, R3, 8);
  if(JP_GH >> (R3+8)) jp_gh = 0xff;

  int jp_ij = getbits(JP_IJ, R3, 8);
  if(JP_IJ >> (R3+8)) jp_ij = 0xff;

  fm005.output = 0;
  fm005.output = 
    bs3 |
    bs2 << 1 |
    bs1 << 2 |
    Jsum23 << 4 |
    jp_gh << 16 |
    jp_ij << 24;
}
