ISR(USART_RX_vect)
{
  static  uint16_t chan_cnt;
  unsigned char status = UCSR0A;
  unsigned char data = UDR0;

  switch (dmx_state)
  {
    case DMX_IDLE:
      if (status & (1 << FE0)) //if a MAB detected goto DMX_BREAK
      {
        dmx_addr = 0;
        dmx_state = DMX_BREAK;
        update = 1;
      }
      break;

    case DMX_BREAK: //if the first bit is 0 (valid frame starts here) goto DMX_START
      if (data == 0)
      {
        dmx_state = DMX_START;
      }
      else
      {
        dmx_state = DMX_IDLE;
      }
      break;

    case DMX_START: //ignore the dmx address not equal to device_address
      dmx_addr++;
      if (dmx_addr == dmx_start_addr) //the next DMX_NUM_CHANNELS bytes we need, store 'em and goto RUN
      {
        chan_cnt = 0;
        dmx_data[chan_cnt++] = data;
        dmx_state = DMX_RUN;
      }
      break;

    case DMX_RUN:
      dmx_data[chan_cnt++] = data;
      //chan_cnt = 0;
      if (chan_cnt >= DMX_NUM_CHANNELS)
      {
        dmx_state = DMX_IDLE;
      }
      break;

    default:
      dmx_state = DMX_IDLE;
      break;
  }
}
