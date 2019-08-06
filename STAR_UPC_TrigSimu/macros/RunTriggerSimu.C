void RunTriggerSimu(int nevents = 100,
//data test file:
const char* indir = "root://xrdstar.rcf.bnl.gov:1095//home/starlib/home/starreco/reco/dAu200_production_2016/ReversedFullField/P17ib/2016/136/17136038/st_upc_17136038_raw_4000004.MuDst.root"
//embedding test file:
//const char* indir = "/gpfs01/star/pwg/ztu/STARlight/starsim/output/slight16dAu_zerobias_incohVM_100k_Emb_v6/0004/out/output.MuDst.root"			 
)
{
//  cout<<"MuDst file is "<<MuDst<<endl;

  gROOT->Macro("loadMuDst.C");
  gROOT->Macro("LoadLogger.C");

  gSystem->Load("StDetectorDbMaker");
  gSystem->Load("StDaqLib");
  gSystem->Load("StEmcRawMaker");
  gSystem->Load("StEmcADCtoEMaker");
  gSystem->Load("StDbBroker");
  gSystem->Load("St_db_Maker");
  gSystem->Load("StEEmcUtil");
  gSystem->Load("StEEmcDbMaker");
  gSystem->Load("StEmcTriggerMaker");
  gSystem->Load("StTriggerUtilities");  
  //gSystem->Load(".sl73_gcc485/lib/libStTriggerUtilities.so");
  gSystem->Load("StTriggerFilterMaker");
  
   StChain *chain = new StChain;

   StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,indir, "","",1000);

   StMuDbReader* muDstDb = StMuDbReader::instance();

   St_db_Maker* starDb = new St_db_Maker("StarDb","MySQL:StarDb");

   StEEmcDbMaker* eemcDb = new StEEmcDbMaker;

   //   StSpinDbMaker* spinDb = new StSpinDbMaker;

   StEmcADCtoEMaker* adc = new StEmcADCtoEMaker;
   adc->saveAllStEvent(true);

   StTriggerSimuMaker* simuTrig = new StTriggerSimuMaker;
   //use online or offline option
   //simuTrig->useOnlineDB();
   simuTrig->useOfflineDB();
   simuTrig->setMC(0);

   //bbc is not used in run12 analysis
   simuTrig->useBbc();
   simuTrig->useBemc();
   simuTrig->useEemc();
   //use online or offline bemc tower pedestals and statuses
   simuTrig->bemc->setConfig(StBemcTriggerSimu::kOnline);
   //simuTrig->bemc->setConfig(StBemcTriggerSimu::kOnline);
   //define triggers with trigger index, trigger name, offline Id, onbits, offbits, onbits1, onbits2, onbits3, offbits1, offbits2, offbits3
   //this method need to be called only when the trigger definitions in online and offline are not correct
   //simuTrig->emc->defineTrigger(8, "JP0", 380401, 0x0, 0x0, 0x80000000, 0x0, 0x0, 0x0, 0x0, 0x1);
   //set jet patch thresholds only used when the jet patch thresholds in online and offline database not correct
   //jp-th0 set to 28
   //simuTrig->setBarrelJetPatchTh(0,28);
   //simuTrig->setOverlapJetPatchTh(0,28);
   //simuTrig->setEndcapJetPatchTh(0,28);
   //set high tower thresholds only used when the jet patch thresholds in online and offline database not correct
   //simuTrig->setBarrelHighTowerTh(0, 11);
   //simuTrig->setEndcapHighTowerTh(0, 25);
   // Run
   chain->Init();
   int nEvents = muDstMaker->chain()->GetEntries();
   cout << "number of events ~ " << nEvents << endl;
   for(int iEvent = 0; iEvent < nEvents; iEvent++)
     {
       chain->Clear();
       int status = chain->Make(iEvent);
       if(status == kStSkip) continue;
       if(status % 10 == kStEOF || status % 10 == kStFatal) break;
       std::cout<<"trigger simulator: UPC-Jpsi fired = "<< simuTrig->isTrigger(530703) <<endl;
       std::cout<<"trigger simulator: UPC-Jpsi fired = "<< simuTrig->isTrigger(530701) <<endl;
       std::cout<<"trigger simulator: UPC-Jpsi fired = "<< simuTrig->isTrigger(530702) <<endl;
     }
   //chain->EventLoop(nevents);
}