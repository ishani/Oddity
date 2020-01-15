/*
  .oooooo.         .o8        .o8   o8o      .               
 d8P'  `Y8b       "888       "888   `"'    .o8               
888      888  .oooo888   .oooo888  oooo  .o888oo oooo    ooo 
888      888 d88' `888  d88' `888  `888    888    `88.  .8'  
888      888 888   888  888   888   888    888     `88..8'   
`88b    d88' 888   888  888   888   888    888 .    `888'    
 `Y8bood8P'  `Y8bod88P" `Y8bod88P" o888o   "888"     .8'  2.0
                                                 .o..P'      
                                                 `Y8P'       
                                                             
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "odd_shared.h"
#include "odd_palette.h"

#include "xp.h"


// http://cpp.sh/5pa4h

#define NOP asm volatile("nop");

//----------------------------------------------------------------------------------------------------------------------
// hax
extern "C" {
int _getpid( void ) { return 0; }
void _exit(int) {}
int _kill(pid_t , int ) { return 0; }
}

//----------------------------------------------------------------------------------------------------------------------
HardwareSPI spi(1);

// PORTB
#define LE     7 // D9 -> PB7
#define STROBE 6 // D5 -> PB6

// PORTA
#define OE     10 // D8 -> PA10
#define CLK    9  // D7 -> PA9
#define DATA   8  // D6 -> PA8


HardwareTimer displayTimer(1);
HardwareTimer frameTimer(2);


// WIDTH x HEIGHT x 2 (colours) / 8 bits per byte
#define BITPLANE_SIZE (DisplaySize >> 2)                 // 16 * 16 / 4 = 64
#define HALFPLANE_SIZE (BITPLANE_SIZE >> 1)              // 64 / 2      = 32

#define NUM_BITPLANES 4
#define BUFFER_SIZE  (BITPLANE_SIZE * NUM_BITPLANES)    // 64 * 4      = 256
#define REFRESH_DELAY 50 // uS
#define FRAME_TIME    17 // mS

//
// Display update variables.
u32 gBitplane;
u32 gColumn;

//
// Display buffer.
byte buffer[BUFFER_SIZE * 2];
byte* pFrontBuffer;
byte* pBackBuffer;

inline void clearBuffer(byte* buffer)
{
  memset( buffer, 0, sizeof(byte) * BUFFER_SIZE );
}

inline void flipBuffer()
{
  byte* temp = pFrontBuffer;
  pFrontBuffer = pBackBuffer;
  pBackBuffer = temp; 
}


//----------------------------------------------------------------------------------------------------------------------
// frame

volatile boolean g_haveNewFrame;

void convertFrameDataForDisplay(const FrameData& data, byte* buffer)
{
  const u32 offset = DisplaySize >> 1;
  for(u32 i = 0; i < DisplaySize; ++i)
  { 
    const byte mask  = (1 << (i & 7)); // % 8

    const byte red   = data.pixels[i] & 0x0f;
    const byte green = (data.pixels[i] >> 4) & 0x0f;

    // some swapping stuff because the hardware is wired upside-down :-)
    i ^= 128;
    /*
    if(i >= offset)
      i -= offset;
    else
      i += offset;
    */

    for(u32 j = 0; j < NUM_BITPLANES; ++j)
    {
      // TODO Figure shifts to remove conditional.
      if(red & (1 << j))
        buffer[j * BITPLANE_SIZE + (i >> 3)] |= mask;
      if(green & (1 << j))   
        buffer[HALFPLANE_SIZE + j * BITPLANE_SIZE + (i >> 3)] |= mask;
    } 
  }
}



//----------------------------------------------------------------------------------------------------------------------
// encoder inputs
#define ENCODER_A_PIN_1 15 // EXTI   0
#define ENCODER_A_PIN_2 16 // EXTI 1
#define ENCODER_B_PIN_1 17 // EXTI   2
#define ENCODER_B_PIN_2 18 // EXTI 4
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
static FrameData g_frameData;
static StateData g_stateData;

//----------------------------------------------------------------------------------------------------------------------
// main code
void setup()
{
  rcc_set_prescaler(RCC_PRESCALER_AHB, RCC_AHB_SYSCLK_DIV_1); 

  xp::glimmer::init(&g_stateData);

  initialize();
}


static size_t pal_choice = 0;


//----------------------------------------------------------------------------------------------------------------------
void loop()
{
  if (g_haveNewFrame)
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
  
  if ( inputs.dialClick )
  {
    pal_choice ++;
    if ( pal_choice >= Gradient_Count )
      pal_choice = 0;
  }

  xp::glimmer::tick( inputs, &g_stateData, g_frameData );

  // tick the VFX core
  
  {
    clearBuffer(pBackBuffer);
    convertFrameDataForDisplay(g_frameData, pBackBuffer);
    g_haveNewFrame = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void updateFrame()
{
  if(g_haveNewFrame == true)
  {
    g_haveNewFrame = false;
    flipBuffer();
  }
  
  frameTimer.pause(); 
  frameTimer.setPeriod(FRAME_TIME * 1000);
  frameTimer.refresh();
  frameTimer.resume();  
}

//----------------------------------------------------------------------------------------------------------------------
void initialize()
{
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);


  GPIOA->regs->BRR = (1 << DATA);
  for(int i = 0; i < 16; i++)
  {
    GPIOA->regs->BSRR = (1 << CLK);
    GPIOA->regs->BRR  = (1 << CLK);
  }

  // Turn on the SPI port
  spi.begin(SPI_18MHZ, MSBFIRST, 0);

  // TODO not sure why this is here...
  NOP
  NOP
  NOP
  NOP

  // TODO not sure why this is here...
  // latch row data
  digitalWrite(LE, 1);
  digitalWrite(LE, 0);

  
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
  
  g_haveNewFrame = false;

  
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

//----------------------------------------------------------------------------------------------------------------------
void updateDisplay()
{
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
  int delay_rack[4];
  delay_rack[0] = 0;
  delay_rack[1] = 50;
  delay_rack[2] = 175;
  delay_rack[3] = 700;

  // update up display timer with delay for this intensity
  displayTimer.pause(); 
  displayTimer.setPeriod(delay_rack[gBitplane]);
  displayTimer.refresh();
  displayTimer.resume();

  if(++gColumn >= DisplayW)
  {
    gColumn = 0;
    if(++gBitplane >= NUM_BITPLANES)
    {
      gBitplane = 0;  
    }
  }

  // push row data
  const u32 bitplaneOffset = gBitplane * BITPLANE_SIZE;
  const u32 columnOffset   = gColumn * 2;

  // red first
  spi.write(pFrontBuffer[bitplaneOffset + columnOffset + 1]);
  spi.write(pFrontBuffer[bitplaneOffset + columnOffset]);
  
  // then green
  spi.write(pFrontBuffer[HALFPLANE_SIZE + bitplaneOffset + columnOffset + 1]);
  spi.write(pFrontBuffer[HALFPLANE_SIZE + bitplaneOffset + columnOffset]);

  // todo figure out how to know when write complete.
  // 4 nops appear to be about right.
  NOP
  NOP
  NOP
  NOP
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
