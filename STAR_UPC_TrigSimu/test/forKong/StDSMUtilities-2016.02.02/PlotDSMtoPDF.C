#include "TH2.h"

#define TEXTCOLOR 16
#define TEXTSIZE  0.04

void PlotDSMtoPDF(const char* rootfile = "dsm.root", const char* psfile = "dsm.pdf")
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(10);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);

  TFile* file = TFile::Open(rootfile);

  TCanvas* c1 = new TCanvas("c1","c1",850,1100);

  // BEMC L0 Input

  c1->Clear();
  c1->Divide(1,2);

  c1->cd(1); Draw("B001HighTower","colz");
  c1->cd(2); Draw("B001TriggerPatch","colz");

  c1->Print(Form("%s(",psfile),"Title:BEMC L0 Input");
  cout<<"Printing BEMC L0"<<endl;
  // EEMC L0 Input

  c1->cd(1); Draw("E001HighTower","colz"); labelE001Histogram("E001HighTower");
  c1->cd(2); Draw("E001TriggerPatch","colz"); labelE001Histogram("E001TriggerPatch");

  c1->Print(psfile,"Title:EEMC L0 Input");
  cout<<"Printing EEMC L0"<<endl;

  gStyle->SetOptStat(10);
  const char *nameB101[8] = {"TP", "HT.TP", "HT-th0", "HT-th1",
                             "HT-th2", "HT-th3", "HT-th4", "HT-UPC"};
  // BEMC L1 Input 1
  c1->Clear();
  c1->Divide(2,4);
  for(int ib = 0; ib < 4; ib++){
    c1->cd(2*ib+1);
    Draw(Form("BC1-%s", nameB101[ib]), "colz");
    labelB101Histogram(Form("BC1-%s", nameB101[ib]));
    c1->cd(2*ib+2);
    Draw(Form("BC1-%s-Diff", nameB101[ib]), "colz");
    labelB101Histogram(Form("BC1-%s-Diff", nameB101[ib]));
  }
  
  c1->Print(psfile,"Title:BEMC L1 Input 1");
  //BEMC L1 Input 2

  c1->Clear();
  c1->Divide(2,4);
  for(int ib = 4; ib < 8; ib++){
    c1->cd(2*ib-7);
    Draw(Form("BC1-%s", nameB101[ib]), "colz");
    labelB101Histogram(Form("BC1-%s", nameB101[ib]));
    c1->cd(2*ib-6);
    Draw(Form("BC1-%s-Diff", nameB101[ib]), "colz");
    labelB101Histogram(Form("BC1-%s-Diff", nameB101[ib]));
  }
  
  c1->Print(psfile,"Title:BEMC L1 Input 2");

  cout<<"Printing BEMC L1"<<endl;
  // EEMC L1 Input
  c1->Clear();
  c1->Divide(2, 4);
  c1->cd(1); Draw("E101LowEtaSum","colz"); labelE101Histogram("E101LowEtaSum");
  c1->cd(2); Draw("E101LowEtaSumDiff","colz"); labelE101Histogram("E101LowEtaSumDiff");
  c1->cd(3); Draw("E101HighEtaSum","colz"); labelE101Histogram("E101HighEtaSum");
  c1->cd(4); Draw("E101HighEtaSumDiff","colz"); labelE101Histogram("E101HighEtaSumDiff");
  const char* nameE101[2] = {"HT-th0", "HT-th1"};
  for(int i = 0; i < 2; i++){
    c1->cd(5+2*i); Draw(Form("E101%s", nameE101[i]), "colztext90"); labelE101Histogram(Form("E101%s", nameE101[i]));
    c1->cd(6+2*i); Draw(Form("E101%sDiff", nameE101[i]), "colztext90"); labelE101Histogram(Form("E101%sDiff", nameE101[i]));
  }
  c1->Print(psfile,"Title:EEMC L1 Input");
  cout<<"Printing EEMC L1"<<endl;

  // EMC L2 Input
  c1->Clear();
  c1->Divide(2, 4);
  for(int ch = 0; ch < 4; ch++){
    c1->cd(2*ch+1);
    Draw(Form("EM201-BC10%d", ch+1), "colztext90");
    c1->cd(2*ch+2);
    Draw(Form("EM201-BC10%dDiff", ch+1), "colztext90");
  }
  c1->Print(psfile,"Title:EMC L2 Input 1");

  // EMC L2 Input
  for(int ch = 4; ch < 8; ch++){
    if(ch < 6){
      c1->cd(2*ch-7);
      Draw(Form("EM201-BC10%d", ch+1), "colztext90");
      c1->cd(2*ch-6);
      Draw(Form("EM201-BC10%dDiff", ch+1), "colztext90");
    }else{
      c1->cd(2*ch-7);
      Draw(Form("EM201-EE10%d", ch-5), "colztext90");
      c1->cd(2*ch-6);
      Draw(Form("EM201-EE10%dDiff", ch-5), "colztext90");
    } 
  }
  c1->Print(psfile,"Title:EMC L2 Input 2");
  cout<<"Printing EMC L2"<<endl;
  // BXing

  c1->Clear();
  c1->Divide(2,3);
  //c1->cd(1); gPad->SetLogy(1); Draw("BunchId7Bit","");
  c1->cd(1); gPad->SetLogy(1); Draw("BunchId7BitBHT1","");
  c1->cd(2); gPad->SetLogy(1); Draw("BunchId7BitHT","");
  c1->cd(3); gPad->SetLogy(1); Draw("BunchId7BitHTTP","");
  c1->cd(4); gPad->SetLogy(1); Draw("BunchId7BitTP","");
  c1->cd(5); gPad->SetLogy(1); Draw("BunchId7BitVPDTAC","");
  c1->cd(6); gPad->SetLogy(1); Draw("BunchId7BitMTD2","");
  //  c1->cd(8); gPad->SetLogy(1); Draw("BunchId7BitRPET","");

  c1->Print(psfile,"Title:BXing");

  // TOF L0 Input

  c1->Clear();
  c1->Divide(2,3);

  c1->cd(1); Draw("TF001MULT","colz");
  c1->cd(2); Draw("TF002MULT","colz");
  c1->cd(3); Draw("TF003MULT","colz");
  c1->cd(4); Draw("TF004MULT","colz");
  c1->cd(5); Draw("TF005MULT","colz");
  c1->cd(6); Draw("TF006MULT","colz");

  c1->Print(psfile,"Title:TOF L0 Input");

  // TOF L1 and L2 Input
  
  c1->Clear();
  c1->Divide(2,5);

  c1->cd(1); Draw("TF101MULT","colz");
  c1->cd(2); Draw("TF101MULTSim","colz");
  for(int iupc = 0; iupc < 4; iupc++){
    c1->cd(3+2*iupc); Draw(Form("TF101UPC-TH-%d", iupc), "colztext89");
    c1->cd(4+2*iupc); Draw(Form("TF101UPCTHSim%d", iupc), "colztext89");
  }
  c1->Print(psfile, "Title: TOF L1 Input");

  c1->Clear();
  c1->Divide(2, 3);
  c1->cd(1); gPad->SetLogy(1); Draw("TF201TotalMult","");
  c1->cd(2); gPad->SetLogy(1); Draw("TF201TotalMultSimu", "");
  c1->cd(3); Draw("TF201SectorThUPC","colztext");
  c1->cd(4); Draw("TF201SectorThUPCSimu","colztext");
