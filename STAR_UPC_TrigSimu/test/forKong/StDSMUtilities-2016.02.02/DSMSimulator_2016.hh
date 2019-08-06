#ifndef DSM_SIMULATOR_2016_HH
#define DSM_SIMULATOR_2016_HH

#include <iostream>
#include "TString.h"
#include "DSMSimulator.hh"

#include "Board.hh"
#include "Crate.hh"

class TFile;
class TH1F;
class TH2F;

class DSMSimulator_2016 : public DSMSimulator {
public:
  DSMSimulator_2016();

  Crate& crateAt(int crateid) { return crates[crateid-1]; }
  const Crate& crateAt(int crateid) const { return crates[crateid-1]; }

  Crate& crateAt(int crateid, int prepost) { return PrePostCrates[prepost][crateid-1]; }
  const Crate& crateAt(int crateid, int prepost) const { return PrePostCrates[prepost][crateid-1]; }

  void setFile(const char* filename);
  void setFullDSMTree(int value = 1);

  void setEMCStatus(int status = 1);
  void setVTXStatus(int status = 1);
  void setTOFStatus(int status = 1);
  void setFPDStatus(int status = 1);

  void init();
  void initEmcBranch();
  void initFpdBranch();
  void initVtxBranch();
  void initTofBranch();

  void run(const TriggerDataBlk& event);
  void readCrates(const TriggerDataBlk& event);
  void readCrates(const TriggerDataBlk& event, int prepost);
  void runEmcBranch();
  void runFpdBranch();
  void runVtxBranch();
  void runTofBranch();

  void setBarrelHighTowerTh(int i, int value);
  void setEndcapHighTowerTh(int i, int value);
  void setBarrelJetPatchTh(int i, int value);
  void setEndcapJetPatchTh(int i, int value);
  void setOverlapJetPatchTh(int i, int value);

  void finish();
  int  eventLoop(char* first, char* last);
  void loadRegisters();
  void loadSlewCorrections();
  void shiftMT102();
private:
  int bb001_slew[32][8];
  int bb002_slew[32][8];

  int vp001_slew[32][8];
  int vp002_slew[32][8];

  int mt001_slew[32][8];
  int mt002_slew[32][8];
  int mt003_slew[32][8];
  int mt004_slew[32][8];
  int mt005_slew[32][8];
  int mt006_slew[32][8];
  int mt007_slew[32][8];
  int mt008_slew[32][8];

  void bookBB001Histograms();
  void bookVP001Histograms();
  void bookZD001Histograms();
//  void bookZP001Histograms();
  void bookMT001Histograms();
  void bookPP001Histograms();
  void bookBB101Histograms();
  void bookBB102Histograms();
  void bookVP101Histograms();
  void bookZD101Histograms();
  void bookMT101Histograms();
  void bookVT201Histograms();
  void bookTF001Histograms();
  void bookTF101Histograms();
  void bookTF201Histograms();
  void bookBeamEnergyScanHistograms();
//  void bookFpdHistograms();
  void bookFmsQtHistograms();
  void bookFmsLayer0Histograms();
  void bookFmsLayer1Histograms();
  void bookFmsLayer2Histograms();

  void labelHistogramYaxis(TH2F* h);
  void labelB101Histogram(TH2F* h);
  void labelE101Histogram(TH2F* h);
  void labelEM201Histogram(TH2F* h);
  void labelVP001Histogram(TH2F* h, int shift);
  void labelBB102Histogram(TH2F* h);
  void labelZD101Histogram(TH2F *h);
  void labelVT201ZDCHistogram(TH2F *h);
  //  void labelFmsLayer0Histogram(TH2F* h);
  //  void labelFpeLayer1Histogram(TH2F* h);
  //  void labelFmsLayer1Histogram(TH2F* h);
  //  void labelFpdLayer2Histogram(TH2F* h);
  void labelLD301TF201(TH2F *h);
  void labelLD301EM201(TH2F *h);
  void labelLD301VT201(TH2F *h);
  void labelTF201MT(TH2F *h);
  void labelTF201TF(TH2F *h);

