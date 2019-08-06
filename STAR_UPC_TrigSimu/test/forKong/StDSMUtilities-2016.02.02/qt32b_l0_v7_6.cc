#include "Board.hh"
#include "qt32b_l0_v7_6.hh"
#include "slew_correction.hh"
#include <iostream>
using namespace std;

void qt32b_l0_v7_6(Board& qt, int slew[][8])
{
  //int slew_correction(int adc, int chn, int slew[][8]);
  const int ADC_THRESHOLD = qt.registers[13];
  //const int ADC_THRESHOLD = 20;
  const int TAC_MIN = qt.registers[14];
  //const int TAC_MIN = 100;
  const int TAC_MAX = qt.registers[15];
  const int Noi_Con = qt.registers[16];
  int Noi_Off[4];
  for(int id = 0; id < 4; id++){ 
    Noi_Off[id] = qt.registers[17+id];
    //cout<<"noise: "<<Noi_Off[id]<<endl;
  }
  //cout<<"ADC_THRESHOLD:"<<ADC_THRESHOLD<<endl;
  //cout<<"TAC_MIN:"<<TAC_MIN<<endl;
  //cout<<"TAC_MAX:"<<TAC_MAX<<endl;
  //const int bitmask = qt.bitmask;
  //  cout<<"bitmask: "<<hex<<bitmask<<endl;
  int adcsum = 0;
  int tacsum = 0;
  int nhits = 0;
  for (int dcard = 0; dcard < 4; ++dcard) {
    int noi = 0;
    if(Noi_Con) noi = qt.channels[dcard*8+4] - Noi_Off[dcard];
    for (int dch = 1; dch < 4; ++dch) {
      int ch = dcard*8+dch;
      int adc = qt.channels[ch];
      int tac = qt.channels[ch+4];
      int corr = slew_correction(adc, ch, slew);
      //cout<<"adc: "<<adc<<" ch:"<<ch<<" slew:"<<corr<<endl;
      tac += corr;
      //noise correction
      tac -= noi;
      if(tac < 0) tac = 0;
      if(tac > 4095) tac = 4095;
      //cout<<"adc: "<<adc<<" tac: "<<tac<<" corr: "<<corr<<endl;
      int good_adc = adc > ADC_THRESHOLD;
      int good_tac_min = tac > TAC_MIN;
      int good_tac_max = tac < TAC_MAX;
      int good_hit = good_adc && good_tac_min && good_tac_max;
      if (good_hit) {
	adcsum += adc;
	tacsum += tac;
        nhits++;
      }
    }
    if(adcsum > 4095) adcsum = 4095;
  }
  //cout<<"adcsum: "<<adcsum<<" tacsum: "<<tacsum<<" nhits:"<<nhits<<endl;
  qt.output = adcsum  | 
              nhits << 12 |
	      tacsum << 16;
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
