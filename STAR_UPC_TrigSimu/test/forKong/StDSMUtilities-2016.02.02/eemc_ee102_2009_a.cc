//
// Pibero Djawotho <pibero@tamu.edu>
// Texas A&M University
// 11 March 2011
//

#include "Board.hh"
#include "eemc_ee102_2009_a.hh"

void eemc_ee102_2009_a(Board& ee102)
{
  // INPUT:

  // EE102 - ch0 - EE005 - (16-31) jp1 clockwise
  //         ch1 - EE006
  //         ch2 - EE007
  //         ch3 - EE008 - (0-15)  jp0 anti-clockwise
  //         ch4 - EE008 - (16-31) jp1 clockwise
  //         ch5 - EE009

  // From E006/007/009:

  // (0-5) TP sum for low-eta group (6)
  // (6-11) TP sum for high-eta group (6)
  // (12-13) HT bits (2)
  // (14-15) Unused (2)

  // From E005/008:

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

  unsigned int jpa; // JP0 - 10 o'clock
  unsigned int jpb; // JP1 - 12 o'clock
  unsigned int jpc; // JP2 - 2  o'clock

  getEemcUpperHalfJetPatchSums(ee102,jpa,jpb,jpc);

  // Place jet patch thresholds on sums

  int jpaBits = 0;

  if ((jpa > ee102.registers[0]) && !(jpa > ee102.registers[1]) && !(jpa > ee102.registers[2])) jpaBits = 1;
  if ((jpa > ee102.registers[0]) &&  (jpa > ee102.registers[1]) && !(jpa > ee102.registers[2])) jpaBits = 2;
  if ((jpa > ee102.registers[0]) &&  (jpa > ee102.registers[1]) &&  (jpa > ee102.registers[2])) jpaBits = 3;

  int jpbBits = 0;

  if ((jpb > ee102.registers[0]) && !(jpb > ee102.registers[1]) && !(jpb > ee102.registers[2])) jpbBits = 1;
  if ((jpb > ee102.registers[0]) &&  (jpb > ee102.registers[1]) && !(jpb > ee102.registers[2])) jpbBits = 2;
  if ((jpb > ee102.registers[0]) &&  (jpb > ee102.registers[1]) &&  (jpb > ee102.registers[2])) jpbBits = 3;

  int jpcBits = 0;

  if ((jpc > ee102.registers[0]) && !(jpc > ee102.registers[1]) && !(jpc > ee102.registers[2])) jpcBits = 1;
  if ((jpc > ee102.registers[0]) &&  (jpc > ee102.registers[1]) && !(jpc > ee102.registers[2])) jpcBits = 2;
  if ((jpc > ee102.registers[0]) &&  (jpc > ee102.registers[1]) &&  (jpc > ee102.registers[2])) jpcBits = 3;

  // OR HT bits

  int highTowerBits = 0;

  for (int ch = 0; ch < 6; ++ch)
    highTowerBits |= ee102.channels[ch] >> 12 & 0xf;

  // Find largest sum for 1.09 < eta < 1.4 (low eta)

  int lowEtaSumA = ee102.channels[1] & 0x3f; // 10 o'clock
  int lowEtaSumB = ee102.channels[2] & 0x3f; // 12 o'clock
  int lowEtaSumC = ee102.channels[5] & 0x3f; // 2  o'clock

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

  int out = 0;

  out |= jpaBits;
  out |= jpbBits << 2;
  out |= jpcBits << 4;
  out |= maxSum << 6;
  out |= maxId << 12;
  out |= highTowerBits << 14;

  ee102.output = out;
}

void getEemcUpperHalfJetPatchSums(const Board& ee102, unsigned int& jpa, unsigned int& jpb, unsigned int& jpc)
{
  int lowEtaSumA = ee102.channels[1] & 0x3f; // 10 o'clock
  int lowEtaSumB = ee102.channels[2] & 0x3f; // 12 o'clock
  int lowEtaSumC = ee102.channels[5] & 0x3f; // 2  o'clock

  int highEtaSumA = (ee102.channels[1] >> 6 & 0x3f) + (ee102.channels[0] & 0x3f); // 10 o'clock
  int highEtaSumB = (ee102.channels[2] >> 6 & 0x3f) + (ee102.channels[3] & 0x3f); // 12 o'clock
  int highEtaSumC = (ee102.channels[5] >> 6 & 0x3f) + (ee102.channels[4] & 0x3f); // 2  o'clock

  jpa = lowEtaSumA + highEtaSumA; // JP0 - 10 o'clock
  jpb = lowEtaSumB + highEtaSumB; // JP1 - 12 o'clock
  jpc = lowEtaSumC + highEtaSumC; // JP2 - 2  o'clock
}