  void fillBemcLayer0Histograms();
  void fillBemcLayer0Histograms(int bin0, const Board& dsm);
  void fillEemcLayer0Histograms();
  void fillEemcLayer0Histograms(int bin0, const Board& dsm);
  void fillBemcLayer1Histograms(const Crate& sim);
  void fillBemcLayer1Histograms(int bin0, const Board& dsm, const Board& sim);
//  void fillBemcJetPatches();
//  void fillBemcJetPatches(const Board& bc101, int jpx, int jpy, int jpz);
  void fillEemcLayer1Histograms(const Crate& sim);
  void fillEemcLayer1Histograms(int bin0, const Board& dsm, const Board& sim);
//  void fillEemcJetPatches();
  void fillEmcLayer2Histograms(const Crate& sim);
  void fillTpcReadoutMaskHistogram();
//  void fillHybridJetPatches();
  void fillBB001Histograms();
  void fillVP001Histograms();
  void fillZD001Histograms();
//  void fillZP001Histograms();
  void fillBB101Histograms();
  void fillBB101Histograms(const Crate& sim);
  void fillBB102Histograms();
  void fillBB102Histograms(const Crate& sim);
  void fillVP101Histograms();
  void fillVP101Histograms(const Crate& sim);
  void fillZD101Histograms();
  void fillZD101Histograms(const Crate& sim);
  void fillVT201Histograms();
  void fillVT201Histograms(const Crate& sim);
  void fillMT001Histograms();
  void fillPP001Histograms();
  void fillTF001Histograms();
  void fillTF101Histograms();
  void fillTF101Histograms(const Crate& sim);
  void fillMT101Histograms();
  void fillMT101Histograms(Board b, int);
  void fillMT101Histograms(const Crate& sim);
  void fillTF201Histograms();
  void fillTF201Histograms(const Crate& sim);
  void fillLastDsmHistograms(const Crate& sim, int ch);
  void fillLastDsmHistograms();
  void fillBunchIdHistograms(const TriggerDataBlk& event);
  void fillBeamEnergyScanHistograms();
  void fillVtxHistograms();
  //  void fillFpeQtLayerHistograms();
  void fillFmsQtLayerHistograms();
  void fillFmsLayer0Histograms();
  void fillFmsLayer0Histograms(const Crate& sim);
  void fillFmsLayer1Histograms();
  void fillFmsLayer1Histograms(const Crate& sim);
  //  void fillFpeLayer1Histograms(const Crate& sim);
  void fillFmsLayer2Histograms();
  void fillFmsLayer2Histograms(const Crate& sim);
  //  void fillFpdLayer2Histograms(const Crate& sim);
  //  void fillBitErrorsHistograms(const Board& dsm, const Board& sim, TH1F* histos[8]);

  void runBemcLayer0();
  void runEemcLayer0();
  void runBemcLayer1();
  void runEemcLayer1();
  void runEmcLayer2();
  void runFpeQtLayer(Crate &sim);
  void runFmsQtLayer(Crate &sim);
  void runFmsLayer0(Crate &sim);
  //  void runFpeLayer1(Crate &sim);
  void runFmsLayer1(Crate &sim);
  void runFmsLayer2(Crate &sim);
  void runVtxLayer0(Crate& sim);
  void runVtxLayer1(Crate& sim);
  void runVtxLayer2(Crate& sim);
  void runMixLayer0(Crate& sim);
  void runMixLayer1(Crate& sim);
  void runMixLayer2(Crate& sim);

  void writeBemcLayer0ToBemcLayer1(Crate& sim);
  void writeEemcLayer0ToEemcLayer1(Crate& sim);
  void writeBemcLayer1ToEmcLayer2(Crate& sim);
  void writeEemcLayer1ToEmcLayer2(Crate& sim);
  void writeEmcLayer2ToLastDsm(Crate& sim);

  //  void writeVtxLayer2ToLastDsm(Crate& sim);
  //  void writeTofLayer2ToLastDsm(Crate& sim);

  TFile* mFile;
  TString mFileName;
  int mFullDSMTree;
  int mEMCStatus;
  int mVTXStatus;
  int mTOFStatus;
  int mFPDStatus;

  // BEMC layer 0

  TH2F* mB001HighTower;
  TH2F* mB001TriggerPatch;

  // EEMC layer 0

  TH2F* mE001HighTower;
  TH2F* mE001TriggerPatch;

  // BEMC layer 1
  TH2F* mB101Bits[8];
  TH2F* mB101BitsDiff[8];
  // EEMC layer 1

  TH2F* mE101LowEtaSum;
  TH2F* mE101HighEtaSum;
  TH2F* mE101HighTowerBits[2];

  TH2F* mE101LowEtaSumDiff;
  TH2F* mE101HighEtaSumDiff;
  TH2F* mE101HighTowerBitsDiff[2];

  // EMC layer 2

  TH2F* mEM201[8];
  TH2F* mEM201Diff[8];

