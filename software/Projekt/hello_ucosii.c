#include <stdio.h>
#include <system.h>
#include "includes.h"
#include <io.h>

#define  LED0 0x00000001
#define  LED1 0x00000002
#define  LED2 0x00000004
#define  LED3 0x00000008
#define  LED4 0x00000010
#define  LED5 0x00000020
#define  LED6 0x00000040
#define  LED7 0x00000080
#define  LED8 0x00000100
#define  LED9 0x00000200
#define  LED10 0x00000400
#define  LED11 0x00000800
#define  LED12 0x00001000
#define  LED13 0x00002000
#define  LED14 0x00004000
#define  LED15 0x00008000
#define  LED16 0x00010000
#define  LED17 0x00020000

#define  SW0 0x00000003
#define  SW1 0x00000005
#define  SW2 0x00000007
#define  SW3 0x00000009
#define  SW4 0x00000011
#define  SW5 0x00000021
#define  SW6 0x00000041
#define  SW7 0x00000081
#define  SW8 0x00000101
#define  SW9 0x00000201
#define  SW10 0x00000401
#define  SW11 0x00000801
#define  SW12 0x00001001
#define  SW13 0x00002001
#define  SW14 0x00004001
#define  SW15 0x00008001
#define  SW16 0x00010001
#define  SW17 0x00020001

#define  SEGA 0x00001
#define  SEGB 0x00002
#define  SEGC 0x00004
#define  SEGD 0x00008
#define  SEGE 0x00010
#define  SEGF 0x00020
#define  SEGG 0x00040

#define ZERO   SEGA | SEGB | SEGC | SEGD | SEGE | SEGF
#define ONE    SEGB | SEGC
#define TWO    SEGA | SEGB | SEGG | SEGE | SEGD
#define THREE  SEGA | SEGB | SEGC | SEGD | SEGG
#define FOUR   SEGF | SEGG | SEGB | SEGC
#define FIVE   SEGA | SEGF | SEGG | SEGC | SEGD
#define SIX    SEGA | SEGF | SEGE | SEGD | SEGC | SEGG
#define SEVEN  SEGA | SEGB | SEGC
#define EIGHT  SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG
#define NINE   SEGA | SEGB | SEGC | SEGD | SEGF | SEGG
#define A      SEGA | SEGB | SEGC | SEGE | SEGF | SEGG
#define B      SEFC | SEFE | SEFD | SEGC | SEGD | SEGG
#define C      SEGA | SEGF | SEGE | SEGD
#define D      SEGB | SEGC | SEGD | SEGE | SEGG
#define E      SEGA | SEGF | SEGE | SEGD | SEGG
#define F      SEGA | SEGF | SEGE | SEGG
#define O      SEGE | SEGD | SEGC | SEGG
#define R      SEGA | SEGB | SEGC | SEGE | SEGF | SEGG
#define o      SEGA | SEGB | SEGG | SEGF
#define S      SEGA | SEGF | SEGG | SEGC | SEGD
#define T      SEGA | SEGF | SEGE
#define P      SEGA | SEGB | SEGE | SEGF | SEGG
#define U      SEGF | SEGE | SEGD | SEGC | SEGB
#define L      SEGF | SEGE | SEGD


typedef enum POZIOM_TEMP{
POZIOM_0 = 0,
POZIOM_1 = 2,
POZIOM_2 = 4,
POZIOM_3 = 8,
POZIOM_4 = 16,
POZIOM_5 = 32,
POZIOM_6 = 64,
POZIOM_7 = 128,
POZIOM_8 = 256,
POZIOM_9 = 512,
POZIOM_10 = 1024,

}TEMP;


#define LED0 0x00000001
#define LED1 0x00000002
#define LED2 0x00000004
#define LED3 0x00000008

#define ZERO SEGA | SEGB | SEGC | SEGD |SEGE | SEGF

