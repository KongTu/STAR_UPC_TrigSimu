#include "Board.hh"
#include "qt32b_l0_v6_f.hh"

//#include <iostream>
//using namespace std;

void qt32b_l0_v6_f(Board& qt)
{
  //West pp algorithm for year 2015
  //East Heavy Ion algorithm
  //for 2016 Heavy Ion algorithm
  //  const int Channel_Mask = 0xCCEECCEE;
  //const int Channel_Mask = qt.registers[11];
  //ADC_Th not used for heavy ion algorithm
  //const int ADC_Th = qt.registers[13];
  const int TAC_Min = qt.registers[14];
  const int TAC_Max = qt.registers[15];
  //heavy ion algorithm

  const int ADC_W_Threshold_0 = qt.registers[16];
  const int ADC_W_Threshold_1 = qt.registers[17];
  const int ADC_W_Threshold_2 = qt.registers[18];
  const int ADC_W_Threshold_3 = qt.registers[19];
  const int ADC_W_Threshold_4 = qt.registers[20];
  const int ADC_W_Threshold_5 = qt.registers[21];
 
  //pp algorithm
  //const int ADC_W_Pair_Threshold = qt.registers[22];
  //const int ADC_W_Sum_Threshold = qt.registers[23];
  //  cout<<"pair th = "<<ADC_W_Pair_Threshold<<" sum-th = "<<ADC_W_Sum_Threshold<<endl;
  //  const int ADC_E_Th = qt.registers[0];
  //  const int TAC_E_Min = qt.registers[1];
  //  const int TAC_E_Max = qt.registers[2];
  const int ADC_E_Threshold_0 = qt.registers[3];
  const int ADC_E_Threshold_1 = qt.registers[4];
  const int ADC_E_Threshold_2 = qt.registers[5];
  const int ADC_E_Threshold_3 = qt.registers[6];
  const int ADC_E_Threshold_4 = qt.registers[7];
  const int ADC_E_Threshold_5 = qt.registers[8];

  /*
  int ch4tac[4];
  int Int_sum_0[4];
  int PairGood[4];

  for (int dcard = 0; dcard < 4; ++dcard) {
    ch4tac[dcard] = 0;
    Int_sum_0[dcard] = 0;
    for (int dch = 0; dch < 2; ++dch) {
      int ch = dcard*8+dch;
      if (Channel_Mask >> ch & 1) continue;
      int adc = qt.channels[ch];
      int tac = qt.channels[ch+4];
      int good_adc = adc > ADC_Threshold;
      int good_tac_min = tac > TAC_MIN;
      int good_tac_max = tac < TAC_MAX;
      int good_hit = good_adc && good_tac_min && good_tac_max;
      if (good_hit) {
	Int_sum_0[dcard] += adc;
	ch4tac[dcard] = tac >> 2 & 0x3ff;
      }
    }
    PairGood[dcard] = Int_sum_0[dcard] > Pair_Threshold;
  }

  int SumAB = Int_sum_0[0]+Int_sum_0[1];
  int SumCD = Int_sum_0[2]+Int_sum_0[3];

  int SumGoodAB = SumAB > Sum_Threshold;
  int SumGoodCD = SumCD > Sum_Threshold;
  */
  int dcard = 2; //card c
  //pp algorithm
  //int adcw1 = qt.channels[8*dcard+0];
  //int wtac1 = qt.channels[8*dcard+4];
  //int w_pair_sum_c = 0;
  //if((adcw1 > ADC_Th) && (wtac1 > TAC_Min && wtac1 < TAC_Max)){
  //  w_pair_sum_c += adcw1;
  //}else{
  //       wtac1 = 0;
  //}
  //wtac1 = wtac1 >> 2;
  int wsum = qt.channels[8*dcard+2];
  int wsuma = qt.channels[8*dcard+3]; 
  int wtac = qt.channels[8*dcard+4];
  
  if((wtac < TAC_Min) || (wtac > TAC_Max)) wtac = 0;
  else wtac = wtac >> 2;

  int wsum_th0 = wsum > ADC_W_Threshold_0;
  int wsum_th1 = wsum > ADC_W_Threshold_1;
  int wsum_th2 = wsum > ADC_W_Threshold_2;
  int wsum_th3 = wsum > ADC_W_Threshold_3;
  int wsuma_th4 = wsuma > ADC_W_Threshold_4;
  int wsuma_th5 = wsuma > ADC_W_Threshold_5;

  /*
  dcard = 3; //card d
  int adcw2 = qt.channels[8*dcard+0];
  int wtac2 = qt.channels[8*dcard+4];
  
  int adcw3 = qt.channels[8*dcard+1];
  int wtac3 = qt.channels[8*dcard+5];
  
  int w_pair_sum_d = 0;

  if((adcw2 > ADC_Th) && (wtac2 > TAC_Min && wtac2 < TAC_Max)){
    w_pair_sum_d += adcw2;
  }

  if((adcw3 > ADC_Th) && (wtac3 > TAC_Min && wtac3 < TAC_Max)){
    w_pair_sum_d += adcw3;
  }
//  cout<<"wtac = "<<wtac<<" wtac = "<<wtac<<" wtac = "<<wtac<<endl;
  int w_sum_c_d = w_pair_sum_c + w_pair_sum_d;

  int w_pair_c_th = w_pair_sum_c > ADC_W_Pair_Threshold;
  int w_pair_d_th = w_pair_sum_d > ADC_W_Pair_Threshold;

  int w_sum_th = w_sum_c_d > ADC_W_Sum_Threshold;

  int w_sum_adc = (w_sum_c_d >> 11) & 0x7;
  */
  dcard = 0;
  int esum = qt.channels[8*dcard+2];
  int esuma = qt.channels[8*dcard+3];
  int etac = qt.channels[8*dcard+4];

  if((etac < TAC_Min) || (etac > TAC_Max)) etac = 0;
  else etac = etac >> 2;

  int esum_th0 = esum > ADC_E_Threshold_0;
  int esum_th1 = esum > ADC_E_Threshold_1;
  int esum_th2 = esum > ADC_E_Threshold_2;
  int esum_th3 = esum > ADC_E_Threshold_3;
  int esuma_th4 = esuma > ADC_E_Threshold_4;
  int esuma_th5 = esuma > ADC_E_Threshold_5;


  qt.output = 0;
  qt.output |= wtac << 0;
  qt.output |= etac << 10;
  //pp algorithm
  //qt.output |= w_sum_adc << 20;
  //qt.output |= w_pair_c_th << 23;
  //qt.output |= w_pair_d_th << 24;
  //qt.output |= w_sum_th << 25;
  //heavy ion algorithm
  qt.output |= wsum_th0 << 20;
  qt.output |= wsum_th1 << 21;
  qt.output |= wsum_th2 << 22;
  qt.output |= wsum_th3 << 23;
  qt.output |= wsuma_th4 << 24;
  qt.output |= wsuma_th5 << 25;
  qt.output |= esum_th0 << 26;
  qt.output |= esum_th1 << 27;
  qt.output |= esum_th2 << 28;
  qt.output |= esum_th3 << 29;
  qt.output |= esuma_th4 << 30;
  qt.output |= esuma_th5 << 31;
}
