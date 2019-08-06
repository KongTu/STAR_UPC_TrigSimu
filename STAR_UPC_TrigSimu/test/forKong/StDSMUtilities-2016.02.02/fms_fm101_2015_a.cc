#include "Board.hh"
#include "bits.hh"
#include "fms_fm101_2015_a.hh"

#include <iostream>
using namespace std;

void fms_fm101_2015_a(Board& fm101)
{
  int fm001 = fm101.channels[0] | fm101.channels[1] << 16; //Top
  int fm002 = fm101.channels[2] | fm101.channels[3] << 16; //Bottom


  const int R0 = fm101.registers[0]; //FMSsmall-BS-th1
  const int R1 = fm101.registers[1]; //FMSsmall-BS-th2
  const int R2 = fm101.registers[2]; //FMSsmall-BS-th3
//  cout<<"R0="<<R0<<" R1="<<R1<<" R2="<<R2<<endl;
  //DD Board Sum
  int T_DD = getbits(fm001, 4, 12);
  int B_DD = getbits(fm002, 4, 12);

  int BS_DD = T_DD + B_DD;
  //overlapping jet patches
  int T_JP_AB = getbits(fm001, 16, 8);
  int T_JP_CD = getbits(fm001, 24, 8);

  int B_JP_AB = getbits(fm002, 16, 8);
  int B_JP_CD = getbits(fm002, 24, 8);
//  cout<<"T_JP_AB="<<T_JP_AB<<" T_JP_CD="<<T_JP_CD<<" B_JP_AB="<<B_JP_AB<<" B_JP_CD="<<B_JP_CD<<endl;
  int JP_T = T_JP_AB + T_JP_CD;
  if(JP_T > 0xff) JP_T = 0xff;
  int JP_M = T_JP_CD + B_JP_CD;
  if(JP_M > 0xff) JP_M = 0xff;
  int JP_B = B_JP_AB + B_JP_CD;
  if(JP_B > 0xff) JP_B = 0xff;
//  cout<<"JP_T="<<JP_T<<" JP_M="<<JP_M<<" JP_B="<<JP_B<<endl;

  int bs3 = (BS_DD > R2) || btest(fm001, 0) || btest(fm002, 0);
  int bs2 = (BS_DD > R1) || btest(fm001, 1) || btest(fm002, 1);
//  int bs1_t = (BS_DD > R0) || btest(fm001, 3);
  int bs1_t =  btest(fm001, 3);
  int bs1_m = (BS_DD > R0) || btest(fm001, 2) || btest(fm002, 2);
//  int bs1_b = (BS_DD > R0) || btest(fm002, 3);
  int bs1_b =  btest(fm002, 3);
//  cout<<"bs3="<<bs3<<" bs2="<<bs2<<" bs1_t="<<bs1_t<<" bs1_m="<<bs1_m<<" bs1_b="<<bs1_b<<endl;

  fm101.output = 0;
  fm101.output = 
    bs3 |
    bs2 << 1 |
    bs1_t << 2 |
    bs1_m << 3 |
    bs1_b << 4 |
    JP_T << 5 |
    JP_M << 16 |
    JP_B << 24;
//  cout<<"output="<<hex<<fm101.output<<dec<<endl;
}
