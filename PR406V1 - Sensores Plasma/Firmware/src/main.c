
#include <htc.h>
#include <stdlib.h>
#include "xtypes.h"
#include "pio.h"

#ifdef __ECLIPSE__
typedef char bit;
#include <port/pic18f/pic18f45k22reg.h>
#define __PROG_CONFIG(a,b)
#define __IDLOC(a)
#define interrupt
#define low_priority
#endif

__PROG_CONFIG(0x1,0x7300); //00-01 (cristal externo de 15Mhz)
__PROG_CONFIG(0x2,0x0006); //02-03
__PROG_CONFIG(0x3,0xB500); //04-05
__PROG_CONFIG(0x4,0x0085); //06-07
__PROG_CONFIG(0x5,0xC00F); //08-09
__PROG_CONFIG(0x6,0xE00F); //10-11
__PROG_CONFIG(0x7,0x400F); //12-13
__IDLOC(01234567);

#define FOSC		60000000UL
#define FOSCUS		(FOSC/4000000) 	//pulsos do oscilador/us
#define FOSCMS		(FOSC/4000) 	//pulsos do oscilador/ms

void delayus(int t) {
	while (t>=10) { _delay(FOSCUS*10-25); t -= 10; }
	while (t--) _delay(FOSCUS-11);
}

void delayms(int t) {
	while (t--) _delay(FOSCMS);
}

void IniciaTMR2(void) {//tempo original de interrupção de 4/60E6 * 256 = 17,066us
	//T2CONbits.T2CKPS = 1; //prescaler 4
	//T2CONbits.T2OUTPS = 0;
	T2CON = 0b00000000;
	TMR2 = 240;
	TMR2IF = 0;
	TMR2IP = 1;//alta prioridade
	TMR2IE = 1;
	TMR2ON = 1;
}

void IniciaTMR6(void) {//tempo original de interrupção de 4/60E6 * 256 = 17,066us
	//T2CONbits.T2CKPS = 1; //prescaler 4
	//T2CONbits.T2OUTPS = 0;
	T6CON = 0b00000000;
	TMR6 = 240;
	TMR6IF = 0;
	TMR6IP = 1;//alta prioridade
	TMR6IE = 1;
	TMR6ON = 1;
}


void IniciaTMR3(void) {//timer ccp2
	T3CONbits.T3CKPS = 0;//verificar
	T3CONbits.TMR3CS = 0;
	T3CONbits.T3RD16 = 1;
	TMR3ON = 1;
}
void IniciaTMR5(void) {//timer ccp1
	T5CONbits.T5CKPS = 0;//verificar
	T5CONbits.TMR5CS = 0;
	T5CONbits.T5RD16 = 1;
	TMR5ON = 1;
}


void IniciaCCP1(){
	CCP1MD=0;//habilita modulo ccp
	CCP1IE=1;//habilita interrupção
	CCPTMRS0bits.C1TSEL=2;//utiliza timer 5;
//	CCP1CONbits.CCP1M = 5;// subida
}

void IniciaCCP2(){
	CCP2MD=0;//habilita modulo ccp
	CCP2IE=1;//habilita interrupção
	CCPTMRS0bits.C2TSEL=1;//utiliza timer 3;
//	CCP2CONbits.CCP2M = 5;//subida
}

void IniciaANALOG(){
	ANSELD = 0b00001001;//AN20 e AN23
	ADCON2bits.ADCS = 1;//FOSC/8
	ADCON1bits.PVCFG = 0;//Ref - VDD
	ADCON1bits.NVCFG = 0;//Ref - VSS
	ADCON2bits.ADFM = 1;//ADRESH/ADRESL
	ADCON2bits.ACQT = 1;//2Tad
}

/*void Inicializa(void) {
	int i;

	for (i=0;i<1000;i++);

	InitSystem();
	IniciaUART1(1250000,1);
	IniciaTMR2();
	IniciaTMR3();
	IniciaTMR5();
	IniciaCCP1();
	IniciaCCP2();
	IniciaANALOG();
	//pin_ENA = 1;//trava motor z
}*/

