/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>            /* Include to use PIC32 peripheral libraries     */
#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
}

void Delay_MS(int x)
{/*
  *This function is used to delay the process for a certian number of
  * milliseconds.  Feed it the number of ms to delay and the function will hold
  * processor stack in nop for the duration.  This function must be tuned to the
  * frequency of the processor.
  */

    float delay=1000;
    float start=0;

    start=ReadCoreTimer();
    while( ReadCoreTimer()<=(start+delay))
    {}
    /*
    int i = 0;
    int j = 0;

    for (i=0; i<x; i++)
    {
        for (j=0; j<1000; j++)//need to verify that 1000 = 1 MS
        {
            asm(nop);
        }
    }
     */

}