#include "bits.hh"
#include "Board.hh"
#include "mix_pp101_2015_a.hh"

void mix_pp101_2015_a(Board& pp101)
{
  const int R0 = pp101.registers[0]; //RPmask(16)
  int pp001out = pp101.channels[0]; //PP001 Ch0

  int e2u1 = btest(pp001out, 0);
  int e2u2 = btest(pp001out, 1);
  int e2d1 = btest(pp001out, 2);
  int e2d2 = btest(pp001out, 3);

  int w2u1 = btest(pp001out, 4);
  int w2u2 = btest(pp001out, 5);
  int w2d1 = btest(pp001out, 6);
  int w2d2 = btest(pp001out, 7);

  int e1d1 = btest(pp001out, 8);
  int e1d2 = btest(pp001out, 9);
  int e1u1 = btest(pp001out, 10);
  int e1u2 = btest(pp001out, 11);

  int w1d1 = btest(pp001out, 12);
  int w1d2 = btest(pp001out, 13);
  int w1u1 = btest(pp001out, 14);
  int w1u2 = btest(pp001out, 15);

  int e2u = (e2u1 && btest(R0, 0)) || (e2u2 && btest(R0, 1));
  int e2d = (e2d1 && btest(R0, 2)) || (e2d2 && btest(R0, 3));

  int w2u = (w2u1 && btest(R0, 4)) || (w2u2 && btest(R0, 5));
  int w2d = (w2d1 && btest(R0, 6)) || (w2d2 && btest(R0, 7));

  int e1u = (e1u1 && btest(R0, 8)) || (e1u2 && btest(R0, 9));
  int e1d = (e1d1 && btest(R0, 10)) || (e1d2 && btest(R0, 11));

  int w1u = (w1u1 && btest(R0, 12)) || (w1u2 && btest(R0, 13));
  int w1d = (w1d1 && btest(R0, 14)) || (w1d2 && btest(R0, 15));

  int eu = e1u || e2u;
  int ed = e1d || e2d;
  int wu = w1u || w2u;
  int wd = w1d || w2d;

  int ea = eu && wd;
  int eb = ed && wu;
  int iu = eu && wu;
  int id = ed && wd;

  int et = ea || eb;
  int it = iu || id;
  int eor = eu || ed;
  int wor = wu || wd;

  pp101.output = 0;
  pp101.output = 
    et |
    it << 1 |
    eor << 2 |
    wor << 3 |
    eu << 4 |
    ed << 5 |
    wu << 6 |
    wd << 7 ;
}
