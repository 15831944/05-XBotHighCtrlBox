//3301 -5  19200
//3317 -4 9600
//3325 -3 4800


/*******************************************************Copyright*********************************************************
**                                            ����������ʢ�����˼������޹�˾
**                                                       �з���
**                                               http://robot.up-tech.com
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			UsartInit.c
** ����޶�����:  	2010-04-12
** ���汾:			1.0
** ����:				Usart��ʼ������
**
**------------------------------------------------------------------------------------------------------------------------
** ������:			����
** ��������:			2010-04-12
** �汾:				1.0
** ����:				Usart��ʼ������
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
*************************************************************************************************************************/
#include "Apps/UsartInit.h"

static int16 BaudRate_A,BaudRate_B;

static void SetBaudRate(uint32 BaudRate)
{
	switch(BaudRate)
	{
	case 4800:
		BaudRate_A = 3325;
		BaudRate_B = -3;

		break;

	case 9600:
		BaudRate_A = 3317;
		BaudRate_B = -4;
		break;
	case 19200:
		BaudRate_A = 3301;
		BaudRate_B = -5;
		break;
	case 115200:

		break;
	}
}

/*************************************************************************************************************************
** ��������:			InitUsartC0
**
** ��������:			��ʼ��USARTCO
**						
**					                 
** �������:			void;
** ����ֵ:			void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:			����
** ��������:			2009-04-10
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitUsartC0(uint32 Baudrate)
{
	/* This PORT setting is only valid to USARTC0 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PC3 (TXD0) as output. */
	PORTC.DIRSET   = PIN3_bm;
	/* PC2 (RXD0) as input. */
	PORTC.DIRCLR   = PIN2_bm;

	/* Use USARTC0 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_C0, &USARTC0, USART_DREINTLVL_MED_gc);

	/* USARTC0, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_C0.usart, USART_CHSIZE_8BIT_gc,
					 USART_PMODE_DISABLED_gc, false);

	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_C0.usart, USART_RXCINTLVL_MED_gc);

	/* Set Baudrate to 19200 bps:
	 * Use the default I/O clock frequency that is 32 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (I/O clock frequency)/(16 * Baudrate)-1
	 *                 = 0
	 */
	SetBaudRate(Baudrate);
	USART_Baudrate_Set(&USARTC0, BaudRate_A , BaudRate_B);


	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_C0.usart);
	USART_Tx_Enable(USART_data_C0.usart);
}


/*************************************************************************************************************************
** ��������:			InitUsartC1
**
** ��������:			��ʼ��USARTC1
**
**
** �������:			void;
** ����ֵ:			void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:			����
** ��������:			2009-04-10
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitUsartC1(uint32 Baudrate)
{
	/* This PORT setting is only valid to USARTC1 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PC7 (TXD1) as output. */
	PORTC.DIRSET   = PIN7_bm;
	/* PC6 (RXD1) as input. */
	PORTC.DIRCLR   = PIN6_bm;

	/* Use USARTC1 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_C1, &USARTC1, USART_DREINTLVL_MED_gc);

	/* USARTC1, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_C1.usart, USART_CHSIZE_8BIT_gc,
					 USART_PMODE_DISABLED_gc, false);

	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_C1.usart, USART_RXCINTLVL_MED_gc);

	/* Set Baudrate to 4800 bps:
	 * Use the default I/O clock frequency that is 32 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (I/O clock frequency)/(16 * Baudrate)-1
	 *                 = 0
	 */
	SetBaudRate(Baudrate);
	USART_Baudrate_Set(&USARTC1, BaudRate_A , BaudRate_B);

	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_C1.usart);
	USART_Tx_Enable(USART_data_C1.usart);
}