  TH1F* mEM202;
  TH1F* mEM202Diff;
  TH1F* mTpcReadoutMask;

  // BBC layer 0

  TH2F* mBB001ADC;
  TH2F* mBB001TAC;
  TH2F* mBB002ADC;
  TH2F* mBB002TAC;
  TH2F* mBB003ADC;
  TH2F* mBB003TAC;

  // BBC layer 1

  TH1F* mBBCSTACW;
  TH1F* mBBCSTACE;
  TH1F* mBBCLTACW;
  TH1F* mBBCLTACE;

  TH1F* mBbcSmallEastAdcSum;
  TH1F* mBbcSmallEastTacMax;
  TH2F* mBbcSmallEastAdcSumVsSimu;
  TH2F* mBbcSmallEastTacMaxVsSimu;

  TH1F* mBbcSmallWestAdcSum;
  TH1F* mBbcSmallWestTacMax;
  TH2F* mBbcSmallWestAdcSumVsSimu;
  TH2F* mBbcSmallWestTacMaxVsSimu;

  TH1F* mBbcLargeEastTacMax;
  TH1F* mBbcLargeWestTacMax;
  TH2F* mBbcLargeEastTacMaxVsSimu;
  TH2F* mBbcLargeWestTacMaxVsSimu;

  TH2F *mBbcLargeHit;
  TH2F *mBbcLargeHitSimu;
  //BBC layer 2
  TH1F *mBbcSmallTacDiff;
  TH2F *mBbcSmallAdcSumTh;

  TH2F *mBbcSmallTacDiffVsSimu;
  TH2F *mBbcSmallAdcSumThSimu;

  TH1F *mBbcLargeTacDiff;
  TH2F *mBbcLargeAdcSumTh;

  TH2F *mBbcLargeTacDiffVsSimu;
  TH2F *mBbcLargeAdcSumThSimu;
  // VPD layer 0

  TH2F* mVP001ADC;
  TH2F* mVP001TAC;
  TH2F* mVP002ADC;
  TH2F* mVP002TAC;
  TH2F* mVP003ADC;
  TH2F* mVP003TAC;
  TH2F* mVP004ADC;
  TH2F* mVP004TAC;

  // VPD layer 1

  TH1F* mVPDTACW;
  TH1F* mVPDTACE;
  TH1F* mVpdEastAdcSum;
  TH1F *mVpdEastNHits;
  TH1F* mVpdEastTacSum;
  TH2F* mVpdEastAdcSumVsSimu;
  TH2F *mVpdEastNHitsVsSimu;
  TH2F* mVpdEastTacSumVsSimu;
  TH1F* mVpdWestAdcSum;
  TH1F *mVpdWestNHits;
  TH1F* mVpdWestTacSum;
  TH2F* mVpdWestAdcSumVsSimu;
  TH2F *mVpdWestNHitsVsSimu;
  TH2F* mVpdWestTacSumVsSimu;
  //  TH1F* mVpdMtdEastMaxTac;
  //  TH2F* mVpdMtdEastMaxTacVsSimu;
  //  TH1F* mVpdMtdWestMaxTac;
  //  TH2F* mVpdMtdWestMaxTacVsSimu;
  //VPD layer 2
  TH2F *mVpdTacDiff;
  TH2F *mVpdAdcSumTh;

  TH2F *mVpdTacDiffVsSimu;
  TH2F *mVpdAdcSumThSimu;
  // ZDC layer 0

  TH2F* mZD001ADC;
  TH2F* mZD001TAC;
  TH2F* mZP001WADC;
  TH2F* mZP001EADC;
  TH1F* mZdcWestTac;
  TH1F* mZdcEastTac;
  TH2F* mZdcWestTacVsSimu;
  TH2F* mZdcEastTacVsSimu;

  TH2F* mZdcAdcSum;
  TH2F* mZdcAdcSumDiff;

  // ZDC layer 1

  TH1F* mZDCTACW;
  TH1F* mZDCTACE;

  //ZDC layer 2

  TH1F *mZdcTacDiff;
  TH2F *mZdcAdcSumTh;
  TH2F *mZdcTacDiffVsSimu;
  TH2F *mZdcAdcSumThSimu;
  // VTX layer 2

  TH1F* mZDCTACDIFF;
  TH1F* mBBCSTACDIFF;
  TH1F* mBBCLTACDIFF;
  TH1F* mVPDTACDIFF;

  // MTD & pp2pp

  TH2F* mMT001[8];
  TH2F* mPP001ADC;
  TH2F* mPP001TAC;

