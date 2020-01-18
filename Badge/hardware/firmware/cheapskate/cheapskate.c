#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

// auto-gen'd header containing in-built animation data
#include <animations.h>

//Define functions
//======================
void ioinit(void);
void timerinit(void);
void init(void);
void delay_ms(uint16_t x);
void loadFrameFromPgmspace(int frame_number, unsigned char* frame_ptr);
void setColumn(unsigned char col);
void setGreen(unsigned char row);
void setRed(unsigned char row);

// some constants
//======================
#define FOSC 8000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define ONE_FPS 31250 // one fps at 8mhz
#define BASE_DELAY 100

// globals
//======================
unsigned char g_buffer[48];
unsigned char* g_framePtr;
int g_current_frame;
int g_frame_brightness;
unsigned int g_on_delay;
unsigned int g_off_delay;
int g_i, g_j;
char g_mask;

/*
 *	Interrupt service routine to drive the display
*/
ISR(TIMER0_COMPA_vect)
{

	if(g_i == 8)
	{
		// if this is the pause frame (to vary brightness)
		// clear everything
		setColumn(0);
		setGreen(0);
		setRed(0);

		OCR0A = BASE_DELAY * 6;
	} 
	else
	{
		setGreen(0);
		setRed(0);

		// set the delay for this pass
		// multiplication by g_j give us geometric brightness
		OCR0A = BASE_DELAY * (g_j + 1);
	
		// set correct column driver
		setColumn(1 << g_i);

		setGreen(*(g_framePtr+g_i));

	}

	// advance the counters
	if(++g_j > 0) // 2)
	{
		g_j = 0;
		g_mask = 1;
		if(++g_i > 7)
		{
			g_i = 0;
		}
	}
}

// interrupt service routine to update animation frames
ISR(TIMER1_COMPA_vect)
{
	// load the next frame
	if(++g_current_frame >= animation_num_frames) g_current_frame = 0;
	loadFrameFromPgmspace(g_current_frame, g_framePtr);
	
	// precompute delays for given brightness
	unsigned char brightness = 127; // to be read from frame
	g_on_delay = (BASE_DELAY * brightness)/255;
	g_off_delay = (6 * BASE_DELAY * (255 - brightness))/255;
}

int main (void)
{
	ioinit(); 		// set up IO pins and defaults
	
	init();				// init global variables
	
	timerinit(); 	// set up timers

	sei(); 				// enable interrupts

	// loop. interrupts will take care of everything else
	while(1) 
	{
	}
	
	return(0);
}

void loadFrameFromPgmspace(int frame_number, unsigned char* frame_ptr)
{
#if 0
	g_frame_brightness = pgm_read_byte(&animation_data[frame_number * 33]);
	unsigned char i, j, k;
	for (i = 0; i < 48; i++)
	{
		frame_ptr[i] = 0;
	}
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 2; j++)
		{
			unsigned char greenData = pgm_read_byte(&animation_data[i * 2 + j]);
			unsigned char redData = pgm_read_byte(&animation_data[16 + i * 2 + j]);
			unsigned char mask = 0x03;
			for (k = 0; k < 4; k++)
			{
				unsigned char bit = (1 << (j * 4 + k));
				unsigned char value = greenData & (mask << (2 * k));
				value = (value >> (2 * k));
				switch(value)
				{
				case 3:
					frame_ptr[i] |= bit;
				case 2:
					frame_ptr[8 + i] |= bit;
				case 1:
					frame_ptr[16 + i] |= bit;
				default:
					break;
				}

				value = redData & (mask << (2 * k));
				value = (value >> (2 * k));
				switch(value)
				{
				case 3:
					frame_ptr[24 + i] |= bit;
				case 2:
					frame_ptr[32 + i] |= bit;
				case 1:
					frame_ptr[40 + i] |= bit;
				default:
					break;
				}
			}
		}
	}
#else
	unsigned char  i;
	for(i = 0; i < 8; ++i)
		*(frame_ptr+i) = (1 << i);
	
	unsigned char data;	
	for(i = 0; i < 8; ++i)
	{
		data = *(frame_ptr+i);
		asm volatile ("nop");
	}

#endif
}

void ioinit (void)
{
	//1 = output, 0 = input
	DDRA = 0b11111111; //All outputs
	DDRB = 0b11111111; //All outputs
	DDRC = 0b11111111; //All outputs
	DDRD = 0b11111111; //PORTD (RX on PD0)
    
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
}

void timerinit (void)
{
	// todo: swap timers. display timer should be the hi-rez one.
	
	// setup display timer
	TCCR0A = 0x00;
	TCCR0B = (_BV(WGM12) | _BV(CS01));
	OCR0A = BASE_DELAY;
	TIMSK0 = _BV(OCIE0A);

	// setup frame timer
	TCCR1A = 0x00;
	TCCR1B = (_BV(WGM12) | _BV(CS12));
	OCR1A = ONE_FPS/animation_fps;
	TIMSK1 = _BV(OCIE1A);
}

void init(void)
{
	g_i = 0;
	g_j = 0;
	g_mask = 1;

	// load up the first frame
	g_current_frame = 0;
	g_framePtr = g_buffer;
	loadFrameFromPgmspace(g_current_frame, g_framePtr);
}

void setColumn(unsigned char col)
{
	PORTC = ~(1 << col);
}

void setGreen(unsigned char row)
{
	PORTA = ~row;
}

void setRed(unsigned char row)
{
	PORTD = ~row;
}

//General short delays
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
}
