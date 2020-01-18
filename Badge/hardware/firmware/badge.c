
#include <stdio.h>
#include <avr/io.h>
#include <avr\interrupt.h>
#include "i2cmaster.h"

#define FOSC 8000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#define sbi(var, mask)   ((var) |= (uint8_t)(1 << mask))
#define cbi(var, mask)   ((var) &= (uint8_t)~(1 << mask))

// default animations
#define ANIM_CHARGING 1

//Define functions
//======================
void ioinit(void);      			// Initializes IO
void delay_ms(uint16_t x); 			// General purpose delay

// console debug functions
static int uart_putchar(char c, FILE *stream);
uint8_t uart_getchar(void);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void serialReadFile();

// MAX6960 drive functions
void displayInit();
void displayWriteEight(uint8_t data);									// Eight-bit write to MAX6960
void displayWriteSixteen(uint8_t high, uint8_t low);	// Sixteen-bit write to MAX6960
void displayEnable(int enable);
void displaySetBrightness(int brightness);

// Animation storage functions
void writeFrame(int address, char* dataPtr);
void readFrame(int address, char* dataPtr);
void readHeader(int address);
void readDefaultFrame(int anim, int frame, char* dataPtr);
void readDefaultHeader(int anim);
void clearBuffer(char* dataPtr);

void writeEight(char high, char low, char data);
void readEight(char high, char low, char* dataPtr);
void splitInteger(int in, char* high, char* low);

void drawFrame(char* dataPtr);

void drawTest();
//======================

#if 1
// arbitrary timing delay for MAX 6960
#define DELAY() asm volatile ("nop");
#else
// debug timings
#define DELAY() delay_ms(500);
#endif

// sets delay properly based on DIV8 fuse setting
#define NO_DIV8 0
 
// set to disable delay loop for breakpointing
#define DEBUG 0

// define pin interface for serial port on PORTD
#define SDA	0b00010000
#define SCL	0b00100000

// define pin interface for i2c on PORTC
#define RXD	0b00000001
#define TXD	0b00000010

// define pin interface to MAX6960
#define BOARD_REV_1 1
#if BOARD_REV_1
// PCB rev 1 setup with pins split between PORTD and PORTB
// CS, DIN, RST on PORTD
#define RESET 	0b00100000 // PD5
#define CS 	0b01000000 // PD6
#define DOUT 	0b10000000 // PD7
// DOUT, CLK on PORTB
#define OSCO	0b00000001 // PB0 / OSCO
#define DIN	0b00000010 // PB1 unused
#define CLK	0b00000100 // PB2
#else
#define CS 	0b00000100
#define DOUT	0b00001000
#define DIN 	0b00010000
#define CLK	0b00100000
#define RESET 	0b01000000
#endif

// define pin interface for detecting bus power and charging on PORTC
#define VBUS 	0b00000100
#define CHARGE 	0b00001000

// define pin interface for switch
#define SWT	0b00000001
#define SW1 	0b00000010
// #define SW2 	0b00001000 badly placed - connected to adc input

enum SwitchState {
	kOff,
	kUp,
	kDown,
	kSelect
} switch_state;

// define configuration word bits for MAX6960
#define SHUTDOWN	0b00000001
#define COLOR 		0b01000000
#define PIXEL_FORMAT	0b10000000

#define BASE_ADDR 	0x03
#define FRAME_SIZE 	33

char buffer[32];

#define Dev24LC64  0xA0      // device address of EEPROM

const int ONE_FPS = 31250;	 // 8Mhz/256 gets us timer count for 1Hz

// globals
int fps;
int numFrames;
int currentFrame;
char enableDisplay;

// interrupt service routine
ISR(TIMER1_COMPA_vect)
{
	OCR1A=ONE_FPS/fps;  // 1 Hz @ 8 MHz divided by fps
	
	// advance frame counter
	currentFrame++;
	if(currentFrame >= numFrames)
		currentFrame = 0;
		
	// load frame
	readFrame(BASE_ADDR+FRAME_SIZE*currentFrame, buffer);
	
	// update display
	drawFrame(buffer);

}