/* Definition of Task Stacks */
#define TASK_STACKSIZE 2048
OS_STK task1_stk[TASK_STACKSIZE];
OS_STK task2_stk[TASK_STACKSIZE];
OS_STK task3_stk[TASK_STACKSIZE];
OS_STK task_case_SW0_stk[TASK_STACKSIZE];
OS_STK task_case_SW1_stk[TASK_STACKSIZE];
OS_STK task_case_SW2_stk[TASK_STACKSIZE];
OS_STK task_case_SW3_stk[TASK_STACKSIZE];
OS_STK task_case_SW4_stk[TASK_STACKSIZE];
OS_STK task_case_SW0_n_stk[TASK_STACKSIZE];
OS_STK task_case_SW1_n_stk[TASK_STACKSIZE];
OS_STK task_case_SW2_n_stk[TASK_STACKSIZE];
OS_STK task_case_SW3_n_stk[TASK_STACKSIZE];
OS_STK task_case_SW4_n_stk[TASK_STACKSIZE];
OS_STK task_case_default_stk[TASK_STACKSIZE];
OS_STK task_case_default_n_stk[TASK_STACKSIZE];


OS_EVENT *SWBox0;
OS_EVENT *SWBox1;
OS_EVENT *SWBox2;
OS_EVENT *SWBox3;
OS_EVENT *SWBox4;
OS_EVENT *SWBox_default;


/* Definition of Task Priorities */

#define TASK1_PRIORITY 1
#define TASK2_PRIORITY 2
#define TASK3_PRIORITY 3
#define TASK4_PRIORITY 4
#define TASK5_PRIORITY 5
#define TASK6_PRIORITY 6
#define TASK7_PRIORITY 7
#define TASK8_PRIORITY 8
#define TASK9_PRIORITY 9
#define TASK10_PRIORITY 10
#define TASK11_PRIORITY 11
#define TASK12_PRIORITY 12
#define TASK13_PRIORITY 13
#define TASK14_PRIORITY 14
#define TASK15_PRIORITY 15


/* Prints "Hello World" and sleeps for three seconds */
void task1(void* pdata)
{
  while (1)
  {
printf("Hello from task1\n");
int sw;
int * msg;
sw = IORD(SW_SLIDERS_BASE, 0);

printf("Slider = %d\n", sw);
OSMboxPostOpt(SWBox1, &sw, OS_POST_OPT_BROADCAST);

IOWR(HEX_BASE, 0, 0);
IOWR(HEX_BASE, 1, 0);
IOWR(HEX_BASE, 2, 0);
IOWR(HEX_BASE, 3, 0);
IOWR(HEX_BASE, 4, 0);
IOWR(HEX_BASE, 5, 0);
OSTimeDlyHMSM(0, 0, 0, 10);
  }
}


void task2(void* pdata)
{
    while (1) {
        INT8U err;
//        printf("Hello from task2\n");
        int *num;

        num = OSMboxPend(SWBox1, 0, &err);

//        printf("T=%d\n", *num);

        IOWR(LEDS_BASE, 0, *num);
        OSTimeDlyHMSM(0, 0, 0, 10);
    }
}


void task3 (void* pdata){
	while(1) {
	    INT8U err;
	    int *sw_val = OSMboxPend(SWBox1, 0, &err);
	    int sw8 = IORD(SW_SLIDERS_BASE, 0) & SW8;

	    printf("warunek:\t %d \t %d \t %d\n ",*sw_val, *sw_val & SW8 , sw8);
        if(sw8 == 257) {
            switch(*sw_val) {
	            case SW0 | SW8:
	                OSMboxPost(SWBox0, sw_val);
	                break;
	            case SW1 | SW8:
	                OSMboxPost(SWBox1, sw_val);
	                break;
	            case SW2 | SW8:
	                OSMboxPost(SWBox2, sw_val);
	                break;
	            case SW3 | SW8:
	                OSMboxPost(SWBox3, sw_val);
	                break;
	            case SW4 | SW8:
	                OSMboxPost(SWBox4, sw_val);
	                break;
	        }
        } else {
        	printf("SW9 is not pressed\n");  // Debugging print
            switch(*sw_val) {

	            case SW0:

	                OSMboxPost(SWBox0, sw_val);
	                break;
	            case SW1:
	                OSMboxPost(SWBox1, sw_val);
	                break;
	            case SW2:
	                OSMboxPost(SWBox2, sw_val);
	                break;
	            case SW3:
	                OSMboxPost(SWBox3, sw_val);
	                break;
	            case SW4:
	                OSMboxPost(SWBox4, sw_val);
	                break;
	            default:
	                OSMboxPost(SWBox_default, sw_val);
	        }
        }
	}
}

