#include "Board.hh"
#include "qt32b_l0_v5_f.hh"
//#include <iostream>
//using namespace std;
void qt32b_l0_v5_f(Board& bb003)
{
  //const int ADC_THRESHOLD = bb003.registers[13];
  //const int TAC_MIN = bb003.registers[14];
  //const int TAC_MAX = bb003.registers[15];
  const int ADC_THRESHOLD = 20;
  const int TAC_MIN = 10;
  const int TAC_MAX = 2500;
  //std::cout<<ADC_THRESHOLD<<" "<<TAC_MIN<<" "<<TAC_MAX<<std::endl;
  int maxTacEast = 0;
  int maxTacWest = 0;
  int eastHit = 0;
  int westHit = 0;

  for (int dcard = 0; dcard < 4; ++dcard) {
    for (int dch = 0; dch < 4; ++dch) {
      int ch = dcard*8+dch;
      int adc = bb003.channels[ch];
      int tac = bb003.channels[ch+4];
      int goodAdc = adc > ADC_THRESHOLD;
      int goodTacMin = tac > TAC_MIN;
      int goodTacMax = tac < TAC_MAX;
      int goodHit = goodAdc && goodTacMin && goodTacMax;
      //if(dcard > 1) cout<<"adc:"<<adc<<" tac:"<<tac<<endl;
      if (goodHit) {
	switch (dcard) {
	case 0:
	case 1:
	  eastHit = 1;
	  if (tac > maxTacEast) maxTacEast = tac;
	  break;
	case 2:
	case 3:
	  westHit = 1;
	  if (tac > maxTacWest) maxTacWest = tac;
	  break;
	}
      }
    }
  }
//  cout<<maxTacEast<<" "<<maxTacWest<<endl;
  bb003.output = maxTacEast | maxTacWest << 12 | eastHit << 24 | westHit << 25;
//  cout<<"output:"<<hex<<bb003.output<<endl;
}