//  c1->cd(5); gPad->SetLogy(1); Draw("TF201UPCBit", "");
//  c1->cd(6); gPad->SetLogy(1); Draw("TF201UPCBitSimu", "");
  c1->cd(5); Draw("TF201RP", "colztext");
  c1->cd(6); Draw("TF201RPSimu", "colztext");
  c1->Print(psfile, "Title:TOF L2 Input 1");

  c1->Clear();
  c1->Divide(2, 4);
  for(int ich = 0; ich < 2; ich++){
  int ip = ich*4;
  c1->cd(ip+1); gPad->SetLogy(1); Draw(Form("TF201MT10%dNMuons", ich+1), "");
  c1->cd(ip+2); gPad->SetLogy(1); Draw(Form("TF201MT10%dNMuonsSimu", ich+1), "");
  c1->cd(ip+3);  Draw(Form("TF201MT10%dCosRay", ich+1), "colztext");
  c1->cd(ip+4);  Draw(Form("TF201MT10%dCosRaySimu", ich+1), "colztext");
  }
  c1->Print(psfile, "Title: TOF L2 Input 2");
  cout<<"TOF DONE"<<endl;
  //MT001
  c1->Clear();
  c1->Divide(2, 4);
  for(int ib = 0; ib < 8; ib++){
    c1->cd(ib+1);
    Draw(Form("mMT00%d", ib+1), "colz");
  }
  c1->Print(psfile, "Title: MTD L0");
  //MT101
  c1->Clear();
  c1->Divide(2, 5);
  for(int ii = 0; ii < 4; ii++){
    c1->cd(2*ii+1); gPad->SetLogz(1); Draw(Form("MT101TACsum%d", ii), "colz");
    //c1->cd(2*ii+2); gPad->SetLogy(1); Draw(Form("MT101TACsum2nd%d", ii), "");
  }
  for(int ii = 8; ii < 10; ii++){
    c1->cd(ii+1); gPad->SetLogy(1); Draw(Form("MT101MaxTAC%d", ii), "");
  }
  c1->Print(psfile, "Title: MTD MT101 L1");

  for(int ii = 0; ii < 4; ii++){
    c1->cd(2*ii+1); Draw(Form("MT102TACsum%d", ii), "colz");
    //c1->cd(2*ii+2); Draw(Form("MT102TACsum2nd%d", ii), "colz");
  }
  for(int ii = 8; ii < 10; ii++){
    c1->cd(ii+1); gPad->SetLogy(1); Draw(Form("MT102MaxTAC%d", ii), "");
  }
  c1->Print(psfile, "Title: MTD MT102 L1");

  cout<<"MTD DONE"<<endl;

  //PP001

  c1->Clear();
  c1->Divide(2, 1);
  c1->cd(1); Draw("mPP001ADC", "colz");
  c1->cd(2); Draw("mPP001TAC", "colz");
  c1->Print(psfile, "Title: PP2PP L0");
  cout<<"PP2 DONE"<<endl;
  
  // BBC-S, BBC-L, and ZDC L0 Input

  c1->Clear();
  c1->Divide(2,4);

  c1->cd(1); Draw("BB001ADC","colz");
  c1->cd(2); Draw("BB001TAC","colz");
  c1->cd(3); Draw("BB002ADC","colz");
  c1->cd(4); Draw("BB002TAC","colz");
  c1->cd(5); Draw("BB003ADC","colz");
  c1->cd(6); Draw("BB003TAC","colz");
  c1->cd(7); Draw("ZD001ADC","colz");
  c1->cd(8); Draw("ZD001TAC","colz");

  c1->Print(psfile,"Title:BBC-S, BBC-L, and ZDC L0 Input");

  // VPD L0 Input

  c1->cd(1); Draw("VP001ADC","colz");
  c1->cd(2); Draw("VP001TAC","colz");
  c1->cd(3); Draw("VP002ADC","colz");
  c1->cd(4); Draw("VP002TAC","colz");
  c1->cd(5); Draw("VP003ADC","colz");
  c1->cd(6); Draw("VP003TAC","colz");
  c1->cd(7); Draw("VP004ADC","colz");
  c1->cd(8); Draw("VP004TAC","colz");

  c1->Print(psfile,"Title:VPD L0 Input");

  // BBC-S L1 Input
  c1->cd(1); gPad->SetLogy(1); Draw("bbcSmallEastAdcSum","");
  c1->cd(2); Draw("bbcSmallEastAdcSumVsSimu","colz");
  c1->cd(3); gPad->SetLogy(1); Draw("bbcSmallEastTacMax","");
  c1->cd(4); Draw("bbcSmallEastTacMaxVsSimu","colz");
  c1->cd(5); gPad->SetLogy(1); Draw("bbcSmallWestAdcSum","");
  c1->cd(6); Draw("bbcSmallWestAdcSumVsSimu","colz");
  c1->cd(7); gPad->SetLogy(1); Draw("bbcSmallWestTacMax","");
  c1->cd(8); Draw("bbcSmallWestTacMaxVsSimu","colz");

  c1->Print(psfile,"Title:BBC-S L1 Input");

  // BBC-L L1 Input
  c1->Clear();
  c1->Divide(2,3);

  c1->cd(1); Draw("bbcLargeHit", "colztext");
  c1->cd(2); Draw("bbcLargeEastHitSimu", "colztext");