#define DISPLAY_TEST_1 	0
#define DISPLAY_TEST_2 	0
#define DISPLAY_TEST_3	0
#define MEMORY_TEST 	0

int main (void)
{
	fps = 1;
	currentFrame = 0;
	enableDisplay = 1;
	switch_state = kOff;

	ioinit(); 		// Setup IO pins and defaults
	displayInit();		// Initialize MAX6960

	// let us know that the serial port is working
	// and that we are, indeed, awesome.
	printf("Hello, Awesome!!\n");

#if DISPLAY_TEST_1
	printf("display test 1\n");
	drawTest();
	while(1) {}
#endif

	// setup display timer
	TCCR1A = 0x00;
	TCCR1B = (_BV(WGM12) | _BV(CS12));
	OCR1A = ONE_FPS/fps;
	TIMSK1 = _BV(OCIE1A);
#if !DISPLAY_TEST_2
	sei(); // enable interrupts
#endif

	i2c_init();                             // initialize I2C library
	
#if MEMORY_TEST
	// test memory by round-tripping a bit of data.

	printf("memory test\n");
	int address = 0;
	char high, low, data = 27;
	printf("writing\n");
	splitInteger(address, &high, &low);
	writeEight(high, low, data);	
	printf("wrote %d to %d\n", data, address);
	data = 0;
	printf("reading\n");
	readEight(high, low, &data);
	printf("read %d from %d\n", data, address);
	if(data == 27)
		printf("pass\n");
	else
		printf("fail\n");

	while(1) {}
#endif

#if DISPLAY_TEST_2
	// test basic display functionality by pushing pattern to
	// display directly.

	printf("display test 2\n");

	cli(); 				// disable interrupts
			
	int j;				// create test pattern in global buffer
	for(j = 0; j < 32; ++j)
		buffer[j] = 0x01;

	drawFrame(buffer);		// draw it

	while(1)
	{
		delay_ms(500);
		displayEnable(0);
		delay_ms(500);
		displayEnable(1);
	}

	sei();				// re-enable interrupts
#endif

	clearBuffer(buffer);

#if DISPLAY_TEST_3

	cli();					// disable interrupts
	
	char high, low, address = BASE_ADDR;
	
	splitInteger(address, &high, &low);
	writeEight(high, low, 64);		// set panel intensity

	int i;					// write test pattern to memory
	for(i = 1; i < FRAME_SIZE; ++i)
	{
		splitInteger(address+i, &high, &low);
		if(i%2 == 0)
			writeEight(high, low, 0b01000100);
		else
			writeEight(high, low, 0b00010001);
		printf(".");
	}

	address = BASE_ADDR + FRAME_SIZE;

	splitInteger(address, &high, &low);
	writeEight(high, low, 64);		// set panel intensity

	for(i = 1; i < FRAME_SIZE; ++i)
	{
		splitInteger(address+i, &high, &low);
		if(i%2 == 0)
			writeEight(high, low, 0b00010001);
		else
			writeEight(high, low, 0b01000100);
		printf(".");
	}

	fps = 1;
	numFrames = 2;
	currentFrame = 0;
	enableDisplay = 1;

	displayEnable(1);

	sei();					// re-enable interrupts

#else
	readHeader(0);
#endif

	while(1)
	{
		// deal with input
		if(UCSR0A & (1<<RXC0))
		{
			cli(); // disable interrupts

			char inChar = UDR0;

			// triggers data download
			if(inChar == 'r')
			{
				serialReadFile();
				readHeader(0);
				readFrame(4, buffer);
			}

			// toggles enabling the display
			else if(inChar == 'e')
	    		{
		    		// toggle MAX6960 shutdown
		    		if(enableDisplay)
				{
					enableDisplay = 0;
					printf("Enable display\n");
					displayWriteSixteen(0x0D,	(COLOR | PIXEL_FORMAT | SHUTDOWN)); // set configuration word
	    			}
				else
				{
					enableDisplay = 1;
					printf("Disable display\n");
	  				displayWriteSixteen(0x0D,	(COLOR | PIXEL_FORMAT) & ~SHUTDOWN);
				}
			}

		    	// queries device status
		    	else if(inChar == 's')
		    	{
				printf("Device status\n");
    				if(PINC & VBUS)
  				{
	  				printf("Connected");
	  				if(!(PINC & CHARGE))
	  				{
	  					printf(" and charging");
	  				}
	  				printf("\n");
	  			}
				else
				{
					printf("Disconnected\n");
				}
				printf("PORTC = %x\n", PORTC);
    			}

			sei(); // re-enable interrupts

    		}

		// update and buffer switch state
		if(PORTC & ~SWT)
			switch_state = kSelect;

		if(switch_state == kSelect)
			cli();
		else
			sei();

	}
   
	return 0;
}

