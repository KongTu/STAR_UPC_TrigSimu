#include "bits.hh"
#include "Board.hh"
#include "mix_mt101_2016_a.hh"
#include <stdio.h>
void mix_mt101_2016_a(Board& mt101)
{
  const int R0 = mt101.registers[0]; //MTD-VPD-TACdiff-Min(11)
  const int R1 = mt101.registers[1]; //MTD-VPD-TACdiff-Max(11)
  const int R2 = mt101.registers[2]; //MTD-InputCh-BitMask(8)
  const int R3 = mt101.registers[3]; //MTD-Cosmic-Tdiff-Min(10)
  const int R4 = mt101.registers[4]; //MTD-Cosmic-Tdiff-Max(10)
//  const int R3 = 10;
//  const int R4 = 1020;
//  int* mt101.channels = (int*)mt101.channels;

  int vp003out = mt101.channels[8]; // VPD east
  int vp004out = mt101.channels[9]; // VPD west

  int vpdtace = getbits(vp003out,0,12);
  int vpdtacw = getbits(vp004out,0,12);
  int goodvpde = vpdtace > 0;
  int goodvpdw = vpdtacw > 0;
  int goodvpd = goodvpde && goodvpdw;

  int vpdsum = vpdtace + vpdtacw;
  vpdsum = vpdsum >> 3;

  int mt00xout[4];
  for(int ichn = 0; ichn < 4; ichn++){
    mt00xout[ichn] = (mt101.channels[2*ichn] & 0xfff) | mt101.channels[2*ichn+1] << 12;
  }

  int tac[8];
//  int id[8];
  int goodmtd[8];
  int mtdvpdtacdiff[8];
  //  int mtdid[8];
  for(int ichn = 0; ichn < 4; ichn++){
    tac[2*ichn] = getbits(mt00xout[ichn], 0, 10);
//    id[2*ichn] = getbits(mt00xout[ichn], 10, 2);
    tac[2*ichn+1] = getbits(mt00xout[ichn], 12, 10);
//    id[2*ichn+1] = getbits(mt00xout[ichn], 22, 2);
   }
  for(int ibit = 0; ibit < 8; ibit++){
    if(!(R2 >> ibit & 0x1)) tac[ibit] = 0;
  }
   for(int ichn = 0; ichn < 8; ichn++){
    //    mtdid[ichn] = id;
    goodmtd[ichn] = tac[ichn] > 0;
    int diff = 1024 + tac[ichn]  - vpdsum;
    mtdvpdtacdiff[ichn] = diff;
  }

  int index[4];
  int best[4];

  for(int ii = 0; ii < 4; ii++){
    index[ii] = 0;
    best[ii] = 0;
  }

  for(int ibit = 0; ibit < 4; ibit++){
    if(tac[ibit] > best[0]){ best[0]= tac[ibit];  index[0] = ibit;}
  }

  for(int ibit = 0; ibit < 4; ibit++){
    if(ibit != index[0] && tac[ibit] > best[1]){ best[1] = tac[ibit];  index[1] = ibit;}
  }

  if(tac[0] == tac [1] && tac [0] == tac[2] && tac[0] == tac[3]){
    best[0] = tac[3];
    best[1] = tac[3];
    index[0] = 3;
    index[1] = 3;
  }
  for(int ibit = 4; ibit < 8; ibit++){
    if(tac[ibit] > best[2]){ best[2]= tac[ibit];  index[2] = ibit;}
  }

  for(int ibit = 4; ibit < 8; ibit++){
    if(ibit != index[2] && tac[ibit] > best[3]){ best[3] = tac[ibit];  index[3] = ibit;}
  }
  if(tac[4] == tac [5] && tac [4] == tac[6] && tac[4] == tac[7]){
    best[2] = tac[7];
    best[3] = tac[7];
    index[2] = 7;
    index[3] = 7;
  }   
  
  int cosmicRay = 0;
  int hit = 0;
  for(int ichn = 0; ichn < 8; ichn++){
    cosmicRay += goodmtd[ichn];
  }
  if(cosmicRay > 0) hit = 1;
  if(cosmicRay > 1) cosmicRay = 1;
  else cosmicRay = 0;
  int goodtacmin[8];
  int goodtacmax[8];
  int goodtacdiff[8];
  int nummuons = 0;
  for(int ichn = 0; ichn < 8; ichn++){
    goodtacmin[ichn] = mtdvpdtacdiff[ichn] > R0;
    goodtacmax[ichn] = mtdvpdtacdiff[ichn] < R1;
    if(!goodvpd || !goodmtd[ichn]){
      goodtacmin[ichn] = 0; 
      goodtacmax[ichn] = 0;
    }
    goodtacdiff[ichn] = goodtacmin[ichn] && goodtacmax[ichn];
    if(goodtacdiff[ichn]) nummuons++;
//    printf("chn%d-good=%d ", ichn, goodtacdiff[ichn]);
  }
//  printf("n_mu=%d\n", nummuons);
  int goodtacwindow = 0;
  for(int ichn = 0; ichn < 8; ichn++){
    goodtacwindow |= goodtacdiff[ichn] << ichn;
  }
  
  int mtdid1 = 0;
  int mtdtac1 = 0;
  int mtdid2 = 0;
  int mtdtac2 = 0;

  for(int ibit = 0; ibit < 4; ibit++){
    if(best[ibit] > mtdtac1){ mtdtac1 = best[ibit];  mtdid1 = index[ibit];}
  }

  for(int ibit = 0; ibit < 4; ibit++){
    if(index[ibit] != mtdid1 && best[ibit] > mtdtac2){ mtdtac2 = best[ibit];  mtdid2 = index[ibit];}
  }

  int mtdtdiff = mtdtac1 - mtdtac2;
  if(mtdtac1 == 0 || mtdtac2 == 0) mtdtdiff = 0;
  //printf("mtddiff=%d R3=%d R4=%d\n", mtdtdiff, R3, R4);
  int tcosmic = mtdtdiff > R3 && mtdtdiff < R4;
  
  mt101.output = 0;
  mt101.output =
    nummuons   |
    goodtacwindow << 4 |
    hit << 12 |
    goodvpd << 13 |
    cosmicRay << 14 |
    tcosmic << 15;
//    mtdtac1  << 16 |
//    mtdid1  << 20 |
//    mtdtac2 << 22 |
//    mtdid2  << 26;
}