/*************************************************************************************************************************
** ��������:			InitUsartD0
**
** ��������:			��ʼ��USARTD0
**
**
** �������:			void;
** ����ֵ:			void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:			����
** ��������:			2009-04-10
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitUsartD0(uint32 Baudrate)
{
	/* This PORT setting is only valid to USARTD0 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PD3 (TXD0) as output. */
	PORTD.DIRSET   = PIN3_bm;
	/* PD2 (RXD0) as input. */
	PORTD.DIRCLR   = PIN2_bm;

	/* Use USARTD0 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_D0, &USARTD0, USART_DREINTLVL_MED_gc);

	/* USARTD0, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_D0.usart, USART_CHSIZE_8BIT_gc,
					 USART_PMODE_DISABLED_gc, false);

	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_D0.usart, USART_RXCINTLVL_MED_gc);

	/* Enable TX Complete interrupt. */
	USART_TxdInterruptLevel_Set(USART_data_D0.usart, USART_TXCINTLVL_HI_gc);

	/* Set Baudrate to 19200 bps:
	 * Use the default I/O clock frequency that is 32 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (I/O clock frequency)/(16 * Baudrate)-1
	 *                 = 0
	 */
	SetBaudRate(Baudrate);
	USART_Baudrate_Set(&USARTD0, BaudRate_A , BaudRate_B);

	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_D0.usart);
	USART_Tx_Enable(USART_data_D0.usart);
}


/*************************************************************************************************************************
** ��������:			InitUsartD1
**
** ��������:			��ʼ��USARTD1
**
**
** �������:			void;
** ����ֵ:			void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:			����
** ��������:			2009-04-10
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitUsartD1(uint32 Baudrate)
{
	/* This PORT setting is only valid to USARTD1 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PD7 (TXD1) as output. */
	PORTD.DIRSET   = PIN7_bm;
	/* PD6 (RXD1) as input. */
	PORTD.DIRCLR   = PIN6_bm;

	/* Use USARTD1 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_D1, &USARTD1, USART_DREINTLVL_MED_gc);

	/* USARTD1, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_D1.usart, USART_CHSIZE_8BIT_gc,
					 USART_PMODE_DISABLED_gc, false);

	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_D1.usart, USART_RXCINTLVL_MED_gc);

	/* Set Baudrate to 19200 bps:
	 * Use the default I/O clock frequency that is 32 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (I/O clock frequency)/(16 * Baudrate)-1
	 *                 = 0
	 */
	SetBaudRate(Baudrate);
	USART_Baudrate_Set(&USARTD1, BaudRate_A , BaudRate_B);

	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_D1.usart);
	USART_Tx_Enable(USART_data_D1.usart);
}


/*************************************************************************************************************************
** ��������:			InitUsartE0
**
** ��������:			��ʼ��USARTE0
**
**
** �������:			void;
** ����ֵ:			void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:			����
** ��������:			2009-04-10
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitUsartE0(uint32 Baudrate)
{
	/* This PORT setting is only valid to USARTE0 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PD3 (TXD0) as output. */
	PORTE.DIRSET   = PIN3_bm;
	/* PD2 (RXD0) as input. */
	PORTE.DIRCLR   = PIN2_bm;

	/* Use USARTE0 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_E0, &USARTE0, USART_DREINTLVL_MED_gc);

	/* USARTE0, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_E0.usart, USART_CHSIZE_8BIT_gc,
					 USART_PMODE_DISABLED_gc, false);

	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_E0.usart, USART_RXCINTLVL_MED_gc);

	/* Set Baudrate to 19200 bps:
	 * Use the default I/O clock frequency that is 32 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (I/O clock frequency)/(16 * Baudrate)-1
	 *                 = 0
	 */
	SetBaudRate(Baudrate);
	USART_Baudrate_Set(&USARTE0, BaudRate_A , BaudRate_B);

	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_E0.usart);
	USART_Tx_Enable(USART_data_E0.usart);
}


/*************************************************************************************************************************
** ��������:			InitUsartE1
**
** ��������:			��ʼ��USARTE1
**
**
** �������:			void;
** ����ֵ:			void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:			����
** ��������:			2009-04-10
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitUsartE1(uint32 Baudrate)
{
	/* PE1 (TXEN) as output */
	PORTE.DIRSET   = PIN1_bm;

	/* TXEN set */
	PORTE.OUTSET   = PIN1_bm;

	/* This PORT setting is only valid to USARTE1 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PE7 (TXD1) as output. */
	PORTE.DIRSET   = PIN7_bm;
	/* PE6 (RXD1) as input. */
	PORTE.DIRCLR   = PIN6_bm;

	/* Use USARTE1 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_E1, &USARTE1, USART_DREINTLVL_MED_gc);

	/* USARTE1, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_E1.usart, USART_CHSIZE_8BIT_gc,
					 USART_PMODE_DISABLED_gc, false);

	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_E1.usart, USART_RXCINTLVL_MED_gc);

	/* Set Baudrate to 19200 bps:
	 * Use the default I/O clock frequency that is 32 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (I/O clock frequency)/(16 * Baudrate)-1
	 *                 = 0
	 */
	SetBaudRate(Baudrate);
	USART_Baudrate_Set(&USARTE1, BaudRate_A , BaudRate_B);

	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_E1.usart);
	USART_Tx_Enable(USART_data_E1.usart);
}


