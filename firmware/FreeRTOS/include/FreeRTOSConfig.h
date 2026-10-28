/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    #include <stdio.h>
    extern uint32_t SystemCoreClock;
#endif

//锟斤拷锟斤拷
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)

/***************************************************************************************************************/
/*                                        FreeRTOS锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷选锟斤拷                                              */
/***************************************************************************************************************/
#define configUSE_PREEMPTION					1                       //1使锟斤拷锟斤拷占式锟节核ｏ拷0使锟斤拷协锟斤拷
#define configUSE_TIME_SLICING					1						//1使锟斤拷时锟斤拷片锟斤拷锟斤拷(默锟斤拷式使锟杰碉拷)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                       //1锟斤拷锟斤拷锟斤拷锟解方锟斤拷锟斤拷选锟斤拷锟斤拷一锟斤拷要锟斤拷锟叫碉拷锟斤拷锟斤拷
                                                                        //一锟斤拷锟斤拷硬锟斤拷锟斤拷锟斤拷前锟斤拷锟斤拷指锟筋，锟斤拷锟斤拷锟绞癸拷玫锟?
                                                                        //MCU没锟斤拷锟斤拷些硬锟斤拷指锟斤拷幕锟斤拷撕锟接︼拷锟斤拷锟斤拷锟轿?锟斤拷
#define configUSE_TICKLESS_IDLE					0                       //1锟斤拷锟矫低癸拷锟斤拷tickless模式
#define configUSE_QUEUE_SETS					1                       //为1时锟斤拷锟矫讹拷锟斤拷
#define configCPU_CLOCK_HZ						(SystemCoreClock)       //CPU频锟斤拷
#define configTICK_RATE_HZ						(1000)                  //时锟接斤拷锟斤拷频锟绞ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷为1000锟斤拷锟斤拷锟节撅拷锟斤拷1ms
#define configMAX_PRIORITIES					(32)                    //锟斤拷使锟矫碉拷锟斤拷锟斤拷锟斤拷燃锟?
#define configMINIMAL_STACK_SIZE				((unsigned short)130)   //锟斤拷锟斤拷锟斤拷锟斤拷使锟矫的讹拷栈锟斤拷小
#define configMAX_TASK_NAME_LEN					(16)                    //锟斤拷锟斤拷锟斤拷锟斤拷锟街凤拷锟斤拷锟斤拷锟斤拷

#define configUSE_16_BIT_TICKS					0                       //系统锟斤拷锟侥硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟酵ｏ拷
                                                                        //1锟斤拷示为16位锟睫凤拷锟斤拷锟斤拷锟轿ｏ拷0锟斤拷示为32位锟睫凤拷锟斤拷锟斤拷锟斤拷
#define configIDLE_SHOULD_YIELD					1                       //为1时锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟紺PU使锟斤拷权锟斤拷锟斤拷锟斤拷同锟斤拷锟饺硷拷锟斤拷锟矫伙拷锟斤拷锟斤拷
#define configUSE_TASK_NOTIFICATIONS            1                       //为1时锟斤拷锟斤拷锟斤拷锟斤拷通知锟斤拷锟杰ｏ拷默锟较匡拷锟斤拷
#define configUSE_MUTEXES						1                       //为1时使锟矫伙拷锟斤拷锟脚猴拷锟斤拷
#define configQUEUE_REGISTRY_SIZE				8                       //锟斤拷为0时锟斤拷示锟斤拷锟矫讹拷锟叫硷拷录锟斤拷锟斤拷锟斤拷锟街碉拷强锟斤拷锟?
                                                                        //锟斤拷录锟侥讹拷锟叫猴拷锟脚猴拷锟斤拷锟斤拷锟斤拷锟侥匡拷锟?
#define configCHECK_FOR_STACK_OVERFLOW			0                       //锟斤拷锟斤拷0时锟斤拷锟矫讹拷栈锟斤拷锟斤拷锟解功锟杰ｏ拷锟斤拷锟绞癸拷么斯锟斤拷锟?
                                                                        //锟矫伙拷锟斤拷锟斤拷锟结供一锟斤拷栈锟斤拷锟斤拷锟斤拷雍锟斤拷锟斤拷锟斤拷锟斤拷使锟矫的伙拷
                                                                        //锟斤拷值锟斤拷锟斤拷为1锟斤拷锟斤拷2锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷栈锟斤拷锟斤拷锟解方锟斤拷锟斤拷
#define configUSE_RECURSIVE_MUTEXES				1                       //为1时使锟矫递归互锟斤拷锟脚猴拷锟斤拷
#define configUSE_MALLOC_FAILED_HOOK			0                       //1使锟斤拷锟节达拷锟斤拷锟斤拷失锟杰癸拷锟接猴拷锟斤拷
#define configUSE_APPLICATION_TASK_TAG			0                       
#define configUSE_COUNTING_SEMAPHORES			1                       //为1时使锟矫硷拷锟斤拷锟脚猴拷锟斤拷