void IniciaUART2(U32 baud, char irqon) {
	U32 x = (60000000UL/(4*baud)) - 1;
	SPBRGH2 = x>>8;
	SPBRG2 = x;
	TXSTA2 = BIT7|BIT5|BIT2;
	RCSTA2 = BIT7|BIT4;
	BAUDCON2 = BIT3;
	RC2IE = irqon;
}

void tx1(U8 d)
{
	TXREG1 = d;
	while (!TRMT1);
//	RCIF = 0;
}

void IniciaDACX(void) {
	//configura os pinos analógicos
	ANSELA = 0x00;
	ANSELB = 0x00;
	ANSELC = 0x00;
	ANSELD = 0x00;
	ANSELE = 0x00;
}

void IniciaPIOX(void) {
	//Entradas e saidas
	TRISA = kTRISA;
	TRISB = kTRISB;
	TRISC = kTRISC;
	TRISD = kTRISD;
	TRISE = kTRISE;

	//valor padrão de inicialização
	PORTA = kPORTA;
	PORTB = kPORTB;
	PORTC = kPORTC;
	PORTD = kPORTD;
	PORTE = kPORTE;
}


//por default a UART inicia com interrupção de alta prioridade
void IniciaUART1X(U32 baud, char irqon) {
	U32 x = (FOSC/(4*baud)) - 1;
	SPBRGH1 = x>>8;
	SPBRG1 = x;
	TXSTA1 = BIT7|BIT5|BIT2;
	RCSTA1 = BIT7|BIT4; // bit 7 trava timer2/4/6 SPEN
//	RCSTA1 = BIT4;
	BAUDCON1 = BIT3;
	RC1IE = irqon;
}

   void showbyte(U8 b0)
    {
	 GIE=0;
	   pin_LEDOK=1;pin_LEDOK=0;pin_LEDOK=1;pin_LEDOK=0;
	 if (b0&128) pin_LEDOK=1;else pin_LEDOK=0;
	 if (b0&64) pin_LEDOK=1;else pin_LEDOK=0;
		 if (b0&32) pin_LEDOK=1;else pin_LEDOK=0;
		 if (b0&16) pin_LEDOK=1;else pin_LEDOK=0;
	 if (b0&8) pin_LEDOK=1;else pin_LEDOK=0;
	 if (b0&4) pin_LEDOK=1;else pin_LEDOK=0;
		 if (b0&2) pin_LEDOK=1;else pin_LEDOK=0;
		 if (b0&1) pin_LEDOK=1;else pin_LEDOK=0;
		pin_LEDOK=0;
		 GIE=1;
    }

volatile U8 bloco0,bloco1,bloco2,bloco3,bloco4,bloco5;
volatile U8 bloco[6];
volatile U8 posicaox=0;
volatile U8 posicaoy=0;
volatile U8 posicaoz=0;
volatile U8 enableall=0;
volatile U8 comando=0;
U8 comando_old=0;

void monta_bloco_thc(U8 a,U8 b,U8 c,U8 d)
{
	U16 check=a+b+c+d+30000;

	GIE = 0;
	NOP();
	bloco0=a;
	bloco1=b;
	bloco2=c;
	bloco3=d;
	bloco4=check>>8;
	bloco5=check;
	GIE = 1;

}



void delayw(BYTE t)
{
	if (t--==0) return;
	if (t--==0) return;
	if (t--==0) return;
	if (t--==0) return;
	if (t--==0) return;
	if (t--==0) return;
	if (t--==0) return;
	if (t--==0) return;
	if (t--==0) return;

}

#define pulsox delayw(5);	pinRC3=1; delayw(5); difzz--;	pinRC3=0; if (difzz==0) {	posicaoy_atual=py; return;}

void atualiza_posicaox()
{
static BYTE	posicaoy_atual=0;

GIE=0;
NOP();
BYTE py=posicaox;
GIE=1;
int difz=py-posicaoy_atual;
if (difz==0) return;

BYTE dirz=0; if (difz>0) dirz=1;

BYTE difzz=abs(py-posicaoy_atual);

	if (difzz>128) // estouro
	{
	  difzz=256-difzz;
	  dirz=1-dirz;
	}

	if (pinRC0!=dirz) delayus(1); // 200khz == 5us alto 5 us baixo

	NOP();
	pinRC0=dirz;

	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	  pulsox
	   pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		  pulsox
		   pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			  pulsox
			   pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				  pulsox
				   pulsox
	   posicaoy_atual=py;

}




