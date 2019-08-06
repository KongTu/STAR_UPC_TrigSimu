#
# Makefile for 2011 DSM simulator
#
#PATH=/afs/rhic.bnl.gov/star/ROOT/5.34.09/.sl64_gcc482/root/bin
CXXFLAGS = -Wall -O2 `root-config --cflags` -I/usr/include/mysql -fvisibility=hidden -O -fno-inline

dsm.exe:	main.o DSMSimulator_2016.o qt32b_l0_v6_d.o qt32b_l0_v6_f.o qt32b_l0_v5_f.o qt32b_l0_v7_6.o\
qt32b_fms_2009_a.o fms_fm001_2015_a.o fms_fm005_2015_a.o fms_fm006_2015_a.o fms_fm101_2015_a.o fms_fm103_2015_a.o l1_fp201_2015_a.o qt32b_fpe_2009_a.o \
bemc_bw001_2014_b.o bemc_bw003_2014_b.o bemc_be001_2014_b.o bemc_be003_2014_b.o eemc_ee001_2009_b.o eemc_ee002_2009_b.o bemc_bc101_2014_b.o eemc_ee101_2009_a.o eemc_ee102_2009_a.o l1_em202_2012_a.o l1_em201_2014_b.o\
l1_vt201_2016_a.o l1_tf201_2016_a.o mix_tf001_2014_c.o mix_tf101_2014_b.o mix_mt101_2016_a.o mix_pp101_2015_a.o bbc_bb101_2009_a.o bbc_bb102_2010_b.o bbc_vp101_2016_a.o bbc_zd101_2016_a.o bbc_bb101_2016_a.o l1_vt201_2016_b.o l1_tf201_2016_b.o\
slew_correction.o
	$(CXX) -m32 `root-config --libs` $^ -o $@

main.o:	DSMSimulator_2016.hh

DSMSimulator_2016.o:	DSMSimulator_2016.hh Crate.hh Board.hh DSMSimulator.hh trgUtil_2009.hh

clean:
	rm -f *.o *~ dsm.exe dsm.*.root dsmEvents.txt