//  c1->cd(3); gPad->SetLogy(1); Draw("bbcLargeEastTacMax","");
//  c1->cd(4); gPad->SetLogz(1); Draw("bbcLargeEastTacMaxVsSimu","colz");
//  c1->cd(5); gPad->SetLogy(1); Draw("bbcLargeWestTacMax","");
//  c1->cd(6); gPad->SetLogz(1); Draw("bbcLargeWestTacMaxVsSimu","colz");
  c1->Print(psfile, "Title:BBC-L L1 Input");
  cout<<"Printing BBC-L L1"<<endl;
//#endif
  // VPD-VTX L1 Input

  c1->Clear();
  c1->Divide(2,3);

  c1->cd(1); gPad->SetLogy(1); Draw("vpdEastAdcSum","");
  c1->cd(2); Draw("vpdEastAdcSumVsSimu","colz");
  c1->cd(3); gPad->SetLogy(1); Draw("vpdEastNHits", "");
  c1->cd(4); Draw("vpdEastNHitsVsSimu", "colz");
  c1->cd(5); gPad->SetLogy(1); Draw("vpdEastTacSum","");
  c1->cd(6); Draw("vpdEastTacSumVsSimu","colz");
  c1->Print(psfile,"Title:VPD-VTX East L1 Input");

  
  c1->cd(1); gPad->SetLogy(1); Draw("vpdWestAdcSum","");
  c1->cd(2); Draw("vpdWestAdcSumVsSimu","colz");
  c1->cd(3); gPad->SetLogy(1); Draw("vpdWestNHits", "");
  c1->cd(4); Draw("vpdWestNHitsVsSimu", "colz");
  c1->cd(5); gPad->SetLogy(1); Draw("vpdWestTacSum","");
  c1->cd(6); Draw("vpdWestTacSumVsSimu","colz");
  c1->Print(psfile,"Title:VPD-VTX West L1 Input");


  // VPD-MTD L1 Input
