#ifndef __THREAD_MW_H
#define __THREAD_MW_H
#include <rtthread.h>
#include "stdio.h"
#include "stm32f10x.h"
#include "string.h"

extern u16 time_x,time_xx,time_xxx,time_xxxx;		//¼ÇÂ¼hzÊý


void get_adc(void* parameter);
void send_data(void* parameter);
void get_num(void* parameter);

void time_thread(void* parameter);

#endif
