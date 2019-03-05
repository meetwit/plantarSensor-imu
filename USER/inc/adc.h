#ifndef __ADC_H
#define __ADC_H	

//#include "sys.h"	
#include "stm32f10x.h"			   

extern struct Analog_voltage		Analog_v;

struct Analog_voltage{
	u16 ch1;
	u16 ch2;
	u16 ch3;
	u16 ch4;
	u16 ch5;
	u16 ch6;
	u16 ch7;
	u16 ch8;
};

#define ADC_CH4  4  	//ͨ��4		 	  						  	 	    
#define ADC_CH5  5  	//ͨ��5	
#define ADC_CH6  6  	//ͨ��6		 	  						  	 	    
#define ADC_CH7  7  	//ͨ��7	 
#define ADC_CH8  8  	//ͨ��8		 	  						  	 	    
#define ADC_CH9  9  	//ͨ��9	 	
#define ADC_CH10  10  	//ͨ��10		 	  						  	 	    
#define ADC_CH11  11  	//ͨ��11	 	    
	   									   
void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ   
void clear_Analog_voltage(void);

#endif 















