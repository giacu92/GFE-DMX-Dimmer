#define DMX_START_ADDRESS 65 //start address for the DMX frame to be interpreted

#define DMX_NUM_CHANNELS 5
#define DMX_NUM_FIXTURES 4

enum
{
  DMX_IDLE,
  DMX_BREAK,
  DMX_START,
  DMX_RUN
};

volatile unsigned char dmx_state;
unsigned int dmx_addr;            //current address of the DMX frame

unsigned long startZeroTime = 0;
unsigned long timeElapsed = 0; //Time until end of cycle
boolean zeroCross[] = {false, false, false, false};
int brightness[DMX_NUM_FIXTURES];
int period = 0;

unsigned char dmx_pin[DMX_NUM_FIXTURES] = {6, 7, 8, 12}; 
unsigned char dmx_data[DMX_NUM_CHANNELS]; //hold the dmx data

volatile unsigned char update; //flag
volatile bool strobe = false;

void setup()
{
  update = 0; //flag idle
  dmx_state = DMX_IDLE; //default DMX state

  delay(500);

  attachInterrupt(digitalPinToInterrupt(3), zeroCrossInterrupt, FALLING);

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
  if(!strobe)
    dimmer();
  else
    strobo();

  
  /*
  for (int i=0; i<DMX_NUM_FIXTURES; i++)
  {
    if (dmx_data[i] > 127)
      digitalWrite(dmx_pin[i], HIGH);
    else
      digitalWrite(dmx_pin[i], LOW);
  }*/
}
