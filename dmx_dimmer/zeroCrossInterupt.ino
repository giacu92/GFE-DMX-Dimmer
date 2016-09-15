void zeroCrossInterrupt()
{
  startZeroTime = micros();
  dmx_state = DMX_IDLE;
  
  for(int ch = 0; ch < DMX_NUM_FIXTURES; ch++)
  {
    zeroCross[ch]  = true;
    brightness[ch] = map(dmx_data[ch], 0, 265, 9700,0); //mapping the delay time from 0 to 9700us, max theorical was 10.000us (half sinewave)
  }
  
  if(dmx_data[4] > 39) // off below 40 to avoid mistake switching
  {
    strobe = true;
    period = round(map(dmx_data[4], 40, 265, 1000, 100)); //compute the time period to wait between two flashes (from 75ms to 975ms)
    //detachInterrupt(zeroCrossInterrupt);
  }
  else
    strobe = false;
}
