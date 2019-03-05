#include "usart3.h"
#include "stdio.h"
#include "string.h"
#include "jy901.h"
#include <rtthread.h>

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x;
return 0;	
} 
//重定向fputc函数
//printf的输出，指向fputc，由fputc输出到串口
//这里使用串口1(USART1)输出printf信息
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART3->DR = (u8) ch;      	//写DR,串口1将发送数据
	return ch;
}
#endif 
/************************************************************
函数名：void usart3_init(u32 baud);
形  参：u32 baud:波特率
返回值：无
功  能：串口3初始化
作  者：meetwit
时  间：2017年11月17日19:29:38
*************************************************************/
void usart3_init(u32 baud){
	/*
	1.开GPIO时钟
	2.初始化PB10(发送	复用推挽)  PB11(接收	浮空输入)
	3.开串口3时钟
	4.字长：1个起始位，8个数据位，1个停止位
	5.发送使能
	6.波特率
	7.串口使能
	*/
	float div,div_frr;
	u16 div_man;
	
	RCC ->APB2ENR |= (0x1<<3);//GPIOB使能
	GPIOB ->CRH &=~(0xF<<8);
	GPIOB ->CRH |=(0xB<<8);//复用推挽
	
	GPIOB ->CRH &=~(0Xf<<12);
	GPIOB ->CRH |=(0X8<<12);//浮空输入
	
	RCC ->APB1ENR |=(0x1<<18);//串口3时钟使能
	USART3->CR1 &=~(0x1<<12);//一个起始位，8个数据位
	USART3->CR2 &=~(0X3<<12);//一个停止位
	USART3->CR1 |=(0x1<<3);//发送使能
	
	USART3->CR1|=(0x1<<2);    //接收使能
	USART3->CR1|=(1<<5);    //当USART_SR中的ORE或者RXNE为’1’时，产生USART中断
	
	div=(float) 36000000/(baud * 16);
	div_man =div;
	div_frr=div-div_man;
	div_man <<= 4;
	
	USART3->BRR = div_man + (div_frr*16);
	
	/*设置优先级*/
	NVIC_SetPriority(USART3_IRQn,NVIC_EncodePriority(7-2,2,3));
	/*使能中断*/
	NVIC_EnableIRQ(USART3_IRQn);//NVIC_EnableIRQ是用来使能外部中断的
	
	USART3->CR1 |=(0x1<<13);//串口使能	
}


/************************************************************
函数名：PcTx_Byte3(u8 Tx_data)
形  参：u8 Tx_data
返回值：无
功  能：串口3发送一个字节
作  者：meetwit
时  间：2017年11月17日19:47:54
*************************************************************/
void PcTx_Byte3(u8 Tx_data){
	while(!(USART3->SR &(0x1<<7)));
	USART3 ->DR = Tx_data;
	
}

/************************************************************
函数名：PcTx_String3(u8 *str)
形  参：u8 *str 字符串地址
返回值：无
功  能：串口3发送字符串
作  者：meetwit
时  间：2017年11月17日19:47:38
*************************************************************/
void PcTx_String3(u8 *str){
		while(*str !='\0'){
			PcTx_Byte3(*(str++));
		}
}


/************************************************************
函数名：USART2_IRQHandler()
形  参：无
返回值：无
功  能：串口2中断
作  者：meetwit
时  间：2017年11月19日11:27:43
*************************************************************/
	void USART3_IRQHandler(void)
{
	u8 res_t3;
	rt_enter_critical();
	if(USART3->SR&(0x1<<5))	//接收到数据
	{ 
		res_t3=USART3->DR;
		CopeSerialData(res_t3);
	}		
	rt_exit_critical();
}


