/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : uart0.c
 * @file_description: This file contains 4 functions Init_UART0 and UART0_IRQHandler,__sys_write and __sys_read
 *					  Init_UART0 function initializes the UART0 by configuring the registers
 *				      UART0_IRQHandler function is serviced whenever UART is called the priority of the UART is 2
 *					  printf() calls __sys_write function
 * @Credits: Referred Dean's Book chapter 8 for uart initialisation and IRQ handler. Also referred Lecture notes.
*************************************************************************************************************************
*/

#include <MKL25Z4.H>
#include <stdio.h>
#include "core_cm0plus.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

//#include "sysclock.h"
#include "llfifo.h"


#include "uart0.h"


#define UART_OVERSAMPLE_RATE       (16)
#define SYSTEM_CLOCK               (24e6) // system clock of 24MHz
#define BUFFER_SIZE                (256)
#define MODE_8_BIT                 (0)
#define DISABLE_PARITY             (0)
#define EVEN_PARITY                (0)

// Buffer declaration
llfifo_t *TxBuffer, *RxBuffer;

/*
 * @Function
 *     This function initializes the UART0 for UART communication
 *     Clock configuration, mode bit setting, Parity setting and Enabling Interrupts are done here
 * @Parametes: Baud rate
 * @Returns : None
 */
void Init_UART0(uint32_t baud_rate)
{
	uint16_t sbr;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 24 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);

	// Setting baud rate and oversampling ratio
	sbr = (uint16_t)((SYSTEM_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE - 1);

	/* Disable RX Input active edge interrupt and LIN Break Detect Interrupt, select one stop bit*/
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(1) | UART0_BDH_LBKDIE(0);

	/*Don't enable Loopback mode, use 8 data bit mode, Parity bit enabled for even*/
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(MODE_8_BIT) | UART0_C1_PE(DISABLE_PARITY);

	/*Don't invert transmit data , do enable interrupts for errors*/
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
					| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// LSB bit is transmitted first, receive data not inverted
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	// initialize Txbuffer and Rxbuffer
	TxBuffer = llfifo_create(BUFFER_SIZE);
	RxBuffer = llfifo_create(BUFFER_SIZE);


	//UART interrupt has been given second priority
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupt
	UART0->C2 |= UART_C2_RIE(1); //Enabling only receive interrupt as transmit interrupt is called in printf
	UART0->C2 &= ~UART_C2_TIE(1);

	//Receiver and Transmitter are enabled
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);
}

/*
 * @Function
 *     This function is UART0 IRQ which is services when an interrupt occurs
 *     Rx and Tx operations are handled here
 * @Parametes: None
 * @Returns : None
 */
void UART0_IRQHandler(void)
{
	uint8_t ch;
	// check for any mask errors
	if(UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK))
	{
		UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;
		ch = UART0->D;
	}

	// Reception part
	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		ch = UART0->D;
		llfifo_enqueue(RxBuffer,ch);
	}
	//Transmission part
	if((UART0->C2 & UART0_C2_TIE_MASK) && (UART0->S1 & UART0_S1_TDRE_MASK))
	{
		ch = llfifo_dequeue(TxBuffer);
		if(ch != 0)
		{
			UART0->D = ch;
		}
		else
		{
			UART0->C2 &= ~UART0_C2_TIE_MASK; //clear the TIE mask
		}
	}
}


/*
 * @Function
 *     This function is called whenever we call printf and it enqueues all the string from the printf
 *     and enables Transmit interrupt
 * @Parametes: handle, buf pointer and size of the buffer
 * @Returns : status of the buffer
 */

int __sys_write(int handle, char* buf, int size)
{
	if(buf==NULL)
	{
		return -1;
	}
	for(int i = 0;i<size;i++){
		while(TxBuffer->length == TxBuffer->capacity);
		__disable_irq();
		llfifo_enqueue(TxBuffer,buf[i]);
		__enable_irq();
	}

	if(!(UART0->C2 & UART0_C2_TIE_MASK))
	{
		UART0->C2 |= UART0_C2_TIE(1);// Enable TIE
	}
	return 0;
}

/*
 * @Function
 *     This function Reads the value according to the input
 *
 * @Parametes: None
 * @Returns : character
 */

int __sys_readc(void) {
	//Only if the queue has a length more than 0
	if (llfifo_length(RxBuffer) > 0) {
		uint8_t incoming_char = llfifo_dequeue(RxBuffer);
		return incoming_char;
	} else {
		return -1;
	}
}
