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

#define ADC_CH4  4  	//通道4		 	  						  	 	    
#define ADC_CH5  5  	//通道5	
#define ADC_CH6  6  	//通道6		 	  						  	 	    
#define ADC_CH7  7  	//通道7	 
#define ADC_CH8  8  	//通道8		 	  						  	 	    
#define ADC_CH9  9  	//通道9	 	
#define ADC_CH10  10  	//通道10		 	  						  	 	    
#define ADC_CH11  11  	//通道11	 	    
	   									   
void Adc_Init(void); 				//ADC通道初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值   
void clear_Analog_voltage(void);

#endif 