#define pulsoy delayw(5);	pinRE2=1;pinRD1=1; delayw(5); difzz--;	pinRE2=0;pinRD1=0; if (difzz==0) {	posicaoy_atual=py; return;}

void atualiza_posicaoy()
{
static BYTE	posicaoy_atual=0;

GIE=0;
NOP();
BYTE py=posicaoy;
GIE=1;
int difz=py-posicaoy_atual;
if (difz==0) return;

BYTE dirz=0; if (difz>0) dirz=1;

BYTE difzz=abs(py-posicaoy_atual);

	if (difzz>128) // estouro
	{
	  difzz=256-difzz;
	  dirz=1-dirz;
	}

	if (pinRE1!=dirz) delayus(1); // 200khz == 5us alto 5 us baixo

	NOP();

	pinRE1=dirz;

   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy
   pulsoy

   posicaoy_atual=py;
}


//#define pinRE0		PORTEbits.RE0
//#define pinRA5		PORTAbits.RA5

#define pulsozz delayw(5); pinRE0=1; delayw(5); difzz--;	pinRE0=0; if (difzz==0) {	posicaoy_atual=py; return;}

void atualiza_posicaoz()
{
static BYTE	posicaoy_atual=0;

GIE=0;
NOP();
BYTE py=posicaoz;
GIE=1;
int difz=py-posicaoy_atual;
if (difz==0) return;

BYTE dirz=0; if (difz>0) dirz=1;

BYTE difzz=abs(py-posicaoy_atual);

	if (difzz>128) // estouro
	{
	  difzz=256-difzz;
	  dirz=1-dirz;
	}

	if (pinRA5!=dirz) delayus(1); // 200khz == 5us alto 5 us baixo

	NOP();

	pinRA5=dirz;

	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz
	pulsozz

	posicaoy_atual=py;
}



char estado(char i){
	 switch (i)	 {
	 case 0: return pin_S1;
	 case 1: return pin_S2;
	 case 2: return pin_S3;
	 case 3: return pin_S4;
	 case 4: return pin_S5;
	 case 8:  return pin_S6;
	 case 9:  return pin_S7;
	 case 10: return pin_S8;
	 case 11: return !pin_S9;
	 case 12: return !pin_S10;
	 }
	return 0;
}

//tratamento das interrupções de baixa prioridade
void onLPISR(void) {
}

void onSystemTick(void) {
}

// 	tempo total == 580,82 us   ==  2,26*257
//  clock timer5 15mhz  = t=66,66ns
// 	fator = 2,26/66,666 == 33,9
// 	contagem maxima = 8712  ==  257 *33.9

unsigned char h1=100;
char mede_hall1(){
	static char evento1=0;
	static char cevent=100;
	if (!cevent--) { cevent=100;  h1=100; return 2;} // falha
	static unsigned int t_subida1,t_descida;
    static unsigned int t_alto,t_baixo;
	static long h2x;
    static unsigned int tab;

	switch (evento1){
	case 0:	 evento1=1;
			 CCP1CON = 0;
			 CCP1MD=0;//habilita modulo ccp
			 CCP1CONbits.CCP1M=5; //ativa_ccp2(1); // pega proxima subida
			 CCP1IF = 0;
			 return 0;

	case 1:	if (!CCP1IF)  return 0;
			t_subida1 = CCPR1;
			CCP1CON = 0;
			CCP1MD=0;//habilita modulo ccp
			CCP1CONbits.CCP1M=4; //ativa_ccp2(0); // pega proxima descida
			CCP1IF = 0;
			evento1=2;
			 return 0;

	case 2:	if (!CCP1IF)  return 0;
			t_descida = CCPR1;
			CCP1CON = 0;
			CCP1MD=0;//habilita modulo ccp
			CCP1CONbits.CCP1M=5; //ativa_ccp2(1); // pega proxima subida
			CCP1IF = 0;
			evento1=3;
			 return 0;

	case 3:	if (!CCP1IF)  return 0;
			cevent=100;
			CCP1CON = 0; // desliga modulo ccp2
			CCP1IF=0;
			t_alto = t_descida - t_subida1; //~t_subida1 + t_descida  + 1;
			t_baixo = ~t_descida + CCPR1  + 1;
			evento1=4;
			return 0;

	case 4:	if ((t_alto+t_baixo)>10000){
					int ref=(t_alto+t_baixo)/2;
					if (t_alto>t_baixo)  t_alto=t_alto-ref;  else  t_baixo=t_baixo-ref;
				}
			evento1=5;
			return 0;

	//	case 5:	long h2x=(((t_alto+17)*(long)257)/(t_alto+t_baixo))-1; // tempo de exec= 100us
	case 5:	h2x=(t_alto+17)*(long)257; // 25us
			tab=t_alto+t_baixo;
			evento1=6;
			return 0;

	case 6:	h1=h2x/tab; // 60us  // 45us com interr desab;
			h1--;
			evento1=0;
			return 1;
	}
	return 1;
}