  TH2F *mMT101TACsum[2][4];
  //TH1F *mMT101TACsum2nd[2][4];
  TH1F *mMT101MaxTAC[2][2];

  // TOF layer 0

  TH2F* mTF001MULT[6];

  // TOF layer 1

  TH2F* mTF101MULT;
  TH2F *mTF101UPC[4];

  TH2F* mTF101MULTSim;
  TH2F *mTF101UPCSim[4];

  // TOF layer 2

  TH1F* mTF201TotalMult;
  TH2F* mTF201SectorThUPC;
//  TH1F *mTF201UPCBit;
  TH2F *mTF201CosRay[2];
  TH1F *mTF201NMuons[2];
  TH2F *mTF201RP;

  TH1F* mTF201TotalMultSimu;
  TH2F* mTF201SectorThUPCSimu;
//  TH1F *mTF201UPCBitSimu;
  TH2F *mTF201CosRaySimu[2];
  TH1F *mTF201NMuonsSimu[2];
  TH2F *mTF201RPSimu;

  // Last DSM or new TCU all channels

  TH2F* mLD301Bits[8];
  TH2F* mLD301BitsDiff[8];
  int mLD301Errors[8];

  // 7-bit bXing

  TH1F* mBunchId7Bit;		// all events
  TH1F* mBunchId7BitHTTP;	
  TH1F* mBunchId7BitBHT1;	
  TH1F* mBunchId7BitHT;	
  TH1F* mBunchId7BitTP;	
  TH1F* mBunchId7BitVPDTAC;
  TH1F* mBunchId7BitMTD2;
  //  TH1F* mBlueFill;
  //  TH1F* mYellowFill;

  // Jet patches

//  TH2F* mBarrelJetPatches;
//  TH2F* mEndcapJetPatches;
//  TH2F* mHybridJetPatches;

  // Beam Energy Scan histograms

  TH2F* hTofVsBbcLargeEast;
  TH2F* hTofVsBbcLargeWest;
  TH2F* hTofVsBbcSmallEast;
  TH2F* hTofVsBbcSmallWest;
  TH2F* hTofVsVpdEast;
  TH2F* hTofVsVpdWest;
  TH2F* hTofVsZdcEast;
  TH2F* hTofVsZdcWest;
  TH2F* hBbcLargeVsSmallEast;
  TH2F* hBbcLargeVsSmallWest;
  TH2F* hBbcLargeVsVpdEast;
  TH2F* hBbcLargeVsVpdWest;
  TH2F* hBbcLargeVsZdcEast;
  TH2F* hBbcLargeVsZdcWest;
  TH2F* hBbcSmallVsVpdEast;
  TH2F* hBbcSmallVsVpdWest;
  TH2F* hBbcSmallVsZdcEast;
  TH2F* hBbcSmallVsZdcWest;
  TH2F* hVpdVsZdcEast;
  TH2F* hVpdVsZdcWest;
  TH2F* hBbcLargeEastVsWest;
  TH2F* hBbcSmallEastVsWest;
  TH2F* hVpdEastVsWest;
  TH2F* hZdcEastVsWest;

  TH2F* hBbcLargeVsSmallTac;
//  TH2F* hBbcLargeVsVpdTac;
  TH2F* hBbcLargeVsZdcTac;
//  TH2F* hBbcSmallVsVpdTac;
  TH2F* hBbcSmallVsZdcTac;
//  TH2F* hVpdVsZdcTac;
  TH2F* hZdcTacEastVsWest;

  // Input to FPE QT boards
  TH2F* hFE001;
  TH2F* hFE002;
  TH2F* hFE003;
  TH2F* hFE004;

  // Input to FMS QT boards
  TH2F* hQT1ADC;
  TH2F* hQT2ADC;
  TH2F* hQT3ADC;
  TH2F* hQT4ADC;
  //  TH2F* hQT3vsQT3ADC;
  //  TH2F* hQT3vsQT4ADC;

  // Input to FMS L0 boards
  TH2F *mFM001;
  TH2F *mFM002;
  TH2F *mFM003;
  TH2F *mFM004;
  TH2F *mFM005;
  TH2F *mFM006;
  TH2F *mFM007;
  TH2F *mFM008;
  TH2F *mFM009;
  TH2F *mFM010;
  TH2F *mFM011;
  TH2F *mFM012;
  // Input to FPE L1 boards
  //  TH2F* hFE101;
  //  TH2F* hFE101Diff;
  //  TH2F* hFE101Corr;

  // Input to FMS L1 boards
  TH2F *mFM101BS[2];
  TH1F *mFM101D[2];
  TH2F *mFM101JP[2];

