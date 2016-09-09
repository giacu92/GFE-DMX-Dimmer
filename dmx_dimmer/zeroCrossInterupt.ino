void zeroCrossInterrupt()
{
  startZeroTime = micros();
  dmx_state = DMX_IDLE;
  
  for(int ch = 0; ch < DMX_NUM_FIXTURES; ch++)
  {
    zeroCross[ch]=true;
    brightness[ch]=map(dmx_data[ch], 0, 255, 9700,0); //mapping the delay time from 0 to 9700us, max theorical was 10.000us (half sinewave)
    period = 1e9;
  }
  
  if(dmx_data[4] > 3)
  {
    brightness[0] = brightness[1] = brightness[2] = brightness[3] = 1e6;
    period = round(map(dmx_data[4], 0, 255, 75000, 975000)); //compute the time period to wait between two flashes (from 75ms to 975ms)
  }
}