unsigned char h2=200;
char mede_hall2(){
	static char evento1=0;
	static char cevent=100;
	if (!cevent--) { cevent=100;  h2=200; return 2;} // falha
	static unsigned int t_subida1,t_descida;
	static unsigned int t_alto,t_baixo;
	static long h2x;
	static unsigned int tab;

	switch (evento1){
	case 0:	 evento1=1;
			 CCP2CON = 0;
			 CCP2MD=0;//habilita modulo ccp
			 CCP2CONbits.CCP2M=5;// pega proxima subida
			 CCP2IF = 0;
			 return 0;

	case 1:	if (!CCP2IF)  return 0;
			t_subida1 = CCPR2;
			CCP2CON = 0;
			CCP2MD=0;//habilita modulo ccp
			CCP2CONbits.CCP2M=4; // pega proxima descida
			CCP2IF = 0;
			evento1=2;
			 return 0;

	case 2:	if (!CCP2IF)  return 0;
			t_descida = CCPR2;
			CCP2CON = 0;
			CCP2MD=0;//habilita modulo ccp
			CCP2CONbits.CCP2M=5;// pega proxima subida
			CCP2IF = 0;
			evento1=3;
			return 0;

	case 3:	if (!CCP2IF)  return 0;
			cevent=100;// desarma protecao
			CCP2CON = 0; // desliga modulo ccp2
			CCP2IF=0;
			t_alto = ~t_subida1 + t_descida  + 1;
			t_baixo = ~t_descida + CCPR2  + 1;
			evento1=4;
			return 0;

	case 4:	if ((t_alto+t_baixo)>10000){ // pegou mais de 1 ciclo?
					int ref=(t_alto+t_baixo)/2;
					if (t_alto>t_baixo)  t_alto=t_alto-ref;  else  t_baixo=t_baixo-ref; // diminue um ciclo
				}
			evento1=5;
			return 0;

//	case 5:	long h2x=(((t_alto+17)*(long)257)/(t_alto+t_baixo))-1; // tempo de exec= 100us
	case 5:	h2x=(t_alto+17)*(long)257; // MULTIPLICACAO COM LONG 25us
			tab=t_alto+t_baixo;
			evento1=6;
			return 0;

	case 6:	h2=h2x/tab; //ATENCAO DIVISAO COM LONG ESTA DEMORANDO 60us  // 45us com interr desab;
			h2--;
			evento1=0;
			return 1;
	}
	return 1;
}


//interrupção de baixa prioridade
void interrupt low_priority LPISR(void) {
}

volatile int errosrx=1;

