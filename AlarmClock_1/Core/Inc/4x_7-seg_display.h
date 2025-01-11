/*
 * 4x_7-seg_display.h
 *
 *  Created on: Oct 8, 2024
 *      Author: Maxim Prokopev
 */
#include "main.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "stdio.h"

#ifndef INC_4X_7_SEG_DISPLAY_H_
#define INC_4X_7_SEG_DISPLAY_H_

void SetLeds(uint8_t number);
void SetLedMinus(void);
void ResetLeds(void);
void SetDigit(uint8_t num_digit);
void PrintValue(int a);
void PrintPoint(uint8_t digit);
void PrintFigure(uint8_t digit, uint8_t figure);
void PrintFigureInt(uint8_t digit, int figure);
void PrintNumber(uint16_t number);
void PrintValueFloat(float value, uint8_t flag_optimization);
void PrintHi(uint8_t led_clock);
void PrintSnakeMove_Direct(void);
void PrintSnakeMove_Indirect(void);
void PrintDegrees(void);

#endif /* INC_4X_7_SEG_DISPLAY_H_ */
