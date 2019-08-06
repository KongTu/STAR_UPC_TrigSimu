int slew_correction(int adc, int chn, int slew[][8])
{
  for(int ii = 0; ii < 8; ii++){
    if(adc <= slew[chn][ii]){
      return slew[chn+4][ii];
    }
  }
  return 0;
}