void ioinit (void)
{
	// 1 = output, 0 = input
	// pins are inputs, except defined outputs
#if BOARD_REV_1
	DDRB = CLK | OSCO;
	DDRD = CS | RESET | TXD | DOUT;
#else
	DDRD = CS | DOUT | CLK | RESET | TXD;
#endif

#if 0 // error in i2c pins?
	DDRC  = 0b00000011;
	PORTC = 0b00000011;  	// set SDA & SCL high
#else
	DDRC = SDA | SCL;
	DDRC = SDA | SCL;	// set SDA & SCL high
#endif	

	//USART Baud rate: 9600
	UBRR0H = (MYUBRR) >> 8;
	UBRR0L = MYUBRR;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	stdout = &mystdout; //Required for printf init

	PORTD = 0x00;
	PORTD |= CS;
}

//General short delays
void delay_ms(uint16_t x)
{
#if !DEBUG_NO_DELAY
  uint16_t y;
  uint8_t z;
  for ( ; x > 0 ; x--){
#if NO_DIV8
	for ( y = 0 ; y < 11 ; y++){
#else
    for ( y = 0 ; y < 90 ; y++){
#endif
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
#endif
}

/*
 *	MAX6960 Functions
 */

void displayInit()
{
	
	delay_ms(100); // wait for max 6960 to stabilize
	PORTD |= RESET;
	
	// configure max 6960
	displayWriteSixteen(0x0E, 0x00); 	// set number of devices to 1
	displayWriteSixteen(0x0F, 0x00); 	// set number of rows to 1

	displayWriteSixteen(0x01, 0x03); 	// set pixel intensity scale
	displayWriteSixteen(0x02, 0x10); 	// set panel intensity
	displayWriteSixteen(0x03, 0xFF); 	// set digit 0 intensity
	displayWriteSixteen(0x04, 0xFF); 	// set digit 1 intensity
	displayWriteSixteen(0x08, 0x00); 	// set global driver indirect address to zero
	displayWriteSixteen(0x09, 0x00);	// set display indirect address to zero
	displayWriteSixteen(0x0A, 0x00);	// set display indirect address to zero
	displayWriteSixteen(0x0B, 0x00); 	// set plane to 0, counter to manual
	displayWriteSixteen(0x0D, (COLOR | PIXEL_FORMAT | SHUTDOWN));
	displayWriteSixteen(0x0E, 0x00); 	// set number of devices to 1
	displayWriteSixteen(0x0F, 0x00); 	// set number of rows to 1
	
}

void displayEnable(int enable)
{
	if(enable)
		displayWriteSixteen(0x0D, (COLOR | PIXEL_FORMAT | SHUTDOWN)); // set configuration word
	else
		displayWriteSixteen(0x0D, (COLOR | PIXEL_FORMAT) & ~SHUTDOWN);
}

void displaySetBrightness(int brightness)
{

}

/*
1) Take CLK low.
2) Take CS low.
3) For an 8-bit transmission:
Clock 8 bits of data into DIN, D7 first to D0 last,
observing the setup and hold times.
For a 16-bit transmission:
Clock 16 bits of data into DIN, D15 first to D0 last,
observing the setup and hold times. Bit D15 is low,
indicating a write command.
For a 24-bit transmission:
Clock 24 bits of data into DIN, D23 first to D0 last,
observing the setup and hold times. Bit D23 is low,
indicating a write command.
4) Take CS high (while CLK is still high after clocking
in the last data bit).
5) Take CLK low.
*/
void displayWriteEight(uint8_t data)
{
#if BOARD_REV_1
	PORTB &= ~CLK; // take clk low
	DELAY();
	PORTD &= ~CS;  // take cs low
	DELAY();
	int i;
	for(i = 0; i < 8; ++i)
	{
		uint8_t mask = 0b10000000;
		PORTB &= ~CLK; // take clk low
		if(mask & data)		// set the bit
			PORTD |= DOUT;
		else
			PORTD &= ~DOUT;
		data = data << 1;
		DELAY();
		PORTB |= CLK; // take clk high
		DELAY();
	}
	PORTD |= CS;  // take cs high
	DELAY();
	PORTB &= ~CLK; // take clk low
	DELAY();
#else
	PORTD &= ~CLK; // take clk low
	DELAY();
	PORTD &= ~CS;  // take cs low
	DELAY();
	int i;
	for(i = 0; i < 8; ++i)
	{
		uint8_t mask = 0b10000000;
		PORTD &= ~CLK; // take clk low
		if(mask & data)		// set the bit
			PORTD |= DOUT;
		else
			PORTD &= ~DOUT;
		data = data << 1;
		DELAY();
		PORTD |= CLK; // take clk high
		DELAY();
	}
	PORTD |= CS;  // take cs high
	DELAY();
	PORTD &= ~CLK; // take clk low
	DELAY();
#endif
}

void displayWriteSixteen(uint8_t high, uint8_t low)
{
#if BOARD_REV_1
	PORTB &= ~CLK; // take clk low
	DELAY();
	PORTD &= ~CS;  // take cs low
	DELAY();
	int i;
	for(i = 0; i < 8; ++i)
	{
		uint8_t mask = 0b10000000;
		PORTB &= ~CLK; // take clk low
		if(mask & high)		// set the bit
			PORTD |= DOUT;
		else
			PORTD &= ~DOUT;
		high = high << 1;
		DELAY();
		PORTB |= CLK; // take clk high
		DELAY();
	}
	for(i = 0; i < 8; ++i)
	{
		uint8_t mask = 0b10000000;
		PORTB &= ~CLK; // take clk low
		if(mask & low)		// set the bit
			PORTD |= DOUT;
		else
			PORTD &= ~DOUT;
		low = low << 1;
		DELAY();
		PORTB |= CLK; // take clk high
		DELAY();
	}
	PORTD |= CS;  // take cs high
	DELAY();
	PORTB &= ~CLK; // take clk low
	DELAY();
#else
	PORTD &= ~CLK; // take clk low
	DELAY();
	PORTD &= ~CS;  // take cs low
	DELAY();
	int i;
	for(i = 0; i < 8; ++i)
	{
		uint8_t mask = 0b10000000;
		PORTD &= ~CLK; // take clk low
		if(mask & high)		// set the bit
			PORTD |= DOUT;
		else
			PORTD &= ~DOUT;
		high = high << 1;
		DELAY();
		PORTD |= CLK; // take clk high
		DELAY();
	}
	for(i = 0; i < 8; ++i)
	{
		uint8_t mask = 0b10000000;
		PORTD &= ~CLK; // take clk low
		if(mask & low)		// set the bit
			PORTD |= DOUT;
		else
			PORTD &= ~DOUT;
		low = low << 1;
		DELAY();
		PORTD |= CLK; // take clk high
		DELAY();
	}
	PORTD |= CS;  // take cs high
	DELAY();
	PORTD &= ~CLK; // take clk low
	DELAY();
#endif
}

/*
 *	Console debug functions
 */

static int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);
  
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    
    return 0;
}

uint8_t uart_getchar(void)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}

