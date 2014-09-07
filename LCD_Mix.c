
#include <user.h>

#include "LCD_Mix.h"
/*The lcd should be connected as follows:
 * 4-bit mode
 * Data 4 goes to bit 0 of port
 * Data 5 goes to bit 1 of port
 * Data 6 goes to bit 2 of port
 * Data 7 goes to bit 3 of port
 * RW pin goes to bit 4 of port
 * E  pin goes to bit 5 of port
 * RS pin goes to bit 6 of port
 */
//define port for lcd//////////////////////////////////////////////////////////

#define LCDPORT  PORTB //Data Port
#define LCDTRIS  TRISB // Data pins for LCD
#define CONTRIS  TRISA //control pins for LCD

#define RW_PIN          PORTAbits.RA2   /* PORT for RW */
//#define RW_PIN_TRIS     TRISBbits.RB0   /* PORT for RW */
#define RS_PIN          PORTAbits.RA0   /* PORT for RS */
//#define RS_PIN_TRIS     TRISBbits.RC0   /* PORT for RW */
#define E_PIN           PORTAbits.RA8   /* PORT for E  */
//#define RW_PIN_TRIS     TRISBbits.RB0   /* PORT for RW */
///////////////////////////////////////////////////////////////////////////////

void lcd_init(void)
{
    CONTRIS = CONTRIS & 0b1100111101111111;

    LCDTRIS =  LCDTRIS & 0b1111100001111111;
    
    //ANSELC = 0x00;
    
    PORTB = 0x00;
    Delay_MS(500);
    //Delay1KTCYx(200);

    E_PIN = 0;
    RS_PIN = 0;
    RW_PIN = 0;


    commd(2);
    set_cursor(3); //set cursor to invisable
    commd(2);
    lcd_go_to(1,1);
    entry_mode(3);
    Delay_MS(500);
    //Delay1KTCYx(200);
}


void clear_screen(void)
{
    commd(1); // clears screen
    Delay_MS(500);
    //Delay10TCYx(100); //Pic 18 function
}

void step_cursor(int direction)
{
    /*Moves the cursor one character in the direction specified
     * dirction 1 equal right
     * diretion 0 equal left
     */

    if (direction)
    {
        commd(20);
    }
    else
    {
        commd(16);

    }
}

void entry_mode(int mode)
{
    /*This controls how the text is placed on the screen.
     * 4 modes
     * 1 - display characters right to left shifting one character at a time
     * 2 - display characters right to left shifting displayed charters over one
     *       space to make room for next character.
     * 3 - display character left to right shifting one character at a time
     * 4 - display characters left to right shifting displayed charters over one
     *       space to make room for next character.
     */

    int instruct = 6;

    if (mode == 1)
    {
        instruct = 4;
    }
    else if (mode == 2)
    {
        instruct = 5;
    }
     else if (mode == 4)
    {
        instruct = 7;
    }

    commd(instruct);
}

void scroll_display(int direction)
{
    /*Scrolls the entire display one character to left or right
     * Both lines scroll the same you cannot scroll one line with this function
     *dirction 1 equal right
     * diretion 0 equal left
     */

     if (direction)
    {
        commd(28);
    }
    else
    {
        commd(24);

    }
}



void set_cursor(int style)
{
    /*Set the diplay mode for the Cursor
     * style 1 = visalbe underline Cursor
     * style 2 = visiable blinking Block Cursor
     * style 3 = invisable cursor
     */
    int instruct = 12;
    if (style == 1)
    {
        instruct = 14;
    }
    else if (style == 2)
    {
        instruct = 15;
    }
    commd(instruct);
}
//4-bit print interface



void prnt_char(unsigned int character)
{
//maintains setting of upper nibble of port
LCDPORT=(LCDPORT & 0b1111111000011111) |( (character << 1) & 0b0000000111100000) ; // send upper nibble

Delay_MS(5);
//Delay10TCYx(10);
RS_PIN = 1;
E_PIN = 1;
E_PIN = 0;
RS_PIN = 0;
Delay_MS(500);
//Delay10TCYx(20);

//maintains setting of upper nibble of port
LCDPORT=(LCDPORT & 0b1111111000011111) | ((character << 4)& 0b0000000111100000);// send lower nibble

//Delay10TCYx(10);
Delay_MS(500);
RS_PIN = 1;
E_PIN = 1;
E_PIN = 0;
RS_PIN = 0;
Delay_MS(500);
//Delay10TCYx(10);


}

void print_string(char *message)
{
    int i = 0;
    while(message[i] != '\0')
    {
    prnt_char(message[i]);
    i++;
    }
}
//4-bit instruction interface

void commd(unsigned int commd)
{
    /*Send command to LCD on 4 bit bus.
     * Send upper nibble first.  LCD accepts on E pin transition to low
     * Sends lower nibble second after slight delay to give LCD time to process
     * sends the data onto the upper nibble of PORTE
     */

    //maintains setting of upper nibble of port
    LCDPORT=(LCDPORT & 0b1111111000011111) | ((commd << 1) & 0b0000000111100000) ; // send upper nibble
    E_PIN = 1;
    E_PIN = 0;

    //Delay10TCYx(10);
    Delay_MS( 500);
    //maintains setting of upper nibble of port
    LCDPORT=(LCDPORT & 0xf0) | ((commd << 1) & 0b0000000111100000) ;// send lower nibble
    E_PIN = 1;
    E_PIN = 0;
    Delay_MS(500);
    //Delay10TCYx(10);

}

void lcd_go_to(int line, int space)
{
    /*Sets the curser on the display
     * Line 1 is the upper line, 2 the lower line
     * space is the character position, 1-16
     */
    if (line == 2)
    {

       commd(192 + space - 1);
    }
    else
    {

       commd(128 + space - 1);
    }


}