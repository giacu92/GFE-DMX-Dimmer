//////////////
//  STROBO  //
//////////////

void strobo() //return period for debugging
{
  digitalWrite(dmx_pin[0], HIGH);  // fire the Triac 1
  digitalWrite(dmx_pin[1], HIGH);  // fire the Triac 2
  digitalWrite(dmx_pin[2], HIGH);  // fire the Triac 3
  digitalWrite(dmx_pin[3], HIGH);  // fire the Triac 4

  delay(100);

  digitalWrite(dmx_pin[0], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)
  digitalWrite(dmx_pin[1], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)
  digitalWrite(dmx_pin[2], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)
  digitalWrite(dmx_pin[3], LOW);   // turn off the Triac gate (triac wont turn off until next zero cross)

  delay(period);
    
  
}