/*
  c1->Clear();
  c1->Divide(2,2);

  c1->cd(1); Draw("vpdMtdEastMaxTacVsSimu","colz");
  c1->cd(2); Draw("vpdMtdWestMaxTacVsSimu","colz");
  c1->cd(3); gPad->SetLogy(1); Draw("vpdMtdEastMaxTac",""); Draw("vpdMtdEastMaxTac","same");
  c1->cd(4); gPad->SetLogy(1); Draw("vpdMtdWestMaxTac",""); Draw("vpdMtdWestMaxTac","same");

  c1->Print(psfile,"Title:VPD-MTD L1 Input");
*/
  // ZDC L1 Input

  c1->Clear();
  c1->Divide(2,3);
  c1->cd(1); gPad->SetLogy(1); Draw("zdcEastTac","");
  c1->cd(2); Draw("zdcEastTacVsSimu","colz");
  c1->cd(3); gPad->SetLogy(1); Draw("zdcWestTac","");
  c1->cd(4); Draw("zdcWestTacVsSimu","colz");
  c1->cd(5); Draw("zdcAdcSum","colztext90");
  c1->cd(6); Draw("zdcAdcSumDiff","colztext90");
  c1->Print(psfile,"Title:ZDC L1 Input");
  cout<<"Printing ZDC L1"<<endl;


  // ZDC, BBC-S, BBC-L, and VPD TAC (or VT201)

  //gStyle->SetOptStat(1110);
  c1->Clear();
  c1->Divide(2,3);
  c1->cd(1); gPad->SetLogy(1); Draw("mBbcSmallTacDiff","");
  c1->cd(2); gPad->SetLogz(1); Draw("mBbcSmallTacDiffVsSimu","");
  c1->cd(3); Draw("mBbcSmallAdcSumTh","colztext");
  c1->cd(4); Draw("mBbcSmallAdcSumThSimu","colztext");
  c1->cd(5); Draw("mBbcLargeAdcSumTh","colztext");
  c1->cd(6); Draw("mBbcLargeAdcSumThSimu","colztext");
