#include "bits.hh"
#include "Board.hh"
#include "mix_tf001_2014_c.hh"

void mix_tf001_2014_c(Board& tf001)
{
  const int R0 = tf001.registers[0]; //TOF-upc-th(8)
  const int R1 = tf001.registers[1]; //TOF_DAQ10k_th(8)

  int tf00xout[6];
  int tf00xmult[21];

  for(int ichn = 0; ichn < 7; ichn++){
    tf00xout[ichn] = tf001.channels[ichn];
    for(int isub = 0; isub < 3; isub++){
      tf00xmult[3*ichn+isub] = getbits(tf00xout[ichn], isub*5, 5);
    }
  }
  
  tf00xmult[20] = 0;

  for(int ii = 0; ii < 20; ii++){
    if(tf00xmult[ii] > 24) tf00xmult[ii] = 0;
  }

  int sum02 = tf00xmult[0] + tf00xmult[1] + tf00xmult[2];
  int sum34 = tf00xmult[3] + tf00xmult[4];
  int sum57 = tf00xmult[5] + tf00xmult[6] + tf00xmult[7];
  int sum89 = tf00xmult[8] + tf00xmult[9];
  int sum1012 = tf00xmult[10] + tf00xmult[11] + tf00xmult[12];
  int sum1314 = tf00xmult[13] + tf00xmult[14];
  int sum1517 = tf00xmult[15] + tf00xmult[16] + tf00xmult[17];
  int sum1819 = tf00xmult[18] + tf00xmult[19];

  int sum04 = sum02 + sum34; // west low hour
  int sum59 = sum57 + sum89; // west high hour
  int sum1014 = sum1012 + sum1314; // east low hour
  int sum1519 = sum1517 + sum1819; // east high hour

  int sum09 = sum04 + sum59;
  int sum1019 = sum1014 + sum1519;

  int upc04 = sum04 > R0;
  int upc59 = sum59 > R0;
  int upc1014 = sum1014 > R0;
  int upc1519 = sum1519 > R0;

  int daq10k04 = sum04 > R1;
  int daq10k59 = sum59 > R1;
  int daq10k1014 = sum1014 > R1;
  int daq10k1519 = sum1519 > R1;

  int sum019 = sum09 + sum1019;

  tf001.output = 0;
  tf001.output =
    sum019   |
    upc04 << 10 |
    upc59 << 11 |
    upc1014 << 12 |
    upc1519 << 13 |
    daq10k04 << 16 |
    daq10k59 << 17 |
    daq10k1014 << 18 |
    daq10k1519 << 19; 
}
