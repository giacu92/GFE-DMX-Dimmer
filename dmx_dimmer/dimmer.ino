//////////////
//  DIMMER  //
//////////////

void dimmer()
{
  timeElapsed = micros() - startZeroTime;
  
  for (int ch = 0; ch < DMX_NUM_FIXTURES; ch++)
  {
    if (zeroCross[ch] && timeElapsed > brightness[ch] && timeElapsed < brightness[ch] + 50)
    { 
      digitalWrite(dmx_pin[ch], HIGH); // fire the Triac
      delayMicroseconds(10);           // pause briefly to ensure the Triac turned on
      digitalWrite(dmx_pin[ch], LOW);  // turn off the Triac gate (Triac will not turn off until next zero cross)
      
      zeroCross[ch] = false;
    }
  }
}
