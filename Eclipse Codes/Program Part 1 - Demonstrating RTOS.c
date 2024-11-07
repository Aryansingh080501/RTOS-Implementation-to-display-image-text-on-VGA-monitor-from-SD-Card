#include <stdio.h>
#include <unistd.h>
#include <io.h>
#include <system.h>
#include <math.h>
#include "altera_avalon_pio_regs.h"
#include <stdio.h>
#include "includes.h"
#include "Altera_UP_SD_Card_Avalon_Interface.h"


/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];
OS_STK    task3_stk[TASK_STACKSIZE];
/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2


#define MAX_SUBDIRECTORIES 20


void clear_all_leds();
void clear_hex();
void find_files (char* path);
void delay(int d);

int switches_in;
int tens_hex;
int ones_hex;
/* Prints "Hello World" and sleeps for three seconds */
void task1(void* pdata)
{
  while (1)
  {
	  clear_all_leds();
	  clear_hex();
	  IOWR_ALTERA_AVALON_PIO_DATA(RED_LEDS_BASE, 0xaaaa);
	  printf("Task 1 executes\n");
	  delay(500000);

	  OSTimeDlyHMSM(0, 0, 3, 0);


  }
}


/* Prints "Hello World" and sleeps for three seconds */
void task2(void* pdata)
{
  while (1)
  {
	  clear_all_leds();
	  clear_hex();

	  IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LEDS_BASE, 0b10101010);
	  printf("Task 2 executes\n");
	  delay(500000);
	  OSTimeDlyHMSM(0, 0,3 , 0);

  }
}
/* The main function creates two task and starts multi-tasking */
int main(void)
{

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


  OSStart();
  return 0;
}


void clear_hex()
{
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_0_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_1_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_2_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_3_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_4_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_5_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_6_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_DATA(SEVEN_SEG_7_BASE, 0xFF);
}

void clear_all_leds()
{
	IOWR_ALTERA_AVALON_PIO_DATA(RED_LEDS_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LEDS_BASE, 0);
}

void delay(int d)
{
	while (d > 0){

		d = d -1;
	}
}