void interrupt onHPISR(void) {
	static U8 crif=0;
	static U8 nbr=0;
	static U8 blocor[6];
	static U8 nbloco=0; // trasm

	static long contt=0;
	static U8 ct=0;
	GIE=0;

  if (OERR2){ CREN2 = 0; CREN2 = 1;	RC2IF = 0; } // para evitar travamento da serial qdo enche a fifo

while (RC2IF)
	{
 	 crif=0;
	 U8 dx = RCREG2; // se nao ler ele reentra instantaneamente
 	 blocor[nbr]=dx;
     nbr++;
	 if (nbr>5)
     {
    	 nbr=0;
     	 U16 checkr=blocor[0]+blocor[1]+blocor[2]+blocor[3]+30000;
     	 U16 check16=(blocor[4]<<8)+blocor[5];
    	 if ( checkr==check16) {
    		 posicaox=blocor[0];
    		 posicaoy=blocor[1];
    		 posicaoz=blocor[2];
    		 comando=blocor[3];
        	 }    	 else    	 {    		 errosrx++;    	 }
     }
	}

	if (TMR6IF)
	{//tempo de interrupção de 10us
	    if (nbloco<6) TXREG1=bloco[nbloco];
		if (nbloco==7)
	    {  // prepara proximo bloco
	         nbloco=0;
			  bloco[0] = bloco0;
			  bloco[1] = bloco1;
			  bloco[2] = bloco2;
			  bloco[3] = bloco3;
			  bloco[4] = bloco4;
			  bloco[5] = bloco5;
	    }
		else
		   nbloco++;

		if (RC2IF) crif=0;
		crif++;
		if (crif>2) {
			nbr=0;
		}// time out
		TMR6IF=0;
		TMR6=129;//129;
	}
	GIE=1;
  }

//long   contw=10;
void main(void) {
	GIE = 0;
	ANSELA = 0x00;
	ANSELB = 0x00;
	ANSELC = 0x00;
	ANSELD = 0x00;
	ANSELE = 0x00;
	IniciaPIOX();

	IniciaUART2(1250000,0);	//Escrito na placa "485 EXT"  usada para receber
	IniciaUART1X(1250000,0); // Escrito na placa "485 CPU" usado para enviar somente

	IPEN = 1;
	PEIE = 1;
//	RC1IE=1;
	pin_TXRXEN = 1;		//Liga uart1  485 para transmitir

	T6CON = 0b00000000;
	TMR6 = 129; // 10us  conta 255-129  freq de 15mhz
	TMR6IF = 0;
	TMR6IP = 1;//alta prioridade
	TMR6IE = 1;
	TMR6ON = 1;


	// timer 5 roda a 15mhz usado para ccp1 e ccp2 medicao dos hall
	T5CONbits.T5CKPS = 0;//verificar
	T5CONbits.TMR5CS = 0;
	T5CONbits.T5RD16 = 1;
	TMR5IE = 0;  // usado somente para ccp1 e dois sem interrupcao
	TMR5ON = 1;

	CCP1MD=0;//habilita modulo ccp
	CCPTMRS0bits.C1TSEL=2; // timer5 no ccp2
	CCP1IE = 0;  // nao usa por interrupcao, sera verificado no poling

	CCP2MD=0;//habilita modulo ccp
	CCPTMRS0bits.C2TSEL=2; // timer5 no ccp2
	CCP2IE = 0;  // nao usa por interrupcao, sera verificado no poling

	long  contw=5;
	GIE = 0;
	while(1){
		pin_LEDOK=!pin_LEDOK;
		//pinRD1=0;
		LATDbits.LATD1 = !LATDbits.LATD1;
		 atualiza_posicaox();
		 atualiza_posicaoy();
		 atualiza_posicaoz();
		 static char ix=0;
		 static  int filtro[16];
		 static int espelho=0;
		 if (filtro[ix]<100){ // roda a aprox 30khz/numero de analises
			if (estado(ix))	filtro[ix]++;
			espelho&=~(1<<ix); // zera bit
		 } else {
			 espelho|=1<<ix; // seta bit
			 if (!estado(ix)) filtro[ix]=0;
		}
		if (ix++==13) ix=0;

		U8 SENSFC=espelho;
		U8 FIM_CURSO_CABECA_NOT=espelho>>8;

		static char medeccp=1;

		if (medeccp==1)	{
			if (mede_hall1()) medeccp=2;
		}else{
			if (mede_hall2()) medeccp=1;
		}

		monta_bloco_thc(SENSFC,FIM_CURSO_CABECA_NOT,h1,h2);

		if (comando){if (comando!=comando_old){ // pulso na fica na direcao que estiver
				comando_old=comando;
				if (comando==55){pinRE2=0; delayw(5);pinRE2=1; delayw(5); pinRE2=0;}
				if (comando==56){pinRD1=0; delayw(5);pinRD1=1; delayw(5); pinRD1=0;}
		}}

		if (contw++>10000){
			contw=0;
//		    cont6++;
		}}}




















