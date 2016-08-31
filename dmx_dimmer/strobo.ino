//////////////
//  STROBO  //
//////////////

int strobo() //return period to debug
{
  timeElapsed = micros() - startZeroTime;

  if (timeElapsed > period)
  {
    digitalWrite(dmx_pin[0], HIGH);  // fire the Triac
    digitalWrite(dmx_pin[1], HIGH);  // fire the Triac
    digitalWrite(dmx_pin[2], HIGH);  // fire the Triac
    digitalWrite(dmx_pin[3], HIGH);  // fire the Triac

    delay(25);           //pause briefly to ensure the triac turned on

    digitalWrite(dmx_pin[0], LOW);   // turn off the Triac gate (triac will not turn off until next zero cross)
    digitalWrite(dmx_pin[1], LOW);   // turn off the Triac gate (triac will not turn off until next zero cross)
    digitalWrite(dmx_pin[2], LOW);   // turn off the Triac gate (triac will not turn off until next zero cross)
    digitalWrite(dmx_pin[3], LOW);   // turn off the Triac gate (triac will not turn off until next zero cross)
  }

  return period;
}
