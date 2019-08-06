//
// Pibero Djawotho <pibero@tamu.edu>
// Texas A&M University
// 11 March 2011
//

#include "Board.hh"
#include "eemc_ee101_2009_a.hh"

void eemc_ee101_2009_a(Board& ee101)
{
  // INPUT:

  // EE101 - ch0 - EE001
  //         ch1 - EE002 - (0-15)  jp0 anti-clockwise
  //         ch2 - EE002 - (16-31) jp1 clockwise
  //         ch3 - EE003
  //         ch4 - EE004
  //         ch5 - EE005 - (0-15) jp0 anti-clockwise

  // From E001/003/004:

  // (0-5) TP sum for low-eta group (6)
  // (6-11) TP sum for high-eta group (6)
  // (12-13) HT bits (2)
  // (14-15) Unused (2)

  // From E002/005:

  // (0-5) TP sum (6)
  // (6-11) Unused (2)
  // (12-13) HT bits (2)
  // (14-15) Unused (2)

  // REGISTERS:

  // R0: EEMC-Jet-Patch-Th0 (8)
  // R1: EEMC-Jet-Patch-Th1 (8)
  // R2: EEMC-Jet-Patch-Th2 (8)

  // ACTION:

  // Make jet patch sums

  unsigned int jpa; // JP3 - 4 o'clock
  unsigned int jpb; // JP4 - 6 o'clock
  unsigned int jpc; // JP5 - 8 o'clock

  getEemcLowerHalfJetPatchSums(ee101,jpa,jpb,jpc);

  // Place jet patch thresholds on sums

  int jpaBits = 0;

  if ((jpa > ee101.registers[0]) && !(jpa > ee101.registers[1]) && !(jpa > ee101.registers[2])) jpaBits = 1;
  if ((jpa > ee101.registers[0]) &&  (jpa > ee101.registers[1]) && !(jpa > ee101.registers[2])) jpaBits = 2;
  if ((jpa > ee101.registers[0]) &&  (jpa > ee101.registers[1]) &&  (jpa > ee101.registers[2])) jpaBits = 3;

  int jpbBits = 0;

  if ((jpb > ee101.registers[0]) && !(jpb > ee101.registers[1]) && !(jpb > ee101.registers[2])) jpbBits = 1;
  if ((jpb > ee101.registers[0]) &&  (jpb > ee101.registers[1]) && !(jpb > ee101.registers[2])) jpbBits = 2;
  if ((jpb > ee101.registers[0]) &&  (jpb > ee101.registers[1]) &&  (jpb > ee101.registers[2])) jpbBits = 3;

  int jpcBits = 0;

  if ((jpc > ee101.registers[0]) && !(jpc > ee101.registers[1]) && !(jpc > ee101.registers[2])) jpcBits = 1;
  if ((jpc > ee101.registers[0]) &&  (jpc > ee101.registers[1]) && !(jpc > ee101.registers[2])) jpcBits = 2;
  if ((jpc > ee101.registers[0]) &&  (jpc > ee101.registers[1]) &&  (jpc > ee101.registers[2])) jpcBits = 3;

  // OR HT bits

  int highTowerBits = 0;

  for (int ch = 0; ch < 6; ++ch)
    highTowerBits |= ee101.channels[ch] >> 12 & 0xf;

  // Find largest sum for 1.09 < eta < 1.4 (low eta)

  int lowEtaSumA = ee101.channels[0] & 0x3f; // 4 o'clock
  int lowEtaSumB = ee101.channels[3] & 0x3f; // 6 o'clock
  int lowEtaSumC = ee101.channels[4] & 0x3f; // 8 o'clock

  int maxA = (lowEtaSumA > lowEtaSumB) && !(lowEtaSumC > lowEtaSumA);
  int maxB = (lowEtaSumB > lowEtaSumC) && !(lowEtaSumA > lowEtaSumB);
  int maxC = (lowEtaSumC > lowEtaSumA) && !(lowEtaSumB > lowEtaSumC);

  int maxId;
  int maxSum;

  if (maxA) {
    maxId  = 1;
    maxSum = lowEtaSumA;
  }
  else if (maxB) {
    maxId  = 2;
    maxSum = lowEtaSumB;
  }
  else if (maxC) {
    maxId  = 3;
    maxSum = lowEtaSumC;
  }
  else {
    maxId  = 1;
    maxSum = lowEtaSumA;
  }

  // If overflow, set to max

  if (maxSum > 63) maxSum = 63;

  // OUTPUT (16):

  // (0-1) JPA threshold bits (2)
  // (2-3) JPB threshold bits (2)
  // (4-5) JPC threshold bits (2)
  // (6-11) Selected partial jet patch sum (6)
  // (12-13) Partial jet patch ID (2)
  // (14-15) HT bits (2)

  ee101.output  = jpaBits;
  ee101.output |= jpbBits << 2;
  ee101.output |= jpcBits << 4;
  ee101.output |= maxSum << 6;
  ee101.output |= maxId << 12;
  ee101.output |= highTowerBits << 14;
}

void getEemcLowerHalfJetPatchSums(const Board& ee101, unsigned int& jpa, unsigned int& jpb, unsigned int& jpc)
{
  int lowEtaSumA = ee101.channels[0] & 0x3f; // 4 o'clock
  int lowEtaSumB = ee101.channels[3] & 0x3f; // 6 o'clock
  int lowEtaSumC = ee101.channels[4] & 0x3f; // 8 o'clock

  int highEtaSumA = (ee101.channels[0] >> 6 & 0x3f) + (ee101.channels[1] & 0x3f); // 4 o'clock
  int highEtaSumB = (ee101.channels[3] >> 6 & 0x3f) + (ee101.channels[2] & 0x3f); // 6 o'clock
  int highEtaSumC = (ee101.channels[4] >> 6 & 0x3f) + (ee101.channels[5] & 0x3f); // 8 o'clock

  jpa = lowEtaSumA + highEtaSumA; // JP3 - 4 o'clock
  jpb = lowEtaSumB + highEtaSumB; // JP4 - 6 o'clock
  jpc = lowEtaSumC + highEtaSumC; // JP5 - 8 o'clock  
}
