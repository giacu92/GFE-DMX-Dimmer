//////////////
//  STROBO  //
//////////////

int strobo() //return period for debugging
{
  timeElapsed = micros() - startZeroTime;

  if (timeElapsed > period)
  {
    detachInterrupt(zeroCrossInterrupt);
    
    digitalWrite(dmx_pin[0], HIGH);  // fire the Triac 1
    digitalWrite(dmx_pin[1], HIGH);  // fire the Triac 2
    digitalWrite(dmx_pin[2], HIGH);  // fire the Triac 3
    digitalWrite(dmx_pin[3], HIGH);  // fire the Triac 4

    //cli();
    delay(25);
    //sei();

    digitalWrite(dmx_pin[0], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)
    digitalWrite(dmx_pin[1], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)
    digitalWrite(dmx_pin[2], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)
    digitalWrite(dmx_pin[3], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)

    attachInterrupt(digitalPinToInterrupt(3), zeroCrossInterrupt, FALLING);  
  }

  return period;
}
