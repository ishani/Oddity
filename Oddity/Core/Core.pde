#include <stdlib.h>
#include <unistd.h>
#include "oddity.h"
#include "gamma.h"

#define NOP asm volatile("nop");

//----------------------------------------------------------------------------------------------------------------------
// hax
extern "C"
{
int _getpid( void ) { return 0; }
void _exit(int status) {}
int _kill(pid_t pid, int sig) { return 0; }
}

#if HEARTH

#define DEBUG_PORTA(_label)
#define DEBUG_PORTB(_label)

// Row data pins on PORTA
#define RD1 0 // D2
#define RD2 1 // D3
#define GR1 2 // D1
#define GR2 3 // D0
#define BL1 4 // D10
#define BL2 5 // D13
#define CLK 6 // D12
#define OE  7 // D11
#define LE  8 // D6

// Column select pins on PORTB
#define A 5   // D4
#define B 6   // D5
#define C 7   // D9

#else

HardwareSPI spi(1);

// PORTB
#define LE     7 // D9 -> PB7
#define STROBE 6 // D5 -> PB6

// PORTA
#define OE     10// D8 -> PA10
#define CLK    9 // D7 -> PA9
#define DATA   8 // D6 -> PA8

#endif

HardwareTimer displayTimer(1);
HardwareTimer frameTimer(2);

#if HEARTH

// See setPixel implementation for format.
#define BITPLANE_SIZE (Constants::FrameWidth * Constants::FrameHeight / 2)
#else
// WIDTH x HEIGHT x 2 (colours) / 8 bits per byte
#define BITPLANE_SIZE (Constants::FrameWidth * Constants::FrameHeight / 4)  // 16 * 16 / 4 = 64
#define HALFPLANE_SIZE (BITPLANE_SIZE / 2)              // 64 / 2      = 32
#endif
#define NUM_BITPLANES 4
#define BUFFER_SIZE  (BITPLANE_SIZE * NUM_BITPLANES)    // 64 * 4      = 256
#define REFRESH_DELAY 50 // uS
#define FRAME_TIME    20 // mS

#if HEARTH
void setPixel(byte* buffer, int x, int y, char r, char g, char b);
void setPixel4Bit(byte* buffer, int x, int y, char r, char g, char b);
void setPixel8Bit(byte* buffer, int x, int y, char r, char g, char b);
#endif

//
// Display update variables.
int gBitplane;
int gColumn;

//
// Display buffer.
byte buffer[BUFFER_SIZE * 2];
byte* pFrontBuffer;
byte* pBackBuffer;

inline void clearBuffer(byte* buffer)
{
  for(int i = 0; i < BUFFER_SIZE; ++i)
    buffer[i] = 0;
}

inline void flipBuffer()
{
  byte* temp = pFrontBuffer;
  pFrontBuffer = pBackBuffer;
  pBackBuffer = temp; 
}

void clearBuffer(byte* buffer);

//----------------------------------------------------------------------------------------------------------------------
// frame
void loadFrame(byte* buffer, uint16_t* frame);
volatile boolean gHaveNewFrame;
uint16_t frame[Constants::FrameSize];

//----------------------------------------------------------------------------------------------------------------------
// encoder inputs
#define ENCODER_A_PIN_1 15 // EXTI   0
#define ENCODER_A_PIN_2 16 // EXTI 1
#define ENCODER_B_PIN_1 17 // EXTI   2
#define ENCODER_B_PIN_2 18// EXTI 4
#define ENCODER_C_PIN_1 19 // EXTI   5
#define ENCODER_C_PIN_2 20 // EXTI 3
#define BUTTON_PIN 0       // EXTI   3

void handleEncoderA();
void handleEncoderB();
void handleEncoderC();
void handleButton();

volatile bool dialButtonClick;
volatile int analogIncA, analogIncB, analogIncC;
int analogLastA, analogLastB, analogLastC;
int buttonSpinDown;

