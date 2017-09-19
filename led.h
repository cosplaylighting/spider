////////////////////////////////////////////////////////////////////////////////
// FAST ASM BASED WS2812B ADDRESSABLE LED LED LIBRARY
////////////////////////////////////////////////////////////////////////////////


#include <stdint.h>


#define RGB(r, g, b) (						\
	(((uint32_t)((r) & 0xFF)) << 16)	|	\
	(((uint32_t)((g) & 0xFF)) <<  8)	|	\
	( (uint32_t)((b) & 0xFF))				\
)

#define RGBX(r, g, b, x) ( (((r) & 0xFF) << (16-x))  |  (((g) & 0xFF) << (8-x)) | (((b) & 0xFF) >> (x)) )
#define DIM(c, x) ( ((((c)&0xff0000)>>(16+(x)))<<16)  |  ((((c)&0xff00)>>(8+(x)))<<8)  |  (((c)&0xff)>>(x)) )



#ifdef __AVR__

//TOTAL NUMBER OF LEDS
#define LED_TOTAL 20

#define LED_PORT	PORTB
#define LED_DDR		DDRB
#define LED_BIT		4

#endif


#define T1H			900		// Width of a 1 bit in ns
#define T1L			600		// Width of a 1 bit in ns

#define T0H			400		// Width of a 0 bit in ns
#define T0L			900		// Width of a 0 bit in ns

#define RES			6000	// Width of the low gap between bits to cause a frame to latch

#define NS_TO_CYCLES(n) ((n) / (1000000000L / (F_CPU)))


// SETUP THE LED STRIP
inline void led_setup();

// FINALIZ AND SHOW LED STRIP
inline void led_show();

// SEND A SINGLE BIT TO THE LED STRIP
inline void led_bit(uint8_t bit);

// SEND A SINGLE BYTE TO THE LED STRIP
inline void led_byte(uint8_t byte);

// SEND A SINGLE PIXEL TO THE LED STRIP
inline void led_pixel(uint8_t r, uint8_t g, uint8_t b);


