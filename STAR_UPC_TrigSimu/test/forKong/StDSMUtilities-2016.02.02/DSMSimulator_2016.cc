#include<cstdlib>
#include<fstream>
#include<numeric>
using namespace std;

#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH2F.h"
#include "TMySQLServer.h"
#include "TMySQLResult.h"
#include "TMySQLRow.h"
#include "trgUtil_2009.hh"
#include "bits.hh"
#include "qt32b_fpe_2009_a.hh"
#include "qt32b_fms_2009_a.hh"
#include "fms_fm001_2015_a.hh"
#include "fms_fm005_2015_a.hh"
#include "fms_fm006_2015_a.hh"
#include "fms_fm101_2015_a.hh"
#include "fms_fm103_2015_a.hh"
#include "l1_fp201_2015_a.hh"
#include "bemc_bw001_2014_b.hh"
#include "bemc_bw003_2014_b.hh"
#include "bemc_be001_2014_b.hh"
#include "bemc_be003_2014_b.hh"
//#include "bemc_bc101_2012_a.hh"
#include "bemc_bc101_2014_b.hh"
#include "eemc_ee001_2009_b.hh"
#include "eemc_ee002_2009_b.hh"
#include "eemc_ee101_2009_a.hh"
#include "eemc_ee102_2009_a.hh"
#include "l1_em201_2014_b.hh"
#include "l1_em202_2012_a.hh"
//#include "l1_vt201_2015_a.hh"
//#include "l1_vt201_2015_b.hh"
//#include "l1_vt201_2015_c.hh"
//#include "l1_vt201_2014_a.hh"
//#include "l1_vt201_2016_a.hh"
#include "l1_vt201_2016_b.hh"
//#include "l1_tf201_2015_a.hh"
//#include "l1_tf201_2015_b.hh"
//#include "l1_tf201_2016_a.hh"
#include "l1_tf201_2016_b.hh"
//#include "qt32b_10_v6_2.hh"
//#include "qt32b_l0_v6_a.hh"
//#include "qt32b_l0_v5_b.hh"
#include "qt32b_l0_v6_d.hh"
#include "qt32b_l0_v7_6.hh"
#include "qt32b_l0_v5_f.hh"
#include "qt32b_l0_v6_f.hh"
#include "mix_tf001_2014_c.hh"
#include "mix_tf101_2014_b.hh"
//#include "mix_mt101_2014_d.hh"
#include "mix_mt101_2016_a.hh"
#include "mix_pp101_2015_a.hh"
//#include "bbc_bb101_2009_a.hh"
#include "bbc_bb101_2016_a.hh"
#include "bbc_bb102_2010_b.hh"
#include "bbc_vp101_2016_a.hh"
//#include "bbc_zd101_2012_a.hh"
//#include "bbc_zd101_2014_c.hh"
#include "bbc_zd101_2016_a.hh"

#include "DSMSimulator_2016.hh"

DSMSimulator_2016::DSMSimulator_2016()
  // Crates
  : l1(crateAt(L1_CONF_NUM))
  , mix(crateAt(MIX_CONF_NUM))
  , bbc(crateAt(BBC_CONF_NUM))
  , fms(crateAt(FMS_CONF_NUM))
  , bc1(crateAt(BC1_CONF_NUM))
  , bcw(crateAt(BCW_CONF_NUM))
  , bce(crateAt(BCE_CONF_NUM))
  , mxq(crateAt(MXQ_CONF_NUM))
  , feq(crateAt(FEQ_CONF_NUM))
  , bbq(crateAt(BBQ_CONF_NUM))
  , qt1(crateAt(QT1_CONF_NUM))
  , qt2(crateAt(QT2_CONF_NUM))
  , qt3(crateAt(QT3_CONF_NUM))
  , qt4(crateAt(QT4_CONF_NUM))

    // L1 crate
  , tf201(l1.boardAt(TF201_BASE_ADDRESS))
  , vt201(l1.boardAt(VT201_BASE_ADDRESS))
  , em201(l1.boardAt(EM201_BASE_ADDRESS))
  , bx201(l1.boardAt(BX201_BASE_ADDRESS))
  , bx202(l1.boardAt(BX202_BASE_ADDRESS))
  , st201(l1.boardAt(ST201_BASE_ADDRESS))
  , fp201(l1.boardAt(FP201_BASE_ADDRESS))
  , ld301(l1.boardAt(LD301_BASE_ADDRESS))

    // BC1 crate
  , bc101(bc1.boardAt(BC101_BASE_ADDRESS))
  , bc102(bc1.boardAt(BC102_BASE_ADDRESS))
  , bc103(bc1.boardAt(BC103_BASE_ADDRESS))
  , bc104(bc1.boardAt(BC104_BASE_ADDRESS))
  , bc105(bc1.boardAt(BC105_BASE_ADDRESS))
  , bc106(bc1.boardAt(BC106_BASE_ADDRESS))
  , ee101(bc1.boardAt(EE101_BASE_ADDRESS))
  , ee102(bc1.boardAt(EE102_BASE_ADDRESS))
  , ee001(bc1.boardAt(EE001_BASE_ADDRESS))
  , ee002(bc1.boardAt(EE002_BASE_ADDRESS))
  , ee003(bc1.boardAt(EE003_BASE_ADDRESS))
  , ee004(bc1.boardAt(EE004_BASE_ADDRESS))
  , ee005(bc1.boardAt(EE005_BASE_ADDRESS))
  , ee006(bc1.boardAt(EE006_BASE_ADDRESS))
  , ee007(bc1.boardAt(EE007_BASE_ADDRESS))
  , ee008(bc1.boardAt(EE008_BASE_ADDRESS))
  , ee009(bc1.boardAt(EE009_BASE_ADDRESS))

    // BCW crate
  , bw001(bcw.boardAt(BW001_BASE_ADDRESS))
  , bw002(bcw.boardAt(BW002_BASE_ADDRESS))
  , bw003(bcw.boardAt(BW003_BASE_ADDRESS))
  , bw004(bcw.boardAt(BW004_BASE_ADDRESS))
  , bw005(bcw.boardAt(BW005_BASE_ADDRESS))
  , bw006(bcw.boardAt(BW006_BASE_ADDRESS))
  , bw007(bcw.boardAt(BW007_BASE_ADDRESS))
  , bw008(bcw.boardAt(BW008_BASE_ADDRESS))
  , bw009(bcw.boardAt(BW009_BASE_ADDRESS))
  , bw010(bcw.boardAt(BW010_BASE_ADDRESS))
  , bw011(bcw.boardAt(BW011_BASE_ADDRESS))
  , bw012(bcw.boardAt(BW012_BASE_ADDRESS))
  , bw013(bcw.boardAt(BW013_BASE_ADDRESS))
  , bw014(bcw.boardAt(BW014_BASE_ADDRESS))
  , bw015(bcw.boardAt(BW015_BASE_ADDRESS))

    // BCE crate
  , be001(bce.boardAt(BE001_BASE_ADDRESS))
  , be002(bce.boardAt(BE002_BASE_ADDRESS))
  , be003(bce.boardAt(BE003_BASE_ADDRESS))
  , be004(bce.boardAt(BE004_BASE_ADDRESS))
  , be005(bce.boardAt(BE005_BASE_ADDRESS))
  , be006(bce.boardAt(BE006_BASE_ADDRESS))
  , be007(bce.boardAt(BE007_BASE_ADDRESS))
  , be008(bce.boardAt(BE008_BASE_ADDRESS))
  , be009(bce.boardAt(BE009_BASE_ADDRESS))
  , be010(bce.boardAt(BE010_BASE_ADDRESS))
  , be011(bce.boardAt(BE011_BASE_ADDRESS))
  , be012(bce.boardAt(BE012_BASE_ADDRESS))
  , be013(bce.boardAt(BE013_BASE_ADDRESS))
  , be014(bce.boardAt(BE014_BASE_ADDRESS))
  , be015(bce.boardAt(BE015_BASE_ADDRESS))

    // MIX crate
//  , fe101(mix.boardAt(FE101_BASE_ADDRESS))
  , pp101(mix.boardAt(PP101_BASE_ADDRESS))
  , mt101(mix.boardAt(MT101_BASE_ADDRESS))
  , tf101(mix.boardAt(TF101_BASE_ADDRESS))
  , tf001(mix.boardAt(TF001_BASE_ADDRESS))
  , tf002(mix.boardAt(TF002_BASE_ADDRESS))
  , tf003(mix.boardAt(TF003_BASE_ADDRESS))
  , tf004(mix.boardAt(TF004_BASE_ADDRESS))
  , tf005(mix.boardAt(TF005_BASE_ADDRESS))
  , tf006(mix.boardAt(TF006_BASE_ADDRESS))
  , em202(mix.boardAt(EM202_BASE_ADDRESS))
  , mt102(mix.boardAt(MT102_BASE_ADDRESS))
  , tf202(mix.boardAt(TF202_BASE_ADDRESS))

    // FEQ crate
  , fe001(feq.boardAt(FE001_BASE_ADDRESS))
  , fe002(feq.boardAt(FE002_BASE_ADDRESS))
  , fe003(feq.boardAt(FE003_BASE_ADDRESS))
  , fe004(feq.boardAt(FE004_BASE_ADDRESS))
  , fs001(feq.boardAt(FS001_BASE_ADDRESS))
  , fs002(feq.boardAt(FS002_BASE_ADDRESS))
  , fs003(feq.boardAt(FS003_BASE_ADDRESS))
  , fs004(feq.boardAt(FS004_BASE_ADDRESS))
  , fs005(feq.boardAt(FS005_BASE_ADDRESS))
  , fs006(feq.boardAt(FS006_BASE_ADDRESS))

    // BBC crate
  , bb101(bbc.boardAt(BB101_BASE_ADDRESS))
  , bb102(bbc.boardAt(BB102_BASE_ADDRESS))
  , zd101(bbc.boardAt(ZD101_BASE_ADDRESS))
  , vp101(bbc.boardAt(VP101_BASE_ADDRESS))

    // FMS crate
  , fm001(fms.boardAt(FM001_BASE_ADDRESS))
  , fm002(fms.boardAt(FM002_BASE_ADDRESS))
  , fm003(fms.boardAt(FM003_BASE_ADDRESS))
  , fm004(fms.boardAt(FM004_BASE_ADDRESS))
  , fm101(fms.boardAt(FM101_BASE_ADDRESS))
  , fm005(fms.boardAt(FM005_BASE_ADDRESS))
  , fm006(fms.boardAt(FM006_BASE_ADDRESS))
  , fm007(fms.boardAt(FM007_BASE_ADDRESS))
  , fm008(fms.boardAt(FM008_BASE_ADDRESS))
  , fm102(fms.boardAt(FM102_BASE_ADDRESS))
  , fm009(fms.boardAt(FM009_BASE_ADDRESS))
  , fm010(fms.boardAt(FM010_BASE_ADDRESS))
  , fm011(fms.boardAt(FM011_BASE_ADDRESS))
  , fm012(fms.boardAt(FM012_BASE_ADDRESS))
  , fm103(fms.boardAt(FM103_BASE_ADDRESS))
  , fm104(fms.boardAt(FM104_BASE_ADDRESS))
    // BBQ crate
  , bb001(bbq.boardAt(BB001_BASE_ADDRESS))
  , bb002(bbq.boardAt(BB002_BASE_ADDRESS))
  , bb003(bbq.boardAt(BB003_BASE_ADDRESS))
  , vp001(bbq.boardAt(VP001_BASE_ADDRESS))
  , vp002(bbq.boardAt(VP002_BASE_ADDRESS))
  , zd001(bbq.boardAt(ZD001_BASE_ADDRESS))

    // MXQ crate
  , mt001(mxq.boardAt(MT001_BASE_ADDRESS))
  , pp001(mxq.boardAt(PP001_BASE_ADDRESS))
//  , zp001(mxq.boardAt(ZP001_BASE_ADDRESS))
  , px001(mxq.boardAt(PX001_BASE_ADDRESS))
  , vp003(mxq.boardAt(VP003_BASE_ADDRESS))
  , vp004(mxq.boardAt(VP004_BASE_ADDRESS))
  , mt002(mxq.boardAt(MT002_BASE_ADDRESS))
  , mt003(mxq.boardAt(MT003_BASE_ADDRESS))
  , mt004(mxq.boardAt(MT004_BASE_ADDRESS))
  , mt005(mxq.boardAt(MT005_BASE_ADDRESS))
  , mt006(mxq.boardAt(MT006_BASE_ADDRESS))
  , mt007(mxq.boardAt(MT007_BASE_ADDRESS))
  , mt008(mxq.boardAt(MT008_BASE_ADDRESS))
{
  // L1 crate
  tf201.setName("TF201");
  vt201.setName("VT201");
  em201.setName("EM201");
  em202.setName("EM202");
  bx201.setName("BX201");
  bx202.setName("BX202");
  st201.setName("ST201");
  fp201.setName("FP201");
  ld301.setName("LD301");

  // BC1 crate
  bc101.setName("BC101");
  bc102.setName("BC102");
  bc103.setName("BC103");
  bc104.setName("BC104");
  bc105.setName("BC105");
  bc106.setName("BC106");
  ee101.setName("EE101");
  ee102.setName("EE102");
  ee001.setName("EE001");
  ee002.setName("EE002");
  ee003.setName("EE003");
  ee004.setName("EE004");
  ee005.setName("EE005");
  ee006.setName("EE006");
  ee007.setName("EE007");
  ee008.setName("EE008");
  ee009.setName("EE009");

  // BCW crate
  bw001.setName("BW001");
  bw002.setName("BW002");
  bw003.setName("BW003");
  bw004.setName("BW004");
  bw005.setName("BW005");
  bw006.setName("BW006");
  bw007.setName("BW007");
  bw008.setName("BW008");
  bw009.setName("BW009");
  bw010.setName("BW010");
  bw011.setName("BW011");
  bw012.setName("BW012");
  bw013.setName("BW013");
  bw014.setName("BW014");
  bw015.setName("BW015");

  // BCE crate
  be001.setName("BE001");
  be002.setName("BE002");
  be003.setName("BE003");
  be004.setName("BE004");
  be005.setName("BE005");
  be006.setName("BE006");
  be007.setName("BE007");
  be008.setName("BE008");
  be009.setName("BE009");
  be010.setName("BE010");
  be011.setName("BE011");
  be012.setName("BE012");
  be013.setName("BE013");
  be014.setName("BE014");
  be015.setName("BE015");

  // MIX crate
  //fe101.setName("FE101");
  pp101.setName("FE101");
  mt101.setName("MT101");
  tf101.setName("TF101");
  tf001.setName("TF001");
  tf002.setName("TF002");
  tf003.setName("TF003");
  tf004.setName("TF004");
  tf005.setName("TF005");
  tf006.setName("TF006");

  // BBQ crate
  bb001.setName("BB001");
  bb002.setName("BB002");
  bb003.setName("BB003");
  vp001.setName("VP001");
  vp002.setName("VP002");
  zd001.setName("ZD001");

  // FMS crate
  fm001.setName("FM001");
  fm002.setName("FM002");
  fm003.setName("FM003");
  fm004.setName("FM004");
  fm101.setName("FM101");
  fm005.setName("FM005");
  fm006.setName("FM006");
  fm007.setName("FM007");
  fm008.setName("FM008");
  fm102.setName("FM102");
  fm009.setName("FM009");
  fm010.setName("FM010");
  fm011.setName("FM011");
  fm012.setName("FM012");
  fm103.setName("FM103");
  fm104.setName("FM104");

  // MXQ crate
  mt001.setName("MT001");
  //zp001.setName("PP001");
  pp001.setName("ZP001");
  vp003.setName("VP003");
  vp004.setName("VP004");
  mt002.setName("MT002");

  // FEQ crate
  fe001.setName("FE001");
  fe002.setName("FE002");
  fe003.setName("FE003");
  fe004.setName("FE004");
  fs001.setName("FS001");
  fs002.setName("FS002");
  fs003.setName("FS003");
  fs004.setName("FS004");
  fs005.setName("FS005");
  fs006.setName("FS006");

  fe001.bitmask = 0x01010101;
  fe002.bitmask = 0xff010101;
  fe003.bitmask = 0x01010101;
  fe004.bitmask = 0xff010101;

  // BBQ crate
  bb001.setName("BB001");
  bb002.setName("BB002");
  bb003.setName("BB003");
  vp001.setName("VP001");
  vp002.setName("VP002");
  zd001.setName("ZD001");
}

void DSMSimulator_2016::setFile(const char* filename)
{
  mFileName = filename;
}

void DSMSimulator_2016::setFullDSMTree(int value)
{
  mFullDSMTree = value;
}

void DSMSimulator_2016::setEMCStatus(int status)
{
  mEMCStatus = status;
}

void DSMSimulator_2016::setVTXStatus(int status)
{
  mVTXStatus = status;
}

void DSMSimulator_2016::setTOFStatus(int status)
{
  mTOFStatus = status;
}

void DSMSimulator_2016::setFPDStatus(int status)
{
  mFPDStatus = status;
}

void DSMSimulator_2016::init()
{
  mFile = TFile::Open(mFileName, "recreate");

  // EMC branch

  if (mEMCStatus) initEmcBranch();
  if (mFPDStatus) initFpdBranch();
  if (mVTXStatus) initVtxBranch();
  if (mTOFStatus) initTofBranch();

  // Last DSM or new TCU all channels

  for (int ch = 0; ch < 8; ++ch) {
    mLD301Bits[ch] = new TH2F(Form("LD301Ch%d",ch),"",16,0,16,2,0,2);
    for (int bin = 1; bin <= 2; ++bin)
      mLD301Bits[ch]->GetYaxis()->SetBinLabel(bin,Form("%d",bin-1));
    mLD301BitsDiff[ch] = new TH2F(Form("LD301Ch%dDiff",ch),"",16,0,16,3,-1,2);
    for (int bin = 1; bin <= 3; ++bin)
      mLD301BitsDiff[ch]->GetYaxis()->SetBinLabel(bin,Form("%d",bin-2));
  }

  // TF201 0-15 (ch0)
  labelLD301TF201(mLD301Bits[0]);
  labelLD301TF201(mLD301BitsDiff[0]);

  // VT201 0-15 (ch1)
  labelLD301VT201(mLD301Bits[1]);
  labelLD301VT201(mLD301BitsDiff[1]);

  // TF201 16-31 (ch2)
  mLD301Bits[2]->SetTitle("Unused (ch2)");

  // EM201 0-15 (ch3)
  labelLD301EM201(mLD301Bits[3]);
  labelLD301EM201(mLD301BitsDiff[3]);
  // RAT board (ch4)

  mLD301Bits[4]->SetTitle("RAT board (ch4)");

  mLD301Bits[4]->GetXaxis()->SetBinLabel(1,"FMS-LED");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(2,"RAT1");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(3,"RAT2");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(4,"RAT3");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(5,"Abort-gaps");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(6,"Yellow-Fill");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(7,"RAT6");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(8,"RAT7");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(9,"RAT8");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(10,"RAT9");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(11,"RAT10");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(12,"RAT11");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(13,"RAT12");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(14,"RAT13");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(15,"RAT14");
  mLD301Bits[4]->GetXaxis()->SetBinLabel(16,"RAT15");

  // FP201 0-15 (ch5)

  mLD301Bits[5]->SetTitle("FP201 0-15 (ch5)");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(1,"FMSsmall-bs3");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(2,"FMSsmall-bs2");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(3,"FMSsmall-bs1");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(4,"FMSlarge-bs3");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(5,"FMSlarge-bs2");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(6,"FMSlarge-bs1");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(7,"FMS-DiBS");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(8,"FMS-JP2");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(9,"FMS-JP1");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(10,"FMS-JP0");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(11,"FMS-DiJet");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(12,"Unused");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(13,"Unused");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(14,"Unused");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(15,"Unused");
  mLD301Bits[5]->GetXaxis()->SetBinLabel(16,"Unused");

  mLD301BitsDiff[5]->SetTitle("FP201 0-15 (ch5)");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(1,"FMSsmall-bs3");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(2,"FMSsmall-bs2");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(3,"FMSsmall-bs1");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(4,"FMSlarge-bs3");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(5,"FMSlarge-bs2");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(6,"FMSlarge-bs1");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(7,"FMS-DiBS");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(8,"FMS-JP2");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(9,"FMS-JP1");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(10,"FMS-JP0");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(11,"FMS-DiJet");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(12,"Unused");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(13,"Unused");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(14,"Unused");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(15,"Unused");
  mLD301BitsDiff[5]->GetXaxis()->SetBinLabel(16,"Unused");

  // ST201 0-15 (ch6)

  mLD301Bits[6]->SetTitle("ST201 0-15 (ch6)");
  mLD301Bits[6]->GetXaxis()->SetBinLabel(1,"Laser-protection");
  mLD301Bits[6]->GetXaxis()->SetBinLabel(2,"Laser-fire");
  mLD301Bits[6]->GetXaxis()->SetBinLabel(3,"Laser-lamp");
  mLD301Bits[6]->GetXaxis()->SetBinLabel(4,"Laser-diode");
  mLD301Bits[6]->GetXaxis()->SetBinLabel(15,"Zero-bias");
  mLD301Bits[6]->GetXaxis()->SetBinLabel(16,"Random");

  // Unused (ch7)

  mLD301Bits[7]->SetTitle("Unused (ch7)");
  
  // 7-bit bXing

  mBunchId7Bit = new TH1F("BunchId7Bit","BunchId7Bit (all events)",120,0,120);
  mBunchId7BitBHT1 = new TH1F("BunchId7BitBHT1","BunchId7Bit (BemcHiTwr-th1)",120,0,120);
  mBunchId7BitHTTP = new TH1F("BunchId7BitHTTP","BunchId7Bit (HT.TP UPCsingle)",120,0,120);
  mBunchId7BitTP = new TH1F("BunchId7BitTP","BunchId7Bit (TP UPCsingle)",120,0,120);
  mBunchId7BitHT = new TH1F("BunchId7BitHT","BunchId7Bit (HT UPCsingle)",120,0,120);
  mBunchId7BitVPDTAC = new TH1F("BunchId7BitVPDTAC","BunchId7Bit (VPD-TAC)",120,0,120);
  mBunchId7BitMTD2 = new TH1F("BunchId7BitMTD2","BunchId7Bit (MTD-th2)",120,0,120);
  //  mBlueFill = new TH1F("BlueFill","Abort-gaps",120,0,120);
  //  mYellowFill = new TH1F("YellowFill","!Yellow-Fill",120,0,120);

  //  mBlueFill->SetFillColor(kBlue);
  //  mYellowFill->SetFillColor(kYellow);
}
void DSMSimulator_2016::labelLD301EM201(TH2F *h)
{
  h->SetTitle("EM201 0-15 (ch3)");
  h->GetXaxis()->SetBinLabel(1,"BHT0");
  h->GetXaxis()->SetBinLabel(2,"BHT1");
  h->GetXaxis()->SetBinLabel(3,"BHT2");
  h->GetXaxis()->SetBinLabel(4,"BHT3");
  h->GetXaxis()->SetBinLabel(5,"BHT4");
  h->GetXaxis()->SetBinLabel(6,"BHT-UPC");
  h->GetXaxis()->SetBinLabel(7,"BTP");
  h->GetXaxis()->SetBinLabel(8,"BHT.TP");
  h->GetXaxis()->SetBinLabel(9,"BTP-topo");
  h->GetXaxis()->SetBinLabel(10,"BHT.TP-topo");
  h->GetXaxis()->SetBinLabel(11,"BHT4-topo");
  h->GetXaxis()->SetBinLabel(12,"Unused");
  h->GetXaxis()->SetBinLabel(13,"Unused");
  h->GetXaxis()->SetBinLabel(14,"EHT0");
  h->GetXaxis()->SetBinLabel(15,"EHT1");
  h->GetXaxis()->SetBinLabel(16,"DAQ10k");
  
  labelHistogramYaxis(h);
}
void DSMSimulator_2016::labelLD301TF201(TH2F *h)
{  
  h->SetTitle("TF201 0-15 (ch0)");
  h->GetXaxis()->SetBinLabel(1,"MTD0");
  h->GetXaxis()->SetBinLabel(2,"MTD1");
  h->GetXaxis()->SetBinLabel(3,"MTD2-T-Cosmic");
  h->GetXaxis()->SetBinLabel(4,"TOF_UPC");
  h->GetXaxis()->SetBinLabel(5,"TOFmult0");
  h->GetXaxis()->SetBinLabel(6,"TOFmult1");
  h->GetXaxis()->SetBinLabel(7,"TOFmult2");
  h->GetXaxis()->SetBinLabel(8,"TOFmult3");
  h->GetXaxis()->SetBinLabel(9,"MTD1-T-Cosmic");
  h->GetXaxis()->SetBinLabel(10,"TOFsector0_3");
  h->GetXaxis()->SetBinLabel(11,"TOFsector1_4");
  h->GetXaxis()->SetBinLabel(12,"TOFsector2_5");
  h->GetXaxis()->SetBinLabel(13,"MTD2-Hit");
  h->GetXaxis()->SetBinLabel(14,"MTD-Cosmic");
  h->GetXaxis()->SetBinLabel(15,"MTD1-Hit");
  h->GetXaxis()->SetBinLabel(16,"TOFmult4");
  labelHistogramYaxis(h);

}
void DSMSimulator_2016::labelLD301VT201(TH2F *h)
{  
  h->SetTitle("VT201 0-15 (ch1)");
  h->GetXaxis()->SetBinLabel(1,"BBC-TAC");
  h->GetXaxis()->SetBinLabel(2,"BBC-E");
  h->GetXaxis()->SetBinLabel(3,"BBC-W");
  h->GetXaxis()->SetBinLabel(4,"VPD-TAC2");
  h->GetXaxis()->SetBinLabel(5,"BBC-Sum");
  h->GetXaxis()->SetBinLabel(6,"BBC-L");
  h->GetXaxis()->SetBinLabel(7,"ZDC-TAC");
  h->GetXaxis()->SetBinLabel(8,"ZDC-E");
  h->GetXaxis()->SetBinLabel(9,"ZDC-W");
  h->GetXaxis()->SetBinLabel(10,"ZDC-UPC");
  h->GetXaxis()->SetBinLabel(11,"ZDC-EW");
  h->GetXaxis()->SetBinLabel(12,"MinB");
  h->GetXaxis()->SetBinLabel(13,"VPD-TAC3");
  h->GetXaxis()->SetBinLabel(14,"VPD-TAC");
  h->GetXaxis()->SetBinLabel(15,"VPD-E");
  h->GetXaxis()->SetBinLabel(16,"VPD-W");

  labelHistogramYaxis(h);
}
void DSMSimulator_2016::initEmcBranch()
{
  // Create EMC histograms

  // BEMC layer 0

  mB001HighTower = new TH2F("B001HighTower", "Barrel EMC L0 Input - High Tower;Trigger Patch;High Tower", 300, 0, 300, 64, 0, 64);
  mB001TriggerPatch = new TH2F("B001TriggerPatch", "Barrel EMC L0 Input - Patch Sum;Trigger Patch;Patch Sum", 300, 0, 300, 64, 0, 64);

  // EEMC layer 0

  mE001HighTower = new TH2F("E001HighTower", "Endcap EMC L0 Input - High Tower;Trigger Patch;High Tower", 90, 0, 90, 64, 0, 64);
  mE001TriggerPatch = new TH2F("E001TriggerPatch", "Endcap EMC L0 Input - Patch Sum;Trigger Patch;Patch Sum", 90, 0, 90, 64, 0, 64);

  // BEMC layer 1
  const char *nameB101[8] = {"TP", "HT.TP", "HT-th0", "HT-th1", 
			     "HT-th2", "HT-th3", "HT-th4", "HT-UPC"};
  for(int ibit = 0; ibit < 8; ibit++){
    mB101Bits[ibit] = new TH2F(Form("BC1-%s", nameB101[ibit]), Form("BC1-%s;channel", nameB101[ibit]), 36, 0, 36, 2, 0, 2);
    labelB101Histogram(mB101Bits[ibit]);
    //Difference
    mB101BitsDiff[ibit] = new TH2F(Form("BC1-%s-Diff", nameB101[ibit]), Form("BC1-%s-Diff;channel", nameB101[ibit]), 36, 0, 36, 3, -1, 2);
    labelB101Histogram(mB101BitsDiff[ibit]);
  }
  // EEMC layer 1

  mE101LowEtaSum = new TH2F("E101LowEtaSum", "Endcap EMC L1 Input - Low Eta Sum;;Low Eta Sum", 12, 0, 12, 64, 0, 64);
  mE101HighEtaSum = new TH2F("E101HighEtaSum", "Endcap EMC L1 Input - High Eta Sum;;High Eta Sum", 12, 0, 12, 64, 0, 64);
  
  labelE101Histogram(mE101LowEtaSum);
  labelE101Histogram(mE101HighEtaSum);

  const char* nameE101[2] = {"HT-th0", "HT-th1"};
  for(int i = 0; i < 2; i++){
    mE101HighTowerBits[i] = new TH2F(Form("E101%s", nameE101[i]), Form("Endcap EMC L1 Input - %s;channel", nameE101[i]), 12, 0, 12, 2, 0, 2);
    labelE101Histogram(mE101HighTowerBits[i]);
  }

  mE101LowEtaSumDiff = new TH2F("E101LowEtaSumDiff", "Endcap EMC L1 Input - Low Eta Sum;;Low Eta Sum - Simulated", 12, 0, 12, 128, -64, 64);
  mE101HighEtaSumDiff = new TH2F("E101HighEtaSumDiff", "Endcap EMC L1 Input - High Eta Sum;;High Eta Sum - Simulated", 12, 0, 12, 128, -64, 64);

  for(int i = 0; i < 2; i++){
    mE101HighTowerBitsDiff[i] = new TH2F(Form("E101%sDiff", nameE101[i]), Form("Endcap EMC L1 Input - %s Diff;channel", nameE101[i]), 12, 0, 12, 3, -1, 2);
    labelE101Histogram(mE101HighTowerBitsDiff[i]);
  }
  labelE101Histogram(mE101LowEtaSumDiff);
  labelE101Histogram(mE101HighEtaSumDiff);

  // EMC layer 2
  for(int ichn = 0; ichn < 6; ichn++){
    mEM201[ichn] = new TH2F(Form("EM201-BC10%d", ichn+1), Form("EM201-BC10%d", ichn+1), 9, 0, 9, 2, 0, 2);
    labelEM201Histogram(mEM201[ichn]);
    //Diff
    mEM201Diff[ichn] = new TH2F(Form("EM201-BC10%dDiff", ichn+1), Form("EM201-BC10%dDiff", ichn+1), 9, 0, 9, 3, -1, 2);
    labelEM201Histogram(mEM201Diff[ichn]);
  }
  mEM201[6] = new TH2F(Form("EM201-EE10%d", 1), Form("EM201-EE10%d", 1), 2, 0, 2, 2, 0, 2);
  labelEM201Histogram(mEM201[6]);
  mEM201[7] = new TH2F(Form("EM201-EE10%d", 2), Form("EM201-EE10%d", 2), 2, 0, 2, 2, 0, 2);
  labelEM201Histogram(mEM201[7]);
  //Diff
  mEM201Diff[6] = new TH2F(Form("EM201-EE10%dDiff", 1), Form("EM201-EE10%dDiff", 1), 2, 0, 2, 3, -1, 2);
  labelEM201Histogram(mEM201Diff[6]);
  mEM201Diff[7] = new TH2F(Form("EM201-EE10%dDiff", 2), Form("EM201-EE10%dDiff", 2), 2, 0, 2, 3, -1, 2);
  labelEM201Histogram(mEM201Diff[7]);
  
  mEM202 = new TH1F("EM202","DAQ10k HT bits",36,0,36);
  mEM202Diff = new TH1F("EM202Diff","DAQ10k HT bits errors",71,-35,36);
  mTpcReadoutMask = new TH1F("TpcReadoutMask","TPC Readout Mask (simulated)",32,0,32);
}