  TH2F *mFM102BS[2];
  TH1F *mFM102D[2];
  TH2F *mFM102JP[2];

  TH2F *mFM103BS[4];
  TH1F *mFM103J[4];
  TH2F *mFM103JP[4];

  TH2F *mFM104BS[4];
  TH1F *mFM104J[4];
  TH2F *mFM104JP[4];
  //simu
  TH2F *mFM101BSsim[2];
  TH1F *mFM101Dsim[2];
  TH2F *mFM101JPsim[2];

  TH2F *mFM102BSsim[2];
  TH1F *mFM102Dsim[2];
  TH2F *mFM102JPsim[2];

  TH2F *mFM103BSsim[4];
  TH1F *mFM103Jsim[4];
  TH2F *mFM103JPsim[4];

  TH2F *mFM104BSsim[4];
  TH1F *mFM104Jsim[4];
  TH2F *mFM104JPsim[4];
  // Input to FPD L2 board
  TH2F *mFP201BS[4];
  TH2F *mFP201JP[4];
  //simu
  TH2F *mFP201BSsim[4];
  TH2F *mFP201JPsim[4];

  // Crates
  enum { NCRATES = 14 };

  Crate crates[NCRATES];
  Crate PrePostCrates[10][NCRATES];

  Crate& l1;
  Crate& mix;
  Crate& bbc;
  Crate& fms;
  Crate& bc1;
  Crate& bcw;
  Crate& bce;
  Crate& mxq;
  Crate& feq;
  Crate& bbq;
  Crate& qt1;
  Crate& qt2;
  Crate& qt3;
  Crate& qt4;

  // L1 crate
  Board& tf201;
  Board& vt201;
  Board& em201;
  Board& bx201;
  Board& bx202;
  Board& st201;
  Board& fp201;
  Board& ld301;

  // BC1 crate
  Board& bc101;
  Board& bc102;
  Board& bc103;
  Board& bc104;
  Board& bc105;
  Board& bc106;
  Board& ee101;
  Board& ee102;
  Board& ee001;
  Board& ee002;
  Board& ee003;
  Board& ee004;
  Board& ee005;
  Board& ee006;
  Board& ee007;
  Board& ee008;
  Board& ee009;

  // BCW crate
  Board& bw001;
  Board& bw002;
  Board& bw003;
  Board& bw004;
  Board& bw005;
  Board& bw006;
  Board& bw007;
  Board& bw008;
  Board& bw009;
  Board& bw010;
  Board& bw011;
  Board& bw012;
  Board& bw013;
  Board& bw014;
  Board& bw015;

  // BCE crate
  Board& be001;
  Board& be002;
  Board& be003;
  Board& be004;
  Board& be005;
  Board& be006;
  Board& be007;
  Board& be008;
  Board& be009;
  Board& be010;
  Board& be011;
  Board& be012;
  Board& be013;
  Board& be014;
  Board& be015;

  // MIX crate
//  Board& fe101;
  Board& pp101;
  Board& mt101;
  Board& tf101;
  Board& tf001;
  Board& tf002;
  Board& tf003;
  Board& tf004;
  Board& tf005;
  Board& tf006;
  Board& em202;
  Board& mt102;
  Board& tf202;

  // FEQ crate
  Board& fe001;
  Board& fe002;
  Board& fe003;
  Board& fe004;
  Board& fs001;
  Board& fs002;
  Board& fs003;
  Board& fs004;
  Board& fs005;
  Board& fs006;

  // BBC crate
  Board& bb101;
  Board& bb102;
  Board& zd101;
  Board& vp101;

  // FMS crate
  Board& fm001;
  Board& fm002;
  Board& fm003;
  Board& fm004;
  Board& fm101;
  Board& fm005;
  Board& fm006;
  Board& fm007;
  Board& fm008;
  Board& fm102;
  Board& fm009;
  Board& fm010;
  Board& fm011;
  Board& fm012;
  Board& fm103;
  Board& fm104;

  // BBQ crate
  Board& bb001;
  Board& bb002;
  Board& bb003;
  Board& vp001;
  Board& vp002;
  Board& zd001;

  // MXQ crate
  Board& mt001;
  Board& pp001;
//  Board& zp001;
  Board& px001;
  Board& vp003;
  Board& vp004;
  Board& mt002;
  Board& mt003;
  Board& mt004;
  Board& mt005;
  Board& mt006;
  Board& mt007;
  Board& mt008;
};

#endif // DSM_SIMULATOR_2016_HH
