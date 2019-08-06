#include "Board.hh"
#include "bits.hh"
#include "bbc_bb102_2010_b.hh"

void bbc_bb102_2010_b(Board& bb102)
{
  //registers
//  const int R0 = bb102.registers[0];
//  const int R1 = bb102.registers[1];

  //input
  const int bb003 = (bb102.channels[0] & 0xffff) | bb102.channels[1] << 16;

  //algo

  int east = btest(bb003, 24);
  int west = btest(bb003, 25);

  int easttac = getbits(bb003, 0, 12);
  int westtac = getbits(bb003, 12, 12);

  int tacdiff = 4096 + easttac - westtac;
  int eastgoodtac = easttac > 0;
  int westgoodtac = westtac > 0;
  if(! eastgoodtac || ! westgoodtac) tacdiff = 0;

//  int easttac_sel = getbits(easttac, R0, 6) & 0x7f;
//  if(easttac >> (R0+7)) easttac_sel = 0x7f;

//  int westtac_sel = getbits(westtac, R1, 6) & 0x7f;
//  if(westtac >> (R1+7)) westtac_sel = 0x7f;

  bb102.output = 0x0;
  bb102.output = (tacdiff |
		  east << 14 |
		  west << 15
		  );		       
}
