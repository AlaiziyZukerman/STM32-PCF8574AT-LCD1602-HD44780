/*
 * lcd_i2c_pcf8574.h
 *
 *  Created on: May 18, 2019
 *      Author: Xusniyor
 */

#ifndef LCD_I2C_PCF8574_H_
#define LCD_I2C_PCF8574_H_

#include "main.h"

#define LCD_LINES           2     /* number of visible lines of the display */
#define LCD_DISP_LENGTH     16    /* visibles characters per line of the display */
#define ADRESS         (0x3F<<1)

#define LCD_PIN_RS     ((uint8_t)(1<<0))
#define LCD_PIN_EN     ((uint8_t)(1<<2))
#define LCD_PIN_LIGHT  ((uint8_t)(1<<3))

#define LCD_LINE_LENGTH  ((uint8_t)0x40)     /* internal line length of the display   */
#define LCD_START_LINE1  ((uint8_t)0x00)     /* DDRAM address of first char of line 1 */
#define LCD_START_LINE2  ((uint8_t)0x40)     /* DDRAM address of first char of line 2 */
#define LCD_START_LINE3  ((uint8_t)0x14)     /* DDRAM address of first char of line 3 */
#define LCD_START_LINE4  ((uint8_t)0x54)     /* DDRAM address of first char of line 4 */

// instruction register bit positions, see HD44780U data sheet
#define LCD_DELAY_MS          5
#define LCD_WRAP_LINES        0     /* 0: no wrap, 1: wrap at end of visibile line */
#define LCD_CLR               0      /* DB0: clear display                  */
#define LCD_HOME              1      /* DB1: return to home position        */
#define LCD_ENTRY_MODE        2      /* DB2: set entry mode                 */
#define LCD_ENTRY_INC         1      /*   DB1: 1=increment, 0=decrement     */
#define LCD_ENTRY_SHIFT       0      /*   DB2: 1=display shift on           */
#define LCD_ON                3      /* DB3: turn lcd/cursor on             */
#define LCD_ON_DISPLAY        2      /*   DB2: turn display on              */
#define LCD_ON_CURSOR         1      /*   DB1: turn cursor on               */
#define LCD_ON_BLINK          0      /*     DB0: blinking cursor ?          */
#define LCD_MOVE              4      /* DB4: move cursor/display            */
#define LCD_MOVE_DISP         3      /*   DB3: move display (0-> cursor) ?  */
#define LCD_MOVE_RIGHT        2      /*   DB2: move right (0-> left) ?      */
#define LCD_FUNCTION          5      /* DB5: function set                   */
#define LCD_FUNCTION_8BIT     4      /*   DB4: set 8BIT mode (0->4BIT mode) */
#define LCD_FUNCTION_2LINES   3      /*   DB3: two lines (0->one line)      */
#define LCD_FUNCTION_10DOTS   2      /*   DB2: 5x10 font (0->5x7 font)      */
#define LCD_CGRAM             6      /* DB6: set CG RAM address             */
#define LCD_DDRAM             7      /* DB7: set DD RAM address             */
#define LCD_BUSY              7      /* DB7: LCD is busy                    */

// set entry mode: display shift on/off, dec/inc cursor move direction
#define LCD_ENTRY_DEC            ((uint8_t)0x04)   /* display shift off, dec cursor move dir */
#define LCD_ENTRY_DEC_SHIFT      ((uint8_t)0x05)   /* display shift on,  dec cursor move dir */
#define LCD_ENTRY_INC_           ((uint8_t)0x06)   /* display shift off, inc cursor move dir */
#define LCD_ENTRY_INC_SHIFT      ((uint8_t)0x07)   /* display shift on,  inc cursor move dir */

// display on/off, cursor on/off, blinking char at cursor position
#define LCD_DISP_OFF             ((uint8_t)0x08)   /* display off                            */
#define LCD_DISP_ON              ((uint8_t)0x0C)   /* display on, cursor off                 */
#define LCD_DISP_ON_BLINK        ((uint8_t)0x0D)   /* display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR       ((uint8_t)0x0E)   /* display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK ((uint8_t)0x0F)   /* display on, cursor on, blink char      */

// move cursor/shift display
#define LCD_MOVE_CURSOR_LEFT     ((uint8_t)0x10)   /* move cursor left  (decrement)          */
#define LCD_MOVE_CURSOR_RIGHT    ((uint8_t)0x14)   /* move cursor right (increment)          */
#define LCD_MOVE_DISP_LEFT       ((uint8_t)0x18)   /* shift display left                     */
#define LCD_MOVE_DISP_RIGHT      ((uint8_t)0x1C)   /* shift display right                    */

// function set: set interface data length and number of display lines
#define LCD_FUNCTION_4BIT_1LINE  ((uint8_t)0x20)   /* 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES ((uint8_t)0x28)   /* 4-bit interface, dual line,   5x7 dots */
#define LCD_FUNCTION_8BIT_1LINE  ((uint8_t)0x30)   /* 8-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_8BIT_2LINES ((uint8_t)0x38)   /* 8-bit interface, dual line,   5x7 dots */

extern void lcd_Init(void);
extern void lcd_Clearscreen(void);
extern void lcd_home(void);
extern void lcd_SetCursor(uint8_t x, uint8_t y);
extern void lcd_command(uint8_t cmd);
extern void lcd_data(uint8_t data);
extern void lcd_SendString(char *str);
extern void lcd_ClearLine(uint8_t line);

#endif /* LCD_I2C_PCF8574_H_ */
