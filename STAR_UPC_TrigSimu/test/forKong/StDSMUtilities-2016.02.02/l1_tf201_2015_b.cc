#include "Board.hh"
#include "bits.hh"
#include "l1_tf201_2015_b.hh"

void l1_tf201_2015_b(Board& tf201)
{
  const int R0 = tf201.registers[0]; // TOFmult0 (13)
  const int R1 = tf201.registers[1]; // TOFmult1 (13)
  const int R2 = tf201.registers[2]; // TOFmult2 (13)
  const int R3 = tf201.registers[3]; // TOFmult3 (13)
//  const int R4 = tf201.registers[4]; // TOFmult4 (13)

  // Inputs: Ch 0   = MT101
  //         Ch 1   = Unused
  //         Ch 2:3 = TF101
  //         Ch 4   = PP001 (QT board); currently unused
  //         Ch 5:7 = Unused

  // From MTD Layer 1 DSM - MT101
  // (0:3)  Num_muons
  // (3:13) Unused
  // (14)   Cosmic-Ray
  // (15)   Unused

  // From TOF Layer 1 DSM - TF101
  // (0:12)  TOF total multiplicity
  // (13:15) Unused
  // (16:21) TOF sector threshold bits
  // (22:31) Unused

  int mt101out = tf201.channels[0];
  int tf101out1 = tf201.channels[2];
  int tf101out2 = tf201.channels[3];
  int pp101out = tf201.channels[4];

  int nmuons = getbits(mt101out,0,4);
  int mtd_th1 = 0;
  int mtd_th2 = 0;
  if(nmuons > 1 || nmuons == 1) mtd_th1 = 1;
  if(nmuons > 2 || nmuons == 2) mtd_th2 = 1;

  int cosmicray = btest(mt101out,14);
  int tcosmic = btest(mt101out, 15);

  int tofmult = getbits(tf101out1, 0, 13);
  int tofmult0 = tofmult > R0;
  int tofmult1 = tofmult > R1;
  int tofmult2 = tofmult > R2;
  int tofmult3 = tofmult > R3;
//  int tofmult4 = tofmult > R4;

  int tofsector03 = btest(tf101out2, 0) & btest(tf101out2, 3);
  int tofsector14 = btest(tf101out2, 1) & btest(tf101out2, 4);
  int tofsector25 = btest(tf101out2, 2) & btest(tf101out2, 5);

  int tofupc = btest(tf101out2, 6);

  int rp_et = btest(pp101out, 0);
  int rp_it = btest(pp101out, 1);
  int rp_eor = btest(pp101out, 2);
  int rp_wor = btest(pp101out, 3);
  int rp_eu = btest(pp101out, 4);
  int rp_ed = btest(pp101out, 5);
  int rp_wu = btest(pp101out, 6);
  int rp_wd = btest(pp101out, 7);

  tf201.output = ( mtd_th1 |
		   mtd_th2 << 1 |
		   rp_et << 2 |
                   tofupc << 3 |
		   tofmult0 << 4 |
		   tofmult1 << 5 |
		   tofmult2 << 6 |
		   tofmult3 << 7 |
//		   tofmult4 << 8 |
		   tcosmic << 8 |
		   tofsector03 <<  9 |
		   tofsector14 << 10 |
		   tofsector25 << 11 |
		   rp_it << 12 |
		   rp_eor << 13 |
		   rp_wor << 14 |
		   cosmicray  << 15 |
		   rp_eu << 16 |
		   rp_ed << 17 |
		   rp_wu << 18 |
		   rp_wd << 19);
}