/*************************************************************************************************************************
** ��������:			InitUsartF0
**
** ��������:			��ʼ��USARTF0
**
**
** �������:			void;
** ����ֵ:			void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:			����
** ��������:			2009-04-10
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void InitUsartF0(uint32 Baudrate)
{
	/* This PORT setting is only valid to USARTF0 if other USARTs is used a
	 * different PORT and/or pins are used. */
	/* PF3 (TXD0) as output. */
	PORTF.DIRSET   = PIN3_bm;
	/* PF2 (RXD0) as input. */
	PORTF.DIRCLR   = PIN2_bm;

	/* Use USARTF0 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_F0, &USARTF0, USART_DREINTLVL_MED_gc);

	/* USARTF0, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_F0.usart, USART_CHSIZE_8BIT_gc,
					 USART_PMODE_DISABLED_gc, false);

	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_F0.usart, USART_RXCINTLVL_MED_gc);

	/* Set Baudrate to 2M bps:
	 * Use the default I/O clock frequency that is 32 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (I/O clock frequency)/(16 * Baudrate)-1
	 *                 = 0
	 */
	SetBaudRate(Baudrate);
	USART_Baudrate_Set(&USARTF0, BaudRate_A , BaudRate_B);

	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_F0.usart);
	USART_Tx_Enable(USART_data_F0.usart);
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTF0_RXC_vect)
{
	USART_RXComplete(&USART_data_F0);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTF0_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_F0);
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTC0_RXC_vect)
{
	USART_RXComplete(&USART_data_C0);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTC0_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_C0);
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTC1_RXC_vect)
{
	USART_RXComplete(&USART_data_C1);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTC1_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_C1);
}
/*! \brief Data Register Empty Interrupt Service Routine.
 *
 *  Data Register Empty Interrupt Service Routine.
 *  Transmits one byte from TX software buffer. Disables DRE interrupt if buffer
 *  is empty. Argument is pointer to USART (USART_data_t).
 *
 *  \param usart_data      The USART_data_t struct instance.
 */
void USART_DataRegEmpty_D0(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	bufPtr = &usart_data->buffer;

	/* Check if all data is transmitted. */
	uint8_t tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		uint8_t tempCTRLA = usart_data->usart->CTRLA;
		tempCTRLA = (tempCTRLA & ~USART_DREINTLVL_gm) | USART_DREINTLVL_OFF_gc;
		usart_data->usart->CTRLA = tempCTRLA;

	}else{
		/* Start transmitting. */
		USARTD0_RS485_TX_EN;
		uint8_t data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DATA = data;

		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}
}

/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTD0_RXC_vect)
{
	USART_RXComplete(&USART_data_D0);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTD0_DRE_vect)
{
	USART_DataRegEmpty_D0(&USART_data_D0);
}

/*! \brief Transmission Complete Interrupt service routine.
 *	2011-06-15  �����ո�д������RS485���ƣ��������ضϷ���ʹ��
 *
 */
ISR(USARTD0_TXC_vect)
{
	USARTD0_RS485_TX_DIS;
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTD1_RXC_vect)
{
	USART_RXComplete(&USART_data_D1);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTD1_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_D1);
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTE0_RXC_vect)
{
	USART_RXComplete(&USART_data_E0);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTE0_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_E0);
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTE1_RXC_vect)
{
	USART_RXComplete(&USART_data_E1);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTE1_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_E1);
}


/*************************************************************************************************************************
**														�ṹ������
*************************************************************************************************************************/
/*! USART data struct used in example. */
USART_data_t USART_data_C0;
USART_data_t USART_data_C1;
USART_data_t USART_data_D0;
USART_data_t USART_data_D1;
USART_data_t USART_data_E0;
USART_data_t USART_data_E1;
USART_data_t USART_data_F0;

/*************************************************************************************************************************
**                                                      �ļ�����
*************************************************************************************************************************/
