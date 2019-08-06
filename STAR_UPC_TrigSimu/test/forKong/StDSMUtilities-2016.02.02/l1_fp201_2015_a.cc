#include "Board.hh"
#include "bits.hh"
#include "l1_fp201_2015_a.hh"
#include <iostream>
using namespace std;

void l1_fp201_2015_a(Board& fp201)
{
  const int R0 = fp201.registers[0]; // FMS-JP0
  const int R1 = fp201.registers[1]; // FMS-JP1
  const int R2 = fp201.registers[2]; // FMS-JP2

  //ch0/1 -- FM102 small north -- fm10x[1]
  //ch2/3 -- FM103 large south -- fm10x[2]
  //ch4/5 -- FM104 large north -- fm10x[3]
  //ch6/7 -- FM101 small south -- fm10x[0]

  int fm10x[4];

  for(int ichn = 0; ichn < 4; ichn++){
    int ii = (ichn+1)%4;
    fm10x[ii] = fp201.channels[2*ichn] | fp201.channels[2*ichn+1] << 16;
  }

  int bs3_large = btest(fm10x[2], 0) || btest(fm10x[3], 0);
  int bs3_small = btest(fm10x[0], 13) || btest(fm10x[1], 13);

  int bs2_large = btest(fm10x[2], 1) || btest(fm10x[3], 1);
  int bs2_small = btest(fm10x[0], 1) || btest(fm10x[1], 1);

  int bs1_large = (getbits(fm10x[2], 2, 3) > 0) || (getbits(fm10x[3], 2, 3) > 0);
  int bs1_small = (getbits(fm10x[0], 2, 3) > 0) || (getbits(fm10x[1], 2, 3) > 0);

  //int bs1[4][3];
  int bs1_bk[12];
  //ifm --> FM10[1:4]
  //itmb --> 0(T), 1(M), and 2(B) south
  //itmb --> 0(B), 1(M), and 2(T) north
  for(int ifm = 0; ifm < 4; ifm++){
    for(int itmb = 0; itmb < 3; itmb++){
      int ii = ifm;
      int jj = itmb;
      if(ifm%2) jj = 2 - itmb;
      //bs1[ii][jj] = btest(fm10x[ifm], 2+itmb);
      bs1_bk[3*ii+jj] = btest(fm10x[ifm], 2+itmb);
    }
  }
  //Di Board Sum
  int di_bs = 0;

  for(int ii = 0; ii < 12; ii++){
    for(int jj = ii+1; jj < 12; jj++){
      int ifm = (ii/3)%2;
      int itmb = ii%3;

      int jfm = (jj/3)%2;
      int jtmb = jj%3;
      
      int flag = 0;
      if((itmb == 0 && jtmb == 2) || (itmb == 2 && jtmb == 0)){
	if(!((ifm+jfm)%2)){
          flag = 1;
	}
      }else{
	if((ifm+jfm)%2){
	  flag = 1;
	}
      }
      if(flag) di_bs |= bs1_bk[ii] && bs1_bk[jj];
//      cout<<flag<<"("<<ifm<<","<<itmb<<";"<<jfm<<","<<jtmb<<") ";	
    }
//    cout<<endl;
  }
  //iff: South(0) North(1)
  //itmb --> 0(T), 1(M), and 2(B) south

  int JP[6];
  for(int iff = 0; iff < 2; iff++){
    for(int itmb = 0; itmb < 3; itmb++){
      int ii = 3*iff + itmb;
      int bit = 5;
      if(itmb == 1) bit = 16;
      if(itmb == 2) bit = 24;
      JP[ii] = getbits(fm10x[iff], bit, 8) + getbits(fm10x[iff+2], bit, 8);
    }
  }
  //JP0, JP1 and JP2
  int jp2 = 0, jp1 = 0, jp0 = 0;
  for(int ii = 0; ii < 6; ii++){
    jp2 |= JP[ii] > R2;
    jp1 |= JP[ii] > R1;
    jp0 |= JP[ii] > R0;
  }
  //Di-Jet
  int di_jet = 0;
  for(int ii = 0; ii < 6; ii++){
    for(int jj = ii+1; jj < 6; jj++){
      int iff = ii/3;
      int itmb = ii%3;

      int jff = jj/3;
      int jtmb = jj%3;

      if(iff != jff){
	if(!((itmb == 0 && jtmb == 0) || (itmb == 2 && jtmb == 2))){
	  di_jet |= (JP[ii] > R0) && (JP[jj] > R0);
	}
      }
    }
  }
  fp201.output = 0; 
  fp201.output = 
    bs3_small |
    bs2_small << 1 |
    bs1_small << 2 |
    bs3_large << 3 |
    bs2_large << 4 |
    bs1_large << 5 |
    di_bs << 6 |
    jp2 << 7 |
    jp1 << 8 |
    jp0 << 9 |
    di_jet << 10;

}