/*
  c1->cd(7); gPad->SetLogy(1); Draw("mBbcLargeTacDiff","");
  c1->cd(8); gPad->SetLogy(1); Draw("mBbcLargeTacDiffVsSimu","");
*/
  c1->Print(psfile, "Title: BB101/2");

  c1->Clear();
  c1->Divide(2, 4);
  c1->cd(1); gPad->SetLogy(1); Draw("mZdcTacDiff","");
  c1->cd(2); gPad->SetLogz(1); Draw("mZdcTacDiffVsSimu","");
  gStyle->SetOptStat(0);
  c1->cd(3); Draw("mZdcAdcSumTh","colztext");
  c1->cd(4); Draw("mZdcAdcSumThSimu","colztext");
  c1->cd(5); Draw("mVpdTacDiff","colztext");
  c1->cd(6); Draw("mVpdTacDiffVsSimu","colztext");
  c1->cd(7); Draw("mVpdAdcSumTh","colztext");
  c1->cd(8); Draw("mVpdAdcSumThSimu","colztext");
  c1->Print(psfile, "Title: VT201");
  cout<<"VT201 DONE"<<endl;

  gStyle->SetOptStat(10);

  // BES Vertex

  c1->Clear();
  c1->Divide(2,3);

//  c1->cd(1); Draw("hTofVsBbcLargeEast","colz");
//  c1->cd(2); Draw("hTofVsBbcLargeWest","colz");
  c1->cd(1); Draw("hTofVsBbcSmallEast","colz");
  c1->cd(2); Draw("hTofVsBbcSmallWest","colz");
  c1->cd(3); Draw("hTofVsVpdEast","colz");
  c1->cd(4); Draw("hTofVsVpdWest","colz");
  c1->cd(5); Draw("hTofVsZdcEast","colz");
  c1->cd(6); Draw("hTofVsZdcWest","colz");

  c1->Print(psfile,"Title:BES Vertex");

  // BES Vertex
  c1->Clear();
  c1->Divide(2, 3);
//  c1->cd(1); Draw("hBbcLargeVsSmallEast","colz");
//  c1->cd(2); Draw("hBbcLargeVsSmallWest","colz");
//  c1->cd(3); Draw("hBbcLargeVsVpdEast","colz");
//  c1->cd(4); Draw("hBbcLargeVsVpdWest","colz");
//  c1->cd(3); Draw("hBbcLargeVsZdcEast","colz");
//  c1->cd(4); Draw("hBbcLargeVsZdcWest","colz");
  c1->cd(1); Draw("hBbcSmallVsZdcEast","colz");
  c1->cd(2); Draw("hBbcSmallVsZdcWest","colz");
  c1->cd(3); Draw("hBbcSmallVsVpdEast","colz");
  c1->cd(4); Draw("hBbcSmallVsVpdWest","colz");
  c1->cd(5); Draw("hVpdVsZdcEast","colz");
  c1->cd(6); Draw("hVpdVsZdcWest","colz");

  c1->Print(psfile,"Title:BES Vertex");

  // BES Vertex
  c1->Clear();
  c1->Divide(2, 2);
//  c1->cd(5); Draw("hBbcLargeEastVsWest","colz");
  c1->cd(1); Draw("hBbcSmallEastVsWest","colz");
  c1->cd(2); Draw("hZdcEastVsWest","colz");
  c1->cd(3); Draw("hVpdEastVsWest","colz");

  c1->cd(4); Draw("hBbcSmallVsZdcTac","colz");
//  c1->cd(4); Draw("hBbcSmallVsVpdTac","colz");
//  c1->cd(6); Draw("hVpdVsZdcTac","colz");

  c1->Print(psfile,"Title:BES Vertex");

  // BES Vertex

//  c1->Clear();
//  c1->Divide(2,3);

//  c1->cd(1); Draw("hBbcLargeVsSmallTac","colz");
//  c1->cd(2); Draw("hBbcLargeVsVpdTac","colz");
//  c1->cd(3); Draw("hBbcLargeVsZdcTac","colz");

