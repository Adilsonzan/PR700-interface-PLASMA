#ifndef XTYPES_H
#define XTYPES_H
//---------------------------------------------------------------------
// historico
//---------------------------------------------------------------------
/*
    16.09.11: primeira versao
*/

//---------------------------------------------------------------------
// includes
//---------------------------------------------------------------------
//...

//---------------------------------------------------------------------
// defines
//---------------------------------------------------------------------
//...
#ifndef NULL
#define NULL    0
#endif

//---------------------------------------------------------------------
// Bit maps
//---------------------------------------------------------------------
//...
#define BIT0    (1UL<<0)	//0x0000 0001
#define BIT1    (1UL<<1)	//0x0000 0002
#define BIT2    (1UL<<2)	//0x0000 0004
#define BIT3    (1UL<<3)	//0x0000 0008
#define BIT4    (1UL<<4)	//0x0000 0010
#define BIT5    (1UL<<5)	//0x0000 0020
#define BIT6    (1UL<<6)	//0x0000 0040
#define BIT7    (1UL<<7)	//0x0000 0080
#define BIT8    (1UL<<8)	//0x0000 0100
#define BIT9    (1UL<<9)	//0x0000 0200
#define BIT10   (1UL<<10)	//0x0000 0400
#define BIT11   (1UL<<11)	//0x0000 0800
#define BIT12   (1UL<<12)	//0x0000 1000
#define BIT13   (1UL<<13)	//0x0000 2000
#define BIT14   (1UL<<14)	//0x0000 4000
#define BIT15   (1UL<<15)	//0x0000 8000
#define BIT16   (1UL<<16)	//0x0001 0000
#define BIT17   (1UL<<17)	//0x0002 0000
#define BIT18   (1UL<<18)	//0x0004 0000
#define BIT19   (1UL<<19)	//0x0008 0000
#define BIT20   (1UL<<20)	//0x0010 0000
#define BIT21   (1UL<<21)	//0x0020 0000
#define BIT22   (1UL<<22)	//0x0040 0000
#define BIT23   (1UL<<23)	//0x0080 0000
#define BIT24   (1UL<<24)	//0x0100 0000
#define BIT25   (1UL<<25)	//0x0200 0000
#define BIT26   (1UL<<26)	//0x0400 0000
#define BIT27   (1UL<<27)	//0x0800 0000
#define BIT28   (1UL<<28)	//0x1000 0000
#define BIT29   (1UL<<29)	//0x2000 0000
#define BIT30   (1UL<<30)	//0x4000 0000
#define BIT31   (1UL<<31)	//0x8000 0000

//---------------------------------------------------------------------
// Tipos de Dados
//---------------------------------------------------------------------
typedef unsigned char U8;
typedef unsigned char U08;
typedef unsigned short U16;
typedef unsigned long U32;
typedef signed char S8;
typedef signed char S08;
typedef signed short S16;
typedef signed long S32;
typedef volatile unsigned char VU8;
typedef volatile unsigned short VU16;
typedef volatile unsigned long VU32;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

typedef char string[32];
typedef float REAL;
//guarda apenas um nome de arquivo no formato 8.3+NULL
//ex: "firmware.hex\0"
//typedef char shortname[8+1+3+1];
typedef char * pchar;
typedef unsigned char * puchar;
typedef const char * cpchar;
typedef unsigned long tTIME;
typedef unsigned long tCOLOR;
typedef void * pvoid;

//ponteiro de funções simples com 1 parametro de entrada e retorno
typedef void (*pfunv)(void);
typedef char (*pfunc)(char data);
typedef short (*pfuns)(short data);
typedef long (*pfunl)(long data);

//limites dos tipos
#define MAXU32      0xFFFFFFFFUL
#define MAXS32      0x7FFFFFFFL
#define MINS32      0x80000000L
#define MAXU16      0xFFFFUL
#define MAXS16      0x7FFFL
#define MINS16      0x8000L

//#ifndef FALSE
//#define FALSE		0
//#endif
//#ifndef TRUE
//#define TRUE		1
//#endif

//---------------------------------------------------------------------
// prototipos
//---------------------------------------------------------------------
//...

//---------------------------------------------------------------------
// dependencias
//---------------------------------------------------------------------
//...

#endif
