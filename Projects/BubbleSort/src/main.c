/*******************************************************************************
FILE NAME   : main.c
DESCRIPTION : Generic main file

*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nucleoboard.h"
#include "hw_init.h"
#include "print.h"
#include "pseudo_random.h"

/* Public variables ----------------------------------------------------------*/
__IO uint32_t timer;
PRINT_DEFINEBUFFER();           /* required for lightweight sprintf */

/* Private variables ----------------------------------------------------------*/
char clr_scrn[] = { 27, 91, 50, 74, 0 };              // esc[2J

// A small array of random value to initialize
int array[20]; 

/* Private prototype ---------------------------------------------------------*/
void delay(uint32_t time);

extern void bubbleSort(int A[], int cnt, int val);

/*******************************************************************************
Function Name   : main
Description     : 
Parameters      :
Return value    :               */
void main() {
  int i;
  uint32_t count;

  Hw_init();
  
  // Initialize Pseudo-Random Generator
  Initialize(0xdeadbeef);

  PrintString(clr_scrn); /* Clear entire screen */

  RETAILMSG(1, ("Lab Week 3: Built %s %s.\r\n\r\n",
              __DATE__,
              __TIME__));  

  // Initialize the entire array to pseudo-random numbers
  PrintString("Array before sort:\n\n");
  count = sizeof(array)/sizeof(int);
  for (i = 0; i < count; i++) 
  {
    // Allow negatives and low byte for clarity
    array[i] = ExtractU32() & 0x800000FF;
    PrintHex(array[i]);
    PrintByte(0x20);
  }
  
  // Sort the array in ascending order
  bubbleSort(array, count, 0 /*ascending*/);
  
  // Display array contents
  PrintString("\n\n Ascending sort:\n");
  for (i = 0; i < count; i++) {
    PrintHex(array[i]);
    PrintByte(0x20);
  }
  
  PrintString("\n\n");
  
  // Initialize the entire array to new pseudo-random numbers
  PrintString("Array before sort:\n\n");
  for (i = 0; i < count; i++) 
  {
    // Allow negatives and low byte for clarity
    array[i] = ExtractU32() & 0x800000FF;
    PrintHex(array[i]);
    PrintByte(0x20);
  }
  
  // Sort the array in descending order
  bubbleSort(array, count, 1 /*descending*/);
  
  // Display the array contents
  PrintString("\n\n Descending sort:\n");
  for (i = 0; i < count; i++) {
    PrintHex(array[i]);
    PrintByte(0x20);
  }
  
  PrintString("\n");

  PrintString("\n STOP");
  while (1) {
    // loop forever
    asm("nop");         // an example of inline assembler
  }
}

/*******************************************************************************
Function Name   : delay
Description     : Add a delay for timing perposes.
Parameters      : Time - In ms. 1 = .001 second
Return value    : None              */
void delay(uint32_t time) {
  
  timer = time;
  while(timer) {}
}
/*******************************************************************************
Function Name   : SystemInit
Description     : Called by IAR's assembly startup file.
Parameters      :
Return value    :               */
void SystemInit(void) {
  // System init is called from the assembly .s file
  // We will configure the clocks in hw_init
  asm("nop");
}