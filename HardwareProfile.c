/* This file is use to for system hardware configuration functions*/
#include <proc/p32mx150f128d.h>
#define OUTPUT 0 // Tris Function for setting pin to output
#define INPUT 1 // tris function for setting pin to input
#define UP PORTBbits.RB9
#define DOWN PORTCbits.RC8
#define LEFT PORTCbits.RC9
#define RIGHT PORTBbits.RB13
#define DOWN PORTAbits.RA10





/*init_hardware = This function is used to set all input/output pins to the
 correct settings.  TRIS and PORT setting should all be done here and this
 function should be called prior to other functions.*/

void init_hardware(void)
{
    CFGCONbits.IOLOCK = 0; // must be done first to unlock and allow mapping of
                            //pins
    /////SPI ////////////////////////////////////////////////
    SDI1R = 0b0010;//set SPI Data in to pin RPB1 chip pin 22

    RPB2R = 0b0011;//set spi Data out to pin RPB2 chip pin 23

    //////////////////////////////////////////////////////////

    ///Serial UART//////////////////////////////////////////
    U1RXR = 0b0101;  //Set Serial PX to RPC6 chip pin 2

    RPC7R = 0b0001;  //Set Serial TX to RPC7 chip pin 3
    ///////////////////////////////////////////////////////



    CFGCONbits.IOLOCK = 1; // must be done last to lock and prevent mapping of
                            //pins
///////////////////////////////////////////////////////////////////////
    /////////Setting up button direction and Pull UP resisitor
    /// Pins set for Active Low
    
    //Port Direction
    TRISAbits.TRISA10 = INPUT;
    TRISBbits.TRISB9 = INPUT;
    TRISBbits.TRISB13 = INPUT;
    TRISCbits.TRISC8 = INPUT;
    TRISCbits.TRISC9 = INPUT;

    //Pull-up resistors on
     CNPUAbits.CNPUA10 = 1;
     CNPUBbits.CNPUB9 = 1;
     CNPUBbits.CNPUB13 = 1;
     CNPUCbits.CNPUC8 = 1;
     CNPUCbits.CNPUC9 = 1;
     
////////////////////////////////////////////////////////////////////


}