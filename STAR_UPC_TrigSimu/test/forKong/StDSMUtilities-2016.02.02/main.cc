#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <numeric>
#include <fstream>
#include "DSMSimulator_2016.hh"

struct DSMSimulatorRunner {
  DSMSimulator& sim;

  explicit DSMSimulatorRunner(DSMSimulator& s) : sim(s) {}

  int operator()(int totalevents, const char* filename)
  {
    sscanf(basename(filename),"run%d.%d.dat",&sim.runNumber,&sim.seqNumber);

    if (!sim.valid) {
      sim.loadRegisters();
      sim.loadSlewCorrections();
      sim.valid = true;
    }

    printf("filename=%s\n",filename);

    int fd = open(filename,O_RDONLY);

    if (fd == -1) {
      perror("open");
      exit(EXIT_FAILURE);
    }

    struct stat sbuf;

    if (fstat(fd,&sbuf) == -1) {
      perror("stat");
      exit(EXIT_FAILURE);
    }

    if (!sbuf.st_size) {
      close(fd);
      return 0;
    }

    void* addr = mmap(NULL,sbuf.st_size,PROT_WRITE,MAP_PRIVATE,fd,0);

    if (addr == MAP_FAILED) {
      perror("mmap");
      exit(EXIT_FAILURE);
    }

    int nevents = sim.eventLoop((char*)addr,(char*)addr+sbuf.st_size);
    printf("nevents=%d\n",nevents);
    fflush(stdout);

    totalevents += nevents;

    if (munmap(addr,sbuf.st_size) == -1) {
      perror("munmap");
      exit(EXIT_FAILURE);
    }

    close(fd);

    return totalevents;
  }
};

int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: %s run10021015.1.dat ...\n\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  DSMSimulator_2016 sim;
  char filename[FILENAME_MAX];

  sprintf(filename,"dsm.%d.root",getpid());
  sim.setFile(filename);
  sim.setFullDSMTree(1);
  sim.setEMCStatus(1);
  sim.setVTXStatus(1);
  sim.setTOFStatus(1);
  sim.setFPDStatus(1);
  sim.init();

  // Run DSM simulator on each trigger data file accumulating number of events
  int nevents = accumulate(argv+1,argv+argc,0,DSMSimulatorRunner(sim));

  // Save number of events to text file
  sprintf(filename,"dsmEvents.%d.txt",getpid());
  ofstream dsmEventsTextFile(filename);
  dsmEventsTextFile << nevents << endl;
  dsmEventsTextFile.close();

  sim.finish();

  exit(EXIT_SUCCESS);
}
