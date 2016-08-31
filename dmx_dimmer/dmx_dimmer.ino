#define DMX_NUM_CHANNELS 5
#define DMX_NUM_FIXTURES 4
#define DMX_START_ADDRESS 65

enum
{
  DMX_IDLE,
  DMX_BREAK,
  DMX_START,
  DMX_RUN
};

volatile unsigned char dmx_state;

//unsigned int dmx_start_addr = 65; //start address for the DMX frame to be interpreted
unsigned int dmx_addr;            //current address of the DMX frame

unsigned long startZeroTime = 0;
unsigned long timeElapsed = 0; //Time until end of cycle
boolean zeroCross[] = {false, false, false, false};
int brightness[4];
int period;

unsigned char dmx_pin[DMX_NUM_FIXTURES] = {6, 7, 8, 12}; //{6, 6, 6, 7, 7, 7, 8, 8, 8, 12, 12, 12}; //led pins
unsigned char dmx_data[DMX_NUM_CHANNELS]; //hold the dmx data

volatile unsigned char update; //whan to update pins

void setup()
{
  update = 0; //flag idle
  dmx_state = DMX_IDLE; //default DMX state

  delay(500);

  attachInterrupt(1, zeroCrossInterupt, FALLING);

  for (int i = 0; i < DMX_NUM_FIXTURES; i++)
  {
    pinMode(dmx_pin[i], OUTPUT);
    digitalWrite(dmx_pin[i], LOW);

    //initialize UART: 250kbps, 8bits, no parity, 2 stop bits
    UCSR0C |= (USBS0);
    Serial.begin(250000);
  }
}

void loop()
{
  if (update)
  {
    update = 0;

    dimmer();

    strobo();
    /*
      // no dimmer yet for now, just testing leds' fading capabilities
      for (int i=0; i<DMX_NUM_CHANNELS; i++)
      {
      //int val = map(dmx_data[i], 0, , 0, 1023);
      analogWrite(dmx_pin[i], dmx_data[i]);
      }*/
  }
}
