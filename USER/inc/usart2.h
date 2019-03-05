#ifndef __USART2_H
#define __USART2_H	 

#include "stm32f10x.h"

void usart2_init(u32 baud);	//≥ı ºªØ		
void PcTx_Byte2(u8 Tx_data);
void PcTx_String2(u8 *str);


#endif

