void DSMSimulator_2016::initVtxBranch()
{
  bookBB001Histograms();
  bookVP001Histograms();
  bookZD001Histograms();
  //bookZP001Histograms();
  bookBB101Histograms();
  bookBB102Histograms();
  bookVP101Histograms();
  bookZD101Histograms();
  bookVT201Histograms(); 
  bookBeamEnergyScanHistograms();
}

void DSMSimulator_2016::initTofBranch()
{
  bookTF001Histograms();
  bookMT001Histograms();
  bookPP001Histograms();
  bookTF101Histograms();
  bookMT101Histograms();
  //  bookPP101Histograms();
  bookTF201Histograms();
}

void DSMSimulator_2016::initFpdBranch()
{
  bookFmsLayer0Histograms();
  bookFmsLayer1Histograms();
  bookFmsLayer2Histograms();
  bookFmsQtHistograms();
}

void DSMSimulator_2016::run(const TriggerDataBlk& event)
{
  // main crossing
  readCrates(event);

  // pre/post crossings
  EvtDescData* evtDesc = (EvtDescData*)((char*)&event+event.EventDesc_ofl.offset);

  assert(strncmp(evtDesc->name,"EVD",3) == 0 || strncmp(evtDesc->name,"EVT",3) == 0);

  if (event.eventNumber % 1000 == 0)
    printf("event=%d format=%08x nbytes=%d npre=%d npost=%d\n",event.eventNumber,event.FormatVersion,event.totalTriggerLength,evtDesc->npre,evtDesc->npost);

  const int nprepost = evtDesc->npre+evtDesc->npost;

  for (int prepost = 0; prepost < nprepost; ++prepost) readCrates(event,prepost);

  shiftMT102();
  /*
  fillBB001Histograms();
  fillVP001Histograms();
  fillZD001Histograms();
  fillZP001Histograms();  
  fillMT001Histograms();  
  fillPP001Histograms();  
  fillTF001Histograms();
  fillTF101Histograms();
  fillTF201Histograms();
  */
  fillBeamEnergyScanHistograms();

  fill(mLD301Errors,mLD301Errors+8,0);
  /*
  if (mEMCStatus) runEmcBranch(event);
  if (mFPDStatus) runFpdBranch(event);
  if (mVTXStatus) runVtxBranch(event);
  if (mTOFStatus) runTofBranch(event);
  */
  //  Crate sim;
  if (mEMCStatus) runEmcBranch();
  if (mFPDStatus) runFpdBranch();
  if (mVTXStatus) runVtxBranch();
  if (mTOFStatus) runTofBranch();

#if 0
  printf("%10d ",event.eventNumber);
  for (int ch = 0; ch < 8; ++ch)
    printf("%04x ",mLD301Errors[ch]);
  printf("\n");
#endif

  fillLastDsmHistograms();

  fillBunchIdHistograms(event);
}
void DSMSimulator_2016::shiftMT102()
{
  //swap mt102 channel bits
  for(int ii = 0; ii < 8; ii++){
    unsigned short buffer = 0x0;
    buffer |= mt102.channels[ii] >> 8 | ((mt102.channels[ii] & 0xff) << 8);
    mt102.channels[ii] = buffer;
    //cout<<ii<<" "<<hex<<mt102.channels[ii]<<dec<<endl;
  }
  //cout<<"tac 8: "<<hex<<mt101.channels[8]<<" tac 9: "<<mt101.channels[9]<<dec<<endl;
  //re-arrange mt102 channel bits
  int channels[10];
  for(int ich = 0; ich < 6; ich += 3){
    int jch = ich/3*4;
    channels[jch] = mt102.channels[ich] & 0xfff;
    channels[jch+1] = ((mt102.channels[ich] >> 12) & 0xf) | ((mt102.channels[ich+1] & 0xff) << 4);
    channels[jch+2] = ((mt102.channels[ich+1] >> 8 ) & 0xff )| ((mt102.channels[ich+2] & 0xf) << 8);
    channels[jch+3] = (mt102.channels[ich+2] >> 4) & 0xfff;
//    cout<<ich<<" "<<jch<<" "<<hex<<mt102.channels[ich]<<" "<<mt102.channels[ich+1]<<" "<<mt102.channels[ich+2]<<dec<<endl;
  }
  channels[8] = mt102.channels[6] & 0xfff;
  channels[9] = ((mt102.channels[6] >> 12) & 0xf) | ((mt102.channels[7] & 0xff) << 4);
  for(int ich = 0; ich < 10; ich++){
    mt102.channels[ich] = channels[ich];
    //cout<<ich<<" "<<hex<<mt102.channels[ich]<<endl;
  }
}

void DSMSimulator_2016::runEmcBranch()
{
  Crate sim;
  fillBemcLayer0Histograms();
  fillEemcLayer0Histograms();

  runBemcLayer0();
  runEemcLayer0();

  writeBemcLayer0ToBemcLayer1(sim);
  writeEemcLayer0ToEemcLayer1(sim);

  fillBemcLayer1Histograms(sim);
  fillEemcLayer1Histograms(sim);

//  fillBemcJetPatches();
//  fillEemcJetPatches();

  runBemcLayer1();
  runEemcLayer1();

  writeBemcLayer1ToEmcLayer2(sim);
  writeEemcLayer1ToEmcLayer2(sim);

  fillEmcLayer2Histograms(sim);

//  fillHybridJetPatches();

  runEmcLayer2();
  fillTpcReadoutMaskHistogram();

  writeEmcLayer2ToLastDsm(sim);

  fillLastDsmHistograms(sim,3);
}

void DSMSimulator_2016::runBemcLayer0()
{
  // west barrel
  bemc_bw001_2014_b(bw001);
  bemc_bw001_2014_b(bw002);
  bemc_bw003_2014_b(bw003);
  bemc_bw001_2014_b(bw004);
  bemc_bw001_2014_b(bw005);
  bemc_bw001_2014_b(bw006);
  bemc_bw001_2014_b(bw007);
  bemc_bw003_2014_b(bw008);
  bemc_bw001_2014_b(bw009);
  bemc_bw001_2014_b(bw010);
  bemc_bw001_2014_b(bw011);
  bemc_bw001_2014_b(bw012);
  bemc_bw003_2014_b(bw013);
  bemc_bw001_2014_b(bw014);
  bemc_bw001_2014_b(bw015);

  // east barrel
  bemc_be001_2014_b(be001);
  bemc_be001_2014_b(be002);
  bemc_be003_2014_b(be003);
  bemc_be001_2014_b(be004);
  bemc_be001_2014_b(be005);
  bemc_be001_2014_b(be006);
  bemc_be001_2014_b(be007);
  bemc_be003_2014_b(be008);
  bemc_be001_2014_b(be009);
  bemc_be001_2014_b(be010);
  bemc_be001_2014_b(be011);
  bemc_be001_2014_b(be012);
  bemc_be003_2014_b(be013);
  bemc_be001_2014_b(be014);
  bemc_be001_2014_b(be015);
}

void DSMSimulator_2016::runEemcLayer0()
{
  eemc_ee001_2009_b(ee001);
  eemc_ee002_2009_b(ee002);
  eemc_ee001_2009_b(ee003);
  eemc_ee001_2009_b(ee004);
  eemc_ee002_2009_b(ee005);
  eemc_ee001_2009_b(ee006);
  eemc_ee001_2009_b(ee007);
  eemc_ee002_2009_b(ee008);
  eemc_ee001_2009_b(ee009);
}

void DSMSimulator_2016::runBemcLayer1()
{ 
  /*
  bemc_bc101_2012_a(bc101);
  bemc_bc101_2012_a(bc102);
  bemc_bc101_2012_a(bc103);
  bemc_bc101_2012_a(bc104);
  bemc_bc101_2012_a(bc105);
  bemc_bc101_2012_a(bc106);
 */
  bemc_bc101_2014_b(bc101);
  bemc_bc101_2014_b(bc102);
  bemc_bc101_2014_b(bc103);
  bemc_bc101_2014_b(bc104);
  bemc_bc101_2014_b(bc105);
  bemc_bc101_2014_b(bc106);
}

void DSMSimulator_2016::runEemcLayer1()
{
  eemc_ee101_2009_a(ee101);
  eemc_ee102_2009_a(ee102);
}

void DSMSimulator_2016::runEmcLayer2()
{
  l1_em201_2014_b(em201);
  l1_em202_2012_a(em202);
}

void DSMSimulator_2016::finish()
{
  mFile->Write();
  mFile->Close();
}

int DSMSimulator_2016::eventLoop(char* first, char* last)
{
  int nevents = 0;

  while (first < last) {
    TriggerDataBlk& event = (TriggerDataBlk&)*first;
    swapTriggerDataBlk(event);
    run(event);
    first += event.totalTriggerLength;
    ++nevents;
    //if (nevents == 1000) break;
  }

  return nevents;
}

void DSMSimulator_2016::fillBemcLayer0Histograms()
{
  fillBemcLayer0Histograms(0,bw001);
  fillBemcLayer0Histograms(10,bw002);
  fillBemcLayer0Histograms(20,bw003);
  fillBemcLayer0Histograms(30,bw004);
  fillBemcLayer0Histograms(40,bw005);
  fillBemcLayer0Histograms(50,bw006);
  fillBemcLayer0Histograms(60,bw007);
  fillBemcLayer0Histograms(70,bw008);
  fillBemcLayer0Histograms(80,bw009);
  fillBemcLayer0Histograms(90,bw010);
  fillBemcLayer0Histograms(100,bw011);
  fillBemcLayer0Histograms(110,bw012);
  fillBemcLayer0Histograms(120,bw013);
  fillBemcLayer0Histograms(130,bw014);
  fillBemcLayer0Histograms(140,bw015);
  fillBemcLayer0Histograms(150,be001);
  fillBemcLayer0Histograms(160,be002);
  fillBemcLayer0Histograms(170,be003);
  fillBemcLayer0Histograms(180,be004);
  fillBemcLayer0Histograms(190,be005);
  fillBemcLayer0Histograms(200,be006);
  fillBemcLayer0Histograms(210,be007);
  fillBemcLayer0Histograms(220,be008);
  fillBemcLayer0Histograms(230,be009);
  fillBemcLayer0Histograms(240,be010);
  fillBemcLayer0Histograms(250,be011);
  fillBemcLayer0Histograms(260,be012);
  fillBemcLayer0Histograms(270,be013);
  fillBemcLayer0Histograms(280,be014);
  fillBemcLayer0Histograms(290,be015);
}

void DSMSimulator_2016::fillBemcLayer0Histograms(int bin0, const Board& dsm)
{
  //printf("%s: ",dsm.name);
  for (int ch = 0; ch < 10; ++ch) {
    int bin = bin0+ch;
    mB001HighTower->Fill(bin,dsm.channels[ch] & 0x3f);
    mB001TriggerPatch->Fill(bin,dsm.channels[ch] >> 6 & 0x3f);
    //printf("%04x ",dsm.channels[ch]);
  }
  //printf("\n");
}

void DSMSimulator_2016::fillEemcLayer0Histograms()
{
  fillEemcLayer0Histograms(0,ee001);
  fillEemcLayer0Histograms(10,ee002);
  fillEemcLayer0Histograms(20,ee003);
  fillEemcLayer0Histograms(30,ee004);
  fillEemcLayer0Histograms(40,ee005);
  fillEemcLayer0Histograms(50,ee006);
  fillEemcLayer0Histograms(60,ee007);
  fillEemcLayer0Histograms(70,ee008);
  fillEemcLayer0Histograms(80,ee009);
}
void DSMSimulator_2016::fillEemcLayer0Histograms(int bin0, const Board& dsm)
{
  for (int ch = 0; ch < 10; ++ch) {
    int bin = bin0+ch;
    mE001HighTower->Fill(bin,dsm.channels[ch] & 0x3f);
    mE001TriggerPatch->Fill(bin,dsm.channels[ch] >> 6 & 0x3f);
  }  
}

void DSMSimulator_2016::fillBemcLayer1Histograms(const Crate& sim)
{
  const Board& bc101sim = sim.boardAt(BC101_BASE_ADDRESS);
  const Board& bc102sim = sim.boardAt(BC102_BASE_ADDRESS);
  const Board& bc103sim = sim.boardAt(BC103_BASE_ADDRESS);
  const Board& bc104sim = sim.boardAt(BC104_BASE_ADDRESS);
  const Board& bc105sim = sim.boardAt(BC105_BASE_ADDRESS);
  const Board& bc106sim = sim.boardAt(BC106_BASE_ADDRESS);

  fillBemcLayer1Histograms(0,bc101,bc101sim);
  fillBemcLayer1Histograms(6,bc102,bc102sim);
  fillBemcLayer1Histograms(12,bc103,bc103sim);
  fillBemcLayer1Histograms(18,bc104,bc104sim);
  fillBemcLayer1Histograms(24,bc105,bc105sim);
  fillBemcLayer1Histograms(30,bc106,bc106sim);
}
/*
void DSMSimulator_2016::fillBemcJetPatches()
{
  // Args: DSM, JPX=east, JPY=middle, JPZ=west
  fillBemcJetPatches(bc101, 6,12,0);
  fillBemcJetPatches(bc102, 7,13,1);
  fillBemcJetPatches(bc103, 8,14,2);
  fillBemcJetPatches(bc104, 9,15,3);
  fillBemcJetPatches(bc105,10,16,4);
  fillBemcJetPatches(bc106,11,17,5);
}
*/
void DSMSimulator_2016::fillBemcLayer1Histograms(int bin0, const Board& dsm, const Board& sim)
{
  for (int ch = 0; ch < 6; ++ch) {
    int bin = bin0+ch;
    for(int ib = 0; ib < 8; ib++){
      mB101Bits[ib]->Fill(bin, btest(dsm.channels[ch], ib+8));
      if (int diff = btest(dsm.channels[ch], ib+8) - btest(sim.channels[ch], ib+8)) mB101BitsDiff[ib]->Fill(bin,diff);
    }
  }
}
/*
void DSMSimulator_2016::fillBemcJetPatches(const Board& bc101, int jpx, int jpy, int jpz)
{
  unsigned int jpxSum, jpySum, jpzSum, jpPartialSum;
  int highTowerBits;

  //getBemcJetPatchSums2015A(bc101,jpxSum,jpySum,jpzSum,jpPartialSum,highTowerBits);

  //mBarrelJetPatches->Fill(jpx,jpxSum);
  //mBarrelJetPatches->Fill(jpy,jpySum);
  //mBarrelJetPatches->Fill(jpz,jpzSum);
}
*/
void DSMSimulator_2016::fillEemcLayer1Histograms(const Crate& sim)
{
  const Board& ee101sim = sim.boardAt(EE101_BASE_ADDRESS);
  const Board& ee102sim = sim.boardAt(EE102_BASE_ADDRESS);

  fillEemcLayer1Histograms(0,ee101,ee101sim);
  fillEemcLayer1Histograms(6,ee102,ee102sim);
}

void DSMSimulator_2016::fillEemcLayer1Histograms(int bin0, const Board& dsm, const Board& sim)
{
  for (int ch = 0; ch < 6; ++ch) {
    int bin = bin0+ch;
    mE101LowEtaSum->Fill(bin,dsm.channels[ch] & 0x3f);
    mE101HighEtaSum->Fill(bin,dsm.channels[ch] >> 6 & 0x3f);
    for(int i = 0; i < 2; i++){
      mE101HighTowerBits[i]->Fill(bin, btest(dsm.channels[ch], 12+i));
      if (int diff = btest(dsm.channels[ch], 12+i) - btest(sim.channels[ch], 12+i)) mE101HighTowerBitsDiff[i]->Fill(bin,diff);
    }
    if (int diff = (dsm.channels[ch] & 0x3f) - (sim.channels[ch] & 0x3f)) mE101LowEtaSumDiff->Fill(bin,diff);
    if (int diff = (dsm.channels[ch] >> 6 & 0x3f) - (sim.channels[ch] >> 6 & 0x3f)) mE101HighEtaSumDiff->Fill(bin,diff);
  }
}
/*
void DSMSimulator_2016::fillEemcJetPatches()
{
  unsigned int jpa, jpb, jpc;

  getEemcLowerHalfJetPatchSums(ee101,jpa,jpb,jpc);

  mEndcapJetPatches->Fill(3.,jpa);
  mEndcapJetPatches->Fill(4.,jpb);
  mEndcapJetPatches->Fill(5.,jpc);

  getEemcUpperHalfJetPatchSums(ee102,jpa,jpb,jpc);

  mEndcapJetPatches->Fill(0.,jpa);
  mEndcapJetPatches->Fill(1.,jpb);
  mEndcapJetPatches->Fill(2.,jpc);
}
*/
void DSMSimulator_2016::fillEmcLayer2Histograms(const Crate& sim)
{
  const Board& em201sim = sim.boardAt(EM201_BASE_ADDRESS);
  for (int ch = 0; ch < 8; ++ch) {
    if(ch < 6){
      //BC101:106
      for(int ib = 0; ib < 9; ib++){
	mEM201[ch]->Fill(ib, btest(em201.channels[ch], ib+7));
	if(int diff = btest(em201.channels[ch], ib+7) - btest(em201sim.channels[ch], ib+7)) mEM201Diff[ch]->Fill(ib, diff);
      }
    }else{
      //EE101:EE102
      for(int ib = 0; ib < 2; ib++){
	mEM201[ch]->Fill(ib, btest(em201.channels[ch], ib+14));
	if(int diff = btest(em201.channels[ch], ib+14) - btest(em201sim.channels[ch], ib+14)) mEM201Diff[ch]->Fill(ib, diff);
      }
    }
  }
  const Board& em202sim = sim.boardAt(EM202_BASE_ADDRESS);
  for (int ch = 0; ch < 6; ++ch) {
    for (int ch2 = 0; ch2 < 6; ++ch2) {
      int idx = ch*6+ch2;
      int htBit = em202.channels[ch] >> ch2 & 1;
      int htBitSim = em202sim.channels[ch] >> ch2 & 1;
      if (htBit) mEM202->Fill(idx);
      if (htBit != htBitSim) mEM202Diff->Fill(idx);
    }
  }
}

void DSMSimulator_2016::fillTpcReadoutMaskHistogram()
{
  for (int i = 0; i < 32; ++i)
    if (btest(em202.output,i)) mTpcReadoutMask->Fill(i);
}
/*
void DSMSimulator_2016::fillHybridJetPatches()
{
  unsigned int jpSums[2];
  //getHybridJetPatchSums(em201,jpSums[0],jpSums[1]);
  for (int i = 0; i < 2; ++i) {
    int jpPartial = em201.channels[6+i] >> 12 & 0x3;
    int jp = (1-i)*3+jpPartial-1;
    //mHybridJetPatches->Fill(jp,jpSums[i]);
  }
}
*/
void DSMSimulator_2016::fillBunchIdHistograms(const TriggerDataBlk& event)
{
  //
  // http://www.star.bnl.gov/public/trg/TSL/Software/DSM_BC_1_SYNC.htm
  // http://www.star.bnl.gov/public/trg/TSL/Software/DSM_BC_2_SYNC.htm
  // http://www.star.bnl.gov/public/trg/TSL/Schematics/L1_Crate_Cable_Map.pdf
  //
  // BX201: Ch1: BX202 Out 16-31: Current 7-bit bunch type counter value
  //        Ch2: Bit 0: RHIC synchronization bit (?)
  //        Out: Bit 0-31: Current counter value
  //
  // BX202: Ch0: BX201 Out 0-15: Lower 16 bits of BC_1 output
  //        Ch1: BX201 Out 16-31: Upper 16 bits of BC_1 output
  //        Ch7: Bit 0: RHIC synchronization bit
  //        Out: Bit 0-15: Current 16-bit bunch crossing counter value
  //             Bit 16-22: Current 7-bit bunch type counter value
  //
  // The 48-bit counter combines the 32-bit counter BX202 channel 0 and
  // channel 1 (lower 32 bits) with BX201 channel 0 (upper 16 bits).
  //
  // http://www.star.bnl.gov/public/trg/TSL/Software/EMC.pdf
  //
  // EM201 output:
  //
  // Bit      Name              Description
  //
  // Bit 0    BemcHiTwr-th0     Barrel HT bit
  // Bit 1    BemcHiTwr-th1     Barrel HT bit
  // Bit 2    BemcHiTwr-th2     Barrel HT bit
  // Bit 3    BemcHiTwr-th3     Barrel HT bit
  // Bit 4    EemcHiTwr-th0     Endcap HT bit
  // Bit 5    EemcHiTwr-th1     Endcap HT bit
  // Bit 6    JP1               JP1, unified over the BEMC+EEMC
  // Bit 7    JP2               JP2, unified over the BEMC+EEMC
  // Bit 8    BJP1              BJP1 for the 18 BEMC-only patches
  // Bit 9    EEMC-dijet        EEMC-only JP0-base dijet trigger bit
  // Bit 10   EJP1              EJP1 for the 6 EEMC-only patches
  // Bit 11   JP1-dijet         JP1-based dijet trigger bit
  // Bit 12   JP0-dijet         JP0-based dijet trigger bit
  // Bit 13   BAJP              AJP for the BEMC-only patches
  // Bit 14   DAQ10k            DAQ10k trigger bit
  // Bit 15   JP0               JP0, unified over the BEMC+EEMC
  //
  int bunchId7Bit = getbits(bx201.channels[1],0,7);
  mBunchId7Bit->Fill(bunchId7Bit); // all events

  int tf201out = ld301.channels[0];
  if (btest(tf201out,1)) mBunchId7BitMTD2->Fill(bunchId7Bit); // MTD-th2
  //  if (btest(tf201out,2)) mBunchId7BitRPET->Fill(bunchId7Bit); // RP_ET

  int vt201out = ld301.channels[1];
  if (btest(vt201out,13)) mBunchId7BitVPDTAC->Fill(bunchId7Bit); // VPD-TAC

  int em201out = ld301.channels[3];
  if (btest(em201out,1)) mBunchId7BitBHT1->Fill(bunchId7Bit); // BHT1
  if (btest(em201out,5)) mBunchId7BitHT->Fill(bunchId7Bit); // HT
  if (btest(em201out,6)) mBunchId7BitTP->Fill(bunchId7Bit); // TP
  if (btest(em201out,7)) mBunchId7BitHTTP->Fill(bunchId7Bit); // HTTP
  //  if (btest(em201out,8)) mBunchId7Bit->Fill(bunchId7Bit); // FMS-JP1
  //int fp201out = ld301.channels[5];
  //if (btest(ld301.channels[4],4)) mBlueFill->Fill(bunchId7Bit);
  //if (!btest(ld301.channels[4],5)) mYellowFill->Fill(bunchId7Bit);
}

void DSMSimulator_2016::fillBeamEnergyScanHistograms()
{
  int tofMult = getbits(tf201.channels[2],0,13);

  int* bb101channels = (int*)bb101.channels;
  int bb001out = bb101channels[0]; // east
  int bb002out = bb101channels[1]; // west
  int bbcSmallEastAdcSum = getbits(bb001out,0,16);
  //int bbcSmallEastTacMax = getbits(bb001out,16,12);
  int bbcSmallWestAdcSum = getbits(bb002out,0,16);
  //int bbcSmallWestTacMax = getbits(bb002out,16,12);

  //int* bb102channels = (int*)bb102.channels;
  //int bb003out = bb102channels[0]; // east and west
  int bbcLargeEastAdcSum = bb003.channels[0]+bb003.channels[1]+bb003.channels[2]+bb003.channels[3]+bb003.channels[8]+bb003.channels[9]+bb003.channels[10]+bb003.channels[11];
  int bbcLargeWestAdcSum = bb003.channels[16]+bb003.channels[17]+bb003.channels[18]+bb003.channels[19]+bb003.channels[24]+bb003.channels[25]+bb003.channels[26]+bb003.channels[27];
  //int bbcLargeEastTacMax = getbits(bb003out,0,12);
  //int bbcLargeWestTacMax = getbits(bb003out,12,12);
  //int bbcLargeEastHit = btest(bb003out,24);
  //int bbcLargeWestHit = btest(bb003out,25);

  int vp003out = vp101.channels[4]; // east
  int vp004out = vp101.channels[6]; // west
  int vpdEastAdcSum = getbits(vp003out,0,12);
  //int vpdEastTacMax = getbits(vp003out,16,12);
  int vpdWestAdcSum = getbits(vp004out,0,12);
  //int vpdWestTacMax = getbits(vp004out,16,12);

  int zdcEastSumAtt = zd001.channels[3];
  int zdcWestSumAtt = zd001.channels[19];
  int bbcstac = getbits(vt201.channels[0],0,13);
  int bbcltac = getbits(vt201.channels[1],0,13);
  //int vpdtac  = getbits(vt201.channels[4],0,13);
  int* zd101channels = (int*)zd101.channels;
  int zd001out = zd101channels[0];
  int zdctacw = getbits(zd001out, 0,10);
  int zdctace = getbits(zd001out,10,10);
  int zdctac = (zdctacw > 0 && zdctace > 0) ? 1024+zdctace-zdctacw : 0;

  hTofVsBbcSmallEast->Fill(bbcSmallEastAdcSum,tofMult);
  hTofVsBbcSmallWest->Fill(bbcSmallWestAdcSum,tofMult);
  hTofVsBbcLargeEast->Fill(bbcLargeEastAdcSum,tofMult);
  hTofVsBbcLargeWest->Fill(bbcLargeWestAdcSum,tofMult);
  hTofVsVpdEast->Fill(vpdEastAdcSum,tofMult);
  hTofVsVpdWest->Fill(vpdWestAdcSum,tofMult);
  hTofVsZdcEast->Fill(zdcEastSumAtt,tofMult);
  hTofVsZdcWest->Fill(zdcWestSumAtt,tofMult);
  hBbcLargeVsSmallEast->Fill(bbcSmallEastAdcSum,bbcLargeEastAdcSum);
  hBbcLargeVsSmallWest->Fill(bbcSmallWestAdcSum,bbcLargeWestAdcSum);
  hBbcLargeVsVpdEast->Fill(vpdEastAdcSum,bbcLargeEastAdcSum);
  hBbcLargeVsVpdWest->Fill(vpdWestAdcSum,bbcLargeWestAdcSum);
  hBbcLargeVsZdcEast->Fill(zdcEastSumAtt,bbcLargeEastAdcSum);
  hBbcLargeVsZdcWest->Fill(zdcWestSumAtt,bbcLargeWestAdcSum);
  hBbcSmallVsVpdEast->Fill(vpdEastAdcSum,bbcSmallEastAdcSum);
  hBbcSmallVsVpdWest->Fill(vpdWestAdcSum,bbcSmallWestAdcSum);
  hBbcSmallVsZdcEast->Fill(zdcEastSumAtt,bbcSmallEastAdcSum);
  hBbcSmallVsZdcWest->Fill(zdcWestSumAtt,bbcSmallWestAdcSum);
  hVpdVsZdcEast->Fill(zdcEastSumAtt,vpdEastAdcSum);
  hVpdVsZdcWest->Fill(zdcWestSumAtt,vpdWestAdcSum);
  hBbcLargeEastVsWest->Fill(bbcLargeWestAdcSum,bbcLargeEastAdcSum);
  hBbcSmallEastVsWest->Fill(bbcSmallWestAdcSum,bbcSmallEastAdcSum);
  hVpdEastVsWest->Fill(vpdWestAdcSum,vpdEastAdcSum);
  hZdcEastVsWest->Fill(zdcWestSumAtt,zdcEastSumAtt);

  hBbcLargeVsSmallTac->Fill(bbcstac,bbcltac);
  //hBbcLargeVsVpdTac->Fill(vpdtac,bbcltac);
  hBbcLargeVsZdcTac->Fill(zdctac,bbcltac);
  //hBbcSmallVsVpdTac->Fill(vpdtac,bbcstac);
  hBbcSmallVsZdcTac->Fill(zdctac,bbcstac);
  //hVpdVsZdcTac->Fill(zdctac,vpdtac);
  hZdcTacEastVsWest->Fill(zdctacw,zdctace);
}