//  c1->Print(psfile,"Title:BES Vertex");

  // FMS QT Crates

  c1->Clear();
  c1->Divide(2,2);

  c1->cd(1); Draw("hQT1ADC","colz");
  c1->cd(2); Draw("hQT3ADC","colz");
  c1->cd(3); Draw("hQT2ADC","colz");
  c1->cd(4); Draw("hQT4ADC","colz");

  c1->Print(psfile,"Title:FMS QT Crates");
  cout<<"FMS QT Crates Done"<<endl;
  // FMS L0 Input

  c1->Clear();
  c1->Divide(2,6);

  for(int ichn = 0; ichn < 12; ichn++){
    c1->cd(ichn+1);
    Draw(Form("mFM0%.2d", ichn+1), "colz");
  }
  c1->Print(psfile,"Title:FMS L0 Input");
  cout<<"FMS L0 Done"<<endl;
  // FMS L1 Input
  //fm101
  c1->Clear();
  c1->Divide(2,6);
  for(int ichn = 0; ichn < 2; ichn++){
    c1->cd(6*ichn+1);
    Draw(Form("mFM101BS_%d", ichn), "colztext");
    c1->cd(6*ichn+2);
    Draw(Form("mFM101BSsim_%d", ichn), "colztext");
    c1->cd(6*ichn+3);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM101D_%d", ichn), "");
    c1->cd(6*ichn+4);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM101Dsim_%d", ichn), "");
    c1->cd(6*ichn+5);
    Draw(Form("mFM101JP_%d", ichn), "colz");
    c1->cd(6*ichn+6);
    Draw(Form("mFM101JPsim_%d", ichn), "colztext");
  }
  c1->Print(psfile,"Title:FMS L1 Input : FM101");
  cout<<"FMS L1 Input: FM101 Done"<<endl;
  //fm102
  c1->Clear();
  c1->Divide(2,6);
  for(int ichn = 0; ichn < 2; ichn++){
    c1->cd(6*ichn+1);
    Draw(Form("mFM102BS_%d", ichn), "colztext");
    c1->cd(6*ichn+2);
    Draw(Form("mFM102BSsim_%d", ichn), "colztext");
    c1->cd(6*ichn+3);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM102D_%d", ichn), "");
    c1->cd(6*ichn+4);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM102Dsim_%d", ichn), "");
    c1->cd(6*ichn+5);
    Draw(Form("mFM102JP_%d", ichn), "colz");
    c1->cd(6*ichn+6);
    Draw(Form("mFM102JPsim_%d", ichn), "colztext");
  }
  c1->Print(psfile,"Title:FMS L1 Input : FM102");
  cout<<"FMS L1 Input: FM102 Done"<<endl;
  //fm103 -- 1
  c1->Clear();
  c1->Divide(2,6);
  for(int ichn = 0; ichn < 2; ichn++){
    c1->cd(6*ichn+1);
    Draw(Form("mFM103BS_%d", ichn), "colztext");
    c1->cd(6*ichn+2);
    Draw(Form("mFM103BSsim_%d", ichn), "colztext");
    c1->cd(6*ichn+3);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM103J_%d", ichn), "");
    c1->cd(6*ichn+4);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM103Jsim_%d", ichn), "");
    c1->cd(6*ichn+5);
    Draw(Form("mFM103JP_%d", ichn), "colz");
    c1->cd(6*ichn+6);
    Draw(Form("mFM103JPsim_%d", ichn), "colztext");
  }
  //fm103 -- 2
  c1->Print(psfile,"Title:FMS L1 Input : FM103 -- 1");
  cout<<"FMS L1 Input: FM103 -- 1 Done"<<endl;
  c1->Clear();
  c1->Divide(2,6);
  for(int ichn = 2; ichn < 4; ichn++){
    c1->cd(6*(ichn-2)+1);
    Draw(Form("mFM103BS_%d", ichn), "colztext");
    c1->cd(6*(ichn-2)+2);
    Draw(Form("mFM103BSsim_%d", ichn), "colztext");
    c1->cd(6*(ichn-2)+3);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM103J_%d", ichn), "");
    c1->cd(6*(ichn-2)+4);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM103Jsim_%d", ichn), "");
    c1->cd(6*(ichn-2)+5);
    Draw(Form("mFM103JP_%d", ichn), "colz");
    c1->cd(6*(ichn-2)+6);
    Draw(Form("mFM103JPsim_%d", ichn), "colztext");
  }
  c1->Print(psfile,"Title:FMS L1 Input : FM103 -- 2");
  cout<<"FMS L1 Input: FM103 -- 2 Done"<<endl;

  //fm104 -- 1
  c1->Clear();
  c1->Divide(2,6);
  for(int ichn = 0; ichn < 2; ichn++){
    c1->cd(6*ichn+1);
    Draw(Form("mFM104BS_%d", ichn), "colztext");
    c1->cd(6*ichn+2);
    Draw(Form("mFM104BSsim_%d", ichn), "colztext");
    c1->cd(6*ichn+3);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM104J_%d", ichn), "");
    c1->cd(6*ichn+4);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM104Jsim_%d", ichn), "");
    c1->cd(6*ichn+5);
    Draw(Form("mFM104JP_%d", ichn), "colz");
    c1->cd(6*ichn+6);
    Draw(Form("mFM104JPsim_%d", ichn), "colztext");
  }
  c1->Print(psfile,"Title:FMS L1 Input : FM104");
  cout<<"FMS L1 Input: FM104 Done"<<endl;

  //fm104 -- 2
  c1->Clear();
  c1->Divide(2,6);
  for(int ichn = 2; ichn < 4; ichn++){
    c1->cd(6*(ichn-2)+1);
    Draw(Form("mFM104BS_%d", ichn), "colztext");
    c1->cd(6*(ichn-2)+2);
    Draw(Form("mFM104BSsim_%d", ichn), "colztext");
    c1->cd(6*(ichn-2)+3);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM104J_%d", ichn), "");
    c1->cd(6*(ichn-2)+4);
    gPad->SetLogy(1);
    gPad->SetLogx(1);
    Draw(Form("mFM104Jsim_%d", ichn), "");
    c1->cd(6*(ichn-2)+5);
    Draw(Form("mFM104JP_%d", ichn), "colz");
    c1->cd(6*(ichn-2)+6);
    Draw(Form("mFM104JPsim_%d", ichn), "colztext");
  }
  c1->Print(psfile,"Title:FMS L1 Input : FM104 -- 2");
  cout<<"FMS L1 Input: FM104 -- 2 Done"<<endl;

  // FMS L2 Input

  c1->Clear();
  c1->Divide(2,4);
  for(int ichn = 0; ichn < 4; ichn++){
    c1->cd(2*ichn+1);
    Draw(Form("mFP201BS_FM10%d", ichn+1), "colztext");
    c1->cd(2*ichn+2);
    Draw(Form("mFP201BSsim_FM10%d", ichn+1), "colztext");
  }
  c1->Print(psfile,"Title:FMS L2 Input : Board Sum");
  cout<<"FMS L2 Input : Board Sum Done"<<endl;

  c1->Clear();
  c1->Divide(2,4);
  for(int ichn = 0; ichn < 4; ichn++){
    c1->cd(2*ichn+1);
    Draw(Form("mFP201JP_FM10%d", ichn+1), "colz");
    c1->cd(2*ichn+2);
    Draw(Form("mFP201JPsim_FM10%d", ichn+1), "colz");
  }
  c1->Print(psfile,"Title:FMS L2 Input : Jet Patch");
  cout<<"FMS L2 Input : Jet Patch Done"<<endl;

  // FPD QT Crates
