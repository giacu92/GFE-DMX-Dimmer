#define DMX_NUM_CHANNELS 4

enum
{
  DMX_IDLE,
  DMX_BREAK,
  DMX_START,
  DMX_RUN
};

volatile unsigned char dmx_state;

unsigned int dmx_start_addr = 65; //start address for the DMX frame to be interpreted
unsigned int dmx_addr;            //current address of the DMX frame

unsigned long startZeroTime=0;
unsigned long timeElapsed=0;//Time until end of cycle
boolean zeroCross[]={false,false,false,false};
int brightness[4];

unsigned char dmx_pin[DMX_NUM_CHANNELS] = {6, 7, 8, 12}; //led pins
unsigned char dmx_data[DMX_NUM_CHANNELS]; //hold the dmx data

volatile unsigned char update; //whan to update pins

void setup()
{
  update = 0; //flag idle
  dmx_state = DMX_IDLE; //default DMX state

  delay(500);

  attachInterrupt(1,zeroCrossInterupt,FALLING);
  
  for (int i=0; i<DMX_NUM_CHANNELS; i++)
  {
    pinMode(dmx_pin[i], OUTPUT);
    digitalWrite(dmx_pin[i], LOW);

    //initialize UART: 250kbps, 8bits, no parity, 2 stop bits
    UCSR0C |= (USBS0);
    Serial.begin(250000);
  }
}

void zeroCrossInterupt(){
  startZeroTime=micros();
  dmx_state= DMX_IDLE;
  for(int ch=0;ch<4;ch++){
    zeroCross[ch]=true;
    brightness[ch]=map(dmx_data[ch],0,265,8000,0);
  }
}

void loop()
{
  if (update)
  {
    update = 0;

    // no dimmer yet for now, just testing fading leds
    for (int i=0; i<DMX_NUM_CHANNELS; i++)
    {
      //int val = map(dmx_data[i], 0, , 0, 1023);
      analogWrite(dmx_pin[i], dmx_data[i]);
    }
  }
}

ISR(USART_RX_vect)
{
  static  uint16_t chan_cnt;
  unsigned char status = UCSR0A;
  unsigned char data = UDR0;

  switch(dmx_state)
  {
    case DMX_IDLE:
    if (status &(1<<FE0)) //if a MAB detected goto DMX_BREAK
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
      dmx_state=DMX_RUN;
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



