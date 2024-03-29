#include "DSMAlgo_BC101_2013.hh"

void DSMAlgo_BC101_2013::operator()(DSM& dsm)
{
 //  // INPUT:

 //  // ----------------------------------------------------------------------
 //  // BC101 - ch0 - BE001               | B101 - ch1 - BW001               |
 //  //         ch2 - BE002               |        ch3 - BW002               |
 //  //         ch4 - BE003 - JP1 (0-15)  |        ch5 - BW003 - JP1 (0-15)  |
 //  // ----------------------------------------------------------------------
 //  // BC102 - ch0 - BE003 - JP6 (16-31) | B102 - ch1 - BW003 - JP6 (16-31) |
 //  //         ch2 - BE004               |        ch3 - BW004               |
 //  //         ch4 - BE005               |        ch5 - BW005               |
 //  // ----------------------------------------------------------------------

 //  // From each channel:

 //  // (0-5) TP sum for low-eta group (6)
 //  // (6-11) TP sum for high-eta group (6)
 //  // (12-15) HT bits (4)

 //  // REGISTERS:

 //  // R0: BEMC-Jet-Patch-Th0 (9)
 //  // R1: BEMC-Jet-Patch-Th1 (9)
 //  // R2: BEMC-Jet-Patch-Th2 (9)
 //  // R4: BEMC-JP-th-dijet (9)
 //  // ACTION:

 //  int jpx = 0;			// East (-1 < eta < 0)
 //  int jpy = 0;			// Middle (-0.6 < eta < 0.4)
 //  int jpz = 0;			// West (0 < eta < 1)
 //  int jpPartial = 0;		// Partial (0.4 < eta < 1)

 //  int highTowerBits = 0;

 //  // East (ch0/2/4 - even channels)

 //  for (int ch = 0; ch <= 4; ch += 2) {
 //    int lowEtaSum = dsm.channels[ch] & 0x3f;
 //    int highEtaSum = dsm.channels[ch] >> 6 & 0x3f;
 //    jpx += lowEtaSum + highEtaSum;
 //    jpy += lowEtaSum;
 //    highTowerBits |= dsm.channels[ch] >> 12 & 0xf;
 //  }

 //  // West (ch1/3/5 - odd channels)

 //  for (int ch = 1; ch <= 5; ch += 2) {
 //    int lowEtaSum = dsm.channels[ch] & 0x3f;
 //    int highEtaSum = dsm.channels[ch] >> 6 & 0x3f;
 //    jpy += lowEtaSum;
 //    jpz += lowEtaSum + highEtaSum;
 //    jpPartial += highEtaSum;
 //    highTowerBits |= dsm.channels[ch] >> 12 & 0xf;
 //  }

 //  // If overflow, set JPpartial sum to max
 //  if (jpPartial > 63) jpPartial = 63;

 //  // Compare each jet patch sum to three thresholds
 //  // and then pack results for each jet patch into
 //  // 2-bit integer.

 //  int jpxBits = 0;
 //  int jpyBits = 0;
 //  int jpzBits = 0;

 //  // 1-bit
 //  int dijetBits = 0 ;
 //  for (int reg = 0; reg < 3; ++reg) {
 //    if (jpx > dsm.registers[reg]) ++jpxBits;
 //    if (jpy > dsm.registers[reg]) ++jpyBits;
 //    if (jpz > dsm.registers[reg]) ++jpzBits;
 //  }
 //  // compare jpx, jpy, jpz to di-jet threshold
 //  // OR the results and produce di-jet output
 //  int r4 = dsm.registers[4];

 //  dijetBits = (jpx > r4) || (jpy > r4) || (jpz > r4);
 //  printf("R4 = %d jpx = %d jpy = %d jpz = %d\n", r4, jpx, jpy, jpz);
 //  // Pack high tower bits
 //  int packedHTBits = 0;
 //  for(int ibit = 0; ibit < 3; ++ibit)
 //    {
 //      if(highTowerBits & (1 << ibit))
	// ++packedHTBits;
 //    }
 //  int fourthHTBits = 0;
 //  fourthHTBits |= highTowerBits >> 3;

 //  printf("highTowerBits = %x packedHTBits = %d fourthHTBits = %d\n", highTowerBits, packedHTBits, fourthHTBits);
 //  // OUTPUT (16):

 //  // (0-1) JPX threshold bits (2)
 //  // (2-3) JPY threshold bits (2)
 //  // (4-5) JPZ threshold bits (2)
 //  // (6-11) JPpartial sum (6)
 //  // (12-15) HT bits (4)

 //  int out = 0;

 //  out |= jpxBits;
 //  out |= jpyBits << 2;
 //  out |= jpzBits << 4;
 //  out |= jpPartial << 6;
 //  out |= packedHTBits << 12;
 //  out |= fourthHTBits << 14;
 //  out |= dijetBits << 15;

  // INPUT:

  // ----------------------------------------------------------------------
  // BC101 - ch0 - BE001               | B101 - ch1 - BW001               |
  //         ch2 - BE002               |        ch3 - BW002               |
  //         ch4 - BE003 - JP1 (0-15)  |        ch5 - BW003 - JP1 (0-15)  |
  // ----------------------------------------------------------------------
  // BC102 - ch0 - BE003 - JP6 (16-31) | B102 - ch1 - BW003 - JP6 (16-31) |
  //         ch2 - BE004               |        ch3 - BW004               |
  //         ch4 - BE005               |        ch5 - BW005               |
  // ----------------------------------------------------------------------

  // From each channel:

  // (0-8) Unused
  // (9) TP threshold bit
  // (10) HT.TP threshold bit
  // (11-15) HT threshold bits

  // REGISTERS:

  // R0: BEMC-DAQ10k-HT-Sel (3)
  int r0 = dsm.registers[0];

  int upperHT = 0;
  int lowerHT = 0;

  int upperTP = 0;
  int lowerTP = 0;

  int upperHTTP = 0;
  int lowerHTTP = 0;

  for(int iichn = 0; iichn < 3; iichn++){
    lowerHT |= dsm.channels[iichn] >> 10 & 0x3f;
    lowerTP |= dsm.channels[iichn] >> 8 & 0x1;
    lowerHTTP |= dsm.channels[iichn] >> 9 & 0x1;
    
    upperHT |= dsm.channels[iichn+3] >> 10 & 0x3f;
    upperTP |= dsm.channels[iichn+3] >> 8 & 0x1;
    upperHTTP |= dsm.channels[iichn+3] >> 9 & 0x1;
  }

  int daq10kSel[6];
  int DAQ10k = 0;

  for(int ichn = 0; ichn < 6; ichn++){
    daq10kSel[ichn] = 0;
    daq10kSel[ichn] = dsm.channels[ichn] >> (10 + r0) & 0x1;
    DAQ10k |= daq10kSel[ichn];
  }

  int HT = 0;
  int TP = 0;
  int HTTP = 0;

  HT = lowerHT | upperHT;
  TP = lowerTP | upperTP;
  HTTP = lowerHTTP | upperHTTP;

  // OUTPUT (16+16):
  // To EM201
  // (0-7) Unused
  // (8) DAQ10k test bit
  // (9) TP threshold bit
  // (10) HT.TP threshold bit
  // (11-15) HT threshold bits
  // To EM202
  // (16-21) DAQ10k HT bits
  // (22-31) Unused

  int out = 0;
  out |= DAQ10k << 7;
  out |= TP << 8;
  out |= HTTP << 9;
  out |= HT << 10;

  out |= daq10kSel[0] << 16;
  out |= daq10kSel[1] << 17;
  out |= daq10kSel[2] << 18;
  out |= daq10kSel[3] << 19;
  out |= daq10kSel[4] << 20;
  out |= daq10kSel[5] << 21;


  dsm.output = out;

  // INFO:
  
  // dsm.info[0] = jpx;
  // dsm.info[1] = jpy;
  // dsm.info[2] = jpz;
}
