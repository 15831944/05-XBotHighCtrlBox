/*******************************************************Copyright*********************************************************
**                                            ����������ʢ�����˼������޹�˾
**                                                       �з���
**                                               http://robot.up-tech.com
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			ConfigTypes.h
** ����޶�����:		2008-11-12
** ���汾:			1.0
** ����:				�������Ͷ��壬�ṩ�˿��ƼĴ����Ĳ�����
**
**------------------------------------------------------------------------------------------------------------------------
** ������:			����
** ��������:			2008-07-24
** �汾:				1.0
** ����:				��BDMC��Ŀͳһ�����ӿ�
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:			����
** �޶�����:			2009-08-02
** �汾:				1.1
** ����:				��AVRGCC�ڵĿ�ͳһ������ӿ�
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
*************************************************************************************************************************/

#ifndef CONFIGTYPES_H_
#define CONFIGTYPES_H_

//#include <avr/io.h>
//#include <avr/wdt.h>
//#include <avr/pgmspace.h>
//#include <avr/eeprom.h>
//#include <avr/interrupt.h>
//
//#include <util/delay.h>
//
//#include <stdlib.h>
//#include <stdio.h>

/*************************************************************************************************************************
**                                                  �߼�����������
*************************************************************************************************************************/
#ifndef FALSE
  #define  FALSE  0                    /* Boolean value FALSE. FALSE is defined always as a zero value. */
#endif
#ifndef TRUE
  #define  TRUE   1                    /* Boolean value TRUE. TRUE is defined always as a non zero value. */
#endif

#ifndef NULL
  #define  NULL   0
#endif


#define ERR_MASK		 0b00111111	   /* ����λ���� */

#define ERR_OK           0             /* ���� */
#define ERR_SPEED        1             /* �����豸�ܹ�������ٶ� */
#define ERR_RANGE        2             /* ����������Χ */
#define ERR_VALUE        3             /* ������ֵ����ȷ */
#define ERR_OVERFLOW     4             /* ��ʱ����� */
#define ERR_MATH         5             /* ��������� */
#define ERR_ENABLED      6             /* �豸������ */
#define ERR_DISABLED     7             /* �豸�ѱ����� */
#define ERR_BUSY         8             /* ����æ */
#define ERR_NOTAVAIL     9             /* �����ֵ�򷽷��޷�ʹ�� */
#define ERR_RXEMPTY      10            /* ���ջ����������� */
#define ERR_TXFULL       11            /* ��������� */
#define ERR_BUSOFF       12            /* �����޷�ʹ�� */
#define ERR_OVERRUN      13            /* ������� */
#define ERR_FRAMING      14            /* ֡���� */
#define ERR_PARITY       15            /* ��ż���� */
#define ERR_NOISE        16            /* ������� */
#define ERR_IDLE         17            /* ���ô��� */
#define ERR_FAULT        18            /* ���� */
#define ERR_BREAK        19            /* ��ͨѶ�н��ܵ���Ϸ��� */
#define ERR_CRC          20            /* CRC��У����� */
#define ERR_ARBITR       21            /* �ڵ㶪ʧ�ٲ� */
#define ERR_PROTECT      22            /* ���� */
#define ERR_UNDERFLOW    23            /* ��������� */
#define ERR_UNDERRUN     24            /* ��ջ������ */
#define ERR_COMMON       25            /* �豸�������� */
#define ERR_LINSYNC      26            /* ����ͬ������ */
#define ERR_DEPENDENCE   27            /* ģ���������豸û������ */

#define INIT_COMPLETE	 7			   /* ��ʼ����ɱ�־λ */



/*************************************************************************************************************************
**                                                  SDK�������Ͷ���
*************************************************************************************************************************/
typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

typedef unsigned       char    uint8;                               /* �޷���8λ���ͱ���  */
typedef signed         char    int8;                                /* �з���8λ���ͱ���  */
typedef unsigned short int     uint16;                              /* �޷���16λ���ͱ��� */
typedef signed   short int     int16;                               /* �з���16λ���ͱ��� */
typedef unsigned long  int     uint32;                              /* �޷���32λ���ͱ��� */
typedef signed   long  int     int32;                               /* �з���32λ���ͱ��� */
typedef                float   fp32;                                /* �����ȸ�������32λ���ȣ� */
typedef                double  fp64;                                /* ˫���ȸ�������64λ���ȣ� */

typedef signed char    Word8;
typedef unsigned char  UWord8;
typedef short          Word16;
typedef unsigned short UWord16;
typedef long           Word32;
typedef unsigned long  UWord32;
typedef signed char    Int8;
typedef unsigned char  UInt8;
typedef int            Int16;
typedef unsigned int   UInt16;
typedef long           Int32;
typedef unsigned long  UInt32;
typedef __typeof__(sizeof(0)) ssize_t;
typedef int ibool;


/*************************************************************************************************************************
**                                                  �Ĵ���������
*************************************************************************************************************************/
#define SetRegBit(reg, bit)                                     (reg |= _BV(bit))
#define ClrRegBit(reg, bit)                                     (reg &= ~_BV(bit))
#define GetRegBit(reg, bit)                                     (reg & _BV(bit))
#define SetReg(reg, val)                                        (reg = (uint8)(val))
#define GetReg(reg)                                             (reg)
#define SetRegBits(reg, mask)                                   (reg |= (uint8)(mask))
#define GetRegBits(reg, mask)                                   (reg & (uint8)(mask))
#define ClrRegBits(reg, mask)                                   (reg &= (uint8)(~(mask)))
#define SetRegMask(reg, maskAnd, maskOr)                        (reg = (uint8)((GetReg(reg) & ~(maskAnd)) | (maskOr)))
#define SetRegBitVal(reg, bit, val)                             ((val) == 0 ? (reg &= ~_BV(bit)) : (reg |= _BV(bit)))
#define ChangeRegBits(reg, mask)                                (reg ^= (mask))
#define ChangeRegBit(reg, bit)                                  (reg ^= _BV(bit))


/* ����λ�����޸ĺ� */
#define In16(var,l,h)  (var = ((word)(l)) | (((word)(h)) << 8))
#define In32(var,l,h)  (var = ((dword)(l)) | (((dword)(h)) << 16))

#define Out16(l,h,val) { h = (byte)((val) >> 8); l = (byte)(val); }
#define Out32(l,h,val) { h = (word)((val) >> 16); l = (word)(val); }

#define Output(P, V) SetReg(P,V)
#define Input(P) GetReg(P)


#define LED1_ON		PORTE.OUTCLR  = PIN4_bm
#define LED2_ON		PORTE.OUTCLR  = PIN5_bm
#define LED1_OFF	PORTE.OUTSET  = PIN4_bm
#define LED2_OFF	PORTE.OUTSET  = PIN5_bm

#define LED3_ON		PORTC.OUTCLR  = PIN1_bm
#define LED4_ON		PORTC.OUTCLR  = PIN1_bm
#define LED3_OFF	PORTC.OUTSET  = PIN4_bm
#define LED4_OFF	PORTC.OUTSET  = PIN4_bm

#define CTRL_DIS	0X00
#define CTRL_EN		0X01

#define USARTD0_RS485_TX_EN		PORTD.OUTSET  = PIN1_bm
#define USARTD0_RS485_TX_DIS	PORTD.OUTCLR  = PIN1_bm


#endif
/*************************************************************************************************************************
**                                                      �ļ�����
*************************************************************************************************************************/
