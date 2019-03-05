#include "adc.h"		
#include "jy901.h"		

struct Analog_voltage		Analog_v={0};

//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��1																	   
void  Adc_Init(void)
{    
	//�ȳ�ʼ��IO��
 	RCC->APB2ENR|=1<<2;    //ʹ��PORTA��ʱ�� 
 	RCC->APB2ENR|=1<<3;    //ʹ��PORTB��ʱ�� 
 	RCC->APB2ENR|=1<<4;    //ʹ��PORTC��ʱ�� 
	GPIOA->CRL=0x0000FFFF;//PA anolog����		//GPIOA->CRL&=0XFFFFFF0F;//PA1 anolog����
	GPIOB->CRL=0xFFFFFF00;//PB anolog����		
	GPIOC->CRL=0xFFFFFF00;//PC anolog����		
	//ͨ��10/11����			 
	RCC->APB2ENR|=1<<9;    //ADC1ʱ��ʹ��	  
	RCC->APB2RSTR|=1<<9;   //ADC1��λ
	RCC->APB2RSTR&=~(1<<9);//��λ����	    
	RCC->CFGR&=~(3<<14);   //��Ƶ��������	
	//SYSCLK/DIV2=12M ADCʱ������Ϊ12M,ADC���ʱ�Ӳ��ܳ���14M!
	//���򽫵���ADC׼ȷ���½�! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //����ģʽ����
	ADC1->CR1|=0<<16;      //��������ģʽ  
	ADC1->CR1&=~(1<<8);    //��ɨ��ģʽ	  
	ADC1->CR2&=~(1<<1);    //����ת��ģʽ	
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //��������ת��  
	ADC1->CR2|=1<<20;      //ʹ�����ⲿ����(SWSTART)!!!	����ʹ��һ���¼�������
	ADC1->CR2&=~(1<<11);   //�Ҷ���	 
	ADC1->SQR1&=~(0XF<<20);
	//ADC1->SQR1|=0<<20;     //1��ת���ڹ��������� Ҳ����ֻת����������1 	
	ADC1->SQR1|=0<<20;     //x��ת���ڹ��������� Ҳ����ֻת����������1 			   
	
	ADC1->SMPR1 = 0x0000003F;//8��ͨ����ʱ��Ϊ239.5T
	ADC1->SMPR2 = 0x3FFFF000;//8��ͨ����ʱ��Ϊ239.5T
	
	ADC1->CR2|=1<<0;	   //����ADת����	 
	ADC1->CR2|=1<<3;       //ʹ�ܸ�λУ׼  
	while(ADC1->CR2&1<<3); //�ȴ�У׼���� 			 
    //��λ���������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ��������� 		 
	ADC1->CR2|=1<<2;        //����ADУ׼	   
	while(ADC1->CR2&1<<2);  //�ȴ�У׼����
	//��λ�����������Կ�ʼУ׼������У׼����ʱ��Ӳ�����  
}

//���ADCֵ
//ch:ͨ��ֵ 0~16
//����ֵ:ת�����
u16 Get_Adc(u8 ch)   
{
	//����ת������	  		 
	ADC1->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //��������ת��ͨ�� 
	while(!(ADC1->SR&1<<1));//�ȴ�ת������	 	   
	return ADC1->DR;		//����adcֵ	
}

void clear_Analog_voltage(void){
	Analog_v.ch1=0;
	Analog_v.ch2=0;
	Analog_v.ch3=0;
	Analog_v.ch4=0;
	Analog_v.ch5=0;
	Analog_v.ch6=0;
	Analog_v.ch7=0;
	Analog_v.ch8=0;
}