//----------------------------------------------------------------------------------------------------------------------
static FrameOutput g_output;
static FXState     g_state;


//----------------------------------------------------------------------------------------------------------------------
// main code
void setup()
{
  rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1); 

  initialize();
  g_output.clear();
  
  vfx::init(g_state);
}

//----------------------------------------------------------------------------------------------------------------------
void loop()
{
  if (gHaveNewFrame)
    return;
  
  FrameInput inputs;

  // work out changes from the encoders
  int alA = analogIncA;
  int alB = analogIncB;
  int alC = analogIncC;
  inputs.dialChange[0] = (alA - analogLastA);
  inputs.dialChange[1] = (alB - analogLastB);
  inputs.dialChange[2] = (alC - analogLastC);
  inputs.dialClick = dialButtonClick;
  analogLastA = alA;
  analogLastB = alB;
  analogLastC = alC;
  dialButtonClick = false;
  
  if (buttonSpinDown > 0)
    buttonSpinDown --;
  

  g_state.counter ++;

  // clear the frame
  //g_output.clear();
  
  // tick the VFX core
  if (vfx::tick(inputs, g_state, g_output))
  {
    clearBuffer(pBackBuffer);
    loadFrame(pBackBuffer, g_output.frame);
    gHaveNewFrame = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void updateFrame()
{
  if(gHaveNewFrame == true)
  {
    gHaveNewFrame = false;
    flipBuffer();
  }
  
  frameTimer.pause(); 
  frameTimer.setPeriod(FRAME_TIME * 1000);
  frameTimer.refresh();
  frameTimer.resume();  
}

void initialize()
{
#if HEARTH

  delay(500);
  
  // Configure data direction for output pins, push/pull, 50MHz
  GPIOA->regs->CRL = 0x33333333;
  GPIOA->regs->CRH = 0x33333333;
  GPIOA->regs->ODR = (1 << LE);
  
  GPIOB->regs->CRL = 0x33344444;
  GPIOB->regs->CRH = 0x44444444;
  GPIOB->regs->ODR = 0;

#else

  /*
  // PORTA
  #define OE     10// D8 -> PA10
  #define CLK    9 // D7 -> PA9
  #define DATA   8 // D6 -> PA8
  // PORTB
  #define LE     7 // D9 -> PB7
  #define STROBE 6 // D5 -> PB6
  */
  
 #if 1
  // This is shonky, but for some reason I can't get the ports to configure
  // properly using the regs approach...
 
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
#else
  
  // Configure data direction for output pins, push/pull, 50MHz
  GPIOA->regs->CRL = 0x03030303;
  GPIOA->regs->CRH = 0x33333333;
  GPIOA->regs->ODR = 0;  
  
  GPIOB->regs->CRL = 0x03030303;
  GPIOB->regs->CRH = 0x33333333;
  GPIOB->regs->ODR = 0;//<< LE);  // Latch starts high.

#endif  
  
  GPIOA->regs->BRR = (1 << DATA);
  for(int i = 0; i < 16; i++)
  {
    GPIOA->regs->BSRR = (1 << CLK);
    GPIOA->regs->BRR  = (1 << CLK);
  }

  // Turn on the SPI port
  spi.begin(SPI_18MHZ, MSBFIRST, 0);

  // TODO not sure why this is here...
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

  // TODO not sure why this is here...
  // latch row data
  digitalWrite(LE, 1);
  digitalWrite(LE, 0);

#endif
  
  // set up frame buffer
  pFrontBuffer = buffer;
  pBackBuffer = buffer + BUFFER_SIZE;
  clearBuffer(pFrontBuffer);
  clearBuffer(pBackBuffer);
  
  analogIncA = analogLastA =0;
  analogIncB = analogLastB =0;
  analogIncC = analogLastC =0;
  dialButtonClick = false;
  buttonSpinDown = 0;
  
  gHaveNewFrame = false;

  
  // encoder interrupts
  pinMode(ENCODER_A_PIN_1, INPUT_PULLUP);
  pinMode(ENCODER_A_PIN_2, INPUT_PULLUP);
  pinMode(ENCODER_B_PIN_1, INPUT_PULLUP);
  pinMode(ENCODER_B_PIN_2, INPUT_PULLUP);
  pinMode(ENCODER_C_PIN_1, INPUT_PULLUP);
  pinMode(ENCODER_C_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  attachInterrupt(ENCODER_A_PIN_1, handleEncoderA, FALLING);
  attachInterrupt(ENCODER_B_PIN_1, handleEncoderB, FALLING);
  attachInterrupt(ENCODER_C_PIN_1, handleEncoderC, FALLING);
  attachInterrupt(BUTTON_PIN, handleButton, FALLING);
  
  //
  // set up frame timer
  frameTimer.pause();
  frameTimer.setPeriod(FRAME_TIME * 1000);
  frameTimer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
  frameTimer.setCompare(TIMER_CH2, 1);
  frameTimer.attachCompare1Interrupt(updateFrame);
  frameTimer.refresh();
  frameTimer.resume();

  //
  // set up display timer
  gBitplane = 0;
  gColumn = 0;

  displayTimer.pause(); 
  displayTimer.setPeriod(REFRESH_DELAY);
  displayTimer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
  displayTimer.setCompare(TIMER_CH1, 1);
  displayTimer.attachCompare1Interrupt(updateDisplay);
  displayTimer.refresh();
  displayTimer.resume();  
}

void updateDisplay()
{
#if HEARTH

  GPIOA->regs->BSRR = (1 << OE);                // Output high, disable output.
  DEBUG_PORTA("disable")

  // Set column address from counter.
  GPIOB->regs->BSRR = ((gColumn & 0x0007) << A) | (0x0007 << (A + 16));
  DEBUG_PORTB("addr set")

  GPIOA->regs->BSRR = (1 << LE);                 // Latch high, data transferred to output latch.
  DEBUG_PORTA("latch up")    
  GPIOA->regs->BRR = (1 << LE);                  // Latch low, latch (last interrupt's) data.
  DEBUG_PORTA("latch down")

  GPIOA->regs->BRR = (1 << OE);                  // Output low, enable output.
  DEBUG_PORTA("enable")

  // Delay doubles for each bit of depth. Produces linear gradient and will
  // require gamma correction.
  int delay = REFRESH_DELAY << gBitplane;
  
  // update up display timer with delay for this intensity
  displayTimer.pause(); 
  displayTimer.setPeriod(delay);
  displayTimer.refresh();
  displayTimer.resume();

  if(++gBitplane == NUM_BITPLANES)
  {
    gBitplane = 0;
    if(++gColumn == 8)
      gColumn = 0;
  }

  // Clock out row data. Data should already be formatted in buffer such that each word
  // contains this bitplane's pixel data for two pixels, according to the display layout.
  for(int i = 0; i < 64; ++i)
  {
    // Clear row data lines, then set as needed.
    GPIOA->regs->BSRR = (pFrontBuffer[gBitplane * BITPLANE_SIZE + gColumn * 64 + i] & 0x3f) | (0x3f << 16);	
    DEBUG_PORTA("data set")
    GPIOA->regs->BSRR = (1 << CLK);             // Clock high, transfers on rising edge.
    DEBUG_PORTA("clock high")
    GPIOA->regs->BRR = (1 << CLK);              // Clock low
    DEBUG_PORTA("clock low")
  }

#else

  /*
  // PORTA
  #define OE     10// D8 -> PA10
  #define CLK    9 // D7 -> PA9
  #define DATA   8 // D6 -> PA8
  // PORTB
  #define LE     7 // D9 -> PB7
  #define STROBE 6 // D5 -> PB6
  */

  GPIOA->regs->BSRR = (1 << OE);      // Disable row drivers
  
  NOP
  if(gColumn != 0)                    // Increment column data
    GPIOA->regs->BSRR = (1 << DATA);
  else
    GPIOA->regs->BRR = (1 << DATA);
  NOP  
  GPIOA->regs->BSRR = (1 << CLK);     // Clock column data
  NOP
  GPIOA->regs->BRR = (1 << CLK);
  NOP
  GPIOB->regs->BSRR = (1 << STROBE);  // Latch column data
  NOP
  GPIOB->regs->BRR = (1 << STROBE);

  NOP
  GPIOB->regs->BSRR = (1 << LE);      // Latch row data (from last tick)
  NOP
  GPIOB->regs->BRR = (1 << LE); 

  GPIOA->regs->BRR = (1 << OE);       // Enable row drivers

  // Delay doubles for each bit of depth. Produces linear gradient and will
  // require gamma correction TODO
  int delay = REFRESH_DELAY << gBitplane;
  
  // update up display timer with delay for this intensity
  displayTimer.pause(); 
  displayTimer.setPeriod(delay);
  displayTimer.refresh();
  displayTimer.resume();

  if(++gColumn >= Constants::FrameWidth)
  {
    gColumn = 0;
    if(++gBitplane >= NUM_BITPLANES)
    {
      gBitplane = 0;  
    }
  }

  // push row data
  const int bitplaneOffset = gBitplane * BITPLANE_SIZE;
  const int columnOffset   = gColumn * 2;
  // red first
  spi.write(pFrontBuffer[bitplaneOffset + columnOffset + 1]);
  spi.write(pFrontBuffer[bitplaneOffset + columnOffset]);
  // then green
  spi.write(pFrontBuffer[HALFPLANE_SIZE + bitplaneOffset + columnOffset + 1]);
  spi.write(pFrontBuffer[HALFPLANE_SIZE + bitplaneOffset + columnOffset]);

  // todo figure out how to know when write complete.
  // 4 nops appear to be about right.
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop"); 
  
#endif
}

//----------------------------------------------------------------------------------------------------------------------
void handleEncoderA()
{
  if(digitalRead(ENCODER_A_PIN_2) == 0)
  {
    analogIncA ++;
  }
  else
  {
    analogIncA --;
  }
}
void handleEncoderB()
{
  if(digitalRead(ENCODER_B_PIN_2) == 0)
  {
    analogIncB ++;
  }
  else
  {
    analogIncB --;
  }
}
void handleEncoderC()
{
  if(digitalRead(ENCODER_C_PIN_2) == 0)
  {
    analogIncC ++;
  }
  else
  {
    analogIncC --;
  }
}

void handleButton()
{
  if(digitalRead(BUTTON_PIN) == 0 && buttonSpinDown == 0)
  {
    dialButtonClick = true;
    buttonSpinDown = 20;
  }
}

#if HEARTH

void loadFrame(byte* buffer, uint16_t* frame)
{
  for(int i = 0; i < Constants::FrameSize; ++i)
  { 
    byte r = frame[i] & 0x0f;
    byte g = (frame[i] >> 4) & 0x0f;
    byte b = (frame[i] >> 8) & 0x0f;
    setPixel(buffer, i % Constants::FrameWidth, i / Constants::FrameWidth, r, g, b);
  }
}

/*
 *    Buffer data map of 32 x 32 pixel RGB panel (assumes two 16 x 32 panels in series).
 *
 *    Index is (y % 8) * 64 + (y > 15 ? 32 : 0) + x.  Each buffer position holds data for
 *    two different pixels, eight rows apart. Set low bits (RD1, GR1, BL1) if Y is in the
 *    range 0..7 or 16..23, otherwise set high bits (RD2, GR2, BL2).
 *
 *     _0____________________________________________________________________________31_
 * 0  | 0    |...................................LOW....................................|
 * 1  |64    |...................................LOW....................................|
 * 2  |128   |...................................LOW....................................|
 * 3  |192   |...................................LOW....................................|
 * 4  |256   |...................................LOW....................................|
 * 5  |320   |...................................LOW....................................|
 * 6  |384   |...................................LOW....................................|
 * 7  |448   |...................................LOW....................................|
 * 8  | 0    |...................................HIGH...................................|
 * 9  |64    |...................................HIGH...................................|
 * 10 |128   |...................................HIGH...................................|
 * 11 |192   |...................................HIGH...................................|
 * 12 |256   |...................................HIGH...................................|
 * 13 |320   |...................................HIGH...................................|
 * 14 |384   |...................................HIGH...................................|
 * 15 |448   |___________________________________HIGH___________________________________|
 * 16 | 0 +32|...................................LOW....................................|
 * 17 |64 +32|...................................LOW....................................|
 * 18 |128+32|...................................LOW....................................|
 * 19 |192+32|...................................LOW....................................|
 * 20 |256+32|...................................LOW....................................|
 * 21 |320+32|...................................LOW....................................|
 * 22 |384+32|...................................LOW....................................|
 * 23 |448+32|...................................LOW....................................|
 * 24 | 0 +32|...................................HIGH...................................|
 * 25 |64 +32|...................................HIGH...................................|
 * 26 |128+32|...................................HIGH...................................|
 * 27 |192+32|...................................HIGH...................................|
 * 28 |256+32|...................................HIGH...................................|
 * 29 |320+32|...................................HIGH...................................|
 * 20 |384+32|...................................HIGH...................................|
 * 31 |448+32|___________________________________HIGH___________________________________|
 *
 */

void setPixel(byte* buffer, int x, int y, char r, char g, char b)
{
  int index = (y % 8) * 64 + (y > 15 ? 32 : 0) + x;
  char mask = 1;
  
  if((y > 7 && y < 16) || (y > 23))
  {
    // set high color bits
    for(int i = 0; i < NUM_BITPLANES; ++i)
    {
      if(r & mask)
        buffer[index] |= (1 << RD2);
      if(g & mask)
        buffer[index] |= (1 << GR2);	
      if(b & mask)
        buffer[index] |= (1 << BL2);
      
      mask = mask << 1;
      index += BITPLANE_SIZE;   
    }
  }
  else
  {
    // set low color bits
    for(int i = 0; i < NUM_BITPLANES; ++i)
    { 
      if(r & mask)
        buffer[index] |= (1 << RD1);
      if(g & mask)
        buffer[index] |= (1 << GR1);
      if(b & mask)
        buffer[index] |= (1 << BL1);
      
      mask = mask << 1;
      index += BITPLANE_SIZE;   
    }      
  }
}

void setPixel4Bit(byte* buffer, int x, int y, char r, char g, char b)
{
  setPixel(buffer, x, y, gamma_lookup[(unsigned int)(r << 4)], gamma_lookup[(unsigned int)(g << 4)], gamma_lookup[(unsigned int)(b << 4)]);
}

void setPixel8Bit(byte* buffer, int x, int y, char r, char g, char b)
{
  setPixel(buffer, x, y, gamma_lookup[(unsigned int)r], gamma_lookup[(unsigned int)g], gamma_lookup[(unsigned int)b]);
}

#else

void loadFrame(byte* buffer, uint16_t* frame)
{
  for(int i = 0; i < Constants::FrameSize; ++i)
  { 
    byte red = frame[i] & 0x0f;
    byte green = (frame[i] >> 4) & 0x0f;

    // some swapping stuff because the hardware is wired upside-down :-)
    int offset = Constants::FrameSize / 2;
    if(i >= offset)
      i -= offset;
    else
      i+= offset;

    byte mask = (1 << (i % 8));

    for(int j = 0; j < NUM_BITPLANES; ++j)
    {
      // TODO Figure shifts to remove conditional.
      if(red & (1 << j))
        buffer[j * BITPLANE_SIZE + i / 8] |= mask;
      if(green & (1 << j))   
        buffer[HALFPLANE_SIZE + j * BITPLANE_SIZE + i / 8] |= mask;
    } 
  }
}

#endif 