/***************************************************************************************************************/
/*                                FreeRTOS锟斤拷锟节达拷锟斤拷锟斤拷锟叫癸拷锟斤拷锟斤拷选锟斤拷                                                */
/***************************************************************************************************************/
#define configSUPPORT_DYNAMIC_ALLOCATION        1                       //支锟街讹拷态锟节达拷锟斤拷锟斤拷
#define configTOTAL_HEAP_SIZE					((size_t)(10*1024))     //系统锟斤拷锟斤拷锟杰的堆达拷小

/***************************************************************************************************************/
/*                                FreeRTOS锟诫钩锟接猴拷锟斤拷锟叫关碉拷锟斤拷锟斤拷选锟斤拷                                              */
/***************************************************************************************************************/
#define configUSE_IDLE_HOOK						0                       //1锟斤拷使锟矫匡拷锟叫癸拷锟接ｏ拷0锟斤拷锟斤拷使锟斤拷
#define configUSE_TICK_HOOK						0                       //1锟斤拷使锟斤拷时锟斤拷片锟斤拷锟接ｏ拷0锟斤拷锟斤拷使锟斤拷

/***************************************************************************************************************/
/*                                FreeRTOS锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟斤拷锟阶刺拷占锟斤拷泄氐锟斤拷锟斤拷锟窖★拷锟?                                */
/***************************************************************************************************************/
#define configGENERATE_RUN_TIME_STATS	        0                       //为1时锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷统锟狡癸拷锟斤拷
#define configUSE_TRACE_FACILITY				1                       //为1锟斤拷锟矫匡拷锟接伙拷锟斤拷锟劫碉拷锟斤拷
#define configUSE_STATS_FORMATTING_FUNCTIONS	1                       //锟斤拷锟絚onfigUSE_TRACE_FACILITY同时为1时锟斤拷锟斤拷锟斤拷锟斤拷锟?锟斤拷锟斤拷锟斤拷
                                                                        //prvWriteNameToBuffer(),vTaskList(),
                                                                        //vTaskGetRunTimeStats()
                                                                        
/***************************************************************************************************************/
/*                                FreeRTOS锟斤拷协锟斤拷锟叫关碉拷锟斤拷锟斤拷选锟斤拷                                                  */
/***************************************************************************************************************/
#define configUSE_CO_ROUTINES 			        0                       //为1时锟斤拷锟斤拷协锟教ｏ拷锟斤拷锟斤拷协锟斤拷锟皆猴拷锟斤拷锟斤拷锟斤拷锟斤拷募锟絚routine.c
#define configMAX_CO_ROUTINE_PRIORITIES         ( 2 )                   //协锟教碉拷锟斤拷效锟斤拷锟饺硷拷锟斤拷目

/***************************************************************************************************************/
/*                                FreeRTOS锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷锟叫关碉拷锟斤拷锟斤拷选锟斤拷                                            */
/***************************************************************************************************************/
#define configUSE_TIMERS				        1                               //为1时锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES-1)        //锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟饺硷拷
#define configTIMER_QUEUE_LENGTH		        5                               //锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟叫筹拷锟斤拷
#define configTIMER_TASK_STACK_DEPTH	        (configMINIMAL_STACK_SIZE*2)    //锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟斤拷锟秸伙拷锟叫?

/***************************************************************************************************************/
/*                                FreeRTOS锟斤拷选锟斤拷锟斤拷锟斤拷锟斤拷选锟斤拷                                                      */
/***************************************************************************************************************/
#define INCLUDE_xTaskGetSchedulerState          1                       
#define INCLUDE_vTaskPrioritySet		        1
#define INCLUDE_uxTaskPriorityGet		        1
#define INCLUDE_vTaskDelete				        1
#define INCLUDE_vTaskCleanUpResources	        1
#define INCLUDE_vTaskSuspend			        1
#define INCLUDE_vTaskDelayUntil			        1
#define INCLUDE_vTaskDelay				        1
#define INCLUDE_eTaskGetState			        1
#define INCLUDE_xTimerPendFunctionCall	        1

/***************************************************************************************************************/
/*                                FreeRTOS锟斤拷锟叫讹拷锟叫关碉拷锟斤拷锟斤拷选锟斤拷                                                  */
/***************************************************************************************************************/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15                      //锟叫讹拷锟斤拷锟斤拷锟斤拷燃锟?
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5                       //系统锟缴癸拷锟斤拷锟斤拷锟斤拷锟斤拷卸锟斤拷锟斤拷燃锟?
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/***************************************************************************************************************/
/*                                FreeRTOS锟斤拷锟叫断凤拷锟斤拷锟斤拷锟叫关碉拷锟斤拷锟斤拷选锟斤拷                                          */
/***************************************************************************************************************/
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler	SVC_Handler
#define xPortSysTickHandler	SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

