#include "usart3.h"
#include "stdio.h"
#include "string.h"
#include "jy901.h"
#include <rtthread.h>

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
int _sys_exit(int x) 
{ 
	x = x;
return 0;	
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART3->DR = (u8) ch;      	//дDR,����1����������
	return ch;
}
#endif 
/************************************************************
��������void usart3_init(u32 baud);
��  �Σ�u32 baud:������
����ֵ����
��  �ܣ�����3��ʼ��
��  �ߣ�meetwit
ʱ  �䣺2017��11��17��19:29:38
*************************************************************/
void usart3_init(u32 baud){
	/*
	1.��GPIOʱ��
	2.��ʼ��PB10(����	��������)  PB11(����	��������)
	3.������3ʱ��
	4.�ֳ���1����ʼλ��8������λ��1��ֹͣλ
	5.����ʹ��
	6.������
	7.����ʹ��
	*/
	float div,div_frr;
	u16 div_man;
	
	RCC ->APB2ENR |= (0x1<<3);//GPIOBʹ��
	GPIOB ->CRH &=~(0xF<<8);
	GPIOB ->CRH |=(0xB<<8);//��������
	
	GPIOB ->CRH &=~(0Xf<<12);
	GPIOB ->CRH |=(0X8<<12);//��������
	
	RCC ->APB1ENR |=(0x1<<18);//����3ʱ��ʹ��
	USART3->CR1 &=~(0x1<<12);//һ����ʼλ��8������λ
	USART3->CR2 &=~(0X3<<12);//һ��ֹͣλ
	USART3->CR1 |=(0x1<<3);//����ʹ��
	
	USART3->CR1|=(0x1<<2);    //����ʹ��
	USART3->CR1|=(1<<5);    //��USART_SR�е�ORE����RXNEΪ��1��ʱ������USART�ж�
	
	div=(float) 36000000/(baud * 16);
	div_man =div;
	div_frr=div-div_man;
	div_man <<= 4;
	
	USART3->BRR = div_man + (div_frr*16);
	
	/*�������ȼ�*/
	NVIC_SetPriority(USART3_IRQn,NVIC_EncodePriority(7-2,2,3));
	/*ʹ���ж�*/
	NVIC_EnableIRQ(USART3_IRQn);//NVIC_EnableIRQ������ʹ���ⲿ�жϵ�
	
	USART3->CR1 |=(0x1<<13);//����ʹ��	
}


/************************************************************
��������PcTx_Byte3(u8 Tx_data)
��  �Σ�u8 Tx_data
����ֵ����
��  �ܣ�����3����һ���ֽ�
��  �ߣ�meetwit
ʱ  �䣺2017��11��17��19:47:54
*************************************************************/
void PcTx_Byte3(u8 Tx_data){
	while(!(USART3->SR &(0x1<<7)));
	USART3 ->DR = Tx_data;
	
}

/************************************************************
��������PcTx_String3(u8 *str)
��  �Σ�u8 *str �ַ�����ַ
����ֵ����
��  �ܣ�����3�����ַ���
��  �ߣ�meetwit
ʱ  �䣺2017��11��17��19:47:38
*************************************************************/
void PcTx_String3(u8 *str){
		while(*str !='\0'){
			PcTx_Byte3(*(str++));
		}
}


/************************************************************
��������USART2_IRQHandler()
��  �Σ���
����ֵ����
��  �ܣ�����2�ж�
��  �ߣ�meetwit
ʱ  �䣺2017��11��19��11:27:43
*************************************************************/
	void USART3_IRQHandler(void)
{
	u8 res_t3;
	rt_enter_critical();
	if(USART3->SR&(0x1<<5))	//���յ�����
	{ 
		res_t3=USART3->DR;
		CopeSerialData(res_t3);
	}		
	rt_exit_critical();
}


