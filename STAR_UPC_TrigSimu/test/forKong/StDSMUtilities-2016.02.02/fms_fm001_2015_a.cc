#include "Board.hh"
#include "bits.hh"
//#include "qt32b_fms_2009_a.hh"
#include "fms_fm001_2015_a.hh"
#include <stdio.h>
void fms_fm001_2015_a(Board& fm001)
{
  const int R0 = fm001.registers[0]; //FMSsmall-BS-th1 (13)
  const int R1 = fm001.registers[1]; //FMSsmall-BS-th2 (13)
  const int R2 = fm001.registers[2]; //FMSsmall-BS-th3 (13)
  const int R3 = fm001.registers[3]; //FMSsmall-BitSelect (3)

  int D = fm001.channels[0] | fm001.channels[1] << 16;
  int C = fm001.channels[2] | fm001.channels[3] << 16;
  int B = fm001.channels[4] | fm001.channels[5] << 16;
  int A = fm001.channels[6] | fm001.channels[7] << 16;

  int Asum01 = getbits(A, 0, 12);
  int Asum23 = getbits(A, 16, 12);
  //  printf("A(0:1)=%d, A(2:3)=%d\n", Asum01, Asum23);
  //  printf("R2=%d\n", R2);
  int Bsum01 = getbits(B, 0, 12);
  int Bsum23 = getbits(B, 16, 12);

  int Csum01 = getbits(C, 0, 12);
  int Csum23 = getbits(C, 16, 12);

  int Dsum01 = getbits(D, 0, 12);
  int Dsum23 = getbits(D, 16, 12);
  //  printf("D(0:1)=%d, D(2:3)=%d\n", Dsum01, Dsum23);
  //BS Sum
  int BS_A = Asum01 + Asum23;
  int BS_B = Bsum01 + Bsum23;
  int BS_BC = Bsum23 + Csum01;
  int BS_C = Csum01 + Csum23;
  int BS_CD = Csum23 + Dsum01;
  int BS_D = Dsum01 + Dsum23;
  //JP Sum
  int JP_AB = BS_A + BS_B;
  int JP_CD = BS_C + BS_D;
  //BS threshold bit
  int bs3 = (BS_A > R2) || (BS_B > R2) || (BS_BC > R2) || (BS_C > R2) || (BS_CD > R2) || (BS_D > R2);
  int bs2 = (BS_A > R1) || (BS_B > R1) || (BS_BC > R1) || (BS_C > R1) || (BS_CD > R1) || (BS_D > R1);
  int bs1_bcd = (BS_B > R0) || (BS_C > R0) || (BS_D > R0) || (BS_BC > R0) || (BS_CD > R0);
  int bs1_a = BS_A > R0;
  //JP bits
  int jp_ab = getbits(JP_AB, R3, 8);
  if(JP_AB >> (R3+8)) jp_ab = 0xff;

  int jp_cd = getbits(JP_CD, R3, 8);
  if(JP_CD >> (R3+8)) jp_cd = 0xff;

  fm001.output = 0;
  fm001.output = 
    bs3 |
    bs2 << 1 |
    bs1_bcd << 2 |
    bs1_a << 3 |
    Dsum23 << 4 |
    jp_ab << 16 |
    jp_cd << 24;
}
