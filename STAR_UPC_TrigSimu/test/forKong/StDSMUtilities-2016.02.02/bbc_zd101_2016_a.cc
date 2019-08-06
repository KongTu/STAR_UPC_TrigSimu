#include "Board.hh"
#include "bits.hh"
#include "bbc_zd101_2016_a.hh"

void bbc_zd101_2016_a(Board& zd101)
{
  //registers
  int R0 = zd101.registers[0]; //ZDC-TAC diff-select (2)
  //  int R1 = zd101.registers[1]; //ZDC-EastTAC-select (3)
  //  int R2 = zd101.registers[2]; //ZDC-WestTAC-select (3)
  //  int R3 = zd101.registers[3]; //ZDC-deadtime (4)
  R0 = 2;
  //input
  //0:9 West-1 TAC
  //10:19 East-1 TAC
  //20 West sum > th-0
  //21 West sum > th-1
  //22 West sum > th-2
  //23 West sum > th-3
  //24 West attenuated sum > th-4
  //25 West attenuated sum > th-5
  //26 East Sum > th-0
  //27 East Sum > th-1
  //28 East Sum > th-2
  //29 East Sum > th-3
  //30 East attenuated sum > th-4 (unused)
  //31 East attenuated sum > th-5 (unused)
  const int zd001 = (zd101.channels[0] & 0xffff) | zd101.channels[1] << 16;
 

  //algo
  int zd001tacw = getbits(zd001, 0, 10);
  int zd001tace = getbits(zd001, 10, 10);
  
  int tacdiff = 1024 + zd001tace - zd001tacw;
  int zd001goodtacw = zd001tacw > 0;
  int zd001goodtace = zd001tace > 0;
  if(! zd001goodtacw || ! zd001goodtace) tacdiff = 0;
  else if(R0 == 0){
    if(btest(tacdiff, 10) || btest(tacdiff, 9)) tacdiff = 511;
    else tacdiff = getbits(tacdiff, 0, 9);
  }else if(R0 == 1){
    if(btest(tacdiff, 10)) tacdiff = 511;
    tacdiff = getbits(tacdiff, 1, 9);
  }else{
    tacdiff = getbits(tacdiff, 2, 9);
  }

  int preceded = 0;

  int zd001w0 = btest(zd001, 20);
  int zd001w1 = btest(zd001, 21);
  int zd001w2 = btest(zd001, 22);
  int zd001w3 = btest(zd001, 23); 

  int zd001e0 = btest(zd001, 26);
  int zd001e1 = btest(zd001, 27);
  int zd001e2 = btest(zd001, 28);
  int zd001e3 = btest(zd001, 29);

  int prow0 = zd001w0 && (!preceded);
  int proe0 = zd001e0 && (!preceded);

  int sumw1 = zd001w1;
  int sumw2 = zd001w2;

  int sume1 = zd001e1;
  int sume2 = zd001e2;
  
  int sumew3 = zd001w3 || zd001e3;

  zd101.output = 0x0;
  zd101.output = (tacdiff << 0 |
		  prow0 << 9 |
		  sumw1 << 10 |
		  sumw2 << 11 |
		  proe0 << 12 |
		  sume1 << 13 |
		  sume2 << 14 |
		  sumew3 << 15
		  );		       
}
