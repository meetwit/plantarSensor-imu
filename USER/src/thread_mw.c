#include "thread_mw.h"
#include "adc.h"
#include "usart2.h"
#include "usart3.h"
#include "jy901.h"

u16 time_x=0,time_xx=0,time_xxx=0,time_xxxx=0;		//¼ÇÂ¼hzÊý


void send_data_f(u8 num){
	if(num==1){
	printf("%d,%d,%d,%d,%d,%d,%d,%d,",Analog_v.ch1,Analog_v.ch2,Analog_v.ch3,Analog_v.ch4,Analog_v.ch5,Analog_v.ch6,Analog_v.ch7,Analog_v.ch8);
	}
}


void send_data_f2(u8 num){
	
	
	if(num==1){
	printf("%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f.\r\n",d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7],d[8]);
	}else if(num==2){
		printf("x_a=%d,y_a=%d,z_a=%d\r\n",x_a,y_a,z_a);
	}else if(num==3){
		printf("x_a=%f,y_a=%f,z_a=%f\r\n",d[0],d[1],d[2]);
	}
	//printf("%7.2f,%7.2f,%7.2f,%7.2f.",d[1],d[2],d[3],d[6]);		
	//printf("h");
	
}

void get_adc(void* parameter){
	while(1){
		time_xx++;
		Analog_v.ch8 = Get_Adc(ADC_CH4);		//12Î»
		Analog_v.ch7 = Get_Adc(ADC_CH5);
		Analog_v.ch6 = Get_Adc(ADC_CH6);
		Analog_v.ch5 = Get_Adc(ADC_CH7);
		Analog_v.ch4 = Get_Adc(ADC_CH8);
		Analog_v.ch3 = Get_Adc(ADC_CH9);
		Analog_v.ch2 = Get_Adc(ADC_CH10);
		Analog_v.ch1 = Get_Adc(ADC_CH11);
		rt_thread_yield();
		//rt_thread_delay(3000);
		rt_timer_check();
	}
	
}

void send_data(void* parameter){
	rt_tick_t tick_temp;
	while(1){
		time_x++;
		tick_temp = rt_tick_get();
		printf("%.3f,",tick_temp/1000.0);
		send_data_f(2);
		send_data_f2(2);
		rt_thread_delay(10);		//other thread time  //==1 60hz	==5 50hz	==10 40hz
		rt_timer_check();
	}
	
}

void time_thread(void* parameter){
	rt_tick_t tick_temp;
  rt_uint8_t h=0,m=0,s=0;
	
	while(1){
		tick_temp = rt_tick_get();
		s=tick_temp/RT_TICK_PER_SECOND%60;
		m=tick_temp/RT_TICK_PER_SECOND/60%60;
		h=tick_temp/RT_TICK_PER_SECOND/60/60%24;
		rt_kprintf("\r\nThe system runtime is %d:%d:%d.%d\r\n",h,m,s,tick_temp%RT_TICK_PER_SECOND);
		rt_kprintf("send_hz=%d,meg_hz=%d,imu_rig_hz=%d,imu_error_hz=%d\r\n",time_x,time_xx,time_xxxx/4,time_xxx);
		time_x=0;
		time_xx=0;
		time_xxx=0;
		time_xxxx=0;
		rt_thread_delay(RT_TICK_PER_SECOND);
	}
	
}

