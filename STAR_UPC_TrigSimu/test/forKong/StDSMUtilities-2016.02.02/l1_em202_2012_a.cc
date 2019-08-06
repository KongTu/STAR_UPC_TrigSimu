//
// Pibero Djawotho <pibero@tamu.edu>
// Texas A&M
// 3 Feb 2012
//

#include "Board.hh"
#include "l1_em202_2012_a.hh"

void l1_em202_2012_a(Board& em202)
{
  // BC101 (10 o'clock)
  int bc101  = em202.channels[0];
  int be001  = bc101 >> 0 & 1;
  int bw001  = bc101 >> 1 & 1;
  int be002  = bc101 >> 2 & 1;
  int bw002  = bc101 >> 3 & 1;
  int be003a = bc101 >> 4 & 1;
  int bw003a = bc101 >> 5 & 1;

  // BC102 (12 o'clock)
  int bc102  = em202.channels[1];
  int be003b = bc102 >> 0 & 1;
  int bw003b = bc102 >> 1 & 1;
  int be004  = bc102 >> 2 & 1;
  int bw004  = bc102 >> 3 & 1;
  int be005  = bc102 >> 4 & 1;
  int bw005  = bc102 >> 5 & 1;

  // BC103 (2 o'clock)
  int bc103  = em202.channels[2];
  int be006  = bc103 >> 0 & 1;
  int bw006  = bc103 >> 1 & 1;
  int be007  = bc103 >> 2 & 1;
  int bw007  = bc103 >> 3 & 1;
  int be008a = bc103 >> 4 & 1;
  int bw008a = bc103 >> 5 & 1;

  // BC104 (4 o'clock)
  int bc104  = em202.channels[3];
  int be008b = bc104 >> 0 & 1;
  int bw008b = bc104 >> 1 & 1;
  int be009  = bc104 >> 2 & 1;
  int bw009  = bc104 >> 3 & 1;
  int be010  = bc104 >> 4 & 1;
  int bw010  = bc104 >> 5 & 1;

  // BC105 (6 o'clock)
  int bc105  = em202.channels[4];
  int be011  = bc105 >> 0 & 1;
  int bw011  = bc105 >> 1 & 1;
  int be012  = bc105 >> 2 & 1;
  int bw012  = bc105 >> 3 & 1;
  int be013a = bc105 >> 4 & 1;
  int bw013a = bc105 >> 5 & 1;

  // BC106 (8 o'clock)
  int bc106  = em202.channels[5];
  int be013b = bc106 >> 0 & 1;
  int bw013b = bc106 >> 1 & 1;
  int be014  = bc106 >> 2 & 1;
  int bw014  = bc106 >> 3 & 1;
  int be015  = bc106 >> 4 & 1;
  int bw015  = bc106 >> 5 & 1;

  int tpcRdoMask = 0;

  tpcRdoMask |= (bw005 || bw006) << 0;
  tpcRdoMask |= (bw006 || bw007) << 1;
  tpcRdoMask |= (bw007 || bw008a || bw008b || bw009) << 2;
  tpcRdoMask |= (bw009 || bw010) << 3;
  tpcRdoMask |= (bw010 || bw011) << 4;
  tpcRdoMask |= (bw011 || bw012) << 5;
  tpcRdoMask |= (bw012 || bw013a || bw013b || bw014) << 6;
  tpcRdoMask |= (bw014 || bw015) << 7;
  tpcRdoMask |= (bw015 || bw001) << 8;
  tpcRdoMask |= (bw001 || bw002) << 9;
  tpcRdoMask |= (bw002 || bw003a || bw003b || bw004) << 10;
  tpcRdoMask |= (bw004 || bw005) << 11;

  tpcRdoMask |= (be004 || be003a || be003b || be002) << 16;
  tpcRdoMask |= (be002 || be001) << 17;
  tpcRdoMask |= (be001 || be015) << 18;
  tpcRdoMask |= (be015 || be014) << 19;
  tpcRdoMask |= (be014 || be013a || be013b || be012) << 20;
  tpcRdoMask |= (be012 || be011) << 21;
  tpcRdoMask |= (be011 || be010) << 22;
  tpcRdoMask |= (be010 || be009) << 23;
  tpcRdoMask |= (be009 || be008a || be008b || be007) << 24;
  tpcRdoMask |= (be007 || be006) << 25;
  tpcRdoMask |= (be006 || be005) << 26;
  tpcRdoMask |= (be005 || be004) << 27;

  // OUTPUT (32)

  // (0:11) TPC Readout Mask: Sectors 1:12
  // (12:15) Unused
  // (16:27) TPC Readout Mask: Sectors 13:24
  // (28:31) Unused

  em202.output = tpcRdoMask;
}
