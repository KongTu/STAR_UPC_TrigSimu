//
// Pibero Djawotho <pibero@comp.tamu.edu>
// Texas A&M University Cyclotron Institute
// 24 Jan 2009
//

#include <fstream>
#include <cstdlib>

void GetRunLogSummary(int runNumber = 10014002)
{
  // Defined in StRoot/RTS/include/rtsSystems.h
  const char* detectorNames[] = {
    "tpc", "svt", "tof", "btow", "fpd", "ftp", "ext", "ric", // 0-7
    "trg", "l3", "sc", "ext2", "pmd", "ssd", "etow", "daq",  // 8-15
    "fgt", "pp", "bsmd", "esmd", "tpx", "pxl", "mtd", "ist", // 16-23
    "sst", "rpii", "gmt", "l4"                               // 24-27
  };

  // I want these quantities out of the STAR RunLog and Conditions_rts databases for this run:

  // From runDescriptor table:
  time_t startRunTime;
  time_t endRunTime;
  TString glbSetupName;
  TString tier1File;

  // From detectorSet table:
  vector<int> detectorID;

  // From daqSummary table:
  int numberOfEvents = 0;

  // From beamInfo table:
  int blueFillNumber;
  int yellowFillNumber;

  // Open connection to STAR RunLog database for Run 9
  const char* database = "mysql://onldb.starp.bnl.gov:3501/RunLog?timeout=60";
  const char* user = "";
  const char* pass = "";
  TMySQLServer* mysql = TMySQLServer::Connect(database, user, pass);

  if (mysql) {
    // Query runDescriptor table
    TString query = Form("select startRunTime,endRunTime,glbSetupName from runDescriptor where runNumber=%d", runNumber);
    TMySQLResult* result = (TMySQLResult*)mysql->Query(query);
    if (result) {
      TMySQLRow* row = (TMySQLRow*)result->Next();
      if (row) {
        startRunTime = strtoul(row->GetField(0),NULL,0);
        endRunTime = strtoul(row->GetField(1),NULL,0);
	glbSetupName = row->GetField(2);
      }
    }

    // Query detectorSet table
    query = Form("select detectorID from detectorSet where runNumber=%d", runNumber);
    result = (TMySQLResult*)mysql->Query(query);
    if (result) {
      TMySQLRow* row;
      while (row = (TMySQLRow*)result->Next()) {
	detectorID.push_back(atoi(row->GetField(0)));
      }
    }

    // Query daqSummary table
    query = Form("select numberOfEvents from daqSummary where runNumber=%d", runNumber);
    result = (TMySQLResult*)mysql->Query(query);
    if (result) {
      TMySQLRow* row = (TMySQLRow*)result->Next();
      if (row) numberOfEvents = atoi(row->GetField(0));
    }

    // Query beamInfo
    query = Form("select blueFillNumber,yellowFillNumber from beamInfo where runNumber=%d",runNumber);
    result = (TMySQLResult*)mysql->Query(query);
    if (result) {
      TMySQLRow* row = (TMySQLRow*)result->Next();
      if (row) {
	blueFillNumber   = atoi(row->GetField(0));
	yellowFillNumber = atoi(row->GetField(1));
      }
    }

    // Select Conditions_rts database
    mysql->SelectDataBase("Conditions_rts");

    // Query run table
    query = Form("select TIER1_name from run where run_number=%d", runNumber);
    result = (TMySQLResult*)mysql->Query(query);
    if (result) {
      TMySQLRow* row = (TMySQLRow*)result->Next();
      if (row) tier1File = row->GetField(0);
    }

    // Close connection to database
    mysql->Close();

    // Save result of queries
    ofstream out;

    out.open("startRunTime.txt");
    out << asctime(localtime(&startRunTime));
    out.close();

    out.open("endRunTime.txt");
    out << asctime(localtime(&endRunTime));
    out.close();

    out.open("duration.txt");
    time_t duration = (endRunTime > startRunTime) ? endRunTime - startRunTime : 0;
    out << duration << endl;
    out.close();

    out.open("glbSetupName.txt");
    out << glbSetupName << endl;
    out.close();

    out.open("numberOfEvents.txt");
    out << numberOfEvents << endl;
    out.close();

    out.open("detectorID.txt");
    for (size_t i = 0; i < detectorID.size(); ++i)
      out << detectorNames[detectorID[i]] << " ";
    out << endl;
    out.close();

    out.open("tier1File.txt");
    out << tier1File << endl;
    out.close();

    out.open("blueFillNumber.txt");
    out << blueFillNumber << endl;
    out.close();

    out.open("yellowFillNumber.txt");
    out << yellowFillNumber << endl;
    out.close();
  }
  else {
    // Connection to database failed
    ofstream out;

    out.open("startRunTime.txt");
    out << "unknown" << endl;
    out.close();

    out.open("duration.txt");
    out << "unknown" << endl;
    out.close();

    out.open("glbSetupName.txt");
    out << "unknown" << endl;
    out.close();

    out.open("numberOfEvents.txt");
    out << "unknown" << endl;
    out.close();

    out.open("detectorID.txt");
    out << "unknown" << endl;
    out.close();

    out.open("tier1File.txt");
    out << "unknown" << endl;
    out.close();

    out.open("blueFillNumber.txt");
    out << "unknown" << endl;
    out.close();

    out.open("yellowFillNumber.txt");
    out << "unknown" << endl;
    out.close();
  }
}
