/*
 * lcd_i2c_pcf8574.c
 *
 *  Created on: May 18, 2019
 *      Author: Xusniyor
 */
#include "lcd_i2c_pcf8574.h"

extern I2C_HandleTypeDef hi2c1;

#if LCD_LINES==1
    #define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_1LINE
#else
    #define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_2LINES
#endif

#define LCD_MODE_DEFAULT     ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC) )

HAL_StatusTypeDef lcd_write(uint8_t data, uint8_t rs)
{
	while(((HAL_StatusTypeDef) HAL_I2C_IsDeviceReady(&hi2c1, ADRESS, 1, HAL_MAX_DELAY)) != HAL_OK);
	uint8_t HIGH_BIT = (data & 0xF0);
	uint8_t LOW_BIT = ((data << 4) & 0xF0);
	uint8_t DATA_BUFFER[4];
	DATA_BUFFER[0] = (HIGH_BIT|rs|LCD_PIN_EN|LCD_PIN_LIGHT);
	DATA_BUFFER[1] = (HIGH_BIT|rs|LCD_PIN_LIGHT);
	DATA_BUFFER[2] = (LOW_BIT |rs|LCD_PIN_EN|LCD_PIN_LIGHT);
	DATA_BUFFER[3] = (LOW_BIT |rs|LCD_PIN_LIGHT);
	HAL_Delay(LCD_DELAY_MS);
	return (HAL_StatusTypeDef)HAL_I2C_Master_Transmit(&hi2c1, ADRESS, (uint8_t*)DATA_BUFFER, sizeof(DATA_BUFFER), HAL_MAX_DELAY);
}

void lcd_command(uint8_t cmd)
{
    lcd_write(cmd,0x00); // rs = 0
}

void lcd_data(uint8_t data)
{
    lcd_write(data,LCD_PIN_RS); // rs = 1
}

void lcd_SetCursor(uint8_t x, uint8_t y)
{
#if LCD_LINES==1
	lcd_command((1<<LCD_DDRAM)+LCD_START_LINE1+x);
#endif

#if LCD_LINES==2
    if ( y==0 )
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE1 + x);
    else
        lcd_command((1 << LCD_DDRAM) + LCD_START_LINE2 + x);
#endif

#if LCD_LINES==4
    if ( y==0 )
    	lcd_command((1<<LCD_DDRAM)+LCD_START_LINE1+x);
    else if ( y==1)
    	lcd_command((1<<LCD_DDRAM)+LCD_START_LINE2+x);
    else if ( y==2)
    	lcd_command((1<<LCD_DDRAM)+LCD_START_LINE3+x);
    else /* y==3 */
    	lcd_command((1<<LCD_DDRAM)+LCD_START_LINE4+x);
#endif
}

void lcd_Clearscreen(void)
{
	lcd_command(1<<LCD_CLR);
}

void lcd_home(void)
{
    lcd_command(1<<LCD_HOME);
}

void lcd_SendString(char *str)
{
    while(*str)
    {
    	lcd_data((uint8_t)(*str));
        str++;
    }
}

void lcd_Init(void)
{
	lcd_command(LCD_FUNCTION_DEFAULT);
	lcd_command(1 << LCD_HOME);
	lcd_command(LCD_DISP_ON);
	lcd_command(1 << LCD_CLR);
}

void lcd_ClearLine(uint8_t line)
{
	lcd_SetCursor(0, line);
	for(uint8_t i = 0; i <= LCD_DISP_LENGTH; i++)
	{
		lcd_SendString(" ");
	}
}