void serialReadFile()
{
	cli();
	printf("File length (bytes)? ");
	char inChar = 0;
	int numBytes = 0;
	int i = 0, j = 1;
	char buf[5];
	while(inChar != '\n' && inChar != '\r' && i < 5)
	{
		while( !(UCSR0A & (1<<RXC0)) );
		inChar = UDR0;
		buf[i] = inChar;
		if(buf[i] > 0x2F && buf[i] < 0x3A)		// make sure we have a digit
		{
			printf("%c", buf[i]);
			++i;
		} else
		{

		}
	}
	for(i--; i >= 0; i--)
	{
		numBytes += j*(buf[i] - 0x30);
		j *= 10;
	}
	printf("\nWaiting for file");
	while ( UCSR0A & (1<<RXC0) ) inChar = UDR0; // flush the USART 
	char address = 0;
	for(i = 0; i < numBytes; ++i)
	{
		while( !(UCSR0A & (1<<RXC0)) );
		inChar = UDR0;
		printf(".");
		char high, low;
		splitInteger(address+i, &high, &low);
		writeEight(high, low, inChar);
	}
	printf("\n");
	printf("File received.\n");
	sei();
}

/*
 *	Functions for saving and retrieving frames of animation
 */
 
void writeFrame(int address, char* dataPtr)
{
	int i;
	for(i = 0; i < 32; ++i)
	{
		char high, low;
		splitInteger(address+i, &high, &low);
		writeEight(high, low, *(dataPtr+i));
	}
}

