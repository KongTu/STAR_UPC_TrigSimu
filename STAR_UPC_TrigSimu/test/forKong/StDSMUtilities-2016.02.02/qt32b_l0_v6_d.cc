#include "Board.hh"
#include "qt32b_l0_v6_d.hh"
#include "slew_correction.hh"
#include <iostream>
using namespace std;

void qt32b_l0_v6_d(Board& qt, int slew[][8])
{
  //int slew_correction(int adc, int chn, int slew[][8]);
  const int ADC_THRESHOLD = qt.registers[13];
  //const int ADC_THRESHOLD = 20;
  const int TAC_MIN = qt.registers[14];
  //const int TAC_MIN = 100;
  const int TAC_MAX = qt.registers[15];
  //cout<<"ADC_THRESHOLD:"<<ADC_THRESHOLD<<endl;
  //cout<<"TAC_MIN:"<<TAC_MIN<<endl;
  //cout<<"TAC_MAX:"<<TAC_MAX<<endl;
  //const int bitmask = qt.bitmask;
  //  cout<<"bitmask: "<<hex<<bitmask<<endl;
  int adcsum = 0;
  int tacmax = 0;

  for (int dcard = 0; dcard < 4; ++dcard) {
    for (int dch = 0; dch < 4; ++dch) {
      int ch = dcard*8+dch;
      int adc = qt.channels[ch];
      int tac = qt.channels[ch+4];
      int corr = slew_correction(adc, ch, slew);
      tac += corr;
      //cout<<"adc: "<<adc<<" tac: "<<tac<<" corr: "<<corr<<endl;
      int good_adc = adc > ADC_THRESHOLD;
      int good_tac_min = tac > TAC_MIN;
      int good_tac_max = tac < TAC_MAX;
      int good_hit = good_adc && good_tac_min && good_tac_max;
      if (good_hit) {
	adcsum += adc;
	if (tac > tacmax) tacmax = tac;
      }
    }
  }
  //cout<<"adcsum: "<<adcsum<<" tacmax: "<<tacmax<<endl;
  qt.output = adcsum | tacmax << 16;
}
/*
int slew_correction(int adc, int chn, int slew[][8])
{
  for(int ii = 0; ii < 8; ii++){
    if(adc <= slew[chn][ii]){
      return slew[chn+4][ii];
    }
  }
  return 0;
}
*/