/*
  c1->Clear();
  c1->Divide(2,2);

  c1->cd(1); Draw("hFE001","colz");
  c1->cd(2); Draw("hFE002","colz");
  c1->cd(3); Draw("hFE003","colz");
  c1->cd(4); Draw("hFE004","colz");
//  c1->cd(5); Draw("hFE101","colz");
//  c1->cd(6); Draw("hFE101Diff","colz");

  c1->Print(psfile,"Title:FPD QT Crates");
*/
  // TCU Input (ch0-3)

  c1->Clear();
  c1->Divide(2,4);

  c1->cd(1); Draw("LD301Ch0","colztext90");
  c1->cd(2); Draw("LD301Ch0Diff","colztext90");
  c1->cd(3); Draw("LD301Ch1","colztext90");
  c1->cd(4); Draw("LD301Ch1Diff","colztext90");
  c1->cd(5); Draw("LD301Ch2","colztext90");
  c1->cd(6); Draw("LD301Ch2Diff","colztext90");
  c1->cd(7); Draw("LD301Ch3","colztext90");
  c1->cd(8); Draw("LD301Ch3Diff","colztext90");

  c1->Print(psfile,"Title:TCU Input (ch0-3)");

  // TCU Input (ch4-7)

  c1->Clear();
  c1->Divide(2,4);

  c1->cd(1); Draw("LD301Ch4","colztext90");
  c1->cd(2); Draw("LD301Ch4Diff","colztext90");
  c1->cd(3); Draw("LD301Ch5","colztext90");
  c1->cd(4); Draw("LD301Ch5Diff","colztext90");
  c1->cd(5); Draw("LD301Ch6","colztext90");
  c1->cd(6); Draw("LD301Ch6Diff","colztext90");
  c1->cd(7); Draw("LD301Ch7","colztext90");
  c1->cd(8); Draw("LD301Ch7Diff","colztext90");

  c1->Print(Form("%s)",psfile),"Title:TCU Input (ch4-7)");