void DSMSimulator_2016::labelB101Histogram(TH2F* h)
{
  for (int bin = 1; bin <= h->GetNbinsX(); ++bin) {
    h->GetXaxis()->SetBinLabel(bin,Form("%d",(bin-1)%6));
  }
  labelHistogramYaxis(h);
}

void DSMSimulator_2016::labelE101Histogram(TH2F* h)
{
  TAxis* xaxis = h->GetXaxis();
  xaxis->SetBinLabel(1,"EE001");
  xaxis->SetBinLabel(2,"EE002-LO");
  xaxis->SetBinLabel(3,"EE002-HI");
  xaxis->SetBinLabel(4,"EE003");
  xaxis->SetBinLabel(5,"EE004");
  xaxis->SetBinLabel(6,"EE005-LO");
  xaxis->SetBinLabel(7,"EE005-HI");
  xaxis->SetBinLabel(8,"EE006");
  xaxis->SetBinLabel(9,"EE007");
  xaxis->SetBinLabel(10,"EE008-LO");
  xaxis->SetBinLabel(11,"EE008-HI");
  xaxis->SetBinLabel(12,"EE009");
  labelHistogramYaxis(h);
}

void DSMSimulator_2016::labelEM201Histogram(TH2F* h)
{
  TAxis* xaxis = h->GetXaxis();
  if(h->GetNbinsX() == 9){
    xaxis->SetBinLabel(1,"DAQ10k");
    xaxis->SetBinLabel(2,"TP");
    xaxis->SetBinLabel(3,"HT.TP");
    xaxis->SetBinLabel(4,"HT-th0");
    xaxis->SetBinLabel(5,"HT-th1");
    xaxis->SetBinLabel(6,"HT-th2");
    xaxis->SetBinLabel(7,"HT-th3");
    xaxis->SetBinLabel(8,"HT-th4");
    xaxis->SetBinLabel(9,"HT-UPC");
  }else if(h->GetNbinsX() == 2){
    xaxis->SetBinLabel(1,"HT-th0");
    xaxis->SetBinLabel(2,"HT-th1");    
  }
  labelHistogramYaxis(h);
}
void DSMSimulator_2016::labelHistogramYaxis(TH2F *h)
{
    if(h->GetNbinsY() == 2){
    h->GetYaxis()->SetBinLabel(1, "0");
    h->GetYaxis()->SetBinLabel(2, "1");
  }else if(h->GetNbinsY() == 3){
    h->GetYaxis()->SetBinLabel(1, "-1");
    h->GetYaxis()->SetBinLabel(2, "0");
    h->GetYaxis()->SetBinLabel(3, "1");
  }
}
void DSMSimulator_2016::loadRegisters()
{
  TMySQLServer* mysql = 0;
  const char* database = "mysql://onldb.starp.bnl.gov:3501/Conditions_rts?timeout=60";
  const char* user = "";
  const char* pass = "";

  // Open connection to database server

  //if (strstr(gSystem->HostName(),"bnl.gov") && (mysql = (TMySQLServer*)TMySQLServer::Connect(database,user,pass))) {
  if ((mysql = (TMySQLServer*)TMySQLServer::Connect(database,user,pass))) {
    // object=crate, idx=board address
    TString query = Form("select object,idx,reg,label,value,defaultvalue from dict where hash=(select dicthash from run where idx_rn = %d)",runNumber);
    if (TMySQLResult* result = (TMySQLResult*)mysql->Query(query)) {
      while (TMySQLRow* row = (TMySQLRow*)result->Next()) {
	int object = atoi(row->GetField(0));
	int idx = atoi(row->GetField(1));
	int reg = atoi(row->GetField(2));
	TString label = row->GetField(3);
	int value = atoi(row->GetField(4));
	int defaultvalue = atoi(row->GetField(5));
	if (object >= 1 && object <= NCRATES && idx >= 0x10) {
	  cout << object << '\t' << idx << '\t' << reg << '\t' << label << '\t' << value << '\t' << defaultvalue << endl;
	  //crateAt(object).boardAt(idx<<24).registerAt((reg%100)<<24) = (value == -1) ? defaultvalue : value;
	  if(object == 9 && idx == 30 && reg/100 == 1){
	    crateAt(object).boardAt(idx<<24).registerAt((reg%100-13)<<24) = (value == -1) ? defaultvalue : value;
          }else if(object == 9 && (idx == 22 || idx == 24) && reg%100 == 17){
	    crateAt(object).boardAt(idx<<24).registerAt((reg%100+reg/100-1)<<24) = (value == -1) ? defaultvalue : value;
          }else{
	    crateAt(object).boardAt(idx<<24).registerAt((reg%100)<<24) = (value == -1) ? defaultvalue : value;
          }
	}
	delete row;
      }
      delete result;
    }

    // Close connection to database server

    mysql->Close();
   // set BBC QT ADC threshold to 20, TAC MIN to 100
   // east
   crateAt(9).boardAt(16<<24).registerAt((513%100)<<24) = 20;
   crateAt(9).boardAt(16<<24).registerAt((514%100)<<24) = 100;
   // west
   crateAt(9).boardAt(18<<24).registerAt((513%100)<<24) = 20;
   crateAt(9).boardAt(18<<24).registerAt((514%100)<<24) = 100;
   //VPD registers ADC threshold to 10
   //east
   crateAt(9).boardAt(22<<24).registerAt((513%100)<<24) = 10;
   //west
   crateAt(9).boardAt(24<<24).registerAt((513%100)<<24) = 10;
  }
  else {

    // Set DSM registers (Run 10100162)

    if (mEMCStatus) {

      // Set DSM registers (Run 12029009)

      // DSM ADC THR -> E_T THR (GeV):
      //
      // --  Towers:  (Thr)*0.236
      // --  Jets:   (Thr-5)*0.236

      const int BEMC_HT_TH0 = 11;
      const int BEMC_HT_TH1 = 18;
      const int BEMC_HT_TH2 = 25;
      const int BEMC_HT_TH3 = 31;

      setBarrelHighTowerTh(0,BEMC_HT_TH0);
      setBarrelHighTowerTh(1,BEMC_HT_TH1);
      setBarrelHighTowerTh(2,BEMC_HT_TH2);
      setBarrelHighTowerTh(3,BEMC_HT_TH3);

      cout << "BEMC_HT_TH0\t" << BEMC_HT_TH0 << endl;
      cout << "BEMC_HT_TH1\t" << BEMC_HT_TH1 << endl;
      cout << "BEMC_HT_TH2\t" << BEMC_HT_TH2 << endl;
      cout << "BEMC_HT_TH3\t" << BEMC_HT_TH3 << endl;

      const int EEMC_HT_TH0 = 25;
      const int EEMC_HT_TH1 = 31;

      setEndcapHighTowerTh(0,EEMC_HT_TH0);
      setEndcapHighTowerTh(1,EEMC_HT_TH1);

      cout << "EEMC_HT_TH0\t" << EEMC_HT_TH0 << endl;
      cout << "EEMC_HT_TH1\t" << EEMC_HT_TH1 << endl;

      const int BEMC_JP_TH0 = 32;
      const int BEMC_JP_TH1 = 43;
      const int BEMC_JP_TH2 = 64;

      setBarrelJetPatchTh(0,BEMC_JP_TH0);
      setBarrelJetPatchTh(1,BEMC_JP_TH1);
      setBarrelJetPatchTh(2,BEMC_JP_TH2);

      cout << "BEMC_JP_TH0\t" << BEMC_JP_TH0 << endl;
      cout << "BEMC_JP_TH1\t" << BEMC_JP_TH1 << endl;
      cout << "BEMC_JP_TH2\t" << BEMC_JP_TH2 << endl;

      const int EEMC_JP_TH0 = 32;
      const int EEMC_JP_TH1 = 43;
      const int EEMC_JP_TH2 = 64;

      setEndcapJetPatchTh(0,EEMC_JP_TH0);
      setEndcapJetPatchTh(1,EEMC_JP_TH1);
      setEndcapJetPatchTh(2,EEMC_JP_TH2);

      cout << "EEMC_JP_TH0\t" << EEMC_JP_TH0 << endl;
      cout << "EEMC_JP_TH1\t" << EEMC_JP_TH1 << endl;
      cout << "EEMC_JP_TH2\t" << EEMC_JP_TH2 << endl;

      const int BEMC_EEMC_OVERLAP_JP_TH0 = 32;
      const int BEMC_EEMC_OVERLAP_JP_TH1 = 43;
      const int BEMC_EEMC_OVERLAP_JP_TH2 = 64;

      setOverlapJetPatchTh(0,BEMC_EEMC_OVERLAP_JP_TH0);
      setOverlapJetPatchTh(1,BEMC_EEMC_OVERLAP_JP_TH1);
      setOverlapJetPatchTh(2,BEMC_EEMC_OVERLAP_JP_TH2);

      cout << "BEMC_EEMC_OVERLAP_JP_TH0\t" << BEMC_EEMC_OVERLAP_JP_TH0 << endl;
      cout << "BEMC_EEMC_OVERLAP_JP_TH1\t" << BEMC_EEMC_OVERLAP_JP_TH1 << endl;
      cout << "BEMC_EEMC_OVERLAP_JP_TH2\t" << BEMC_EEMC_OVERLAP_JP_TH2 << endl;
    }

    if (mFPDStatus) {
      const int FMS_SMALL_HT_TH0 = 4;
      const int FMS_SMALL_HT_TH1 = 8;
      const int FMS_LARGE_HT_TH0 = 4;
      const int FMS_LARGE_HT_TH1 = 8;
      const int FMS_SMALL_CLUSTER_TH0 = 5;
      const int FMS_SMALL_CLUSTER_TH1 = 13;
      const int FMS_SMALL_CLUSTER_TH2 = 22;
      const int FMS_LARGE_CLUSTER_TH0 =  6 /* 61 */;
      const int FMS_LARGE_CLUSTER_TH1 = 17 /* 62 */;
      const int FMS_LARGE_CLUSTER_TH2 = 25 /* 63 */;
      const int FMS_JP0 = 12 /* 50 */;
      const int FMS_JP1 = 18 /* 62 */;
      const int FMS_JP2 = 30 /* 63 */;

      cout << "FMS_SMALL_HT_TH0\t" << FMS_SMALL_HT_TH0 << endl;
      cout << "FMS_SMALL_HT_TH1\t" << FMS_SMALL_HT_TH1 << endl;
      cout << "FMS_LARGE_HT_TH0\t" << FMS_LARGE_HT_TH0 << endl;
      cout << "FMS_LARGE_HT_TH1\t" << FMS_LARGE_HT_TH1 << endl;
      cout << "FMS_SMALL_CLUSTER_TH0\t" << FMS_SMALL_CLUSTER_TH0 << endl;
      cout << "FMS_SMALL_CLUSTER_TH1\t" << FMS_SMALL_CLUSTER_TH1 << endl;
      cout << "FMS_SMALL_CLUSTER_TH2\t" << FMS_SMALL_CLUSTER_TH2 << endl;
      cout << "FMS_LARGE_CLUSTER_TH0\t" << FMS_LARGE_CLUSTER_TH0 << endl;
      cout << "FMS_LARGE_CLUSTER_TH1\t" << FMS_LARGE_CLUSTER_TH1 << endl;
      cout << "FMS_LARGE_CLUSTER_TH2\t" << FMS_LARGE_CLUSTER_TH2 << endl;
      cout << "FMS_JP0\t" << FMS_JP0 << endl;
      cout << "FMS_JP1\t" << FMS_JP1 << endl;
      cout << "FMS_JP2\t" << FMS_JP2 << endl;

      fm001.registers[0] = FMS_SMALL_HT_TH0;
      fm002.registers[0] = FMS_SMALL_HT_TH0;
      fm003.registers[0] = FMS_SMALL_HT_TH0;
      fm004.registers[0] = FMS_SMALL_HT_TH0;
      fm005.registers[0] = FMS_LARGE_HT_TH0;
      fm006.registers[0] = FMS_LARGE_HT_TH0;
      fm007.registers[0] = FMS_LARGE_HT_TH0;
      fm008.registers[0] = FMS_LARGE_HT_TH0;
      fm009.registers[0] = FMS_LARGE_HT_TH0;
      fm010.registers[0] = FMS_LARGE_HT_TH0;
      fm011.registers[0] = FMS_LARGE_HT_TH0;
      fm012.registers[0] = FMS_LARGE_HT_TH0;

      fm001.registers[1] = FMS_SMALL_HT_TH1;
      fm002.registers[1] = FMS_SMALL_HT_TH1;
      fm003.registers[1] = FMS_SMALL_HT_TH1;
      fm004.registers[1] = FMS_SMALL_HT_TH1;
      fm005.registers[1] = FMS_LARGE_HT_TH1;
      fm006.registers[1] = FMS_LARGE_HT_TH1;
      fm007.registers[1] = FMS_LARGE_HT_TH1;
      fm008.registers[1] = FMS_LARGE_HT_TH1;
      fm009.registers[1] = FMS_LARGE_HT_TH1;
      fm010.registers[1] = FMS_LARGE_HT_TH1;
      fm011.registers[1] = FMS_LARGE_HT_TH1;
      fm012.registers[1] = FMS_LARGE_HT_TH1;

      fm101.registers[0] = FMS_SMALL_CLUSTER_TH0;
      fm101.registers[1] = FMS_SMALL_CLUSTER_TH1;
      fm101.registers[2] = FMS_SMALL_CLUSTER_TH2;

      fm102.registers[0] = FMS_LARGE_CLUSTER_TH0;
      fm102.registers[1] = FMS_LARGE_CLUSTER_TH1;
      fm102.registers[2] = FMS_LARGE_CLUSTER_TH2;

      fm103.registers[0] = FMS_LARGE_CLUSTER_TH0;
      fm103.registers[1] = FMS_LARGE_CLUSTER_TH1;
      fm103.registers[2] = FMS_LARGE_CLUSTER_TH2;

      fp201.registers[0] = FMS_JP0;
      fp201.registers[1] = FMS_JP1;
      fp201.registers[2] = FMS_JP2;

      //const int FPE_THRESHOLD_12LSB = 500;
      //const int FPE_THRESHOLD_6MSB  = 0;

      //cout << "FPE_THRESHOLD_12LSB\t" << FPE_THRESHOLD_12LSB << endl;
      //cout << "FPE_THRESHOLD_6MSB\t"  << FPE_THRESHOLD_6MSB  << endl;

      //fe101.registers[0] = FPE_THRESHOLD_12LSB;
      //fe101.registers[1] = FPE_THRESHOLD_6MSB;
    }
  }
}
void DSMSimulator_2016::loadSlewCorrections()
{
  void output_slew(int slew[][8]);

  const char dir[] = {"/net/trgscratch.starp.bnl.gov/data/plots/slew_corr"};
  int addr;
  int bin;
  int nbin;
  int flag;
  //for each channel 8 bins
  int tmp[8];
  //bbq
  char file_bbq[128];
  sprintf(file_bbq, "%s/bbq_slew_corr.%d.txt", dir, runNumber);
  ifstream in_bbq(file_bbq);
  
  if(!in_bbq){
    cout<<file_bbq<<" can not be opened!"<<endl;
  }else{
    while(in_bbq >> hex >> addr >> dec >> bin >> nbin >> flag){
      for(int ii = 0; ii < nbin; ii++){
        in_bbq >> tmp[ii];
      }
      int index = bin;
      if(flag == 0) index = bin - 4;
      if(addr == 0x10){
	for(int ii = 0; ii < nbin; ii++){
          bb001_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x12){
	for(int ii = 0; ii < nbin; ii++){
          bb002_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x16){
	for(int ii = 0; ii < nbin; ii++){
          vp001_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x18){
	for(int ii = 0; ii < nbin; ii++){
          vp002_slew[index][ii] = tmp[ii];
        }
      }
    }
  }
  in_bbq.close();
  //mxq
  char file_mxq[128];
  sprintf(file_mxq, "%s/mxq_slew_corr.%d.txt", dir, runNumber);
  ifstream in_mxq(file_mxq);
  
  if(!in_mxq){
    cout<<file_mxq<<" can not be opened!"<<endl;
  }else{
    while(in_mxq >> hex >> addr >> dec >> bin >> nbin >> flag){
      for(int ii = 0; ii < nbin; ii++){
        in_mxq >> tmp[ii];
      }
      int index = bin;
      if(flag == 0) index = bin - 4;
      if(addr == 0x10){
	for(int ii = 0; ii < nbin; ii++){
          mt001_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x19){
	for(int ii = 0; ii < nbin; ii++){
          mt002_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x1a){
	for(int ii = 0; ii < nbin; ii++){
          mt003_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x1b){
	for(int ii = 0; ii < nbin; ii++){
          mt004_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x1c){
	for(int ii = 0; ii < nbin; ii++){
          mt005_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x1d){
	for(int ii = 0; ii < nbin; ii++){
          mt006_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x1e){
	for(int ii = 0; ii < nbin; ii++){
          mt007_slew[index][ii] = tmp[ii];
        }
      }else if(addr == 0x1f){
	for(int ii = 0; ii < nbin; ii++){
          mt008_slew[index][ii] = tmp[ii];
        }
      }
    }
  }
  in_mxq.close();
  //output
  cout<<"bb001 slew corrections"<<endl;
  output_slew(bb001_slew);
  cout<<"bb002 slew corrections"<<endl;
  output_slew(bb002_slew);
  cout<<"vp001 slew corrections"<<endl;
  output_slew(vp001_slew);
  cout<<"vp001 slew corrections"<<endl;
  output_slew(vp002_slew);
  //mt001
  cout<<"mt001 slew corrections"<<endl;
  output_slew(mt001_slew);
  cout<<"mt002 slew corrections"<<endl;
  output_slew(mt002_slew);
  cout<<"mt003 slew corrections"<<endl;
  output_slew(mt003_slew);
  cout<<"mt004 slew corrections"<<endl;
  output_slew(mt004_slew);
  cout<<"mt005 slew corrections"<<endl;
  output_slew(mt005_slew);
  cout<<"mt006 slew corrections"<<endl;
  output_slew(mt006_slew);
  cout<<"mt007 slew corrections"<<endl;
  output_slew(mt007_slew);
  cout<<"mt008 slew corrections"<<endl;
  output_slew(mt008_slew);
  
}
void output_slew(int slew[][8])
{
  for(int ii = 0; ii < 4; ii++){
    for(int jj = 0; jj < 4; jj++){
      int ichn = 8*ii + jj;
      for(int ibin = 0; ibin < 8; ibin++)
	cout<<slew[ichn][ibin]<<" ";
      cout<<endl;
      for(int ibin = 0; ibin < 8; ibin++)
	cout<<slew[ichn+4][ibin]<<" ";
      cout<<endl;
    }
  }  
}
void DSMSimulator_2016::setBarrelHighTowerTh(int i, int value)
{
  bw001.registers[i] = value;
  bw002.registers[i] = value;
  bw003.registers[i] = value;
  bw004.registers[i] = value;
  bw005.registers[i] = value;
  bw006.registers[i] = value;
  bw007.registers[i] = value;
  bw008.registers[i] = value;
  bw009.registers[i] = value;
  bw010.registers[i] = value;
  bw011.registers[i] = value;
  bw012.registers[i] = value;
  bw013.registers[i] = value;
  bw014.registers[i] = value;
  bw015.registers[i] = value;

  be001.registers[i] = value;
  be002.registers[i] = value;
  be003.registers[i] = value;
  be004.registers[i] = value;
  be005.registers[i] = value;
  be006.registers[i] = value;
  be007.registers[i] = value;
  be008.registers[i] = value;
  be009.registers[i] = value;
  be010.registers[i] = value;
  be011.registers[i] = value;
  be012.registers[i] = value;
  be013.registers[i] = value;
  be014.registers[i] = value;
  be015.registers[i] = value;
}

void DSMSimulator_2016::setEndcapHighTowerTh(int i, int value)
{
  ee001.registers[i] = value;
  ee002.registers[i] = value;
  ee003.registers[i] = value;
  ee004.registers[i] = value;
  ee005.registers[i] = value;
  ee006.registers[i] = value;
  ee007.registers[i] = value;
  ee008.registers[i] = value;
  ee009.registers[i] = value;
}

void DSMSimulator_2016::setBarrelJetPatchTh(int i, int value)
{
  bc101.registers[i] = value;
  bc102.registers[i] = value;
  bc103.registers[i] = value;
  bc104.registers[i] = value;
  bc105.registers[i] = value;
  bc106.registers[i] = value;
}

void DSMSimulator_2016::setEndcapJetPatchTh(int i, int value)
{
  ee101.registers[i] = value;
  ee102.registers[i] = value;
}

void DSMSimulator_2016::setOverlapJetPatchTh(int i, int value)
{
  em201.registers[i] = value;
}

void DSMSimulator_2016::readCrates(const TriggerDataBlk& event)
{
  for (int crateid = 1; crateid <= NCRATES; ++crateid) crateAt(crateid).read(event,crateid);
}

void DSMSimulator_2016::readCrates(const TriggerDataBlk& event, int prepost)
{
//  for (int crateid = 1; crateid <= NCRATES; ++crateid) crateAt(crateid,prepost).read(event,crateid,prepost);
}

void DSMSimulator_2016::bookBB001Histograms()
{
  mBB001ADC = new TH2F("BB001ADC","BBQ-BB001 (BBC east small tiles ADC);QT Input Channel;ADC",16,0,16,4096,0,4096);
  mBB001TAC = new TH2F("BB001TAC","BBQ-BB001 (BBC east small tiles TAC);QT Input Channel;TAC",16,0,16,4096,0,4096);

  mBB002ADC = new TH2F("BB002ADC","BBQ-BB002 (BBC west small tiles ADC);QT Input Channel;ADC",16,0,16,4096,0,4096);
  mBB002TAC = new TH2F("BB002TAC","BBQ-BB002 (BBC west small tiles TAC);QT Input Channel;TAC",16,0,16,4096,0,4096);

  mBB003ADC = new TH2F("BB003ADC","BBQ-BB003 (BBC E+W large tiles ADC);QT Input Channel;ADC",16,0,16,4096,0,4096);
  mBB003TAC = new TH2F("BB003TAC","BBQ-BB003 (BBC E+W large tiles TAC);QT Input Channel;TAC",16,0,16,4096,0,4096);

  mBB001ADC->GetXaxis()->SetBinLabel(1,"E1");
  mBB001ADC->GetXaxis()->SetBinLabel(2,"E7");
  mBB001ADC->GetXaxis()->SetBinLabel(3,"E2");
  mBB001ADC->GetXaxis()->SetBinLabel(4,"E8");
  mBB001ADC->GetXaxis()->SetBinLabel(5,"E3");
  mBB001ADC->GetXaxis()->SetBinLabel(6,"E9");
  mBB001ADC->GetXaxis()->SetBinLabel(7,"E10");
  mBB001ADC->GetXaxis()->SetBinLabel(8,"E11");
  mBB001ADC->GetXaxis()->SetBinLabel(9,"E4");
  mBB001ADC->GetXaxis()->SetBinLabel(10,"E12");
  mBB001ADC->GetXaxis()->SetBinLabel(11,"E13");
  mBB001ADC->GetXaxis()->SetBinLabel(12,"E5");
  mBB001ADC->GetXaxis()->SetBinLabel(13,"E6");
  mBB001ADC->GetXaxis()->SetBinLabel(14,"E14");
  mBB001ADC->GetXaxis()->SetBinLabel(15,"E15");
  mBB001ADC->GetXaxis()->SetBinLabel(16,"E16");

  mBB001TAC->GetXaxis()->SetBinLabel(1,"E1");
  mBB001TAC->GetXaxis()->SetBinLabel(2,"E7");
  mBB001TAC->GetXaxis()->SetBinLabel(3,"E2");
  mBB001TAC->GetXaxis()->SetBinLabel(4,"E8");
  mBB001TAC->GetXaxis()->SetBinLabel(5,"E3");
  mBB001TAC->GetXaxis()->SetBinLabel(6,"E9");
  mBB001TAC->GetXaxis()->SetBinLabel(7,"E10");
  mBB001TAC->GetXaxis()->SetBinLabel(8,"E11");
  mBB001TAC->GetXaxis()->SetBinLabel(9,"E4");
  mBB001TAC->GetXaxis()->SetBinLabel(10,"E12");
  mBB001TAC->GetXaxis()->SetBinLabel(11,"E13");
  mBB001TAC->GetXaxis()->SetBinLabel(12,"E5");
  mBB001TAC->GetXaxis()->SetBinLabel(13,"E6");
  mBB001TAC->GetXaxis()->SetBinLabel(14,"E14");
  mBB001TAC->GetXaxis()->SetBinLabel(15,"E15");
  mBB001TAC->GetXaxis()->SetBinLabel(16,"E16");

  mBB002ADC->GetXaxis()->SetBinLabel(1,"W1");
  mBB002ADC->GetXaxis()->SetBinLabel(2,"W7");
  mBB002ADC->GetXaxis()->SetBinLabel(3,"W2");
  mBB002ADC->GetXaxis()->SetBinLabel(4,"W8");
  mBB002ADC->GetXaxis()->SetBinLabel(5,"W3");
  mBB002ADC->GetXaxis()->SetBinLabel(6,"W9");
  mBB002ADC->GetXaxis()->SetBinLabel(7,"W10");
  mBB002ADC->GetXaxis()->SetBinLabel(8,"W11");
  mBB002ADC->GetXaxis()->SetBinLabel(9,"W4");
  mBB002ADC->GetXaxis()->SetBinLabel(10,"W12");
  mBB002ADC->GetXaxis()->SetBinLabel(11,"W13");
  mBB002ADC->GetXaxis()->SetBinLabel(12,"W5");
  mBB002ADC->GetXaxis()->SetBinLabel(13,"W6");
  mBB002ADC->GetXaxis()->SetBinLabel(14,"W14");
  mBB002ADC->GetXaxis()->SetBinLabel(15,"W15");
  mBB002ADC->GetXaxis()->SetBinLabel(16,"W16");

  mBB002TAC->GetXaxis()->SetBinLabel(1,"W1");
  mBB002TAC->GetXaxis()->SetBinLabel(2,"W7");
  mBB002TAC->GetXaxis()->SetBinLabel(3,"W2");
  mBB002TAC->GetXaxis()->SetBinLabel(4,"W8");
  mBB002TAC->GetXaxis()->SetBinLabel(5,"W3");
  mBB002TAC->GetXaxis()->SetBinLabel(6,"W9");
  mBB002TAC->GetXaxis()->SetBinLabel(7,"W10");
  mBB002TAC->GetXaxis()->SetBinLabel(8,"W11");
  mBB002TAC->GetXaxis()->SetBinLabel(9,"W4");
  mBB002TAC->GetXaxis()->SetBinLabel(10,"W12");
  mBB002TAC->GetXaxis()->SetBinLabel(11,"W13");
  mBB002TAC->GetXaxis()->SetBinLabel(12,"W5");
  mBB002TAC->GetXaxis()->SetBinLabel(13,"W6");
  mBB002TAC->GetXaxis()->SetBinLabel(14,"W14");
  mBB002TAC->GetXaxis()->SetBinLabel(15,"W15");
  mBB002TAC->GetXaxis()->SetBinLabel(16,"W16");

  mBB003ADC->GetXaxis()->SetBinLabel(1,"E17");
  mBB003ADC->GetXaxis()->SetBinLabel(2,"E18");
  mBB003ADC->GetXaxis()->SetBinLabel(3,"E19");
  mBB003ADC->GetXaxis()->SetBinLabel(4,"E20");
  mBB003ADC->GetXaxis()->SetBinLabel(5,"E21");
  mBB003ADC->GetXaxis()->SetBinLabel(6,"E22");
  mBB003ADC->GetXaxis()->SetBinLabel(7,"E23");
  mBB003ADC->GetXaxis()->SetBinLabel(8,"E24");
  mBB003ADC->GetXaxis()->SetBinLabel(9,"W17");
  mBB003ADC->GetXaxis()->SetBinLabel(10,"W18");
  mBB003ADC->GetXaxis()->SetBinLabel(11,"W19");
  mBB003ADC->GetXaxis()->SetBinLabel(12,"W20");
  mBB003ADC->GetXaxis()->SetBinLabel(13,"W21");
  mBB003ADC->GetXaxis()->SetBinLabel(14,"W22");
  mBB003ADC->GetXaxis()->SetBinLabel(15,"W23");
  mBB003ADC->GetXaxis()->SetBinLabel(16,"W24");

  mBB003TAC->GetXaxis()->SetBinLabel(1,"E17");
  mBB003TAC->GetXaxis()->SetBinLabel(2,"E18");
  mBB003TAC->GetXaxis()->SetBinLabel(3,"E19");
  mBB003TAC->GetXaxis()->SetBinLabel(4,"E20");
  mBB003TAC->GetXaxis()->SetBinLabel(5,"E21");
  mBB003TAC->GetXaxis()->SetBinLabel(6,"E22");
  mBB003TAC->GetXaxis()->SetBinLabel(7,"E23");
  mBB003TAC->GetXaxis()->SetBinLabel(8,"E24");
  mBB003TAC->GetXaxis()->SetBinLabel(9,"W17");
  mBB003TAC->GetXaxis()->SetBinLabel(10,"W18");
  mBB003TAC->GetXaxis()->SetBinLabel(11,"W19");
  mBB003TAC->GetXaxis()->SetBinLabel(12,"W20");
  mBB003TAC->GetXaxis()->SetBinLabel(13,"W21");
  mBB003TAC->GetXaxis()->SetBinLabel(14,"W22");
  mBB003TAC->GetXaxis()->SetBinLabel(15,"W23");
  mBB003TAC->GetXaxis()->SetBinLabel(16,"W24");
}
void DSMSimulator_2016::bookBB101Histograms()
{
  float adcmax = 65536;

  mBbcSmallEastAdcSum = new TH1F("bbcSmallEastAdcSum","bbcSmallEastAdcSum",4096,0,adcmax);
  mBbcSmallEastTacMax = new TH1F("bbcSmallEastTacMax","bbcSmallEastTacMax",4096,0,4096);
  mBbcSmallEastAdcSumVsSimu = new TH2F("bbcSmallEastAdcSumVsSimu","bbcSmallEastAdcSumVsSimu;Simu;Data",256,0,adcmax,256,0,adcmax);
  mBbcSmallEastTacMaxVsSimu = new TH2F("bbcSmallEastTacMaxVsSimu","bbcSmallEastTacMaxVsSimu;Simu;Data",256,0,4096,256,0,4096);

  mBbcSmallWestAdcSum = new TH1F("bbcSmallWestAdcSum","bbcSmallWestAdcSum",4096,0,adcmax);
  mBbcSmallWestTacMax = new TH1F("bbcSmallWestTacMax","bbcSmallWestTacMax",4096,0,4096);
  mBbcSmallWestAdcSumVsSimu = new TH2F("bbcSmallWestAdcSumVsSimu","bbcSmallWestAdcSumVsSimu;Simu;Data",256,0,adcmax,256,0,adcmax);
  mBbcSmallWestTacMaxVsSimu = new TH2F("bbcSmallWestTacMaxVsSimu","bbcSmallWestTacMaxVsSimu;Simu;Data",256,0,4096,256,0,4096);
}
void DSMSimulator_2016::bookBB102Histograms()
{
  mBbcLargeEastTacMax = new TH1F("bbcLargeEastTacMax","bbcLargeEastTacMax",4096,0,4096);
  mBbcLargeWestTacMax = new TH1F("bbcLargeWestTacMax","bbcLargeWestTacMax",4096,0,4096);
  mBbcLargeHit = new TH2F("bbcLargeHit","bbcLargeHit", 2, 0, 2, 2,0,2);
  labelBB102Histogram(mBbcLargeHit);

  mBbcLargeEastTacMaxVsSimu = new TH2F("bbcLargeEastTacMaxVsSimu","bbcLargeEastTacMaxVsSimu;Simu;Data",256,0,4096,256,0,4096);
  mBbcLargeWestTacMaxVsSimu = new TH2F("bbcLargeWestTacMaxVsSimu","bbcLargeWestTacMaxVsSimu;Simu;Data",256,0,4096,256,0,4096);

  mBbcLargeHitSimu = new TH2F("bbcLargeEastHitSimu","bbcLargeEastHitSimu",2, 0, 2, 3,-1,2);
  labelBB102Histogram(mBbcLargeHitSimu);
}
void DSMSimulator_2016::labelBB102Histogram(TH2F *h)
{
  h->GetXaxis()->SetBinLabel(1, "E-Hit");
  h->GetXaxis()->SetBinLabel(2, "W-Hit");
  labelHistogramYaxis(h);
}
void DSMSimulator_2016::bookVP001Histograms()
{
  mVP001ADC = new TH2F("VP001ADC","BBQ-VP001 (LO threshold);QT Input Channel;ADC",16,0,16,4096,0,4096);
  mVP001TAC = new TH2F("VP001TAC","BBQ-VP001 (LO threshold);QT Input Channel;TAC",16,0,16,4096,0,4096);

  mVP002ADC = new TH2F("VP002ADC","BBQ-VP002 (LO threshold);QT Input Channel;ADC",16,0,16,4096,0,4096);
  mVP002TAC = new TH2F("VP002TAC","BBQ-VP002 (LO threshold);QT Input Channel;TAC",16,0,16,4096,0,4096);

  mVP003ADC = new TH2F("VP003ADC","BBQ-VP003 (HI threshold);QT Input Channel;ADC",16,0,16,4096,0,4096);
  mVP003TAC = new TH2F("VP003TAC","BBQ-VP003 (HI threshold);QT Input Channel;TAC",16,0,16,4096,0,4096);

  mVP004ADC = new TH2F("VP004ADC","BBQ-VP004 (HI threshold);QT Input Channel;ADC",16,0,16,4096,0,4096);
  mVP004TAC = new TH2F("VP004TAC","BBQ-VP004 (HI threshold);QT Input Channel;TAC",16,0,16,4096,0,4096);
  //adc
  labelVP001Histogram(mVP001ADC, 0);
  labelVP001Histogram(mVP002ADC, 0);
  labelVP001Histogram(mVP003ADC, 0);
  labelVP001Histogram(mVP004ADC, 0);
  //tac
  labelVP001Histogram(mVP001TAC, 4);
  labelVP001Histogram(mVP002TAC, 4);
  labelVP001Histogram(mVP003TAC, 4);
  labelVP001Histogram(mVP004TAC, 4);
  /*
  mVP001ADC->GetXaxis()->SetBinLabel(1,"VPDE1");
  mVP001ADC->GetXaxis()->SetBinLabel(2,"VPDE2");
  mVP001ADC->GetXaxis()->SetBinLabel(3,"VPDE3");
  mVP001ADC->GetXaxis()->SetBinLabel(4,"VPDE4");
  mVP001ADC->GetXaxis()->SetBinLabel(5,"VPDE7");
  mVP001ADC->GetXaxis()->SetBinLabel(6,"VPDE8");
  mVP001ADC->GetXaxis()->SetBinLabel(7,"VPDE14");
  mVP001ADC->GetXaxis()->SetBinLabel(8,"VPDE15");
  mVP001ADC->GetXaxis()->SetBinLabel(9,"VPDE6");
  mVP001ADC->GetXaxis()->SetBinLabel(10,"VPDE12");
  mVP001ADC->GetXaxis()->SetBinLabel(11,"VPDE13");
  mVP001ADC->GetXaxis()->SetBinLabel(12,"VPDE5");
  mVP001ADC->GetXaxis()->SetBinLabel(13,"VPDE16");
  mVP001ADC->GetXaxis()->SetBinLabel(14,"VPDE9");
  mVP001ADC->GetXaxis()->SetBinLabel(15,"VPDE10");
  mVP001ADC->GetXaxis()->SetBinLabel(16,"VPDE11");

  mVP001TAC->GetXaxis()->SetBinLabel(1,"VPDE1");
  mVP001TAC->GetXaxis()->SetBinLabel(2,"VPDE2");
  mVP001TAC->GetXaxis()->SetBinLabel(3,"VPDE3");
  mVP001TAC->GetXaxis()->SetBinLabel(4,"VPDE4");
  mVP001TAC->GetXaxis()->SetBinLabel(5,"VPDE7");
  mVP001TAC->GetXaxis()->SetBinLabel(6,"VPDE8");
  mVP001TAC->GetXaxis()->SetBinLabel(7,"VPDE14");
  mVP001TAC->GetXaxis()->SetBinLabel(8,"VPDE15");
  mVP001TAC->GetXaxis()->SetBinLabel(9,"VPDE6");
  mVP001TAC->GetXaxis()->SetBinLabel(10,"VPDE12");
  mVP001TAC->GetXaxis()->SetBinLabel(11,"VPDE13");
  mVP001TAC->GetXaxis()->SetBinLabel(12,"VPDE5");
  mVP001TAC->GetXaxis()->SetBinLabel(13,"VPDE16");
  mVP001TAC->GetXaxis()->SetBinLabel(14,"VPDE9");
  mVP001TAC->GetXaxis()->SetBinLabel(15,"VPDE10");
  mVP001TAC->GetXaxis()->SetBinLabel(16,"VPDE11");

  mVP002ADC->GetXaxis()->SetBinLabel(1,"VPDW1");
  mVP002ADC->GetXaxis()->SetBinLabel(2,"VPDW2");
  mVP002ADC->GetXaxis()->SetBinLabel(3,"VPDW3");
  mVP002ADC->GetXaxis()->SetBinLabel(4,"VPDW4");
  mVP002ADC->GetXaxis()->SetBinLabel(5,"VPDW7");
  mVP002ADC->GetXaxis()->SetBinLabel(6,"VPDW8");
  mVP002ADC->GetXaxis()->SetBinLabel(7,"VPDW14");
  mVP002ADC->GetXaxis()->SetBinLabel(8,"VPDW15");
  mVP002ADC->GetXaxis()->SetBinLabel(9,"VPDW6");
  mVP002ADC->GetXaxis()->SetBinLabel(10,"VPDW12");
  mVP002ADC->GetXaxis()->SetBinLabel(11,"VPDW13");
  mVP002ADC->GetXaxis()->SetBinLabel(12,"VPDW5");
  mVP002ADC->GetXaxis()->SetBinLabel(13,"VPDW16");
  mVP002ADC->GetXaxis()->SetBinLabel(14,"VPDW9");
  mVP002ADC->GetXaxis()->SetBinLabel(15,"VPDW10");
  mVP002ADC->GetXaxis()->SetBinLabel(16,"VPDW11");

  mVP002TAC->GetXaxis()->SetBinLabel(1,"VPDW1");
  mVP002TAC->GetXaxis()->SetBinLabel(2,"VPDW2");
  mVP002TAC->GetXaxis()->SetBinLabel(3,"VPDW3");
  mVP002TAC->GetXaxis()->SetBinLabel(4,"VPDW4");
  mVP002TAC->GetXaxis()->SetBinLabel(5,"VPDW7");
  mVP002TAC->GetXaxis()->SetBinLabel(6,"VPDW8");
  mVP002TAC->GetXaxis()->SetBinLabel(7,"VPDW14");
  mVP002TAC->GetXaxis()->SetBinLabel(8,"VPDW15");
  mVP002TAC->GetXaxis()->SetBinLabel(9,"VPDW6");
  mVP002TAC->GetXaxis()->SetBinLabel(10,"VPDW12");
  mVP002TAC->GetXaxis()->SetBinLabel(11,"VPDW13");
  mVP002TAC->GetXaxis()->SetBinLabel(12,"VPDW5");
  mVP002TAC->GetXaxis()->SetBinLabel(13,"VPDW16");
  mVP002TAC->GetXaxis()->SetBinLabel(14,"VPDW9");
  mVP002TAC->GetXaxis()->SetBinLabel(15,"VPDW10");
  mVP002TAC->GetXaxis()->SetBinLabel(16,"VPDW11");

  mVP003ADC->GetXaxis()->SetBinLabel(1,"VPDE1");
  mVP003ADC->GetXaxis()->SetBinLabel(2,"VPDE2");
  mVP003ADC->GetXaxis()->SetBinLabel(3,"VPDE3");
  mVP003ADC->GetXaxis()->SetBinLabel(4,"VPDE4");
  mVP003ADC->GetXaxis()->SetBinLabel(5,"VPDE7");
  mVP003ADC->GetXaxis()->SetBinLabel(6,"VPDE8");
  mVP003ADC->GetXaxis()->SetBinLabel(7,"VPDE14");
  mVP003ADC->GetXaxis()->SetBinLabel(8,"VPDE15");
  mVP003ADC->GetXaxis()->SetBinLabel(9,"VPDE6");
  mVP003ADC->GetXaxis()->SetBinLabel(10,"VPDE12");
  mVP003ADC->GetXaxis()->SetBinLabel(11,"VPDE13");
  mVP003ADC->GetXaxis()->SetBinLabel(12,"VPDE5");
  mVP003ADC->GetXaxis()->SetBinLabel(13,"VPDE16");
  mVP003ADC->GetXaxis()->SetBinLabel(14,"VPDE9");
  mVP003ADC->GetXaxis()->SetBinLabel(15,"VPDE10");
  mVP003ADC->GetXaxis()->SetBinLabel(16,"VPDE11");

  mVP003TAC->GetXaxis()->SetBinLabel(1,"VPDE1");
  mVP003TAC->GetXaxis()->SetBinLabel(2,"VPDE2");
  mVP003TAC->GetXaxis()->SetBinLabel(3,"VPDE3");
  mVP003TAC->GetXaxis()->SetBinLabel(4,"VPDE4");
  mVP003TAC->GetXaxis()->SetBinLabel(5,"VPDE7");
  mVP003TAC->GetXaxis()->SetBinLabel(6,"VPDE8");
  mVP003TAC->GetXaxis()->SetBinLabel(7,"VPDE14");
  mVP003TAC->GetXaxis()->SetBinLabel(8,"VPDE15");
  mVP003TAC->GetXaxis()->SetBinLabel(9,"VPDE6");
  mVP003TAC->GetXaxis()->SetBinLabel(10,"VPDE12");
  mVP003TAC->GetXaxis()->SetBinLabel(11,"VPDE13");
  mVP003TAC->GetXaxis()->SetBinLabel(12,"VPDE5");
  mVP003TAC->GetXaxis()->SetBinLabel(13,"VPDE16");
  mVP003TAC->GetXaxis()->SetBinLabel(14,"VPDE9");
  mVP003TAC->GetXaxis()->SetBinLabel(15,"VPDE10");
  mVP003TAC->GetXaxis()->SetBinLabel(16,"VPDE11");

  mVP004ADC->GetXaxis()->SetBinLabel(1,"VPDW1");
  mVP004ADC->GetXaxis()->SetBinLabel(2,"VPDW2");
  mVP004ADC->GetXaxis()->SetBinLabel(3,"VPDW3");
  mVP004ADC->GetXaxis()->SetBinLabel(4,"VPDW4");
  mVP004ADC->GetXaxis()->SetBinLabel(5,"VPDW7");
  mVP004ADC->GetXaxis()->SetBinLabel(6,"VPDW8");
  mVP004ADC->GetXaxis()->SetBinLabel(7,"VPDW14");
  mVP004ADC->GetXaxis()->SetBinLabel(8,"VPDW15");
  mVP004ADC->GetXaxis()->SetBinLabel(9,"VPDW6");
  mVP004ADC->GetXaxis()->SetBinLabel(10,"VPDW12");
  mVP004ADC->GetXaxis()->SetBinLabel(11,"VPDW13");
  mVP004ADC->GetXaxis()->SetBinLabel(12,"VPDW5");
  mVP004ADC->GetXaxis()->SetBinLabel(13,"VPDW16");
  mVP004ADC->GetXaxis()->SetBinLabel(14,"VPDW9");
  mVP004ADC->GetXaxis()->SetBinLabel(15,"VPDW10");
  mVP004ADC->GetXaxis()->SetBinLabel(16,"VPDW11");

  mVP004TAC->GetXaxis()->SetBinLabel(1,"VPDW1");
  mVP004TAC->GetXaxis()->SetBinLabel(2,"VPDW2");
  mVP004TAC->GetXaxis()->SetBinLabel(3,"VPDW3");
  mVP004TAC->GetXaxis()->SetBinLabel(4,"VPDW4");
  mVP004TAC->GetXaxis()->SetBinLabel(5,"VPDW7");
  mVP004TAC->GetXaxis()->SetBinLabel(6,"VPDW8");
  mVP004TAC->GetXaxis()->SetBinLabel(7,"VPDW14");
  mVP004TAC->GetXaxis()->SetBinLabel(8,"VPDW15");
  mVP004TAC->GetXaxis()->SetBinLabel(9,"VPDW6");
  mVP004TAC->GetXaxis()->SetBinLabel(10,"VPDW12");
  mVP004TAC->GetXaxis()->SetBinLabel(11,"VPDW13");
  mVP004TAC->GetXaxis()->SetBinLabel(12,"VPDW5");
  mVP004TAC->GetXaxis()->SetBinLabel(13,"VPDW16");
  mVP004TAC->GetXaxis()->SetBinLabel(14,"VPDW9");
  mVP004TAC->GetXaxis()->SetBinLabel(15,"VPDW10");
  mVP004TAC->GetXaxis()->SetBinLabel(16,"VPDW11");
  */
}
void DSMSimulator_2016::labelVP001Histogram(TH2F *h, int shift)
{
  char card[] = {'A', 'B', 'C', 'D'};
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      h->GetXaxis()->SetBinLabel(i*4+j+1, Form("%c-ch%d", card[i], j+shift));
    }
  }
}
void DSMSimulator_2016::bookVP101Histograms(){
  int adcmax = 4096;
  int tacmax = 65536;
  mVpdEastAdcSum = new TH1F("vpdEastAdcSum","vpdEastAdcSum",4096,0,adcmax);
  mVpdEastTacSum = new TH1F("vpdEastTacSum","vpdEastTacSum",4096,0,tacmax);
  mVpdEastNHits = new TH1F("vpdEastNHits","vpdEastNHits", 16, 0, 16);
  mVpdEastAdcSumVsSimu = new TH2F("vpdEastAdcSumVsSimu","vpdEastAdcSumVsSimu;Simu;Data",256,0,adcmax,256,0,adcmax);
  mVpdEastTacSumVsSimu = new TH2F("vpdEastTacSumVsSimu","vpdEastTacSumVsSimu;Simu;Data",256,0,tacmax,256,0,tacmax);
  mVpdEastNHitsVsSimu = new TH2F("vpdEastNHitsVsSimu","vpdEastNHitsVsSimu", 16, 0, 16, 16, 0, 16);

  mVpdWestAdcSum = new TH1F("vpdWestAdcSum","vpdWestAdcSum",4096,0,adcmax);
  mVpdWestTacSum = new TH1F("vpdWestTacSum","vpdWestTacSum",4096,0,tacmax);
  mVpdWestNHits = new TH1F("vpdWestNHits","vpdWestNHits", 16, 0, 16);
  mVpdWestAdcSumVsSimu = new TH2F("vpdWestAdcSumVsSimu","vpdWestAdcSumVsSimu;Simu;Data",256,0,adcmax,256,0,adcmax);
  mVpdWestTacSumVsSimu = new TH2F("vpdWestTacSumVsSimu","vpdWestTacSumVsSimu;Simu;Data",256,0,tacmax,256,0,tacmax);
  mVpdWestNHitsVsSimu = new TH2F("vpdWestNHitsVsSimu","vpdWestNHitsVsSimu", 16, 0, 16, 16, 0, 16);

  //  mVpdMtdEastMaxTac = new TH1F("vpdMtdEastMaxTac","vpdMtdEastMaxTac",4096,0,4096);
  //  mVpdMtdWestMaxTac = new TH1F("vpdMtdWestMaxTac","vpdMtdWestMaxTac",4096,0,4096);

  //  mVpdMtdEastMaxTacVsSimu = new TH2F("vpdMtdEastMaxTacVsSimu","vpdMtdEastMaxTacVsSimu;Simu;Data",256,0,4096,256,0,4096);
  //  mVpdMtdWestMaxTacVsSimu = new TH2F("vpdMtdWestMaxTacVsSimu","vpdMtdWestMaxTacVsSimu;Simu;Data",256,0,4096,256,0,4096);
}

void DSMSimulator_2016::bookZD001Histograms()
{
  mZD001ADC = new TH2F("ZD001ADC","BBQ-ZD001 (ZDC TOWER);;ADC",16,0,16,4096,0,4096);
  mZD001TAC = new TH2F("ZD001TAC","BBQ-ZD001 (ZDC TOWER);;TAC",16,0,16,4096,0,4096);

  mZD001ADC->GetXaxis()->SetBinLabel(1,"E1");
  mZD001ADC->GetXaxis()->SetBinLabel(2,"E1A");
  mZD001ADC->GetXaxis()->SetBinLabel(3,"Esum");
  mZD001ADC->GetXaxis()->SetBinLabel(4,"EsumA");
  mZD001ADC->GetXaxis()->SetBinLabel(5,"E2");
  mZD001ADC->GetXaxis()->SetBinLabel(6,"E3");
  mZD001ADC->GetXaxis()->SetBinLabel(7,"E2A");
  mZD001ADC->GetXaxis()->SetBinLabel(8,"E+W A");
  mZD001ADC->GetXaxis()->SetBinLabel(9,"W1");
  mZD001ADC->GetXaxis()->SetBinLabel(10,"W1A");
  mZD001ADC->GetXaxis()->SetBinLabel(11,"Wsum");
  mZD001ADC->GetXaxis()->SetBinLabel(12,"WsumA");
  mZD001ADC->GetXaxis()->SetBinLabel(13,"W2");
  mZD001ADC->GetXaxis()->SetBinLabel(14,"W3");
  mZD001ADC->GetXaxis()->SetBinLabel(15,"W2A");

  mZD001TAC->GetXaxis()->SetBinLabel(1,"E1TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(2,"E1ATAC");
  mZD001TAC->GetXaxis()->SetBinLabel(3,"EsumTAC");
  mZD001TAC->GetXaxis()->SetBinLabel(4,"EsumATAC");
  mZD001TAC->GetXaxis()->SetBinLabel(5,"E2TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(6,"E3TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(7,"E2ATAC");
  mZD001TAC->GetXaxis()->SetBinLabel(8,"E+W A TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(9,"W1TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(10,"W1ATAC");
  mZD001TAC->GetXaxis()->SetBinLabel(11,"WsumTAC");
  mZD001TAC->GetXaxis()->SetBinLabel(12,"WsumA TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(13,"W2TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(14,"W3TAC");
  mZD001TAC->GetXaxis()->SetBinLabel(15,"W2ATAC");
}
void DSMSimulator_2016::bookZD101Histograms()
{
  void setZD101Style(TH2F *h);
  mZdcWestTac = new TH1F("zdcWestTac","zdcWestTac",1024,0,1024);
  mZdcEastTac = new TH1F("zdcEastTac","zdcEastTac",1024,0,1024);
  mZdcWestTacVsSimu = new TH2F("zdcWestTacVsSimu","zdcWestTacVsSimu;Simu;Data",256,0,1024,256,0,1024);
  mZdcEastTacVsSimu = new TH2F("zdcEastTacVsSimu","zdcEastTacVsSimu;Simu;Data",256,0,1024,256,0,1024);

  mZdcAdcSum = new TH2F("zdcAdcSum","zdcAdcSum",12,0,12,2,0,2);
  mZdcAdcSumDiff = new TH2F("zdcAdcSumDiff","zdcAdcSumDiff",12,0,12,3,-1,2);

  labelZD101Histogram(mZdcAdcSum);
  labelZD101Histogram(mZdcAdcSumDiff);
}
void DSMSimulator_2016::labelZD101Histogram(TH2F *h)
{
  h->GetXaxis()->SetBinLabel(1,"ZDC-W-th0");
  h->GetXaxis()->SetBinLabel(2,"ZDC-W-th1");
  h->GetXaxis()->SetBinLabel(3,"ZDC-W-th2");
  h->GetXaxis()->SetBinLabel(4,"ZDC-W-th3");
  h->GetXaxis()->SetBinLabel(5,"ZDC-W-att-th4(Unused)");
  h->GetXaxis()->SetBinLabel(6,"ZDC-W-att-th5(Unused)");
  h->GetXaxis()->SetBinLabel(7,"ZDC-E-th0");
  h->GetXaxis()->SetBinLabel(8,"ZDC-E-th1");
  h->GetXaxis()->SetBinLabel(9,"ZDC-E-th2");
  h->GetXaxis()->SetBinLabel(10,"ZDC-E-th3");
  h->GetXaxis()->SetBinLabel(11,"ZDC-E-att-th4(Unused)");
  h->GetXaxis()->SetBinLabel(12,"ZDC-E-att-th5(Unused)");
  labelHistogramYaxis(h);
}
void DSMSimulator_2016::bookVT201Histograms(){

  mBbcSmallTacDiff = new TH1F("mBbcSmallTacDiff", "VT201 Input Ch0: BBC Small Tac Diff; Tac", 4096, 0, 8192);
  mBbcSmallAdcSumTh = new TH2F("mBbcSmallAdcSumTh", "VT201 Input Ch0: BBC Small Adc Sum Th", 3, 0, 3, 2, 0, 2);
  
  mBbcSmallAdcSumTh->GetXaxis()->SetBinLabel(1, "TAC-Sum");
  mBbcSmallAdcSumTh->GetXaxis()->SetBinLabel(2, "East");
  mBbcSmallAdcSumTh->GetXaxis()->SetBinLabel(3, "West");
  mBbcSmallAdcSumTh->GetYaxis()->SetBinLabel(1, "0");
  mBbcSmallAdcSumTh->GetYaxis()->SetBinLabel(2, "1");
  
  mBbcLargeTacDiff = new TH1F("mBbcLargeTacDiff", "VT201 Input Ch1: BBC Large Tac Diff; Tac", 8, 0, 8);
  mBbcLargeAdcSumTh = new TH2F("mBbcLargeAdcSumTh", "VT201 Input Ch1: BBC Large Adc Sum Th", 2, 0, 2, 2, 0, 2);
  mBbcLargeAdcSumTh->GetXaxis()->SetBinLabel(1, "East");
  mBbcLargeAdcSumTh->GetXaxis()->SetBinLabel(2, "West");
  mBbcLargeAdcSumTh->GetYaxis()->SetBinLabel(1, "0");
  mBbcLargeAdcSumTh->GetYaxis()->SetBinLabel(2, "1");

  mZdcTacDiff = new TH1F("mZdcTacDiff", "VT201 Input Ch2: ZDC Tac Diff; Tac", 512, 0, 512);
  mZdcAdcSumTh = new TH2F("mZdcAdcSumTh", "VT201 Input Ch2: ZDC Adc Sum Th", 7, 0, 7, 2, 0, 2);
  labelVT201ZDCHistogram(mZdcAdcSumTh);

  mVpdTacDiff = new TH2F("mVpdTacDiff", "VT201 Input Ch4: VPD Tac Diff; Tac Window", 3, 0, 3, 2, 0, 2);
  mVpdTacDiff->GetXaxis()->SetBinLabel(1, "Mean-TAC Diff W-1");
  mVpdTacDiff->GetXaxis()->SetBinLabel(2, "Mean-TAC Diff W-2");
  mVpdTacDiff->GetXaxis()->SetBinLabel(3, "Mean-TAC Diff W-3");
  labelHistogramYaxis(mVpdTacDiff);
  
  mVpdAdcSumTh = new TH2F("mVpdAdcSumTh", "VT201 Input Ch4: VPD Adc Sum Th", 2, 0, 2, 2, 0, 2);
  mVpdAdcSumTh->GetXaxis()->SetBinLabel(1, "East");
  mVpdAdcSumTh->GetXaxis()->SetBinLabel(2, "West");
  mVpdAdcSumTh->GetYaxis()->SetBinLabel(1, "0");
  mVpdAdcSumTh->GetYaxis()->SetBinLabel(2, "1");

  //Simu
  mBbcSmallTacDiffVsSimu = new TH2F("mBbcSmallTacDiffVsSimu", "VT201 Input Ch0: BBC Small Tac Diff;Real;Simu", 256, 0, 4096,  256, 0, 4096);
  mBbcSmallAdcSumThSimu = new TH2F("mBbcSmallAdcSumThSimu", "VT201 Input Ch0: BBC Small Adc Sum Th (Real-Simu)", 3, 0, 3, 3, -1, 2);
  mBbcSmallAdcSumThSimu->GetXaxis()->SetBinLabel(1, "TAC-sum");
  mBbcSmallAdcSumThSimu->GetXaxis()->SetBinLabel(2, "East");
  mBbcSmallAdcSumThSimu->GetXaxis()->SetBinLabel(3, "West");
  mBbcSmallAdcSumThSimu->GetYaxis()->SetBinLabel(1, "-1");
  mBbcSmallAdcSumThSimu->GetYaxis()->SetBinLabel(2, "0");
  mBbcSmallAdcSumThSimu->GetYaxis()->SetBinLabel(3, "1");

  mBbcLargeTacDiffVsSimu = new TH2F("mBbcLargeTacDiffVsSimu", "VT201 Input Ch1: BBC Large Tac Diff;Real;Simu", 8, 0, 8, 8, 0, 8);
  mBbcLargeAdcSumThSimu = new TH2F("mBbcLargeAdcSumThSimu", "VT201 Input Ch1: BBC Large Adc Sum Th(Real-Simu)", 2, 0, 2, 3, -1, 2);
  mBbcLargeAdcSumThSimu->GetXaxis()->SetBinLabel(1, "East");
  mBbcLargeAdcSumThSimu->GetXaxis()->SetBinLabel(2, "West");


  mZdcTacDiffVsSimu = new TH2F("mZdcTacDiffVsSimu", "VT201 Input Ch2: ZDC Tac Diff;Real;Simu", 256, 0, 1024, 256, 0, 1024);
  mZdcAdcSumThSimu = new TH2F("mZdcAdcSumThSimu", "VT201 Input Ch2: ZDC Adc Sum Th (Real-Simu)", 7, 0, 7, 3, -1, 2);
  labelVT201ZDCHistogram(mZdcAdcSumThSimu);

  //vpd
  mVpdTacDiffVsSimu = new TH2F("mVpdTacDiffVsSimu", "VT201 Input Ch4: VPD Tac Diff; Tac Window;Real-Simu", 3, 0, 3, 3, -1, 2);
  mVpdTacDiffVsSimu->GetXaxis()->SetBinLabel(1, "Mean-TAC Diff W-1");
  mVpdTacDiffVsSimu->GetXaxis()->SetBinLabel(2, "Mean-TAC Diff W-2");
  mVpdTacDiffVsSimu->GetXaxis()->SetBinLabel(3, "Mean-TAC Diff W-3");
  labelHistogramYaxis(mVpdTacDiffVsSimu);

  //  mVpdTacDiffVsSimu = new TH2F("mVpdTacDiffVsSimu", "VT201 Input Ch4: VPD Tac Diff;Real;Simu", 256, 0 , 8191,  256, 0, 8191);
  mVpdAdcSumThSimu = new TH2F("mVpdAdcSumThSimu", "VT201 Input Ch4: VPD Adc Sum Th(Real-Simu)", 2, 0, 2, 3, -1, 2);
  mVpdAdcSumThSimu->GetXaxis()->SetBinLabel(1, "East");
  mVpdAdcSumThSimu->GetXaxis()->SetBinLabel(2, "West");
  labelHistogramYaxis(mVpdAdcSumThSimu);
}
void DSMSimulator_2016::labelVT201ZDCHistogram(TH2F *h)
{
  h->GetXaxis()->SetBinLabel(1, "Pro-sum-W-th0");
  h->GetXaxis()->SetBinLabel(2, "Sum-W-th1");
  h->GetXaxis()->SetBinLabel(3, "Sum-W-th2");
  h->GetXaxis()->SetBinLabel(4, "Pro-Sum-E-th0");
  h->GetXaxis()->SetBinLabel(5, "Sum-E-th1");
  h->GetXaxis()->SetBinLabel(6, "Sum-E-th2");
  h->GetXaxis()->SetBinLabel(7, "Sum-E(or W)-th3");
  labelHistogramYaxis(h);
}
/*
void DSMSimulator_2016::bookZP001Histograms()
{
  mZP001WADC = new TH2F("mZP001WADC","MXQ-ZP001 (ZDC SMD);;ADC",16,0,16,4096,0,4096);
  mZP001WADC->GetXaxis()->SetBinLabel(1,"WH1");
  mZP001WADC->GetXaxis()->SetBinLabel(2,"WH2");
  mZP001WADC->GetXaxis()->SetBinLabel(3,"WH3");
  mZP001WADC->GetXaxis()->SetBinLabel(4,"WH4");
  mZP001WADC->GetXaxis()->SetBinLabel(5,"WH5");
  mZP001WADC->GetXaxis()->SetBinLabel(6,"WH6");
  mZP001WADC->GetXaxis()->SetBinLabel(7,"WH7");
  mZP001WADC->GetXaxis()->SetBinLabel(8,"WH8");
  mZP001WADC->GetXaxis()->SetBinLabel(9,"WV1");
  mZP001WADC->GetXaxis()->SetBinLabel(10,"WV2");
  mZP001WADC->GetXaxis()->SetBinLabel(11,"WV3");
  mZP001WADC->GetXaxis()->SetBinLabel(12,"WV4");
  mZP001WADC->GetXaxis()->SetBinLabel(13,"WV5");
  mZP001WADC->GetXaxis()->SetBinLabel(14,"WV6");
  mZP001WADC->GetXaxis()->SetBinLabel(15,"WV7");
  mZP001WADC->GetXaxis()->SetBinLabel(16,"W-LED");

  mZP001EADC = new TH2F("mZP001EADC","MXQ-ZP001 (ZDC SMD);;ADC",16,0,16,4096,0,4096);
  mZP001EADC->GetXaxis()->SetBinLabel(1,"EH1");
  mZP001EADC->GetXaxis()->SetBinLabel(2,"EH2");
  mZP001EADC->GetXaxis()->SetBinLabel(3,"EH3");
  mZP001EADC->GetXaxis()->SetBinLabel(4,"EH4");
  mZP001EADC->GetXaxis()->SetBinLabel(5,"EH5");
  mZP001EADC->GetXaxis()->SetBinLabel(6,"EH6");
  mZP001EADC->GetXaxis()->SetBinLabel(7,"EH7");
  mZP001EADC->GetXaxis()->SetBinLabel(8,"EH8");
  mZP001EADC->GetXaxis()->SetBinLabel(9,"EV1");
  mZP001EADC->GetXaxis()->SetBinLabel(10,"EV2");
  mZP001EADC->GetXaxis()->SetBinLabel(11,"EV3");
  mZP001EADC->GetXaxis()->SetBinLabel(12,"EV4");
  mZP001EADC->GetXaxis()->SetBinLabel(13,"EV5");
  mZP001EADC->GetXaxis()->SetBinLabel(14,"EV6");
  mZP001EADC->GetXaxis()->SetBinLabel(15,"EV7");
  mZP001EADC->GetXaxis()->SetBinLabel(16,"E-LED");
}
*/
void DSMSimulator_2016::bookMT001Histograms()
{
  for(int ib = 0; ib < 8; ib++){
    mMT001[ib] = new TH2F(Form("mMT00%d", ib+1), Form("MXQ-MT00%d", ib+1), 32,0,32,4096,0,4096);
    char card[4] = {'A', 'B', 'C', 'D'};
    for(int ich = 0; ich < 32; ich++){
      int dd = ich/8;
      mMT001[ib]->GetXaxis()->SetBinLabel(ich+1, Form("%c-%d", card[dd], ich%8));
    }
  }
}

void DSMSimulator_2016::bookPP001Histograms()
{
  mPP001ADC = new TH2F("mPP001ADC","MXQ-PP001;;ADC",16,0,16,4096,0,4096);
  mPP001ADC->GetXaxis()->SetBinLabel(1,"RPEVU1");
  mPP001ADC->GetXaxis()->SetBinLabel(2,"RPEVU2");
  mPP001ADC->GetXaxis()->SetBinLabel(3,"RPEVD1");
  mPP001ADC->GetXaxis()->SetBinLabel(4,"RPEVD2");
  mPP001ADC->GetXaxis()->SetBinLabel(5,"RPWVU1");
  mPP001ADC->GetXaxis()->SetBinLabel(6,"RPWVU2");
  mPP001ADC->GetXaxis()->SetBinLabel(7,"RPWVD1");
  mPP001ADC->GetXaxis()->SetBinLabel(8,"RPWVD2");
  mPP001ADC->GetXaxis()->SetBinLabel(9,"RPEHO1");
  mPP001ADC->GetXaxis()->SetBinLabel(10,"RPEHO2");
  mPP001ADC->GetXaxis()->SetBinLabel(11,"RPEHI1");
  mPP001ADC->GetXaxis()->SetBinLabel(12,"RPEHI2");
  mPP001ADC->GetXaxis()->SetBinLabel(13,"RPWHO1");
  mPP001ADC->GetXaxis()->SetBinLabel(14,"RPWHO2");
  mPP001ADC->GetXaxis()->SetBinLabel(15,"RPWHI1");
  mPP001ADC->GetXaxis()->SetBinLabel(16,"RPWHI2");

  mPP001TAC = new TH2F("mPP001TAC","MXQ-PP001;;TAC",16,0,16,4096,0,4096);
  mPP001TAC->GetXaxis()->SetBinLabel(1,"RPEVU1");
  mPP001TAC->GetXaxis()->SetBinLabel(2,"RPEVU2");
  mPP001TAC->GetXaxis()->SetBinLabel(3,"RPEVD1");
  mPP001TAC->GetXaxis()->SetBinLabel(4,"RPEVD2");
  mPP001TAC->GetXaxis()->SetBinLabel(5,"RPWVU1");
  mPP001TAC->GetXaxis()->SetBinLabel(6,"RPWVU2");
  mPP001TAC->GetXaxis()->SetBinLabel(7,"RPWVD1");
  mPP001TAC->GetXaxis()->SetBinLabel(8,"RPWVD2");
  mPP001TAC->GetXaxis()->SetBinLabel(9,"RPEHO1");
  mPP001TAC->GetXaxis()->SetBinLabel(10,"RPEHO2");
  mPP001TAC->GetXaxis()->SetBinLabel(11,"RPEHI1");
  mPP001TAC->GetXaxis()->SetBinLabel(12,"RPEHI2");
  mPP001TAC->GetXaxis()->SetBinLabel(13,"RPWHO1");
  mPP001TAC->GetXaxis()->SetBinLabel(14,"RPWHO2");
  mPP001TAC->GetXaxis()->SetBinLabel(15,"RPWHI1");
  mPP001TAC->GetXaxis()->SetBinLabel(16,"RPWHI2");
}

void DSMSimulator_2016::bookTF001Histograms()
{
  // TF001
  mTF001MULT[0] = new TH2F("TF001MULT","MIX-TF001;TOF tray;TOF MULT",21,0,21,32,0,32);
  mTF001MULT[0]->GetXaxis()->SetBinLabel(1,"13W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(2,"12W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(3,"11W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(4,"10W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(5,"9W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(6,"8W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(7,"7W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(8,"6W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(9,"5W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(10,"4W");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(11,"103E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(12,"104E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(13,"105E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(14,"106E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(15,"107E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(16,"108E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(17,"109E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(18,"110E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(19,"111E");
  mTF001MULT[0]->GetXaxis()->SetBinLabel(20,"112E");

  // TF002
  mTF001MULT[1] = new TH2F("TF002MULT","MIX-TF002;TOF tray;TOF MULT",21,0,21,32,0,32);
  mTF001MULT[1]->GetXaxis()->SetBinLabel(1,"3W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(2,"2W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(3,"1W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(4,"60W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(5,"59W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(6,"58W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(7,"57W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(8,"56W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(9,"55W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(10,"54W");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(11,"113E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(12,"114E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(13,"115E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(14,"116E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(15,"117E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(16,"118E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(17,"119E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(18,"120E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(19,"61E");
  mTF001MULT[1]->GetXaxis()->SetBinLabel(20,"62E");

  // TF003
  mTF001MULT[2] = new TH2F("TF003MULT","MIX-TF003;TOF tray;TOF MULT",21,0,21,32,0,32);
  mTF001MULT[2]->GetXaxis()->SetBinLabel(1,"53W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(2,"52W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(3,"51W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(4,"50W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(5,"49W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(6,"48W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(7,"47W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(8,"46W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(9,"45W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(10,"44W");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(11,"63E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(12,"64E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(13,"65E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(14,"66E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(15,"67E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(16,"68E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(17,"69E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(18,"70E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(19,"71E");
  mTF001MULT[2]->GetXaxis()->SetBinLabel(20,"72E");

  // TF004
  mTF001MULT[3] = new TH2F("TF004MULT","MIX-TF004;TOF tray;TOF MULT",21,0,21,32,0,32);
  mTF001MULT[3]->GetXaxis()->SetBinLabel(1,"43W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(2,"42W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(3,"41W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(4,"40W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(5,"39W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(6,"38W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(7,"37W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(8,"36W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(9,"35W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(10,"34W");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(11,"73E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(12,"74E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(13,"75E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(14,"76E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(15,"77E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(16,"78E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(17,"79E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(18,"80E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(19,"81E");
  mTF001MULT[3]->GetXaxis()->SetBinLabel(20,"82E");

  // TF005
  mTF001MULT[4] = new TH2F("TF005MULT","MIX-TF005;TOF tray;TOF MULT",21,0,21,32,0,32);
  mTF001MULT[4]->GetXaxis()->SetBinLabel(1,"33W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(2,"32W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(3,"31W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(4,"30W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(5,"29W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(6,"28W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(7,"27W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(8,"26W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(9,"25W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(10,"24W");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(11,"83E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(12,"84E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(13,"85E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(14,"86E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(15,"87E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(16,"88E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(17,"89E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(18,"90E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(19,"91E");
  mTF001MULT[4]->GetXaxis()->SetBinLabel(20,"92E");

  // TF006
  mTF001MULT[5] = new TH2F("TF006MULT","MIX-TF006;TOF tray;TOF MULT",21,0,21,32,0,32);
  mTF001MULT[5]->GetXaxis()->SetBinLabel(1,"23W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(2,"22W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(3,"21W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(4,"20W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(5,"19W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(6,"18W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(7,"17W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(8,"16W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(9,"15W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(10,"14W");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(11,"93E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(12,"94E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(13,"95E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(14,"96E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(15,"97E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(16,"98E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(17,"99E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(18,"100E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(19,"101E");
  mTF001MULT[5]->GetXaxis()->SetBinLabel(20,"102E");
}

void DSMSimulator_2016::bookTF101Histograms()
{
  mTF101MULT = new TH2F("TF101MULT","MIX-TF101;DSM Input Channel;TOF MULT", 6, 0, 6, 120 ,0,120);
  mTF101MULT->GetXaxis()->SetBinLabel(1,"TF001");
  mTF101MULT->GetXaxis()->SetBinLabel(2,"TF002");
  mTF101MULT->GetXaxis()->SetBinLabel(3,"TF003");
  mTF101MULT->GetXaxis()->SetBinLabel(4,"TF004");
  mTF101MULT->GetXaxis()->SetBinLabel(5,"TF005");
  mTF101MULT->GetXaxis()->SetBinLabel(6,"TF006");
  const char *name[4] = {"WestLow", "WestHigh", "EastLow", "EastHigh"};
  for(int iupc = 0; iupc < 4; iupc++){
    mTF101UPC[iupc] = new TH2F(Form("TF101UPC-TH-%d", iupc), Form("MIX-TF101;DSM Input Channel;TOF UPC-TH-%s", name[iupc]), 6,0,6, 2, 0, 2);
    mTF101UPC[iupc]->GetXaxis()->SetBinLabel(1,"TF001");
    mTF101UPC[iupc]->GetXaxis()->SetBinLabel(2,"TF002");
    mTF101UPC[iupc]->GetXaxis()->SetBinLabel(3,"TF003");
    mTF101UPC[iupc]->GetXaxis()->SetBinLabel(4,"TF004");
    mTF101UPC[iupc]->GetXaxis()->SetBinLabel(5,"TF005");
    mTF101UPC[iupc]->GetXaxis()->SetBinLabel(6,"TF006");
  }

  mTF101MULTSim = new TH2F("TF101MULTSim","MIX-TF101;DSM Input Channel;TOF MULT(Real-Simu)",6,0,6, 240, -120, 120);
  mTF101MULTSim->GetXaxis()->SetBinLabel(1,"TF001");
  mTF101MULTSim->GetXaxis()->SetBinLabel(2,"TF002");
  mTF101MULTSim->GetXaxis()->SetBinLabel(3,"TF003");
  mTF101MULTSim->GetXaxis()->SetBinLabel(4,"TF004");
  mTF101MULTSim->GetXaxis()->SetBinLabel(5,"TF005");
  mTF101MULTSim->GetXaxis()->SetBinLabel(6,"TF006");
  //  char *name[4] = {"WestLow", "WestHigh", "EastLow", "EastHigh"};
  for(int iupc = 0; iupc < 4; iupc++){
    mTF101UPCSim[iupc] = new TH2F(Form("TF101UPCTHSim%d", iupc), Form("MIX-TF101;DSM Input Channel;TOF UPC-TH-%s(Real-Simu)", name[iupc]), 6,0,6, 4, -2, 2);
    mTF101UPCSim[iupc]->GetXaxis()->SetBinLabel(1,"TF001");
    mTF101UPCSim[iupc]->GetXaxis()->SetBinLabel(2,"TF002");
    mTF101UPCSim[iupc]->GetXaxis()->SetBinLabel(3,"TF003");
    mTF101UPCSim[iupc]->GetXaxis()->SetBinLabel(4,"TF004");
    mTF101UPCSim[iupc]->GetXaxis()->SetBinLabel(5,"TF005");
    mTF101UPCSim[iupc]->GetXaxis()->SetBinLabel(6,"TF006");
  }

}
void DSMSimulator_2016::labelTF201MT(TH2F *h)
{
    h->GetXaxis()->SetBinLabel(1, "Hit");
    h->GetXaxis()->SetBinLabel(2, "Cosmic-Ray");
    h->GetXaxis()->SetBinLabel(3, "Timed-Cosmic-Ray");
    labelHistogramYaxis(h);
}

void DSMSimulator_2016::bookTF201Histograms()
{
  mTF201TotalMult = new TH1F("TF201TotalMult","L2-TF201;TOF total mult", 4096, 0, 4096);
  mTF201SectorThUPC = new TH2F("TF201SectorThUPC","L2-TF201;TOF sector/UPC;Threshold/UPC bits",7,0,7,2,0,2);
  labelTF201TF(mTF201SectorThUPC);

//  mTF201UPCBit = new TH1F("TF201UPCBit", "L2-TF201 Input Ch3 -- UPC Bit;UPC Bit", 2, 0, 2);

  for(int ich = 0; ich < 2; ich++){
    int channel = 6*ich;
    mTF201NMuons[ich] = new TH1F(Form("TF201MT10%dNMuons", ich+1), Form("L2-TF201 Input chn %d -- Number of Muons; Number of Muons", channel), 16, 0, 16);
    mTF201CosRay[ich] = new TH2F(Form("TF201MT10%dCosRay", ich+1), Form("L2-TF201 Input chn %d -- Cosmic-Ray",  channel), 3, 0, 3, 2, 0, 2);
    labelTF201MT(mTF201CosRay[ich]);
  }


  mTF201RP = new TH2F("TF201RP", "L2-TF201 Input Ch4 -- PP101 (Roman Plot);Bit;Fired", 8, 0, 8, 2, 0, 2);

  mTF201RP->GetXaxis()->SetBinLabel(1, "ET");
  mTF201RP->GetXaxis()->SetBinLabel(2, "IT");
  mTF201RP->GetXaxis()->SetBinLabel(3, "EOR");
  mTF201RP->GetXaxis()->SetBinLabel(4, "WOR");
  mTF201RP->GetXaxis()->SetBinLabel(5, "EU");
  mTF201RP->GetXaxis()->SetBinLabel(6, "ED");
  mTF201RP->GetXaxis()->SetBinLabel(7, "WU");
  mTF201RP->GetXaxis()->SetBinLabel(8, "WD");

  mTF201RP->GetYaxis()->SetBinLabel(1, "0");
  mTF201RP->GetYaxis()->SetBinLabel(2, "1");
  //Simu
  mTF201TotalMultSimu = new TH1F("TF201TotalMultSimu","L2-TF201;TOF total mult(Real-Simu)", 4096, -4095, 4096);
  mTF201SectorThUPCSimu = new TH2F("TF201SectorThUPCSimu","L2-TF201;TOF sector/UPC;Threshold bits/UPC (Real-Simu)",7,0,7,3,-1,2);
  labelTF201TF(mTF201SectorThUPCSimu);

//  mTF201UPCBitSimu = new TH1F("TF201UPCBitSimu", "L2-TF201 Input Ch3 -- UPC Bit;UPC Bit(Real-Simu)", 3, -1, 2);

  for(int ich = 0; ich < 2; ich++){
    int channel = 6*ich;
    mTF201NMuonsSimu[ich] = new TH1F(Form("TF201MT10%dNMuonsSimu", ich+1), Form("L2-TF201 Input chn %d -- Number of Muons; Number of Muons (Real-Simu)", channel), 31, -15, 16);
    mTF201CosRaySimu[ich] = new TH2F(Form("TF201MT10%dCosRaySimu", ich+1), Form("L2-TF201 Input chn %d -- Cosmic-Ray (Real-Simu)",  channel), 3, 0, 3, 3, -1, 2);
    labelTF201MT(mTF201CosRaySimu[ich]);
  }

  mTF201RPSimu = new TH2F("TF201RPSimu", "L2-TF201 Input Ch4 -- PP101 (Roman Plot);Bit;Fired(Real-Simu)", 8, 0, 8, 3, -1, 2);

  mTF201RPSimu->GetXaxis()->SetBinLabel(1, "ET");
  mTF201RPSimu->GetXaxis()->SetBinLabel(2, "IT");
  mTF201RPSimu->GetXaxis()->SetBinLabel(3, "EOR");
  mTF201RPSimu->GetXaxis()->SetBinLabel(4, "WOR");
  mTF201RPSimu->GetXaxis()->SetBinLabel(5, "EU");
  mTF201RPSimu->GetXaxis()->SetBinLabel(6, "ED");
  mTF201RPSimu->GetXaxis()->SetBinLabel(7, "WU");
  mTF201RPSimu->GetXaxis()->SetBinLabel(8, "WD");

//  mTF201RPSimu->GetYaxis()->SetBinLabel(1, "0");
//  mTF201RPSimu->GetYaxis()->SetBinLabel(2, "1");
}
void DSMSimulator_2016::labelTF201TF(TH2F *h)
{
  h->GetXaxis()->SetBinLabel(1,"TF001");
  h->GetXaxis()->SetBinLabel(2,"TF002");
  h->GetXaxis()->SetBinLabel(3,"TF003");
  h->GetXaxis()->SetBinLabel(4,"TF004");
  h->GetXaxis()->SetBinLabel(5,"TF005");
  h->GetXaxis()->SetBinLabel(6,"TF006");
  h->GetXaxis()->SetBinLabel(7,"UPC");
  labelHistogramYaxis(h);
}
void DSMSimulator_2016::bookMT101Histograms()
{
  for(int ib = 0; ib < 2; ib++){
  for(int ichn = 0; ichn < 4; ichn++){
    mMT101TACsum[ib][ichn] = new TH2F(Form("MT10%dTACsum%d", ib+1, ichn), Form("MIX-MT10%d Input: MT00%d MTDE+W TAC sum;ID;TAC sum", ib+1, 4*ib+ichn+1), 2, 0, 2, 1024, 0, 1024);
    mMT101TACsum[ib][ichn]->GetXaxis()->SetBinLabel(1, "1st-Best");
    mMT101TACsum[ib][ichn]->GetXaxis()->SetBinLabel(2, "2nd-Best");
//    mMT101TACsum2nd[ib][ichn] = new TH1F(Form("MT10%dTACsum2nd%d", ib+1, ichn), Form("MIX-MT10%d Input: MT00%d 2nd Best MTDE+W TAC sum;ID;TAC sum", ib+1, 4*ib+ichn+1), 1024, 0, 1024);
  }

  for(int ichn = 8; ichn < 10; ichn++){
    mMT101MaxTAC[ib][ichn-8] = new TH1F(Form("MT10%dMaxTAC%d", ib+1, ichn), Form("MIX-MT10%d Input: VP00%d Max TAC", ib+1, ichn-5), 4096, 0, 4096);
  }
  }
  /*
  for(int ichn = 0; ichn < 4; ichn++){
    mMT101TACsum1stSim[ichn] = new TH2F(Form("MT101TACsum1stSimu%d", ichn), Form("MIX-MT101 Input: MT00%d Best MTDE+W TAC sum (Simu);ID(Real-Simu);TAC sum(Real-Simu)", ichn+1), 8, -4, 4, 960, -480, 480);
    mMT101TACsum2ndSim[ichn] = new TH2F(Form("MT101TACsum2ndSimu%d", ichn), Form("MIX-MT101 Input: MT00%d 2nd Best MTDE+W TAC sum (Simu);ID(Real-Simu);TAC sum(Real-Simu)", ichn+1), 8, -4, 4, 960, -480, 480);
  }

  for(int ichn = 8; ichn < 10; ichn++){
    mMT101MaxTACSim[ichn-8] = new TH1F(Form("MT101MaxTACSimu%d", ichn), Form("MIX-MT101 Input: VP00%d Max TAC (Real-Simu)", ichn-5), 8192, -4096, 4096);
  }
  */
}

void DSMSimulator_2016::bookBeamEnergyScanHistograms()
{
  // 2013 pp 500 GeV
  const int nbins = 256;
  const int tofmax = 4096;
  const int bbclmaxadc = 65536;
  const int bbcsmaxadc = 65536;
  const int vpdmaxadc = 4096;
  const int zdcmaxadc = 4096;

  hTofVsBbcLargeEast = new TH2F("hTofVsBbcLargeEast",";BBC-L-East ADC Sum;TOF Mult",nbins,0,bbclmaxadc,nbins,0,tofmax);
  hTofVsBbcLargeWest = new TH2F("hTofVsBbcLargeWest",";BBC-L-West ADC Sum;TOF Mult",nbins,0,bbclmaxadc,nbins,0,tofmax);
  hTofVsBbcSmallEast = new TH2F("hTofVsBbcSmallEast",";BBC-S-East ADC Sum;TOF Mult",nbins,0,bbcsmaxadc,nbins,0,tofmax);
  hTofVsBbcSmallWest = new TH2F("hTofVsBbcSmallWest",";BBC-S-West ADC Sum;TOF Mult",nbins,0,bbcsmaxadc,nbins,0,tofmax);
  hTofVsVpdEast = new TH2F("hTofVsVpdEast",";VPD-East ADC Sum;TOF Mult",nbins,0,vpdmaxadc,nbins,0,tofmax);
  hTofVsVpdWest = new TH2F("hTofVsVpdWest",";VPD-West ADC Sum;TOF Mult",nbins,0,vpdmaxadc,nbins,0,tofmax);
  hTofVsZdcEast = new TH2F("hTofVsZdcEast",";ZDC-East ADC Sum Att;TOF Mult",nbins,0,zdcmaxadc,nbins,0,tofmax);
  hTofVsZdcWest = new TH2F("hTofVsZdcWest",";ZDC-West ADC Sum Att;TOF Mult",nbins,0,zdcmaxadc,nbins,0,tofmax);

  hBbcLargeVsSmallEast = new TH2F("hBbcLargeVsSmallEast",";BBC-S-East ADC Sum;BBC-L-East ADC Sum",nbins,0,bbcsmaxadc,nbins,0,bbclmaxadc);
  hBbcLargeVsSmallWest = new TH2F("hBbcLargeVsSmallWest",";BBC-S-West ADC Sum;BBC-L-West ADC Sum",nbins,0,bbcsmaxadc,nbins,0,bbclmaxadc);
  hBbcLargeVsVpdEast = new TH2F("hBbcLargeVsVpdEast",";VPD-East ADC Sum;BBC-L-East ADC Sum",nbins,0,vpdmaxadc,nbins,0,bbclmaxadc);
  hBbcLargeVsVpdWest = new TH2F("hBbcLargeVsVpdWest",";VPD-West ADC Sum;BBC-L-West ADC Sum",nbins,0,vpdmaxadc,nbins,0,bbclmaxadc);
  hBbcLargeVsZdcEast = new TH2F("hBbcLargeVsZdcEast",";ZDC-East ADC Sum Att;BBC-L-East ADC Sum",nbins,0,zdcmaxadc,nbins,0,bbclmaxadc);
  hBbcLargeVsZdcWest = new TH2F("hBbcLargeVsZdcWest",";ZDC-West ADC Sum Att;BBC-L-West ADC Sum",nbins,0,zdcmaxadc,nbins,0,bbclmaxadc);
  hBbcSmallVsVpdEast = new TH2F("hBbcSmallVsVpdEast",";VPD-East ADC Sum;BBC-S-East ADC Sum",nbins,0,vpdmaxadc,nbins,0,bbcsmaxadc);
  hBbcSmallVsVpdWest = new TH2F("hBbcSmallVsVpdWest",";VPD-West ADC Sum;BBC-S-West ADC Sum",nbins,0,vpdmaxadc,nbins,0,bbcsmaxadc);
  hBbcSmallVsZdcEast = new TH2F("hBbcSmallVsZdcEast",";ZDC-East ADC Sum Att;BBC-S-East ADC Sum",nbins,0,zdcmaxadc,nbins,0,bbcsmaxadc);
  hBbcSmallVsZdcWest = new TH2F("hBbcSmallVsZdcWest",";ZDC-West ADC Sum Att;BBC-S-West ADC Sum",nbins,0,zdcmaxadc,nbins,0,bbcsmaxadc);
  hVpdVsZdcEast = new TH2F("hVpdVsZdcEast",";ZDC-East ADC Sum Att;VPD-East ADC Sum",nbins,0,zdcmaxadc,nbins,0,vpdmaxadc);
  hVpdVsZdcWest = new TH2F("hVpdVsZdcWest",";ZDC-West ADC Sum Att;VPD-West ADC Sum",nbins,0,zdcmaxadc,nbins,0,vpdmaxadc);
  hBbcLargeEastVsWest = new TH2F("hBbcLargeEastVsWest",";BBC-L-West ADC Sum;BBC-L-East ADC Sum",nbins,0,bbclmaxadc,nbins,0,bbclmaxadc);
  hBbcSmallEastVsWest = new TH2F("hBbcSmallEastVsWest",";BBC-S-West ADC Sum;BBC-S-East ADC Sum",nbins,0,bbcsmaxadc,nbins,0,bbcsmaxadc);
  hVpdEastVsWest = new TH2F("hVpdEastVsWest",";VPD West ADC Sum;VPD East ADC Sum",nbins,0,vpdmaxadc,nbins,0,vpdmaxadc);
  hZdcEastVsWest = new TH2F("hZdcEastVsWest",";ZDC West ADC Sum Att;ZDC East ADC Sum Att",nbins,0,zdcmaxadc,nbins,0,zdcmaxadc);

  const int bbclmaxtac = 8192;
  const int bbcsmaxtac = 8192;
//  const int vpdmaxtac = 8192;
  const int zdcmaxtac = 2048;

  hBbcLargeVsSmallTac = new TH2F("hBbcLargeVsSmallTac",";BCC-S TAC Diff;BBC-L TAC Diff",nbins,-128,bbcsmaxtac,nbins,-128,bbclmaxtac);
  //hBbcLargeVsVpdTac = new TH2F("hBbcLargeVsVpdTac",";VPD TAC Diff;BBC-L TAC Diff",nbins,-128,vpdmaxtac,nbins,-128,bbclmaxtac);
  hBbcLargeVsZdcTac = new TH2F("hBbcLargeVsZdcTac",";ZDC TAC Diff;BBC-L TAC Diff",nbins,-128,zdcmaxtac,nbins,-128,bbclmaxtac);
  //hBbcSmallVsVpdTac = new TH2F("hBbcSmallVsVpdTac",";VPD TAC Diff;BBC-S TAC Diff",nbins,-128,vpdmaxtac,nbins,-128,bbcsmaxtac);
  hBbcSmallVsZdcTac = new TH2F("hBbcSmallVsZdcTac",";ZDC TAC Diff;BBC-S TAC Diff",nbins,-128,zdcmaxtac,nbins,-128,bbcsmaxtac);
  //hVpdVsZdcTac = new TH2F("hVpdVsZdcTac",";ZDC TAC Diff;VPD TAC Diff",nbins,-128,zdcmaxtac,nbins,-128,vpdmaxtac);
  hZdcTacEastVsWest = new TH2F("hZdcTacEastVsWest",";ZDC TAC-W;ZDC TAC-E",nbins,-128,zdcmaxtac,nbins,-128,zdcmaxtac);
}

void DSMSimulator_2016::fillBB001Histograms()
{
  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mBB001ADC->Fill(adc++,bbq.boards[0].channels[ch++]);
    mBB001ADC->Fill(adc++,bbq.boards[0].channels[ch++]);
    mBB001ADC->Fill(adc++,bbq.boards[0].channels[ch++]);
    mBB001ADC->Fill(adc++,bbq.boards[0].channels[ch++]);

    mBB001TAC->Fill(tac++,bbq.boards[0].channels[ch++]);
    mBB001TAC->Fill(tac++,bbq.boards[0].channels[ch++]);
    mBB001TAC->Fill(tac++,bbq.boards[0].channels[ch++]);
    mBB001TAC->Fill(tac++,bbq.boards[0].channels[ch++]);
  }

  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mBB002ADC->Fill(adc++,bbq.boards[2].channels[ch++]);
    mBB002ADC->Fill(adc++,bbq.boards[2].channels[ch++]);
    mBB002ADC->Fill(adc++,bbq.boards[2].channels[ch++]);
    mBB002ADC->Fill(adc++,bbq.boards[2].channels[ch++]);

    mBB002TAC->Fill(tac++,bbq.boards[2].channels[ch++]);
    mBB002TAC->Fill(tac++,bbq.boards[2].channels[ch++]);
    mBB002TAC->Fill(tac++,bbq.boards[2].channels[ch++]);
    mBB002TAC->Fill(tac++,bbq.boards[2].channels[ch++]);
  }

  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mBB003ADC->Fill(adc++,bbq.boards[4].channels[ch++]);
    mBB003ADC->Fill(adc++,bbq.boards[4].channels[ch++]);
    mBB003ADC->Fill(adc++,bbq.boards[4].channels[ch++]);
    mBB003ADC->Fill(adc++,bbq.boards[4].channels[ch++]);

    mBB003TAC->Fill(tac++,bbq.boards[4].channels[ch++]);
    mBB003TAC->Fill(tac++,bbq.boards[4].channels[ch++]);
    mBB003TAC->Fill(tac++,bbq.boards[4].channels[ch++]);
    mBB003TAC->Fill(tac++,bbq.boards[4].channels[ch++]);
  }

  /*  int* bb101channels = (int*)bb101.channels;
  int bbcstace = bb101channels[0] >> 16 & 0xfff;
  int bbcstacw = bb101channels[1] >> 16 & 0xfff;
  if (bbcstace > 0 && bbcstace < 4095) mBBCSTACE->Fill(bbcstace);
  if (bbcstacw > 0 && bbcstacw < 4095) mBBCSTACW->Fill(bbcstacw);

  int* bb102channels = (int*)bb102.channels;
  int bbcltace = bb102channels[0] >>  0 & 0xfff;
  int bbcltacw = bb102channels[0] >> 12 & 0xfff;
  if (bbcltace > 0 && bbcltace < 4095) mBBCLTACE->Fill(bbcltace);
  if (bbcltacw > 0 && bbcltacw < 4095) mBBCLTACW->Fill(bbcltacw);

  int bbcstacdiff = vt201.channels[0] & 0x1fff;
  int bbcltacdiff = vt201.channels[1] & 0x1fff;
  if (bbcstacdiff > 0 && bbcstacdiff < 8191) mBBCSTACDIFF->Fill(bbcstacdiff);
  if (bbcltacdiff > 0 && bbcltacdiff < 8191) mBBCLTACDIFF->Fill(bbcltacdiff);
  */
}

void DSMSimulator_2016::fillVP001Histograms()
{
  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mVP001ADC->Fill(adc++,vp001.channels[ch++]);
    mVP001ADC->Fill(adc++,vp001.channels[ch++]);
    mVP001ADC->Fill(adc++,vp001.channels[ch++]);
    mVP001ADC->Fill(adc++,vp001.channels[ch++]);

    mVP001TAC->Fill(tac++,vp001.channels[ch++]);
    mVP001TAC->Fill(tac++,vp001.channels[ch++]);
    mVP001TAC->Fill(tac++,vp001.channels[ch++]);
    mVP001TAC->Fill(tac++,vp001.channels[ch++]);
  }

  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mVP002ADC->Fill(adc++,vp002.channels[ch++]);
    mVP002ADC->Fill(adc++,vp002.channels[ch++]);
    mVP002ADC->Fill(adc++,vp002.channels[ch++]);
    mVP002ADC->Fill(adc++,vp002.channels[ch++]);

    mVP002TAC->Fill(tac++,vp002.channels[ch++]);
    mVP002TAC->Fill(tac++,vp002.channels[ch++]);
    mVP002TAC->Fill(tac++,vp002.channels[ch++]);
    mVP002TAC->Fill(tac++,vp002.channels[ch++]);
  }

  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mVP003ADC->Fill(adc++,vp003.channels[ch++]);
    mVP003ADC->Fill(adc++,vp003.channels[ch++]);
    mVP003ADC->Fill(adc++,vp003.channels[ch++]);
    mVP003ADC->Fill(adc++,vp003.channels[ch++]);

    mVP003TAC->Fill(tac++,vp003.channels[ch++]);
    mVP003TAC->Fill(tac++,vp003.channels[ch++]);
    mVP003TAC->Fill(tac++,vp003.channels[ch++]);
    mVP003TAC->Fill(tac++,vp003.channels[ch++]);
  }

  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mVP004ADC->Fill(adc++,vp004.channels[ch++]);
    mVP004ADC->Fill(adc++,vp004.channels[ch++]);
    mVP004ADC->Fill(adc++,vp004.channels[ch++]);
    mVP004ADC->Fill(adc++,vp004.channels[ch++]);

    mVP004TAC->Fill(tac++,vp004.channels[ch++]);
    mVP004TAC->Fill(tac++,vp004.channels[ch++]);
    mVP004TAC->Fill(tac++,vp004.channels[ch++]);
    mVP004TAC->Fill(tac++,vp004.channels[ch++]);
  }
/*
  int* vp101channels = (int*)vp101.channels;
  int vpdtace = vp101channels[2] >> 16 & 0xfff;
  int vpdtacw = vp101channels[3] >> 16 & 0xfff;
  int vpdtacdiff = vt201.channels[4] & 0x1fff;
  if (vpdtace > 0 && vpdtace < 4095) mVPDTACE->Fill(vpdtace);
  if (vpdtacw > 0 && vpdtacw < 4095) mVPDTACW->Fill(vpdtacw);
  if (vpdtacdiff > 0 && vpdtacdiff < 8191) mVPDTACDIFF->Fill(vpdtacdiff);
*/
}

void DSMSimulator_2016::fillZD001Histograms()
{
  for (int ch = 0, adc = 0, tac = 0; ch < 32;) {
    mZD001ADC->Fill(adc++,zd001.channels[ch++]);
    mZD001ADC->Fill(adc++,zd001.channels[ch++]);
    mZD001ADC->Fill(adc++,zd001.channels[ch++]);
    mZD001ADC->Fill(adc++,zd001.channels[ch++]);

    mZD001TAC->Fill(tac++,zd001.channels[ch++]);
    mZD001TAC->Fill(tac++,zd001.channels[ch++]);
    mZD001TAC->Fill(tac++,zd001.channels[ch++]);
    mZD001TAC->Fill(tac++,zd001.channels[ch++]);
  }

//  int* zd001out = (int*)zd101.channels;
//  int zdctacw = zd001out[0] >>  0 & 0x3ff;
//  int zdctace = zd001out[0] >> 10 & 0x3ff;
//  if (zdctacw > 0 && zdctacw < 1023) mZDCTACW->Fill(zdctacw);
//  if (zdctace > 0 && zdctace < 1023) mZDCTACE->Fill(zdctace);
//  int zdctacdiff = 1024+zdctace-zdctacw;
//  if (zdctacdiff >= 0 && zdctacdiff < 2048) mZDCTACDIFF->Fill(zdctacdiff);
//  if (zdctacw > 0 && zdctace > 0) mZDCTACDIFF->Fill(zdctacdiff);
}

void DSMSimulator_2016::fillMT001Histograms()
{
  for (int ch = 0; ch < 32; ++ch) {
    mMT001[0]->Fill(ch,mt001.channels[ch]);
    mMT001[1]->Fill(ch,mt002.channels[ch]);
    mMT001[2]->Fill(ch,mt003.channels[ch]);
    mMT001[3]->Fill(ch,mt004.channels[ch]);
    mMT001[4]->Fill(ch,mt005.channels[ch]);
    mMT001[5]->Fill(ch,mt006.channels[ch]);
    mMT001[6]->Fill(ch,mt007.channels[ch]);
    mMT001[7]->Fill(ch,mt008.channels[ch]);
  }
}

void DSMSimulator_2016::fillPP001Histograms()
{
  for (int i = 0; i < 4; ++i) {
    mPP001ADC->Fill(i,pp001.channels[i]);
    mPP001TAC->Fill(i,pp001.channels[i+4]);
    mPP001ADC->Fill(i+4,pp001.channels[i+8]);
    mPP001TAC->Fill(i+4,pp001.channels[i+12]);
    mPP001ADC->Fill(i+8,pp001.channels[i+16]);
    mPP001TAC->Fill(i+8,pp001.channels[i+20]);
    mPP001ADC->Fill(i+12,pp001.channels[i+24]);
    mPP001TAC->Fill(i+12,pp001.channels[i+28]);
  }
}
/*
void DSMSimulator_2016::fillZP001Histograms()
{
  for (int ch = 0; ch < 16; ++ch) {
    mZP001WADC->Fill(ch,zp001.channels[ch]);
    mZP001EADC->Fill(ch,zp001.channels[ch+16]);
  }
}
*/
void DSMSimulator_2016::fillTF001Histograms()
{
/*
  for (int addr = 4; addr < 16; ++addr) {
    for (int ch = 0; ch < 7; ++ch) {
      int mult = mix.boards[addr].channels[ch];
      for (int i = 0; i < 3; ++i) {
        mTF001MULT[(addr-4)/2]->Fill(ch*3+i,mult & 0x1f);
        mult >>= 5;
      }
    }
  }
*/
  int mult;
  for (int ch = 0; ch < 7; ++ch) {
    mult = tf001.channels[ch];
    for (int i = 0; i < 3; ++i) {
      mTF001MULT[0]->Fill(ch*3+i,mult & 0x1f);
      mult >>= 5;
    }
  }

  for (int ch = 0; ch < 7; ++ch) {
    mult = tf002.channels[ch];
    for (int i = 0; i < 3; ++i) {
      mTF001MULT[1]->Fill(ch*3+i,mult & 0x1f);
      mult >>= 5;
    }
  }

  for (int ch = 0; ch < 7; ++ch) {
    mult = tf003.channels[ch];
    for (int i = 0; i < 3; ++i) {
      mTF001MULT[2]->Fill(ch*3+i,mult & 0x1f);
      mult >>= 5;
    }
  }

  for (int ch = 0; ch < 7; ++ch) {
    mult = tf004.channels[ch];
    for (int i = 0; i < 3; ++i) {
      mTF001MULT[3]->Fill(ch*3+i,mult & 0x1f);
      mult >>= 5;
    }
  }

  for (int ch = 0; ch < 7; ++ch) {
    mult = tf005.channels[ch];
    for (int i = 0; i < 3; ++i) {
      mTF001MULT[4]->Fill(ch*3+i,mult & 0x1f);
      mult >>= 5;
    }
  }

  for (int ch = 0; ch < 7; ++ch) {
    mult = tf006.channels[ch];
    for (int i = 0; i < 3; ++i) {
      mTF001MULT[5]->Fill(ch*3+i,mult & 0x1f);
      mult >>= 5;
    }
  }
}

void DSMSimulator_2016::fillTF101Histograms()
{
  for (int ch = 0; ch < 6; ++ch) {
    int mult = getbits(tf101.channels[ch], 0, 10);
    mTF101MULT->Fill(ch,mult);
    for(int ii = 0; ii < 4; ii++){
      int upc = btest(tf101.channels[ch], 10+ii);
      mTF101UPC[ii]->Fill(ch, upc);
    }
  }
}
void DSMSimulator_2016::fillTF101Histograms(const Crate& sim)
{
  fillTF101Histograms();

  const Board& tf101sim = sim.boardAt(TF101_BASE_ADDRESS);
  for (int ch = 0; ch < 6; ++ch) {
    int mult = getbits(tf101.channels[ch], 0, 10);
    int multsim = getbits(tf101sim.channels[ch], 0, 10);

    if(mult-multsim) mTF101MULTSim->Fill(ch,mult-multsim);

    for(int ii = 0; ii < 4; ii++){
      int upc = btest(tf101.channels[ch], 10+ii);
      int upcsim = btest(tf101.channels[ch], 10+ii);

      if(upc-upcsim) mTF101UPCSim[ii]->Fill(ch, upc-upcsim);
    }
  }
}
void DSMSimulator_2016::fillMT101Histograms()
{
  fillMT101Histograms(mt101, 0);
  fillMT101Histograms(mt102, 1);
}
void DSMSimulator_2016::fillMT101Histograms(Board mt10x, int index)
{
  for(int ichn = 0; ichn < 8; ichn += 2){
    unsigned int bits = mt10x.channels[ichn] & 0xfff;
    bits |= mt10x.channels[ichn+1] << 12;
//    if(index == 1)
//      cout<<"filling: "<<ichn<<" "<<hex<<bits<<dec<<endl;
    int tac = getbits(bits, 0, 10);
//    cout<<"1st: "<<tac<<endl;
    //int id = getbits(bits, 10, 2);
    mMT101TACsum[index][ichn/2]->Fill(0., tac);

    tac = getbits(bits, 12, 10);
//    cout<<"2nd: "<<tac<<endl;
    //id = getbits(bits, 22, 2);
    mMT101TACsum[index][ichn/2]->Fill(1., tac);
  }

  for(int ichn = 8; ichn < 10; ichn++){
    int tac = getbits(mt10x.channels[ichn], 0, 12);
    mMT101MaxTAC[index][ichn-8]->Fill(tac);
  }
}

void DSMSimulator_2016::fillTF201Histograms()
{
  int totalMult = getbits(tf201.channels[2], 0, 13);
  mTF201TotalMult->Fill(totalMult);
  int sectorThUPC = tf201.channels[3];
  for (int ib = 0; ib < 7; ++ib)
    mTF201SectorThUPC->Fill(ib, btest(sectorThUPC, ib));
//  int upc = btest(tf201.channels[3], 6);
//  mTF201UPCBit->Fill(upc);
  for(int ich = 0; ich < 2; ich++){
    int cc = ich*6;
    int muons = getbits(tf201.channels[cc], 0, 4);
    mTF201NMuons[ich]->Fill(muons);
    int hit = btest(tf201.channels[cc], 12);
    mTF201CosRay[ich]->Fill(0., hit);
    int cosmic = btest(tf201.channels[cc], 14);
    mTF201CosRay[ich]->Fill(1., cosmic);
    int t_cosmic = btest(tf201.channels[cc], 15);
    mTF201CosRay[ich]->Fill(2., t_cosmic);
  }
  int pp101 = tf201.channels[4];
  for(int ii = 0; ii < 8; ii++){
    mTF201RP->Fill(ii, btest(pp101, ii));
  }
}
void DSMSimulator_2016::fillTF201Histograms(const Crate& sim)
{
  fillTF201Histograms();

  int totalMult = getbits(tf201.channels[2], 0, 13);

  int sectorThUPC = tf201.channels[3];
//  int upc = btest(tf201.channels[3], 6);

  const Board& tf201sim = sim.boardAt(TF201_BASE_ADDRESS);
  int totalMultsim = getbits(tf201sim.channels[2], 0, 13);
  if(totalMult-totalMultsim) mTF201TotalMultSimu->Fill(totalMult-totalMultsim);

  int sectorThUPCsim = tf201sim.channels[3];
  for (int ib = 0; ib < 6; ++ib)
    if(int diff = btest(sectorThUPC, ib) - btest(sectorThUPCsim, ib)) mTF201SectorThUPCSimu->Fill(ib,diff);

//  int upcsim = btest(tf201sim.channels[3], 6);
//  if(upc-upcsim) mTF201UPCBitSimu->Fill(upc-upcsim);

  for(int ich = 0; ich < 2; ich++){
    int cc = ich*6;
    //data
    int muons = getbits(tf201.channels[cc], 0, 4);
    int hit = btest(tf201.channels[cc], 12);
    int cosmic = btest(tf201.channels[cc], 14);
    int t_cosmic = btest(tf201.channels[cc], 15);

    int muonssim = getbits(tf201sim.channels[cc], 0, 4);
    if(muons-muonssim) mTF201NMuonsSimu[ich]->Fill(muons-muonssim);
    int hitsim = btest(tf201sim.channels[cc], 12);
    if(int diff = hit-hitsim) mTF201CosRaySimu[ich]->Fill(0., diff);
    int cosmicsim = btest(tf201sim.channels[cc], 14);
    if(cosmic-cosmicsim) mTF201CosRaySimu[ich]->Fill(1., cosmic-cosmicsim);
    int t_cosmicsim = btest(tf201sim.channels[cc], 15);
    if(t_cosmic-t_cosmicsim) mTF201CosRaySimu[ich]->Fill(2., t_cosmic-t_cosmicsim);
  }
  int pp101 = tf201.channels[4];
  int pp101sim = tf201sim.channels[4];
  for(int ii = 0; ii < 8; ii++){
    if(btest(pp101, ii)-btest(pp101sim, ii)) mTF201RPSimu->Fill(ii, btest(pp101, ii)-btest(pp101sim, ii));
  }

}
void DSMSimulator_2016::runMixLayer0(Crate& sim)
{
  mix_tf001_2014_c(tf001);
  mix_tf001_2014_c(tf002);
  mix_tf001_2014_c(tf003);
  mix_tf001_2014_c(tf004);
  mix_tf001_2014_c(tf005);
  mix_tf001_2014_c(tf006);

  Board &tf101sim = sim.boardAt(TF101_BASE_ADDRESS);
  tf101sim.channels[0] = tf001.output & 0xffff;
  tf101sim.channels[1] = tf002.output & 0xffff;
  tf101sim.channels[2] = tf003.output & 0xffff;
  tf101sim.channels[3] = tf004.output & 0xffff;
  tf101sim.channels[4] = tf005.output & 0xffff;
  tf101sim.channels[5] = tf006.output & 0xffff;
}
void DSMSimulator_2016::runMixLayer1(Crate& sim)
{
  mix_tf101_2014_b(tf101);
  mix_mt101_2016_a(mt101);
  mix_mt101_2016_a(mt102);
  mix_pp101_2015_a(pp101);//in run15 pp101 uses fe101

  Board &tf201sim = sim.boardAt(TF201_BASE_ADDRESS);
  tf201sim.channels[0] = mt101.output;
  tf201sim.channels[2] = getbits(tf101.output, 0, 16);
  tf201sim.channels[3] = getbits(tf101.output, 16, 16);
  tf201sim.channels[4] = getbits(pp101.output, 0, 16);
  tf201sim.channels[6] = mt102.output;
}
void DSMSimulator_2016::runMixLayer2(Crate& sim)
{
  //l1_tf201_2016_a(tf201);
  l1_tf201_2016_b(tf201);

  Board &ld301sim = sim.boardAt(LD301_BASE_ADDRESS);
  ld301sim.channels[0] = tf201.output;
}
void DSMSimulator_2016::runFpdBranch()
{
  Crate sim;
  //  fillFpeQtLayerHistograms();
  //  runFpeQtLayer(sim);
  //  fillFpeLayer1Histograms(sim);

  fillFmsQtLayerHistograms();
  runFmsQtLayer(sim);
  fillFmsLayer0Histograms();

  runFmsLayer0(sim);
  fillFmsLayer1Histograms(sim);

  //  runFpeLayer1();
  runFmsLayer1(sim);
  fillFmsLayer2Histograms(sim);

  runFmsLayer2(sim);

  fillLastDsmHistograms(sim,5);
}

void DSMSimulator_2016::runFpeQtLayer(Crate &sim)
{
  //  qt32b_fpe_2009_a(fe001);
  //  qt32b_fpe_2009_a(fe002);
  //  qt32b_fpe_2009_a(fe003);
  //  qt32b_fpe_2009_a(fe004);

  /*  
      Board& fe101sim = sim.boardAt(FE101_BASE_ADDRESS);
      fe101sim.channels[0] = fe001.output;
      fe101sim.channels[1] = fe002.output;
      fe101sim.channels[2] = fe003.output;
      fe101sim.channels[3] = fe004.output;
  */

}

void DSMSimulator_2016::runFmsQtLayer(Crate &sim)
{
  for_each(qt1.boards,qt1.boards+12,qt32b_fms_2009_a);
  for_each(qt2.boards,qt2.boards+12,qt32b_fms_2009_a);
  for_each(qt3.boards,qt3.boards+12,qt32b_fms_2009_a);
  for_each(qt4.boards,qt4.boards+12,qt32b_fms_2009_a);

  Board& fm001sim = sim.boardAt(FM001_BASE_ADDRESS);
  Board& fm002sim = sim.boardAt(FM002_BASE_ADDRESS);
  Board& fm003sim = sim.boardAt(FM003_BASE_ADDRESS);
  Board& fm004sim = sim.boardAt(FM004_BASE_ADDRESS);

  Board& fm005sim = sim.boardAt(FM005_BASE_ADDRESS);
  Board& fm006sim = sim.boardAt(FM006_BASE_ADDRESS);
  Board& fm007sim = sim.boardAt(FM007_BASE_ADDRESS);
  Board& fm008sim = sim.boardAt(FM008_BASE_ADDRESS);

  Board& fm009sim = sim.boardAt(FM009_BASE_ADDRESS);
  Board& fm010sim = sim.boardAt(FM010_BASE_ADDRESS);
  Board& fm011sim = sim.boardAt(FM011_BASE_ADDRESS);
  Board& fm012sim = sim.boardAt(FM012_BASE_ADDRESS);

  for (int ch = 0; ch < 4; ++ch) {
    ((int*)fm001sim.channels)[ch] = qt1.boards[3-ch].output;
    ((int*)fm002sim.channels)[ch] = qt2.boards[3-ch].output;
    ((int*)fm003sim.channels)[ch] = qt3.boards[3-ch].output;
    ((int*)fm004sim.channels)[ch] = qt4.boards[3-ch].output;
    ((int*)fm005sim.channels)[ch] = qt1.boards[7-ch].output;
    ((int*)fm007sim.channels)[ch] = qt2.boards[7-ch].output;
    ((int*)fm009sim.channels)[ch] = qt3.boards[7-ch].output;
    ((int*)fm011sim.channels)[ch] = qt4.boards[7-ch].output;
  }

  for (int ch = 0; ch < 2; ++ch) {
    ((int*)fm006sim.channels)[ch] = qt1.boards[9-ch].output;
    ((int*)fm008sim.channels)[ch] = qt2.boards[9-ch].output;
    ((int*)fm010sim.channels)[ch] = qt3.boards[9-ch].output;
    ((int*)fm012sim.channels)[ch] = qt4.boards[9-ch].output;
  }

  for (int ch = 2; ch < 4; ++ch) {
    ((int*)fm006sim.channels)[ch] = 0xffffffff;
    ((int*)fm008sim.channels)[ch] = 0xffffffff;
    ((int*)fm010sim.channels)[ch] = 0xffffffff;
    ((int*)fm012sim.channels)[ch] = 0xffffffff;
  }
}

void DSMSimulator_2016::runFmsLayer0(Crate &sim)
{
  fms_fm001_2015_a(fm001);
  fms_fm001_2015_a(fm002);
  fms_fm001_2015_a(fm003);
  fms_fm001_2015_a(fm004);
  fms_fm005_2015_a(fm005);
  fms_fm005_2015_a(fm007);
  fms_fm005_2015_a(fm009);
  fms_fm005_2015_a(fm011);

  fms_fm006_2015_a(fm006);
  fms_fm006_2015_a(fm008);
  fms_fm006_2015_a(fm010);
  fms_fm006_2015_a(fm012);

  Board& fm101sim = sim.boardAt(FM101_BASE_ADDRESS);
  Board& fm102sim = sim.boardAt(FM102_BASE_ADDRESS);
  Board& fm103sim = sim.boardAt(FM103_BASE_ADDRESS);
  Board& fm104sim = sim.boardAt(FM104_BASE_ADDRESS);

  fm101sim.channels[0] = getbits(fm001.output, 0, 16);
  fm101sim.channels[1] = getbits(fm001.output, 16, 16);
  fm101sim.channels[2] = getbits(fm002.output, 0, 16);
  fm101sim.channels[3] = getbits(fm002.output, 16, 16);

  fm102sim.channels[0] = getbits(fm003.output, 0, 16);
  fm102sim.channels[1] = getbits(fm003.output, 16, 16);
  fm102sim.channels[2] = getbits(fm004.output, 0, 16);
  fm102sim.channels[3] = getbits(fm004.output, 16, 16);

  fm103sim.channels[0] = getbits(fm005.output, 0, 16);
  fm103sim.channels[1] = getbits(fm005.output, 16, 16);
  fm103sim.channels[2] = getbits(fm006.output, 0, 16);
  fm103sim.channels[3] = getbits(fm006.output, 16, 16);
  fm103sim.channels[4] = getbits(fm007.output, 0, 16);
  fm103sim.channels[5] = getbits(fm007.output, 16, 16);
  fm103sim.channels[6] = getbits(fm008.output, 0, 16);
  fm103sim.channels[7] = getbits(fm008.output, 16, 16);
  
  fm104sim.channels[0] = getbits(fm009.output, 0, 16);
  fm104sim.channels[1] = getbits(fm009.output, 16, 16);
  fm104sim.channels[2] = getbits(fm010.output, 0, 16);
  fm104sim.channels[3] = getbits(fm010.output, 16, 16);
  fm104sim.channels[4] = getbits(fm011.output, 0, 16);
  fm104sim.channels[5] = getbits(fm011.output, 16, 16);
  fm104sim.channels[6] = getbits(fm012.output, 0, 16);
  fm104sim.channels[7] = getbits(fm012.output, 16, 16);
  
}
/*
void DSMSimulator_2016::runFpeLayer1(Crate &sim)
{
  mix_fe101_2009_a(fe101);
  Board& fp201sim = sim.boardAt(FP201_BASE_ADDRESS);
  fp201sim.channels[6] = 0xffff; // unused
  fp201sim.channels[7] = fe101.output;
}
*/
void DSMSimulator_2016::runFmsLayer1(Crate &sim)
{
  fms_fm101_2015_a(fm101);
  fms_fm101_2015_a(fm102);
  fms_fm103_2015_a(fm103);
  fms_fm103_2015_a(fm104);

  Board& fp201sim = sim.boardAt(FP201_BASE_ADDRESS);

  fp201sim.channels[0] = getbits(fm102.output, 0, 16);
  fp201sim.channels[1] = getbits(fm102.output, 16, 16);
  fp201sim.channels[2] = getbits(fm103.output, 0, 16);
  fp201sim.channels[3] = getbits(fm103.output, 16, 16);
  fp201sim.channels[4] = getbits(fm104.output, 0, 16);
  fp201sim.channels[5] = getbits(fm104.output, 16, 16);
  fp201sim.channels[6] = getbits(fm101.output, 0, 16);
  fp201sim.channels[7] = getbits(fm101.output, 16, 16);
}

void DSMSimulator_2016::runFmsLayer2(Crate &sim)
{
  l1_fp201_2015_a(fp201);
  Board& ld301sim = sim.boardAt(LD301_BASE_ADDRESS);
  ld301sim.channels[5] = fp201.output;
}

void DSMSimulator_2016::writeBemcLayer0ToBemcLayer1(Crate& sim)
{
  Board& bc101sim = sim.boardAt(BC101_BASE_ADDRESS);
  Board& bc102sim = sim.boardAt(BC102_BASE_ADDRESS);
  Board& bc103sim = sim.boardAt(BC103_BASE_ADDRESS);
  Board& bc104sim = sim.boardAt(BC104_BASE_ADDRESS);
  Board& bc105sim = sim.boardAt(BC105_BASE_ADDRESS);
  Board& bc106sim = sim.boardAt(BC106_BASE_ADDRESS);

  bc101sim.channels[0] = be001.output;
  bc101sim.channels[1] = bw001.output;
  bc101sim.channels[2] = be002.output;
  bc101sim.channels[3] = bw002.output;
  bc101sim.channels[4] = be003.output >> 16 & 0xffff; // Out 0-15
  bc101sim.channels[5] = bw003.output & 0xffff; // Out 0-15

  bc102sim.channels[0] = be003.output & 0xffff; // Out 16-31
  bc102sim.channels[1] = bw003.output >> 16 & 0xffff; // Out 16-31
  bc102sim.channels[2] = be004.output;
  bc102sim.channels[3] = bw004.output;
  bc102sim.channels[4] = be005.output;
  bc102sim.channels[5] = bw005.output;

  bc103sim.channels[0] = be006.output;
  bc103sim.channels[1] = bw006.output;
  bc103sim.channels[2] = be007.output;
  bc103sim.channels[3] = bw007.output;
  bc103sim.channels[4] = be008.output >> 16 & 0xffff; // Out 0-15
  bc103sim.channels[5] = bw008.output & 0xffff; // Out 0-15

  bc104sim.channels[0] = be008.output & 0xffff; // Out 16-31
  bc104sim.channels[1] = bw008.output >> 16 & 0xffff; // Out 16-31
  bc104sim.channels[2] = be009.output;
  bc104sim.channels[3] = bw009.output;
  bc104sim.channels[4] = be010.output;
  bc104sim.channels[5] = bw010.output;

  bc105sim.channels[0] = be011.output;
  bc105sim.channels[1] = bw011.output;
  bc105sim.channels[2] = be012.output;
  bc105sim.channels[3] = bw012.output;
  bc105sim.channels[4] = be013.output >> 16 & 0xffff; // Out 0-15
  bc105sim.channels[5] = bw013.output & 0xffff; // Out 0-15

  bc106sim.channels[0] = be013.output & 0xffff; // Out 16-31
  bc106sim.channels[1] = bw013.output >> 16 & 0xffff; // Out 16-31
  bc106sim.channels[2] = be014.output;
  bc106sim.channels[3] = bw014.output;
  bc106sim.channels[4] = be015.output;
  bc106sim.channels[5] = bw015.output;
}

void DSMSimulator_2016::writeEemcLayer0ToEemcLayer1(Crate& sim)
{
  Board& ee101sim = sim.boardAt(EE101_BASE_ADDRESS);
  Board& ee102sim = sim.boardAt(EE102_BASE_ADDRESS);

  ee101sim.channels[0] = ee001.output;
  ee101sim.channels[1] = ee002.output & 0xffff; // Out 0-15
  ee101sim.channels[2] = ee002.output >> 16 & 0xffff; // Out 16-31
  ee101sim.channels[3] = ee003.output;
  ee101sim.channels[4] = ee004.output;
  ee101sim.channels[5] = ee005.output & 0xffff; // Out 0-15

  ee102sim.channels[0] = ee005.output >> 16 & 0xffff; // Out 16-31
  ee102sim.channels[1] = ee006.output;
  ee102sim.channels[2] = ee007.output;
  ee102sim.channels[3] = ee008.output & 0xffff; // Out 0-15
  ee102sim.channels[4] = ee008.output >> 16 & 0xffff; // Out 16-31
  ee102sim.channels[5] = ee009.output;
}

void DSMSimulator_2016::writeBemcLayer1ToEmcLayer2(Crate& sim)
{
  Board& em201sim = sim.boardAt(EM201_BASE_ADDRESS);
  Board& em202sim = sim.boardAt(EM202_BASE_ADDRESS);

  em201sim.channels[0] = bc101.output & 0xffff;
  em201sim.channels[1] = bc102.output & 0xffff;
  em201sim.channels[2] = bc103.output & 0xffff;
  em201sim.channels[3] = bc104.output & 0xffff;
  em201sim.channels[4] = bc105.output & 0xffff;
  em201sim.channels[5] = bc106.output & 0xffff;

  em202sim.channels[0] = bc101.output >> 16 & 0xffff;
  em202sim.channels[1] = bc102.output >> 16 & 0xffff;
  em202sim.channels[2] = bc103.output >> 16 & 0xffff;
  em202sim.channels[3] = bc104.output >> 16 & 0xffff;
  em202sim.channels[4] = bc105.output >> 16 & 0xffff;
  em202sim.channels[5] = bc106.output >> 16 & 0xffff;
}

void DSMSimulator_2016::writeEemcLayer1ToEmcLayer2(Crate& sim)
{
  Board& em201sim = sim.boardAt(EM201_BASE_ADDRESS);

  em201sim.channels[6] = ee101.output;
  em201sim.channels[7] = ee102.output;
}

void DSMSimulator_2016::writeEmcLayer2ToLastDsm(Crate& sim)
{
  Board& ld301sim = sim.boardAt(LD301_BASE_ADDRESS);

  ld301sim.channels[3] = em201.output;
}
void DSMSimulator_2016::bookFmsLayer0Histograms()
{
  void labelFM001(TH2F *h);
  void labelFM005(TH2F *h);
  void labelFM006(TH2F *h);

  mFM001 = new TH2F("mFM001", "FM001;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM001(mFM001);
  mFM002 = new TH2F("mFM002", "FM002;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM001(mFM002);
  mFM003 = new TH2F("mFM003", "FM003;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM001(mFM003);
  mFM004 = new TH2F("mFM004", "FM004;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM001(mFM004);

  mFM005 = new TH2F("mFM005", "FM005;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM005(mFM005);
  mFM007 = new TH2F("mFM007", "FM007;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM005(mFM007);
  mFM009 = new TH2F("mFM009", "FM009;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM005(mFM009);
  mFM011 = new TH2F("mFM011", "FM011;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM005(mFM011);

  mFM006 = new TH2F("mFM006", "FM006;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM006(mFM006);
  mFM008 = new TH2F("mFM008", "FM008;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM006(mFM008);
  mFM010 = new TH2F("mFM010", "FM010;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM006(mFM010);
  mFM012 = new TH2F("mFM012", "FM012;chn;Sum", 8, 0, 8, 2048, 0, 2048);
  labelFM006(mFM012);
}
void labelFM001(TH2F *h)
{
  const char *QT[4] = {"D", "C", "B", "A"};
  for(int ibin = 0; ibin < 8; ibin++){
    int iQT = ibin/2;
    h->GetXaxis()->SetBinLabel(ibin+1, Form("%s(%d:%d)", QT[iQT], 2*(ibin%2), 2*(ibin%2)+1));
  }
}
void labelFM005(TH2F *h)
{
  const char *QT[4] = {"J", "I", "H", "G"};
  for(int ibin = 0; ibin < 8; ibin++){
    int iQT = ibin/2;
    h->GetXaxis()->SetBinLabel(ibin+1, Form("%s(%d:%d)", QT[iQT], 2*(ibin%2), 2*(ibin%2)+1));
  }
}
void labelFM006(TH2F *h)
{
  const char *QT[4] = {"F", "E", "EMPTY", "EMPTY"};
  for(int ibin = 0; ibin < 4 ; ibin++){
    int iQT = ibin/2;
    h->GetXaxis()->SetBinLabel(ibin+1, Form("%s(%d:%d)", QT[iQT], 2*(ibin%2), 2*(ibin%2)+1));
  }
}
void DSMSimulator_2016::fillFmsLayer0Histograms()
{
  //
  //cout<<"A="<<fm001.channels[6]<<" B="<<fm001.channels[7]<<endl;
  for(int ichn = 0; ichn < 8; ichn++){
    mFM001->Fill(ichn, fm001.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM002->Fill(ichn, fm002.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM003->Fill(ichn, fm003.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM004->Fill(ichn, fm004.channels[ichn] & 0xfff);
  }
  //
  for(int ichn = 0; ichn < 8; ichn++){
    mFM005->Fill(ichn, fm005.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM007->Fill(ichn, fm007.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM009->Fill(ichn, fm009.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM011->Fill(ichn, fm011.channels[ichn] & 0xfff);
  }
  //
  for(int ichn = 0; ichn < 8; ichn++){
    mFM006->Fill(ichn, fm006.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM008->Fill(ichn, fm008.channels[ichn] &0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM010->Fill(ichn, fm010.channels[ichn] & 0xfff);
  }

  for(int ichn = 0; ichn < 8; ichn++){
    mFM012->Fill(ichn, fm012.channels[ichn] & 0xfff);
  }
}
void DSMSimulator_2016::bookFmsLayer1Histograms()
{
  void labelFM101(TH2F *h, TH1F *hs, TH2F *hjp);
  void labelFM103(int pos, TH2F *h, TH1F *hs, TH2F *hjp);

  const char *pos[2] = {"Top", "Bottom"};
  for(int ipos = 0; ipos < 2; ipos++){
    mFM101BS[ipos] = new TH2F(Form("mFM101BS_%d", ipos), Form("mFM101BS -- South -- %s -- FM00%d", pos[ipos], ipos+1), 4, 0, 4, 2, 0, 2);
    mFM101BS[ipos]->GetYaxis()->SetBinLabel(1, "0");
    mFM101BS[ipos]->GetYaxis()->SetBinLabel(2, "1");
    mFM101D[ipos] = new TH1F(Form("mFM101D_%d", ipos), Form("mFM101D -- South -- %s -- FM00%d", pos[ipos], ipos+1), 4096, 0, 4096);
    mFM101JP[ipos] = new TH2F(Form("mFM101JP_%d", ipos), Form("mFM101JP -- South -- %s -- FM00%d", pos[ipos], ipos+1), 2, 0, 2, 256 ,0, 256);
    labelFM101(mFM101BS[ipos], mFM101D[ipos], mFM101JP[ipos]);
    //
    mFM102BS[ipos] = new TH2F(Form("mFM102BS_%d", ipos), Form("mFM102BS -- North -- %s -- FM00%d", pos[ipos], ipos+3), 4, 0, 4, 2, 0, 2);
    mFM102BS[ipos]->GetYaxis()->SetBinLabel(1, "0");
    mFM102BS[ipos]->GetYaxis()->SetBinLabel(2, "1");
    mFM102D[ipos] = new TH1F(Form("mFM102D_%d", ipos), Form("mFM102D -- South -- %s -- FM00%d", pos[ipos], ipos+3), 4096,0, 4096);
    mFM102JP[ipos] = new TH2F(Form("mFM102JP_%d", ipos), Form("mFM102JP -- South -- %s -- FM00%d", pos[ipos], ipos+3), 2, 0, 2, 256 ,0, 256);
    labelFM101(mFM102BS[ipos], mFM102D[ipos], mFM102JP[ipos]);
  }

  for(int ipos = 0; ipos < 2; ipos++){
    mFM101BSsim[ipos] = new TH2F(Form("mFM101BSsim_%d", ipos), Form("mFM101BSsim -- South -- %s -- FM00%d", pos[ipos], ipos+1), 4, 0, 4, 3, -1, 2);
    mFM101BSsim[ipos]->GetYaxis()->SetBinLabel(1, "-1");
    mFM101BSsim[ipos]->GetYaxis()->SetBinLabel(2, "0");
    mFM101BSsim[ipos]->GetYaxis()->SetBinLabel(3, "1");

    mFM101Dsim[ipos] = new TH1F(Form("mFM101Dsim_%d", ipos), Form("mFM101Dsim -- South -- %s -- FM00%d", pos[ipos], ipos+1), 4096,-4095, 4096);
    mFM101JPsim[ipos] = new TH2F(Form("mFM101JPsim_%d", ipos), Form("mFM101JPsim -- South -- %s -- FM00%d", pos[ipos], ipos+1), 2, 0, 2, 256 , -255, 256);
    labelFM101(mFM101BSsim[ipos], mFM101Dsim[ipos], mFM101JPsim[ipos]);
    //
    mFM102BSsim[ipos] = new TH2F(Form("mFM102BSsim_%d", ipos), Form("mFM102BSsim -- North -- %s -- FM00%d", pos[ipos], ipos+3), 4, 0, 4, 3, -1, 2);
    mFM102BSsim[ipos]->GetYaxis()->SetBinLabel(1, "-1");
    mFM102BSsim[ipos]->GetYaxis()->SetBinLabel(2, "0");
    mFM102BSsim[ipos]->GetYaxis()->SetBinLabel(3, "1");
    mFM102Dsim[ipos] = new TH1F(Form("mFM102Dsim_%d", ipos), Form("mFM102Dsim -- South -- %s -- FM00%d", pos[ipos], ipos+3), 4096, -4095, 4096);
    mFM102JPsim[ipos] = new TH2F(Form("mFM102JPsim_%d", ipos), Form("mFM102JPsim -- South -- %s -- FM00%d", pos[ipos], ipos+3), 2, 0, 2, 256 , -255, 256);
    labelFM101(mFM102BSsim[ipos], mFM102Dsim[ipos], mFM102JPsim[ipos]);
  }

  const char *pos_2[4] = {"Top/Side", "Top", "Bottom/Side", "Bottom"};
  for(int ipos = 0; ipos < 4; ipos++){
    mFM103BS[ipos] = new TH2F(Form("mFM103BS_%d", ipos), Form("mFM103BS -- South -- %s --FM%3.3d", pos_2[ipos], ipos+5), 4, 0, 4, 2, 0, 2);
    mFM103BS[ipos]->GetYaxis()->SetBinLabel(1, "0");
    mFM103BS[ipos]->GetYaxis()->SetBinLabel(2, "1");

    mFM103J[ipos] = new TH1F(Form("mFM103J_%d", ipos), Form("mFM103J -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+5), 4096,0, 4096);
    mFM103JP[ipos] = new TH2F(Form("mFM103JP_%d", ipos), Form("mFM103JP -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+5), 2, 0, 2, 256 ,0, 256);
    labelFM103(ipos, mFM103BS[ipos], mFM103J[ipos], mFM103JP[ipos]);
    //
    mFM104BS[ipos] = new TH2F(Form("mFM104BS_%d", ipos), Form("mFM104BS -- North -- %s -- FM%3.3d", pos_2[ipos], ipos+9), 4, 0, 4, 2, 0, 2);
    mFM104BS[ipos]->GetYaxis()->SetBinLabel(1, "0");
    mFM104BS[ipos]->GetYaxis()->SetBinLabel(2, "1");

    mFM104J[ipos] = new TH1F(Form("mFM104J_%d", ipos), Form("mFM104J -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+9), 4096,0, 4096);
    mFM104JP[ipos] = new TH2F(Form("mFM104JP_%d", ipos), Form("mFM104JP -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+9), 2, 0, 2, 256 ,0, 256);
    labelFM103(ipos, mFM104BS[ipos], mFM104J[ipos], mFM104JP[ipos]);
  }

  for(int ipos = 0; ipos < 4; ipos++){
    mFM103BSsim[ipos] = new TH2F(Form("mFM103BSsim_%d", ipos), Form("mFM103BSsim -- South -- %s --FM0%3.3d", pos_2[ipos], ipos+5), 4, 0, 4, 3, -1, 2);
    mFM103BSsim[ipos]->GetYaxis()->SetBinLabel(1, "-1");
    mFM103BSsim[ipos]->GetYaxis()->SetBinLabel(2, "0");
    mFM103BSsim[ipos]->GetYaxis()->SetBinLabel(3, "1");

    mFM103Jsim[ipos] = new TH1F(Form("mFM103Jsim_%d", ipos), Form("mFM103Jsim -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+5), 4096, -4095, 4096);
    mFM103JPsim[ipos] = new TH2F(Form("mFM103JPsim_%d", ipos), Form("mFM103JPsim -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+5), 2, 0, 2, 256 , -255, 256);
    labelFM103(ipos, mFM103BSsim[ipos], mFM103Jsim[ipos], mFM103JPsim[ipos]);
    //
    mFM104BSsim[ipos] = new TH2F(Form("mFM104BSsim_%d", ipos), Form("mFM104BSsim -- North -- %s -- FM%3.3d", pos_2[ipos], ipos+9), 4, 0, 4, 3, -1, 2);
    mFM104BSsim[ipos]->GetYaxis()->SetBinLabel(1, "-1");
    mFM104BSsim[ipos]->GetYaxis()->SetBinLabel(2, "0");
    mFM104BSsim[ipos]->GetYaxis()->SetBinLabel(3, "1");

    mFM104Jsim[ipos] = new TH1F(Form("mFM104Jsim_%d", ipos), Form("mFM104Jsim -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+9), 4096, -4096, 4096);
    mFM104JPsim[ipos] = new TH2F(Form("mFM104JPsim_%d", ipos), Form("mFM104JPsim -- South -- %s -- FM%3.3d", pos_2[ipos], ipos+9), 2, 0, 2, 256 ,-255, 256);
    labelFM103(ipos, mFM104BSsim[ipos], mFM104Jsim[ipos], mFM104JPsim[ipos]);
  }

}
void labelFM101(TH2F *hbs, TH1F *hs, TH2F *hjp)
{
  hbs->GetXaxis()->SetBinLabel(1, "BS3");
  hbs->GetXaxis()->SetBinLabel(2, "BS2");
  hbs->GetXaxis()->SetBinLabel(3, "BS1-BCD");
  hbs->GetXaxis()->SetBinLabel(4, "BS1-A");
  //  hbs->GetYaxis()->SetBinLabel(1, "0");
  //  hbs->GetYaxis()->SetBinLabel(2, "1");

  hs->GetXaxis()->SetTitle("D(23)");

  hjp->GetXaxis()->SetBinLabel(1, "JP-AB");
  hjp->GetXaxis()->SetBinLabel(2, "JP-CD");
}
void labelFM103(int pos, TH2F *hbs, TH1F *hs, TH2F *hjp)
{
  if(pos%2){
    hbs->GetXaxis()->SetBinLabel(1, "BS3");
    hbs->GetXaxis()->SetBinLabel(2, "BS2");
    hbs->GetXaxis()->SetBinLabel(3, "BS1-E");
    hbs->GetXaxis()->SetBinLabel(4, "BS1-F");
    //    hbs->GetYaxis()->SetBinLabel(1, "0");
    //    hbs->GetYaxis()->SetBinLabel(2, "1");

    hs->GetXaxis()->SetTitle("Unused");

    hjp->GetXaxis()->SetBinLabel(1, "JP-EF");
    hjp->GetXaxis()->SetBinLabel(2, "Unused");
  }else{
    hbs->GetXaxis()->SetBinLabel(1, "BS3");
    hbs->GetXaxis()->SetBinLabel(2, "BS2");
    hbs->GetXaxis()->SetBinLabel(3, "BS1");
    hbs->GetXaxis()->SetBinLabel(4, "Unused");
    //    hbs->GetYaxis()->SetBinLabel(1, "0");
    //    hbs->GetYaxis()->SetBinLabel(2, "1");
    
    hs->GetXaxis()->SetTitle("J(23)");
    
    hjp->GetXaxis()->SetBinLabel(1, "JP-GH");
    hjp->GetXaxis()->SetBinLabel(2, "JP-IJ");
  }
}
void DSMSimulator_2016::fillFmsLayer1Histograms()
{
  for(int ichn = 0; ichn < 2; ichn++){
    int fm00xout = fm101.channels[2*ichn] | fm101.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      mFM101BS[ichn]->Fill(ibit, bs);
    }
    int d = getbits(fm00xout, 4, 12);
    mFM101D[ichn]->Fill(d);
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      mFM101JP[ichn]->Fill(ibit, jp);
    }
  }

  for(int ichn = 0; ichn < 2; ichn++){
    int fm00xout = fm102.channels[2*ichn] | fm102.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      mFM102BS[ichn]->Fill(ibit, bs);
    }
    int d = getbits(fm00xout, 4, 12);
    mFM102D[ichn]->Fill(d);
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      mFM102JP[ichn]->Fill(ibit, jp);
    }
  }

  for(int ichn = 0; ichn < 4; ichn++){
    int fm00xout = fm103.channels[2*ichn] | fm103.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      mFM103BS[ichn]->Fill(ibit, bs);
    }
    int j = getbits(fm00xout, 4, 12);
    mFM103J[ichn]->Fill(j);
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      mFM103JP[ichn]->Fill(ibit, jp);
    }
  }
  
  for(int ichn = 0; ichn < 4; ichn++){
    int fm00xout = fm104.channels[2*ichn] | fm104.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      mFM104BS[ichn]->Fill(ibit, bs);
    }
    int j = getbits(fm00xout, 4, 12);
    mFM104J[ichn]->Fill(j);
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      mFM104JP[ichn]->Fill(ibit, jp);
    }
  }
}
void DSMSimulator_2016::fillFmsLayer1Histograms(const Crate& sim)
{
  fillFmsLayer1Histograms();
  //fm101
  const Board fm101sim = sim.boardAt(FM101_BASE_ADDRESS);
  for(int ichn = 0; ichn < 2; ichn++){
    int fm00xout = fm101.channels[2*ichn] | fm101.channels[2*ichn+1] << 16;
    int fm00xoutsim = fm101sim.channels[2*ichn] | fm101sim.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      int bs_sim = btest(fm00xoutsim, ibit);
      if(bs-bs_sim) {
        mFM101BSsim[ichn]->Fill(ibit, bs-bs_sim);
//        if(ibit == 2) cout<<"bs1_bcd="<<bs<<" bs1_bcd="<<bs_sim<<endl;
//
      }
    }
    int d = getbits(fm00xout, 4, 12);
    int d_sim = getbits(fm00xoutsim, 4, 12);
    if(d-d_sim){
      mFM101Dsim[ichn]->Fill(d-d_sim);
//	cout<<d-d_sim<<" d="<<d<<" d_sim="<<d_sim<<endl;
    }
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      int jp_sim = getbits(fm00xoutsim, 8*ibit+16, 8);
      if(jp-jp_sim) mFM101JPsim[ichn]->Fill(ibit, jp-jp_sim);
    }
  }
  //fm102
  const Board fm102sim = sim.boardAt(FM102_BASE_ADDRESS);
  for(int ichn = 0; ichn < 2; ichn++){
    int fm00xout = fm102.channels[2*ichn] | fm102.channels[2*ichn+1] << 16;
    int fm00xoutsim = fm102sim.channels[2*ichn] | fm102sim.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      int bs_sim = btest(fm00xoutsim, ibit);
      if(bs-bs_sim) mFM102BSsim[ichn]->Fill(ibit, bs-bs_sim);
    }
    int d = getbits(fm00xout, 4, 12);
    int d_sim = getbits(fm00xoutsim, 4, 12);
    if(d-d_sim) mFM102Dsim[ichn]->Fill(d-d_sim);
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      int jp_sim = getbits(fm00xoutsim, 8*ibit+16, 8);
      if(jp-jp_sim) mFM102JPsim[ichn]->Fill(ibit, jp-jp_sim);
    }
  }
  //fm103
  const Board fm103sim = sim.boardAt(FM103_BASE_ADDRESS);
  for(int ichn = 0; ichn < 4; ichn++){
    int fm00xout = fm103.channels[2*ichn] | fm103.channels[2*ichn+1] << 16;
    int fm00xoutsim = fm103sim.channels[2*ichn] | fm103sim.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      int bs_sim = btest(fm00xoutsim, ibit);
      if(bs-bs_sim) mFM103BSsim[ichn]->Fill(ibit, bs-bs_sim);
    }
    int j = getbits(fm00xout, 4, 12);
    int j_sim = getbits(fm00xoutsim, 4, 12);
    if(j-j_sim) mFM103Jsim[ichn]->Fill(j-j_sim);
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      int jp_sim = getbits(fm00xoutsim, 8*ibit+16, 8);
      if(jp-jp_sim) mFM103JPsim[ichn]->Fill(ibit, jp-jp_sim);
    }
  }
  //fm104
  
  const Board fm104sim = sim.boardAt(FM104_BASE_ADDRESS);
  for(int ichn = 0; ichn < 4; ichn++){
    int fm00xout = fm104.channels[2*ichn] | fm104.channels[2*ichn+1] << 16;
    int fm00xoutsim = fm104sim.channels[2*ichn] | fm104sim.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 4; ibit++){
      int bs = btest(fm00xout, ibit);
      int bs_sim = btest(fm00xoutsim, ibit);
      if(bs-bs_sim) mFM104BSsim[ichn]->Fill(ibit, bs-bs_sim);
    }
    int j = getbits(fm00xout, 4, 12);
    int j_sim = getbits(fm00xoutsim, 4, 12);
    if(j-j_sim) mFM104Jsim[ichn]->Fill(j-j_sim);
    for(int ibit = 0; ibit < 2; ibit++){
      int jp = getbits(fm00xout, 8*ibit+16, 8);
      int jp_sim = getbits(fm00xoutsim, 8*ibit+16, 8);
      if(jp-jp_sim) mFM104JPsim[ichn]->Fill(ibit, jp-jp_sim);
    }
  }
  
}
void DSMSimulator_2016::bookFmsLayer2Histograms()
{
  void labelFP201(TH2F *h, TH2F *hjp);
  const char *size[2] = {"small", "large"};
  const char *pos[2] = {"south", "north"};
  for(int ichn = 0; ichn < 4; ichn++){
    int ii = ichn+2;
    if(ii > 4) ii = ii%4;
    int isize = (ii-1)/2;
    int ipos = ii%2;
    mFP201BS[ichn] = new TH2F(Form("mFP201BS_FM10%d", ii), Form("mFP201BS_FM10%d %s %s", ii, size[isize], pos[ipos]), 5, 0, 5, 2, 0, 2);
    mFP201BS[ichn]->GetYaxis()->SetBinLabel(1, "0");
    mFP201BS[ichn]->GetYaxis()->SetBinLabel(2, "1");
    mFP201JP[ichn] = new TH2F(Form("mFP201JP_FM10%d", ii), Form("mFP201JP_FM10%d %s %s", ii, size[isize], pos[ipos]), 3, 0, 3, 256, 0, 256);
    labelFP201(mFP201BS[ichn], mFP201JP[ichn]);
    //simu
    mFP201BSsim[ichn] = new TH2F(Form("mFP201BSsim_FM10%d", ii), Form("mFP201BSsim_FM10%d %s %s", ii, size[isize], pos[ipos]), 5, 0, 5, 3, -1, 2);
    mFP201BSsim[ichn]->GetYaxis()->SetBinLabel(1, "-1");
    mFP201BSsim[ichn]->GetYaxis()->SetBinLabel(2, "0");
    mFP201BSsim[ichn]->GetYaxis()->SetBinLabel(3, "1");
    mFP201JPsim[ichn] = new TH2F(Form("mFP201JPsim_FM10%d", ii), Form("mFP201JPsim_FM10%d %s %s", ii, size[isize], pos[ipos]), 3, 0, 3, 256, -255, 256);
    labelFP201(mFP201BSsim[ichn], mFP201JPsim[ichn]);
  }
}
void labelFP201(TH2F *hbs, TH2F *hjp)
{
  hbs->GetXaxis()->SetBinLabel(1, "BS3");
  hbs->GetXaxis()->SetBinLabel(2, "BS2");
  hbs->GetXaxis()->SetBinLabel(3, "BS1-T");
  hbs->GetXaxis()->SetBinLabel(4, "BS1-M");
  hbs->GetXaxis()->SetBinLabel(5, "BS1-B");

  hjp->GetXaxis()->SetBinLabel(1, "JP-T");
//  hjp->GetXaxis()->SetBinLabel(2, "Unused");
  hjp->GetXaxis()->SetBinLabel(2, "JP-M");
  hjp->GetXaxis()->SetBinLabel(3, "JP-B");
}
void DSMSimulator_2016::fillFmsLayer2Histograms()
{
  for(int ichn = 0; ichn < 4; ichn++){
    int fm10xout = fp201.channels[2*ichn] | fp201.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 5; ibit++){
      int bs = btest(fm10xout, ibit);
      if((ichn == 0 || ichn == 3) && ibit == 0) bs = btest(fm10xout, 13);
      mFP201BS[ichn]->Fill(ibit, bs);
    }
    for(int ibit = 0; ibit < 3; ibit++){
      int jp = getbits(fm10xout, ibit*8+8, 8);
      if(ibit == 0) jp = getbits(fm10xout, ibit*8+5, 8);
      mFP201JP[ichn]->Fill(ibit, jp);
    }
  }
}
void DSMSimulator_2016::fillFmsLayer2Histograms(const Crate &sim)
{
  fillFmsLayer2Histograms();
  const Board fp201sim = sim.boardAt(FP201_BASE_ADDRESS);  
  for(int ichn = 0; ichn < 4; ichn++){
    int fm10xout = fp201.channels[2*ichn] | fp201.channels[2*ichn+1] << 16;
    int fm10xoutsim = fp201sim.channels[2*ichn] | fp201sim.channels[2*ichn+1] << 16;
    for(int ibit = 0; ibit < 5; ibit++){
      int bs = btest(fm10xout, ibit);
      if((ichn == 0 || ichn == 3) && ibit == 0) bs = btest(fm10xout, 13);
      int bs_sim = btest(fm10xoutsim, ibit);
      if(bs-bs_sim){
         mFP201BSsim[ichn]->Fill(ibit, bs-bs_sim);
	 //         cout<<"error: "<<"ichn="<<ichn<<" ibit="<<ibit<<" bs="<<bs<<" bs_sim="<<bs_sim<<endl;
      }
    }
    for(int ibit = 0; ibit < 3; ibit++){
      int jp = getbits(fm10xout, ibit*8+8, 8);
      if(ibit == 0) jp = getbits(fm10xout, ibit*8+5, 8);
      int jp_sim = getbits(fm10xoutsim, ibit*8+8, 8);
      if(ibit == 0) jp_sim = getbits(fm10xoutsim, ibit*8+5, 8);
      if(jp-jp_sim){
         mFP201JPsim[ichn]->Fill(ibit, jp-jp_sim);
//         cout<<"error: "<<"ichn="<<ichn<<" ibit="<<ibit<<" jp="<<jp<<" jp_sim="<<jp_sim<<endl;
       }
    }
  }    
}
void DSMSimulator_2016::bookFmsQtHistograms()
{
  hQT1ADC = new TH2F("hQT1ADC","Input to QT1 crate (south-top);channel;ADC",384,0,384,256,0,4096);
  hQT2ADC = new TH2F("hQT2ADC","Input to QT2 crate (south-bottom);channel;ADC",384,0,384,256,0,4096);
  hQT3ADC = new TH2F("hQT3ADC","Input to QT3 crate (north-top);channel;ADC",384,0,384,256,0,4096);
  hQT4ADC = new TH2F("hQT4ADC","Input to QT4 crate (north-bottom);channel;ADC",384,0,384,256,0,4096);

}
/*
void DSMSimulator_2016::bookFpdHistograms()
{
  hFE001 = new TH2F("hFE001","Input to FE001 QT board;channel;ADC",32,0,32,256,0,1024);
  hFE002 = new TH2F("hFE002","Input to FE002 QT board;channel;ADC",32,0,32,256,0,1024);
  hFE003 = new TH2F("hFE003","Input to FE003 QT board;channel;ADC",32,0,32,256,0,1024);
  hFE004 = new TH2F("hFE004","Input to FE004 QT board;channel;ADC",32,0,32,256,0,1024);

  hQT1ADC = new TH2F("hQT1ADC","Input to QT1 crate (south-top);channel;ADC",384,0,384,256,0,4096);
  hQT2ADC = new TH2F("hQT2ADC","Input to QT2 crate (south-bottom);channel;ADC",384,0,384,256,0,4096);
  hQT3ADC = new TH2F("hQT3ADC","Input to QT3 crate (north-top);channel;ADC",384,0,384,256,0,4096);
  hQT4ADC = new TH2F("hQT4ADC","Input to QT4 crate (north-bottom);channel;ADC",384,0,384,256,0,4096);

  
  //  hFE101 = new TH2F("hFE101","Input to FPE L1 DSM;;ADC sum",4,0,4,1024,0,4096);
  //  hFE101Diff = new TH2F("hFE101Diff","Input to FPE L1 DSM;;ADC sum - simulated",4,0,4,1024,-512,512);
  //  hFE101Corr = new TH2F("hFE101Corr",";DSM ADC sum;Simulated ADC sum",256,0,1024,256,0,1024);
  //  labelFpeLayer1Histogram(hFE101);
  //  labelFpeLayer1Histogram(hFE101Diff);
  
}

void labelFpeLayer1Histogram(TH2F* h)
{
  h->GetXaxis()->SetBinLabel(1,"FE001");
  h->GetXaxis()->SetBinLabel(2,"FE002");
  h->GetXaxis()->SetBinLabel(3,"FE003");
  h->GetXaxis()->SetBinLabel(4,"FE004");
}

void DSMSimulator_2016::fillFpeQtLayerHistograms()
{
  for (int ch = 0; ch < 32; ++ch) {
    hFE001->Fill(ch,fe001.channels[ch]);
    hFE002->Fill(ch,fe002.channels[ch]);
    hFE003->Fill(ch,fe003.channels[ch]);
    hFE004->Fill(ch,fe004.channels[ch]);
  }
}
*/ 
void DSMSimulator_2016::fillFmsQtLayerHistograms()
{
  const int NSLOTS = 12;
  const int NCHANNELS = 32;

  for (int slot = 0; slot < NSLOTS; ++slot) {
    for (int ch = 0; ch < NCHANNELS; ++ch) {
      int bin = slot*NCHANNELS+ch;
      int adc1 = qt1.boards[slot].channels[ch];
      int adc2 = qt2.boards[slot].channels[ch];
      int adc3 = qt3.boards[slot].channels[ch];
      int adc4 = qt4.boards[slot].channels[ch];
      if (adc1) hQT1ADC->Fill(bin,adc1);
      if (adc2) hQT2ADC->Fill(bin,adc2);
      if (adc3) hQT3ADC->Fill(bin,adc3);
      if (adc4) hQT4ADC->Fill(bin,adc4);
    }
  }
}
/*
void DSMSimulator_2016::fillFpeLayer1Histograms(const Crate& sim)
{
  int* fe101channels = (int*)fe101.channels;
  const Board& fe101sim = sim.boardAt(FE101_BASE_ADDRESS);
  int* fe101simchannels = (int*)fe101sim.channels;
  for (int ch = 0; ch < 4; ++ch) {
    int fe001out = fe101channels[ch];
    int sum = getbits(fe001out,0,17);
    //cout << sum << ' ';
    hFE101->Fill(ch,sum);
    int fe001simout = fe101simchannels[ch];
    int sumsim = getbits(fe001simout,0,17);
    hFE101Corr->Fill(sum,sumsim);
    if (int diff = sum-sumsim) hFE101Diff->Fill(ch,diff);
  }
 
  //cout << endl;
}
void DSMSimulator_2016::labelFpeLayer1Histogram(TH2F* h)
{
  h->GetXaxis()->SetBinLabel(1,"FE001");
  h->GetXaxis()->SetBinLabel(2,"FE002");
  h->GetXaxis()->SetBinLabel(3,"FE003");
  h->GetXaxis()->SetBinLabel(4,"FE004");
}
*/
void DSMSimulator_2016::runVtxBranch()
//void DSMSimulator_2016::runVtxBranch(const TriggerDataBlk& event)
{
  fillBB001Histograms();
  fillZD001Histograms();
  fillVP001Histograms();
  //fillZP001Histograms();
  Crate sim;
  runVtxLayer0(sim);
  fillBB101Histograms(sim);
  fillBB102Histograms(sim);
  fillZD101Histograms(sim);
  fillVP101Histograms(sim);
  runVtxLayer1(sim);
  fillVT201Histograms(sim);
  runVtxLayer2(sim);
  //fillVtxHistograms(sim);
  //  Crate sim;
  //  uriteVtxLayer2ToLastDsm(sim);
  fillLastDsmHistograms(sim,1);
}

void DSMSimulator_2016::runVtxLayer0(Crate& sim)
{
  qt32b_l0_v6_d(bb001, bb001_slew);
  qt32b_l0_v6_d(bb002, bb002_slew);
  qt32b_l0_v5_f(bb003);
  //  qt32b_l0_v6_d(vp001);
  //  qt32b_l0_v6_d(vp002);
  qt32b_l0_v7_6(vp001, vp001_slew);
  qt32b_l0_v7_6(vp002, vp002_slew);
  //  qt32b_10_v6_2(zd001);
 //  qt32b_l0_v6_a(zd001);
 qt32b_l0_v6_f(zd001);

  Board& bb101sim = sim.boardAt(BB101_BASE_ADDRESS);
  bb101sim.channels[0] = bb001.output & 0xffff;
  bb101sim.channels[1] = bb001.output >> 16 & 0xffff;

  bb101sim.channels[2] = bb002.output & 0xffff;
  bb101sim.channels[3] = bb002.output >> 16 & 0xffff;

  Board& bb102sim = sim.boardAt(BB102_BASE_ADDRESS);
  //cout<<"bb003.output:"<<hex<<bb003.output<<endl;
  bb102sim.channels[0] = bb003.output & 0xffff;
  bb102sim.channels[1] = bb003.output >> 16 & 0xffff;

  Board& vp101sim = sim.boardAt(VP101_BASE_ADDRESS);
  vp101sim.channels[4] = vp001.output & 0xffff;
  vp101sim.channels[5] = vp001.output >> 16 & 0xffff;

  vp101sim.channels[6] = vp002.output & 0xffff;
  vp101sim.channels[7] = vp002.output >> 16 & 0xffff;

  Board& zd101sim = sim.boardAt(ZD101_BASE_ADDRESS);
  zd101sim.channels[0] = zd001.output & 0xffff;
  zd101sim.channels[1] = zd001.output >> 16 & 0xffff;
}

void DSMSimulator_2016::runVtxLayer1(Crate &sim)
{
  //bbc_bb101_2009_a(bb101);
  bbc_bb101_2016_a(bb101);
  bbc_bb102_2010_b(bb102);
  bbc_vp101_2016_a(vp101);
  bbc_zd101_2016_a(zd101);

  Board& vt201sim = sim.boardAt(VT201_BASE_ADDRESS);
  vt201sim.channels[0] = bb101.output;
  vt201sim.channels[1] = bb102.output;
  vt201sim.channels[2] = zd101.output;
  vt201sim.channels[4] = vp101.output;
}

void DSMSimulator_2016::runVtxLayer2(Crate &sim)
{
//  l1_vt201_2015_a(vt201);
//  l1_vt201_2015_b(vt201);
//  l1_vt201_2015_c(vt201);
//  l1_vt201_2014_a(vt201);
  l1_vt201_2016_b(vt201);
//  l1_vt201_2016_a(vt201);
  Board& ld301sim = sim.boardAt(LD301_BASE_ADDRESS);
  ld301sim.channels[1] = vt201.output;
}

void DSMSimulator_2016::fillVT201Histograms()
{
  int bb101out = vt201.channels[0];
  mBbcSmallTacDiff->Fill(getbits(bb101out, 0, 13));
  for(int bit = 13; bit < 16; bit++){
    mBbcSmallAdcSumTh->Fill(bit-13, btest(bb101out, bit));
  }
			 
  int bb102out = vt201.channels[1];
  mBbcLargeTacDiff->Fill(getbits(bb102out, 0, 3));
  for(int bit = 14; bit < 16; bit++){
    mBbcLargeAdcSumTh->Fill(bit-14, btest(bb102out, bit));
  }
  
  int zd101out = vt201.channels[2];
  mZdcTacDiff->Fill(getbits(zd101out, 0, 9));
  for(int bit = 9; bit < 16; bit++){
    mZdcAdcSumTh->Fill(bit-9, btest(zd101out, bit));
  }

  int vp101out = vt201.channels[4];
  for(int ib = 0; ib < 3; ib++){
    mVpdTacDiff->Fill(ib, btest(vp101out, ib));
  }
  for(int bit = 14; bit < 16; bit++){
    mVpdAdcSumTh->Fill(bit-14, btest(vp101out, bit));
  }

}
void DSMSimulator_2016::fillVT201Histograms(const Crate& sim)
{
  fillVT201Histograms();

  int bb101out = vt201.channels[0];
  int bb102out = vt201.channels[1];
  int zd101out = vt201.channels[2];
  int vp101out = vt201.channels[4];

  //
  const Board& vt201sim = sim.boardAt(VT201_BASE_ADDRESS);
  int bb101outsim = vt201sim.channels[0];
  if(getbits(bb101out, 0, 13) - getbits(bb101outsim, 0, 13)) mBbcSmallTacDiffVsSimu->Fill(getbits(bb101out, 0, 13), getbits(bb101outsim, 0, 13));
  for(int bit = 13; bit < 16; bit++){
    if(btest(bb101out, bit) - btest(bb101outsim, bit)) mBbcSmallAdcSumThSimu->Fill(bit-13, btest(bb101out, bit)-btest(bb101outsim, bit));
  }
			 
  int bb102outsim = vt201sim.channels[1];
  if(getbits(bb102out, 0, 3) - getbits(bb102outsim, 0, 3)) mBbcLargeTacDiffVsSimu->Fill(getbits(bb102out, 0, 3), getbits(bb102outsim, 0, 3));
  for(int bit = 14; bit < 16; bit++){
    if(btest(bb102out, bit) - btest(bb102out, bit)) mBbcLargeAdcSumThSimu->Fill(bit-14, btest(bb102out, bit)-btest(bb102outsim, bit));
  }
  
  int zd101outsim = vt201sim.channels[2];
  if(getbits(zd101out, 0, 9) - getbits(zd101outsim, 0, 9)) mZdcTacDiffVsSimu->Fill(getbits(zd101out, 0, 9), getbits(zd101outsim, 0, 9));
  for(int bit = 9; bit < 16; bit++){
    if(int diff = btest(zd101out, bit) - btest(zd101outsim, bit)) mZdcAdcSumThSimu->Fill(bit-9, diff);
  }

  int vp101outsim = vt201sim.channels[4];
  for(int ib = 0; ib < 3; ib++){
    if(btest(vp101out, ib) - btest(vp101outsim, ib)){
      mVpdTacDiffVsSimu->Fill(ib, btest(vp101out, ib) - btest(vp101outsim, ib));
    }
  }
  for(int bit = 14; bit < 16; bit++){
    if(btest(vp101out, bit) - btest(vp101outsim, bit)) mVpdAdcSumThSimu->Fill(bit, btest(vp101out, bit)-btest(vp101outsim, bit));
  }
  
}
void DSMSimulator_2016::fillBB101Histograms()
{
  int bb001out = bb101.channels[0] | bb101.channels[1] << 16; // east
  int bb002out = bb101.channels[2] | bb101.channels[3] << 16; // west

  int bbcSmallEastAdcSum = getbits(bb001out,0,16);
  int bbcSmallEastTacMax = getbits(bb001out,16,12);
  int bbcSmallWestAdcSum = getbits(bb002out,0, 16);
  int bbcSmallWestTacMax = getbits(bb002out,16, 12);

  mBbcSmallEastAdcSum->Fill(bbcSmallEastAdcSum);
  mBbcSmallEastTacMax->Fill(bbcSmallEastTacMax);

  mBbcSmallWestAdcSum->Fill(bbcSmallWestAdcSum);
  mBbcSmallWestTacMax->Fill(bbcSmallWestTacMax);
}
void DSMSimulator_2016::fillBB101Histograms(const Crate& sim)
{
  fillBB101Histograms();

  int bb001out = bb101.channels[0] | bb101.channels[1] << 16; // east
  int bb002out = bb101.channels[2] | bb101.channels[3] << 16; // west

  int bbcSmallEastAdcSum = getbits(bb001out,0,16);
  int bbcSmallEastTacMax = getbits(bb001out,16,12);
  int bbcSmallWestAdcSum = getbits(bb002out,0, 16);
  int bbcSmallWestTacMax = getbits(bb002out,16, 12);

  const Board &bb101sim = sim.boardAt(BB101_BASE_ADDRESS);
  int bb001outsim = bb101sim.channels[0] | bb101sim.channels[1] << 16; // east
  int bb002outsim = bb101sim.channels[2] | bb101sim.channels[3] << 16; // west

  int bbcSmallEastAdcSumSimu = getbits(bb001outsim,0,16);
  int bbcSmallEastTacMaxSimu = getbits(bb001outsim,16,12);
  int bbcSmallWestAdcSumSimu = getbits(bb002outsim,0,16);
  int bbcSmallWestTacMaxSimu = getbits(bb002outsim,16,12);

  if(bbcSmallEastAdcSum-bbcSmallEastAdcSumSimu){
    mBbcSmallEastAdcSumVsSimu->Fill(bbcSmallEastAdcSumSimu,bbcSmallEastAdcSum);
//    cout<<"EastADC: "<<bbcSmallEastAdcSum<<" EastADC(simu): "<<bbcSmallEastAdcSumSimu<<endl;
  }
  if(bbcSmallEastTacMax-bbcSmallEastTacMaxSimu){
    mBbcSmallEastTacMaxVsSimu->Fill(bbcSmallEastTacMaxSimu,bbcSmallEastTacMax);
  }

  if(bbcSmallWestAdcSum-bbcSmallWestAdcSumSimu){
    mBbcSmallWestAdcSumVsSimu->Fill(bbcSmallWestAdcSumSimu,bbcSmallWestAdcSum);
  }
  if(bbcSmallWestTacMax-bbcSmallWestTacMaxSimu){
    mBbcSmallWestTacMaxVsSimu->Fill(bbcSmallWestTacMaxSimu,bbcSmallWestTacMax);
  }
}

void DSMSimulator_2016::fillBB102Histograms(const Crate& sim)
{
  fillBB102Histograms();

  int bb003out = bb102.channels[0] | bb102.channels[1] << 16; // east and west
  int bbcLargeEastTacMax = getbits(bb003out,0,12);
  int bbcLargeWestTacMax = getbits(bb003out,12,12);

  const Board& bb102sim = sim.boardAt(BB102_BASE_ADDRESS);
  int bb003outsim = bb102sim.channels[0] | bb102sim.channels[1] << 16; // east and west       
  //cout<<"bb003outsim:"<<hex<<bb003outsim<<endl; 
  int bbcLargeEastTacMaxSimu = getbits(bb003outsim,0,12);
  int bbcLargeWestTacMaxSimu = getbits(bb003outsim,12,12);

  if(bbcLargeEastTacMax-bbcLargeEastTacMaxSimu){
    mBbcLargeEastTacMaxVsSimu->Fill(bbcLargeEastTacMaxSimu,bbcLargeEastTacMax);
    //cout<<"east simu:"<<bbcLargeEastTacMaxSimu<<" data:"<<bbcLargeEastTacMax<<endl;
  }
  if(bbcLargeWestTacMax-bbcLargeWestTacMaxSimu){
    //cout<<"west simu:"<<bbcLargeWestTacMaxSimu<<" data:"<<bbcLargeWestTacMax<<endl;
    mBbcLargeWestTacMaxVsSimu->Fill(bbcLargeWestTacMaxSimu,bbcLargeWestTacMax);
  }

  for(int ib = 0; ib < 2; ib++){
    if(int diff = btest(bb003out, ib+24) - btest(bb003outsim, ib+24)){
      mBbcLargeHitSimu->Fill(ib, diff);
    }
  }
}

void DSMSimulator_2016::fillBB102Histograms()
{
  int bb003out = bb102.channels[0] | bb102.channels[1] << 16; // east and west                                              
  int bbcLargeEastTacMax = getbits(bb003out,0,12);
  int bbcLargeWestTacMax = getbits(bb003out,12,12);

  mBbcLargeEastTacMax->Fill(bbcLargeEastTacMax);
  mBbcLargeWestTacMax->Fill(bbcLargeWestTacMax);
  for(int ib = 0; ib < 2; ib++){
    mBbcLargeHit->Fill(ib, btest(bb003out, ib+24));
  }
}

void DSMSimulator_2016::fillVP101Histograms()
{
  int vp003out = vp101.channels[4] | vp101.channels[5] << 16; // east
  int vp004out = vp101.channels[6] | vp101.channels[7] << 16; // west
  //east
  int vpdEastAdcSum = getbits(vp003out,0,12);
  int vpdEastNHits = getbits(vp003out, 12, 4);
  int vpdEastTacSum = getbits(vp003out,16,16);
  //west
  int vpdWestAdcSum = getbits(vp004out,0,12);
  int vpdWestNHits = getbits(vp004out, 12, 4);
  int vpdWestTacSum = getbits(vp004out,16,16);

  mVpdEastAdcSum->Fill(vpdEastAdcSum);
  mVpdEastNHits->Fill(vpdEastNHits);
  mVpdEastTacSum->Fill(vpdEastTacSum);

  mVpdWestAdcSum->Fill(vpdWestAdcSum);
  mVpdWestNHits->Fill(vpdWestNHits);
  mVpdWestTacSum->Fill(vpdWestTacSum);
}
void DSMSimulator_2016::fillVP101Histograms(const Crate& sim)
{
  fillVP101Histograms();

  int vp003out = vp101.channels[4] | vp101.channels[5] << 16; // east
  int vp004out = vp101.channels[6] | vp101.channels[7] << 16; // west
  //east
  int vpdEastAdcSum = getbits(vp003out,0,12);
  int vpdEastNHits = getbits(vp003out, 12, 4);
  int vpdEastTacSum = getbits(vp003out,16,16);
  //west
  int vpdWestAdcSum = getbits(vp004out,0,12);
  int vpdWestNHits = getbits(vp004out, 12, 4);
  int vpdWestTacSum = getbits(vp004out,16,16);

  const Board & vp101sim = sim.boardAt(VP101_BASE_ADDRESS);
  int vp003outsim = vp101sim.channels[4] | vp101sim.channels[5] << 16; // east
  int vp004outsim = vp101sim.channels[6] | vp101sim.channels[7] << 16; // west
  //east
  int vpdEastAdcSumSimu = getbits(vp003outsim,0,12);
  int vpdEastNHitsSimu = getbits(vp003outsim, 12, 4);
  int vpdEastTacSumSimu = getbits(vp003outsim,16,16);
  //west
  int vpdWestAdcSumSimu = getbits(vp004outsim,0,12);
  int vpdWestNHitsSimu = getbits(vp004outsim, 12, 4);
  int vpdWestTacSumSimu = getbits(vp004outsim,16,16);

  //east
  if(vpdEastAdcSum-vpdEastAdcSumSimu){
    mVpdEastAdcSumVsSimu->Fill(vpdEastAdcSumSimu,vpdEastAdcSum);
    //cout<<"VPD EastADC: "<<vpdEastAdcSum<<" EastADC(simu): "<<vpdEastAdcSumSimu<<endl;
  }
  if(vpdEastNHits-vpdEastNHitsSimu){
    mVpdEastNHitsVsSimu->Fill(vpdEastNHits, vpdEastNHitsSimu);
  }
  if(vpdEastTacSum-vpdEastTacSumSimu){
    mVpdEastTacSumVsSimu->Fill(vpdEastTacSumSimu,vpdEastTacSum);
    //cout<<"VPD EastTAC: "<<vpdEastTacMax<<" EastTAC(simu): "<<vpdEastTacMaxSimu<<endl;
  }
  //west
  if(vpdWestAdcSum-vpdWestAdcSumSimu){
        mVpdWestAdcSumVsSimu->Fill(vpdWestAdcSumSimu,vpdWestAdcSum);
    //cout<<"VPD WestADC: "<<vpdWestAdcSum<<" WestADC(simu): "<<vpdWestAdcSumSimu<<endl;
  }
  if(vpdWestNHits-vpdWestNHitsSimu){
    mVpdWestNHitsVsSimu->Fill(vpdWestNHits, vpdWestNHitsSimu);
  }

  if(vpdWestTacSum-vpdWestTacSumSimu){
    mVpdWestTacSumVsSimu->Fill(vpdWestTacSumSimu,vpdWestTacSum);
    //cout<<"VPD WestTAC: "<<vpdWestTacMax<<" WestTAC(simu): "<<vpdWestTacMaxSimu<<endl;
  }
}

void DSMSimulator_2016::fillZD101Histograms()
{
  int zd001out = zd101.channels[0] | zd101.channels[1] << 16;

  int zdcWestTac = getbits(zd001out,0,10);
  int zdcEastTac = getbits(zd001out,10,10);

  mZdcWestTac->Fill(zdcWestTac);
  mZdcEastTac->Fill(zdcEastTac);

  for (int i = 0; i < 12; ++i) {
    mZdcAdcSum->Fill(i,btest(zd001out,i+20));
  }
}
void DSMSimulator_2016::fillZD101Histograms(const Crate& sim)
{
  fillZD101Histograms();

  int zd001out = zd101.channels[0] | zd101.channels[1] << 16;
  int zdcWestTac = getbits(zd001out,0,10);
  int zdcEastTac = getbits(zd001out,10,10);

  const Board & zd101sim = sim.boardAt(ZD101_BASE_ADDRESS);
  int zd001outsim = zd101sim.channels[0] | zd101sim.channels[1] << 16;
  int zdcWestTacSimu = getbits(zd001outsim,0,10);
  int zdcEastTacSimu = getbits(zd001outsim,10,10);
  if(zdcWestTac-zdcWestTacSimu){
    mZdcWestTacVsSimu->Fill(zdcWestTacSimu,zdcWestTac);
  }
  if(zdcEastTac-zdcEastTacSimu){
    mZdcEastTacVsSimu->Fill(zdcEastTacSimu,zdcEastTac);
  }
  for (int i = 0; i < 12; ++i) {
    int diff = btest(zd001out,i+20)-btest(zd001outsim,i+20); 
    if(diff) mZdcAdcSumDiff->Fill(i,diff);
  }
}
/*
void DSMSimulator_2016::writeVtxLayer2ToLastDsm(Crate& sim)
{
  Board& ld301sim = sim.boardAt(LD301_BASE_ADDRESS);
  ld301sim.channels[1] = vt201.output;
}
*/
void DSMSimulator_2016::fillLastDsmHistograms()
{
  for (int ch = 0; ch < 8; ++ch)
    for (int bit = 0; bit < 16; ++bit)
      mLD301Bits[ch]->Fill(bit,btest(ld301.channels[ch],bit));
}

void DSMSimulator_2016::fillLastDsmHistograms(const Crate& sim, int ch)
{
  const Board& ld301sim = sim.boardAt(LD301_BASE_ADDRESS);
  for (int bit = 0; bit < 16; ++bit) {
    if (int diff = btest(ld301.channels[ch],bit) - btest(ld301sim.channels[ch],bit)) {
      mLD301BitsDiff[ch]->Fill(bit,diff);
//      if(ch == 5){ cout<<"bit:"<<bit<<" real:"<<btest(ld301.channels[ch], bit)<<" diff:"<<diff<<endl;}
      mLD301Errors[ch] |= 1 << bit;
    }
  }
}

//void DSMSimulator_2016::runTofBranch(const TriggerDataBlk& event)
void DSMSimulator_2016::runTofBranch()
{
  Crate sim;
  runMixLayer0(sim);
  runMixLayer1(sim);
  runMixLayer2(sim);
  fillTF001Histograms();
  fillMT001Histograms();
  fillPP001Histograms();
  fillTF101Histograms(sim);
  fillMT101Histograms();
  fillTF201Histograms(sim);
  //  writeTofLayer2ToLastDsm(sim);
  fillLastDsmHistograms(sim,0);
}
/*
void DSMSimulator_2016::runTofLayer2()
{
  l1_tf201_2012_b(tf201);
}
*/
/*
void DSMSimulator_2016::writeTofLayer2ToLastDsm(Crate& sim)
{
  Board& ld301sim = sim.boardAt(LD301_BASE_ADDRESS);
  ld301sim.channels[0] = tf201.output;
}
*/
