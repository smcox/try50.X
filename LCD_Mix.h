/* 
 * File:   LCD_Mix.h
 * Author: Phil
 *
 * Created on March 14, 2014, 1:49 PM
 */

#ifndef LCD_MIX_H
#define	LCD_MIX_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_MIX_H */



void lcd_init(void);
void prnt_char(unsigned int character);
void commd(unsigned int commd);
void print_string(char *string);
void lcd_go_to(int line, int space);
void set_cursor(int style);
void clear_screen(void);
void step_cursor(int direction);
void scroll_display(int direction);
void entry_mode(int mode);