#if 0
  // More pages...

  DrawBitErrorsHistogram(c1,"hFP201BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM101BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM102BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM103BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM001BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM002BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM003BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM004BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM005BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM006BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM007BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM008BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM009BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM010BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM011BitErrorsCh",psfile);
  DrawBitErrorsHistogram(c1,"hFM012BitErrorsCh",psfile);
#endif

  // Delete canvas

  delete c1;
}

void labelB101Histogram(const char* hname)
{
  TH2F* h = (TH2F*)gFile->Get(hname);
  for (int ch = 6; ch <= 30; ch += 6) {
    double y1 = h->GetYaxis()->GetBinLowEdge(1);
    double y2 = h->GetYaxis()->GetBinUpEdge(h->GetYaxis()->GetNbins());
    TLine* line = new TLine(ch, y1, ch, y2);
    line->SetLineColor(TEXTCOLOR);
    line->Draw("same");
  }

  for (int ch = 0; ch < 36; ch += 6) {
    double x = ch + 0.5;
    double y = h->GetYaxis()->GetBinUpEdge(h->GetYaxis()->GetNbins());
    TString dsm = Form("BC10%d", ch/6+1);
    TLatex* text = new TLatex(x, y * 0.9, dsm);
    text->SetTextColor(TEXTCOLOR);
    text->SetTextSize(TEXTSIZE);
    text->Draw("same");    
  }
}

void labelE101Histogram(const char* hname)
{
  TH2F* h = (TH2F*)gFile->Get(hname);
  double y1 = h->GetYaxis()->GetBinLowEdge(1);
  double y2 = h->GetYaxis()->GetBinUpEdge(h->GetYaxis()->GetNbins());
  TLine* line = new TLine(6,y1,6,y2);
  line->SetLineColor(TEXTCOLOR);
  line->Draw("same");
  TLatex* text1 = new TLatex(2,y2*0.9,"EE101");
  TLatex* text2 = new TLatex(8,y2*0.9,"EE102");
  text1->SetTextColor(TEXTCOLOR);
  text2->SetTextColor(TEXTCOLOR);
  text1->Draw("same");
  text2->Draw("same");
}

void labelE001Histogram(const char* hname)
{
  TH2F* h = (TH2F*)gFile->Get(hname);
  for (int triggerPatch = 15; triggerPatch < 90; triggerPatch += 15) {
    double y1 = h->GetYaxis()->GetBinLowEdge(1);
    double y2 = h->GetYaxis()->GetBinUpEdge(h->GetYaxis()->GetNbins());
    TLine* line = new TLine(triggerPatch, y1, triggerPatch, y2);
    line->SetLineColor(TEXTCOLOR);
    line->Draw("same");
  }

  for (int crate = 1; crate <= 6; ++crate) {
    double x = ((crate+3)%6)*15+3.0;
    double y = h->GetYaxis()->GetBinUpEdge(h->GetYaxis()->GetNbins());
    TString crateString = Form("crate %d", crate);
    TLatex* text = new TLatex(x, y * 0.9, crateString);
    text->SetTextColor(TEXTCOLOR);
    text->SetTextSize(TEXTSIZE);
    text->Draw("same");    
  }
}

void Draw(const char* hname, const char* opt)
{
  TH1* h = (TH1*)gFile->Get(hname);
  if(h->GetEntries()) gPad->SetLogz(1);
  if (strstr(hname,"BitErrors")) h->SetFillColor(kRed);
  h->Draw(opt);
}

void DrawProY(const char* hname, int bina, int binb, const char* opt)
{
  TH2* hh = (TH2*)gFile->Get(hname);
  TH1* h_y = hh->ProjectionY(Form("%s_%d_%d_py", hname, bina, binb), bina, binb);
  h_y->GetXaxis()->SetTitle(Form("%s (%d - %d) JP ADC", hname, bina, binb));
  
  if(h_y->GetEntries()) gPad->SetLogy(1);
  h_y->Draw(opt);
}

/*
void DrawBitErrorsHistogram(TCanvas* c1, const char* hname, const char* psfile)
{
  c1->Clear();
  c1->Divide(2,4);

  for (int ch = 0; ch < 8; ++ch) {
    c1->cd(ch+1);
    Draw(Form("%s%d",hname,ch),"");
  }

  c1->Print(psfile);
}
*/