void readHeader(int address)
{
	char tempA, tempB;
	char high, low;
	splitInteger(address, &high, &low);
	readEight(0x00, address, &tempA);			// number of frames low
	splitInteger(address+1, &high, &low);
	readEight(high, low, &tempB);		// number of frames high
	numFrames = tempA + 256*tempB;
	splitInteger(address+2, &high, &low);
	readEight(high, low, &tempA);		// frames per second
	fps = tempA;
}

void readFrame(int address, char* dataPtr)
{
	char high, low, temp;
	splitInteger(address, &high, &low);
	readEight(high, low, &temp);					// read frame brightness
	displayWriteSixteen(0x02, temp); 		  // set panel intensity
	int i;
	for(i = 0; i < 32; ++i)
	{
		splitInteger(address+i+1, &high, &low);
		readEight(high, low, dataPtr+i);
	}
}

void clearBuffer(char* dataPtr)
{
	int i;
	for(i = 0; i < 32; ++i)
	{
		*(dataPtr+i) = 0x00;
	}
}

void drawFrame(char* dataPtr)
{
	displayWriteSixteen(0x09, 0x00);	// set display indirect address to zero
	displayWriteSixteen(0x0A, 0x00);	// set display indirect address to zero
	int j;
	for(j = 0; j < 32; ++j)
		displayWriteEight(*(dataPtr+j));
}

void drawTest()
{
	displayWriteSixteen(0x09, 0x00);	// set display indirect address to zero
	displayWriteSixteen(0x0A, 0x00);	// set display indirect address to zero
	int j;
	for(j = 0; j < 32; ++j)
		displayWriteEight(0x01);
}

void writeEight(char high, char low, char data)
{
	char ret = 0;
	i2c_start_wait(Dev24LC64+I2C_WRITE);    	// set device address and write mode
	ret = i2c_write(high);            				// write high address = 0
	if(ret == 0x01)
		printf("address write (high) failed\n");
	ret = i2c_write(low);              				// write address low byte
	if(ret == 0x01)
		printf("address write (low) failed\n");
	ret = i2c_write(data);										// write value to EEPROM
	if(ret == 0x01)
		printf("write failed\n");
	i2c_stop();                             	// set stop conditon = release bus
}

void readEight(char high, char low, char* dataPtr)
{
	char ret = 0;
	i2c_start_wait(Dev24LC64+I2C_WRITE);    	// set device address and write mode
	ret = i2c_write(high);            				// write high address = 0
	if(ret == 0x01)
		printf("address write (high) failed\n");
	ret = i2c_write(low);              				// write address low byte
	if(ret == 0x01)
		printf("address write (low) failed\n");
	i2c_rep_start(Dev24LC64+I2C_READ);      // set device address and read mode
	*dataPtr = i2c_readNak();                 // read one byte from EEPROM
	i2c_stop();
}

void splitInteger(int in, char* high, char* low)
{
	*low = in & 0x00FF;
	*high = (in & 0xFF00) >> 8;
}

void readDefaultFrame(int anim, int frame, char* dataPtr)
{
	switch(anim)
	{
		case ANIM_CHARGING:
			




			break;
		default:	
			break;
	}
}

void readDefaultHeader(int anim)
{
	switch(anim)
	{
		case ANIM_CHARGING:
			numFrames = 19;
			fps = 15;			
			break;
		default:	
			break;
	}
}