void task_case_SW0(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox0, 0, &err);
        if(*num == SW0) {
            IOWR(LEDS_BASE, 0, LED0);
            IOWR(HEX_BASE, 0, C);
            IOWR(HEX_BASE, 1, o);
            IOWR(HEX_BASE, 2, ZERO);
            IOWR(HEX_BASE, 3, THREE);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW1(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == SW1) {
            IOWR(LEDS_BASE, 0, LED1);
            IOWR(HEX_BASE, 0, C);
            IOWR(HEX_BASE, 1, o);
            IOWR(HEX_BASE, 2, ZERO);
            IOWR(HEX_BASE, 3, FIVE);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW2(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == SW2) {
            IOWR(LEDS_BASE, 0, LED2);
            IOWR(HEX_BASE, 0, C);
            IOWR(HEX_BASE, 1, o);
            IOWR(HEX_BASE, 2, ZERO);
            IOWR(HEX_BASE, 3, SIX);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW3(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == SW3) {
            IOWR(LEDS_BASE, 0, LED3);
            IOWR(HEX_BASE, 0, C);
            IOWR(HEX_BASE, 1, o);
            IOWR(HEX_BASE, 2, FIVE);
            IOWR(HEX_BASE, 3, SEVEN);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW4(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == SW4) {
            IOWR(LEDS_BASE, 0, LED4);
            IOWR(HEX_BASE, 0, C);
            IOWR(HEX_BASE, 1, o);
            IOWR(HEX_BASE, 2, ZERO);
            IOWR(HEX_BASE, 3, NINE);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_default(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);

        int value = *num;

        // ignorujemy SW0 w sprawdzeniu
        int value_without_sw0 = value & ~SW0 & ~SW8;

        // jeśli więcej niż jeden bit jest ustawiony poza SW0
        if(value_without_sw0 & (value_without_sw0 - 1)) {
            IOWR(LEDS_BASE, 0, LED9);
            IOWR(HEX_BASE, 5, E);
            IOWR(HEX_BASE, 4, R);
            IOWR(HEX_BASE, 3, R);
            IOWR(HEX_BASE, 2, O);
            IOWR(HEX_BASE, 1, R);
        }

        OSTimeDlyHMSM(0,0,0,5);
    }
}


void task_case_SW0_n(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox0, 0, &err);
        if(*num == (SW0 | SW8)) {
            IOWR(LEDS_BASE, 0, LED0);
            IOWR(HEX_BASE, 0, ZERO);
            IOWR(HEX_BASE, 1, C);
            IOWR(HEX_BASE, 2, E);
            IOWR(HEX_BASE, 3, 0);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW1_n(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == (SW1 | SW8)) {
            IOWR(LEDS_BASE, 0, LED1);
            IOWR(HEX_BASE, 0, T);
            IOWR(HEX_BASE, 1, S);
            IOWR(HEX_BASE, 2, A);
            IOWR(HEX_BASE, 3, F);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW2_n(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == (SW2 | SW8)) {
            IOWR(LEDS_BASE, 0, LED2);
            IOWR(HEX_BASE, 0, ZERO);
            IOWR(HEX_BASE, 1, R);
            IOWR(HEX_BASE, 2, P);
            IOWR(HEX_BASE, 3, 0);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW3_n(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == (SW3 | SW8)) {
            IOWR(LEDS_BASE, 0, LED3);
            IOWR(HEX_BASE, 0, ZERO);
            IOWR(HEX_BASE, 1, T);
            IOWR(HEX_BASE, 2, U);
            IOWR(HEX_BASE, 3, A);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_SW4_n(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);
        if(*num == (SW4 | SW8)) {
            IOWR(LEDS_BASE, 0, LED4);
            IOWR(HEX_BASE, 0, S);
            IOWR(HEX_BASE, 1, S);
            IOWR(HEX_BASE, 2, A);
            IOWR(HEX_BASE, 3, L);
            IOWR(HEX_BASE, 4, SIX);
        }
        OSTimeDlyHMSM(0,0,0,5);
    }
}

void task_case_default_n(void* pdata) {
    while(1) {
        INT8U err;
        int *num = OSMboxPend(SWBox1, 0, &err);

        int value = *num;

        // ignorujemy SW0 w sprawdzeniu
        int value_without_sw0 = value & ~SW0 & ~SW8;

        // jeśli więcej niż jeden bit jest ustawiony poza SW0
        if(value_without_sw0 & (value_without_sw0 - 1)) {
            IOWR(LEDS_BASE, 0, LED9);
            IOWR(HEX_BASE, 5, E);
            IOWR(HEX_BASE, 4, R);
            IOWR(HEX_BASE, 3, R);
            IOWR(HEX_BASE, 2, ZERO);
            IOWR(HEX_BASE, 1, R);
        }

        OSTimeDlyHMSM(0,0,0,5);
    }
}






/* The main function creates two task and starts multi-tasking */
int main(void)
{

SWBox0 = OSMboxCreate((void*)0);
SWBox1 = OSMboxCreate((void*)0);
SWBox2 = OSMboxCreate((void*)0);
SWBox3 = OSMboxCreate((void*)0);
SWBox4 = OSMboxCreate((void*)0);

SWBox_default = OSMboxCreate((void*)0);


  OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);


  OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task3,
                  NULL,
                  (void *)&task3_stk[TASK_STACKSIZE-1],
                  TASK3_PRIORITY,
                  TASK3_PRIORITY,
                  task3_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW0,
                  NULL,
                  (void *)&task_case_SW0_stk[TASK_STACKSIZE-1],
                  TASK4_PRIORITY,
                  TASK4_PRIORITY,
                  task_case_SW0_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW1,
                  NULL,
                  (void *)&task_case_SW1_stk[TASK_STACKSIZE-1],
                  TASK5_PRIORITY, TASK5_PRIORITY,
                  task_case_SW1_stk, TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW2,
                  NULL,
                  (void *)&task_case_SW2_stk[TASK_STACKSIZE-1],
                  TASK6_PRIORITY,
                  TASK6_PRIORITY,
                  task_case_SW2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW3,
                  NULL,
                  (void *)&task_case_SW3_stk[TASK_STACKSIZE-1],
                  TASK7_PRIORITY,
                  TASK7_PRIORITY,
                  task_case_SW3_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW4,
                  NULL,
                  (void *)&task_case_SW4_stk[TASK_STACKSIZE-1],
                  TASK8_PRIORITY,
                  TASK8_PRIORITY,
                  task_case_SW4_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_default,
                  NULL,
                  (void *)&task_case_default_stk[TASK_STACKSIZE-1],
                  TASK9_PRIORITY,
                  TASK9_PRIORITY,
                  task_case_default_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW0_n,
                  NULL,
                  (void *)&task_case_SW0_n_stk[TASK_STACKSIZE-1],
                  TASK10_PRIORITY,
                  TASK10_PRIORITY,
                  task_case_SW0_n_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW1_n,
                  NULL,
                  (void *)&task_case_SW1_n_stk[TASK_STACKSIZE-1],
                  TASK11_PRIORITY,
                  TASK11_PRIORITY,
                  task_case_SW1_n_stk, TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW2_n,
                  NULL,
                  (void *)&task_case_SW2_n_stk[TASK_STACKSIZE-1],
                  TASK12_PRIORITY,
                  TASK12_PRIORITY,
                  task_case_SW2_n_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW3_n,
                  NULL,
                  (void *)&task_case_SW3_n_stk[TASK_STACKSIZE-1],
                  TASK13_PRIORITY,
                  TASK13_PRIORITY,
                  task_case_SW3_n_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_SW4_n,
                  NULL,
                  (void *)&task_case_SW4_n_stk[TASK_STACKSIZE-1],
                  TASK14_PRIORITY,
                  TASK14_PRIORITY,
                  task_case_SW4_n_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(task_case_default_n,
                  NULL,
                  (void *)&task_case_default_n_stk[TASK_STACKSIZE-1],
                  TASK15_PRIORITY,
                  TASK15_PRIORITY,
                  task_case_default_n_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSStart();
  return 0;
}
