#include <rtthread.h>
#include "stdio.h"
#include "stm32f10x.h"
#include "string.h"

#include "thread_mw.h"

rt_thread_t tid1=RT_NULL;
rt_thread_t tid2=RT_NULL;
rt_thread_t tid_time=RT_NULL;


int main(){
	rt_kprintf("\r\n\r\nmeetwit rtt systerm start init!\r\n\r\n");
	
	tid1=rt_thread_create("get_adc",get_adc,RT_NULL,256,6,100);
	rt_thread_startup(tid1);
	
	tid2=rt_thread_create("send_data",send_data,RT_NULL,2048,4,100);
	rt_thread_startup(tid2);

	tid_time=rt_thread_create("tid_time",time_thread,RT_NULL,512,3,100);
	rt_thread_startup(tid_time);
	
	
	rt_kprintf("meetwit rtt systerm started!\r\n\r\n");
	
	return 0;
}








