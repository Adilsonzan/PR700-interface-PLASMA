#include "piobitspin.h"

//---------------------------------------------------------------------
// Definições dos pinos de acordo com o esquemático
//---------------------------------------------------------------------
/*<PORTA>
[RA0]  2, in,	S6
[RA1]  3, in,	S7
[RA2]  4, in,	S8
[RA3]  5, in,	S9
[RA4]  6, in,	S10
[RA5]  7, in,	S11
[RA6] 14, in,	OSC1:
[RA7] 15, in,	OSC2:*/
//  adn S11 agora é saida do eixo z dir #define kTRISA			(BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
#define kTRISA			(BIT7|BIT6|BIT4|BIT3|BIT2|BIT1|BIT0)
#define kPORTA			0x00

/*<PORTB>
[RB0] in,	S1
[RB1] in,	S2
[RB2] in,	S3
[RB3] in,	S4
[RB4] in,	S5
[RB5] in,	ENCODER3
[RB6] PGC:
[RB7] PGD: */
#define kTRISB			(BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)
#define kPORTB			0x00

/*<PORTC>
[RC0] out,	IO4
[RC1] in,	ENCODER2
[RC2] in,	ENCODER1
[RC3] out,	IO5
[RC4] out,	IO6
[RC5] out,	TX/#RX
[RC6] out,	TX
[RC7] in,	RX*/
#define kTRISC			(BIT7|BIT2|BIT1)
#define kPORTC			0x00

/*<PORTD>
[RD0] in, AN2
[RD1] out, LED_STATUS
[RD2] out, LED_OK
[RD3] in, AN1
[RD4] out, TX/#RX2
[RD5] in, ERRO
[RD6] out, TX2
[RD7] in, RX2*/
#define kTRISD			(BIT7|BIT5|BIT3|BIT0)
#define kPORTD			0x00

/*<PORTE>
[RE0] out,	IO1
[RE1] out,	IO2
[RE2] out,	IO3
[RE3] MCLR: nMCURESET*/
#define kTRISE			(BIT3)
#define kPORTE			0x00

//---------------------------------------------------------------------
// Definições dos pinos de acordo com a aplicação
//---------------------------------------------------------------------
//pinLXX - out;
//pinRXX - in;
//outros
#define pin_TXRXEN			pinLC5
#define pin_LEDTXRX			pinLD1
#define pin_LEDOK			pinLD2
#define pin_TXD				pinLC6

#define pin_PUL				pinLE0
#define pin_DIR				pinLE1
#define pin_ENA				pinLE2
#define pin_HABOHM			pinLC0

#define pin_S1				pinRB0
#define pin_S2				pinRB1
#define pin_S3				pinRB2
#define pin_S4				pinRB3
#define pin_S5				pinRB4
#define pin_S6				pinRA0
#define pin_S7				pinRA1
#define pin_S8				pinRA2
#define pin_S9				pinRA3
#define pin_S10				pinRA4
#define pin_S11				pinRA5

#define pin_ENC1			pinRC2
#define pin_ENC2			pinRC1
#define pin_ENC3			pinRB5

