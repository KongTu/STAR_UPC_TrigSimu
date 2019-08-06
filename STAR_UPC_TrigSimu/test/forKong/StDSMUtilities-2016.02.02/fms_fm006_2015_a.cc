#include "Board.hh"
#include "bits.hh"
//#include "qt32b_fms_2009_a.hh"
#include "fms_fm006_2015_a.hh"

void fms_fm006_2015_a(Board& fm006)
{
  const int R0 = fm006.registers[0]; //FMSsmall-BS-th1 (13)
  const int R1 = fm006.registers[1]; //FMSsmall-BS-th2 (13)
  const int R2 = fm006.registers[2]; //FMSsmall-BS-th3 (13)
  const int R3 = fm006.registers[3]; //FMSsmall-BitSelect (3)

  int F = fm006.channels[0] | fm006.channels[1] << 16;
  int E = fm006.channels[2] | fm006.channels[3] << 16;

  int Esum01 = getbits(E, 0, 12);
  int Esum23 = getbits(E, 16, 12);

  int Fsum01 = getbits(F, 0, 12);
  int Fsum23 = getbits(F, 16, 12);
  //BS Sum
  int BS_E = Esum01 + Esum23;
  int BS_EF = Esum23 + Fsum01;
  int BS_F = Fsum01 + Fsum23;
  //JP Sum
  int JP_EF = BS_E + BS_F;
  //BS threshold bit
  int bs3 = (BS_E > R2) || (BS_EF > R2) || (BS_F > R2);
  int bs2 = (BS_E > R1) || (BS_EF > R1) || (BS_F > R1);
  int bs1_e = (BS_E > R0) || (BS_EF > R0);
  int bs1_f = BS_F > R0;
  //JP bits
  int jp_ef = getbits(JP_EF, R3, 8);
  if(JP_EF >> (R3+8)) jp_ef = 0xff;

  fm006.output = 0;
  fm006.output = 
    bs3 |
    bs2 << 1 |
    bs1_e << 2 |
    bs1_f << 3 |
    jp_ef << 16;
}
