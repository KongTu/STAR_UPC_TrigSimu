//
// Pibero Djawotho <pibero@tamu.edu>
// Texas A&M University
// 12 Feb 2011
//

#ifndef DSM_SIMULATOR_HH
#define DSM_SIMULATOR_HH

class DSMSimulator {
public:
  explicit DSMSimulator() : runNumber(-1), seqNumber(-1), valid(false) {}
  virtual ~DSMSimulator() {}
  virtual int eventLoop(char* first, char* last) = 0;
  virtual void loadRegisters() = 0;
  virtual void loadSlewCorrections() = 0;

  int runNumber;
  int seqNumber;
  bool valid;			// registers loaded
};

#endif	// DSM_SIMULATOR_HH
