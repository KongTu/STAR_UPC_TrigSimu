#include "Board.hh"
#include "bits.hh"
#include "l1_vt201_2016_b.hh"

void l1_vt201_2016_b(Board& vt201)
{
  //registers
  const int R0 = vt201.registers[0]; //BBCsmall-TACdiff-Min (13)
  const int R1 = vt201.registers[1]; //BBCsmall-TACdiff-Max (13)
  const int R2 = vt201.registers[2]; //BBClarge-TACdiff-Min (13)
  const int R3 = vt201.registers[3]; //BBClarge-TACdiff-Max (13)
  const int R4 = vt201.registers[4]; //ZDC-TACdiff-Min (9)
  const int R5 = vt201.registers[5]; //ZDC-TACdiff-Max (9)
  //const int R6 = vt201.registers[6]; //Minimum-Bias Select (4)
  const int R6 = 15;
  const int R7 = vt201.registers[7]; //BBClarge-Combo-Sel(1)
  //input
  const int bb101out = vt201.channels[0];
  const int bb102out = vt201.channels[1];
  const int zd101out = vt201.channels[2];
  const int vp101out = vt201.channels[4];

  int bbcstacdiff = getbits(bb101out, 0, 13);
  int bbcltacdiff = getbits(bb102out, 0, 13);
  int zdctacdiff = getbits(zd101out, 0, 9);

  int bbcstac = R0 < bbcstacdiff && bbcstacdiff < R1;
  int bbcltac = R2 < bbcltacdiff && bbcltacdiff < R3;
  int zdctac = R4 < zdctacdiff && zdctacdiff < R5;

  int vpdtac1 = btest(vp101out, 0);
  int vpdtac2 = btest(vp101out, 1);
  int vpdtac3 = btest(vp101out, 2);

  int vpde = btest(vp101out,14);
  int vpdw = btest(vp101out,15);
  //int vpdcoin = vpde && vpdw;
  
  int bbcse = btest(bb101out,14);
  int bbcsw = btest(bb101out,15);

  int bbcle = btest(bb102out,14);
  int bbclw = btest(bb102out,15);
  //printf("R6=%d\n", R6);
  int mb = ((btest(R6,0) && bbcstac && bbcse && bbcsw) ||
	    (btest(R6,1) && bbcltac && bbcle && bbclw) ||
	    (btest(R6,2) && zdctac) ||
	    (btest(R6,3) && vpdtac1));

  int zdcw1 = btest(zd101out, 10);
  int zdcw2 = btest(zd101out, 11);
  
  int zdce1 = btest(zd101out, 13);
  int zdce2 = btest(zd101out, 14);

  int zdcewin = zdce1 && !zdce2;
  int zdcwwin = zdcw1 && !zdcw2;

  int zdcupc = zdcewin && zdcwwin;

  int zdcpw0 = btest(zd101out, 9);
  int zdcpe0 = btest(zd101out, 12);

//  int zdccoin = zdcpw0 && zdcpe0;
  int zdcew = btest(zd101out, 15);
//  int preceded = 0;
  int bbclcmb = 0;
  if(R7) bbclcmb = bbcle && bbclw;
  else bbclcmb = bbcle || bbclw;

  int bbcstacwin = btest(bb101out, 13);
  vt201.output = (bbcstac << 0 |
		  bbcse << 1 |
		  bbcsw << 2 |
		  vpdtac2 << 3 |
		  bbcstacwin << 4 |
		  bbclcmb << 5 |
		  zdctac << 6 |
		  zdcpe0 << 7 |
		  zdcpw0 << 8 |
		  zdcupc << 9 |
		  zdcew << 10 |
		  mb << 11 |
		  vpdtac3 << 12 |
		  vpdtac1 << 13 |
		  vpde << 14 |
		  vpdw << 15);
}
