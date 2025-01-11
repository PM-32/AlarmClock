/*
 * 4x_7-seg_display.c
 *
 *  Created on: Oct 8, 2024
 *      Author: Maxim Prokopev
 */

#include "4x_7-seg_display.h"


// Сбрасывает все светодиоды для отрисовки одной цифры
void ResetLeds(void)
{
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
}


// Зажигает нужные светодиоды для отрисовки одной цифры
void SetLeds(uint8_t number)
{
	switch (number)
	{
		case 0:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);

		break;


		case 1:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
		    HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
		    HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
		    HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
		    HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);

		break;


		case 2:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

		break;


		case 3:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

		break;


		case 4:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

		break;


		case 5:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

		break;


		case 6:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

		break;


		case 7:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);

		break;


		case 8:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

		break;


		case 9:

			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

		break;


		default:
		break;
	}
}


// Зажигает светодиод для отрисовки знака минуса
void SetLedMinus(void)
{
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
}


// Выбор разряда на панели для записи цифры
void SetDigit(uint8_t num_digit)
{
	switch (num_digit)
	{
		case 1:

			HAL_GPIO_WritePin(Dig1_GPIO_Port, Dig1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Dig2_GPIO_Port, Dig2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig3_GPIO_Port, Dig3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig4_GPIO_Port, Dig4_Pin, GPIO_PIN_SET);

		break;


		case 2:

			HAL_GPIO_WritePin(Dig1_GPIO_Port, Dig1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig2_GPIO_Port, Dig2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Dig3_GPIO_Port, Dig3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig4_GPIO_Port, Dig4_Pin, GPIO_PIN_SET);

		break;


		case 3:

			HAL_GPIO_WritePin(Dig1_GPIO_Port, Dig1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig2_GPIO_Port, Dig2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig3_GPIO_Port, Dig3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Dig4_GPIO_Port, Dig4_Pin, GPIO_PIN_SET);

		break;


		case 4:

			HAL_GPIO_WritePin(Dig1_GPIO_Port, Dig1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig2_GPIO_Port, Dig2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig3_GPIO_Port, Dig3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Dig4_GPIO_Port, Dig4_Pin, GPIO_PIN_RESET);

		break;


		default:
		break;
	}
}


// Вывод цифры в указанном разряде
void PrintFigure(uint8_t digit, uint8_t figure)
{
	SetDigit(digit);
	SetLeds(figure);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);
}


// Вывод цифры в указанном разряде (изменен тип figure)
void PrintFigureInt(uint8_t digit, int figure)
{
	SetDigit(digit);
	SetLeds(figure);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);
}


// Вывод знака минус
void PrintMinus(uint8_t digit)
{
	SetDigit(digit);
	SetLedMinus();
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);
}


// Вывод любого целочисленного числа
void PrintValue(int value)
{
	char string[4] = "";
	char* ptrMinus = 0;
	char pos_minus = 0;
	uint8_t length = 0;

	// Преобразование числа в строку
	itoa(value, string, 10);

	// Указатель на позиция минуса в строке
	ptrMinus = strchr(string,'-');

	// Количество символов в строке
	length = strlen(string);

	// Если есть минус
	if (ptrMinus != NULL)
	{
		// Позиция минуса в строке
		pos_minus = ptrMinus - string + 1;

		// Избавление от минуса для
		// удобства при поиске цифр числа
		// (в данном случае альтернатива модулю,
		// так как уже известно, что число отрицательное)
		value *= -1;

		// Защита от неправильного ввода
		// (минус может быть только на позиции 1 в строке)
		if (pos_minus == 1)
		{
			// Зная количество символов в строке
			// и позицию минуса, выводим минус и
			// затем само число по модулю
			switch (length)
			{
				case 2:
						PrintMinus(3);
						PrintFigure(4, value);
				break;

				case 3:
						PrintMinus(2);
						PrintFigure(3, value / 10);
						PrintFigure(4, value % 10);
				break;

				case 4:
						PrintMinus(1);
						PrintFigure(2, value / 100);
						PrintFigure(3, (value % 100) / 10);
						PrintFigure(4, value % 10);
				break;

				default:
				break;
			}
		}
	}

	else
	{
		switch(length)
		{
			case 1:
					PrintFigure(4, value % 10);
			break;

			case 2:
					PrintFigure(3, (value % 100) / 10);
					PrintFigure(4, value % 10);
			break;

			case 3:
					PrintFigure(2, (value % 1000) / 100);
					PrintFigure(3, (value % 100) / 10);
					PrintFigure(4, value % 10);
			break;

			case 4:
					PrintFigure(1, value / 1000);
					PrintFigure(2, (value % 1000) / 100);
					PrintFigure(3, (value % 100) / 10);
					PrintFigure(4, value % 10);
			break;

			default:
			break;
		}
	}
}


// Отрисовка точки
void PrintPoint(uint8_t digit)
{
	SetDigit(digit);
	HAL_GPIO_WritePin(DP_GPIO_Port, DP_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(DP_GPIO_Port, DP_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
}


// Вывод пробегающей змейки слева направо
void PrintSnakeMove_Direct(void)
{
	uint8_t i = 1;

	for (i = 1; i < 5; i++)
	{
		SetDigit(i);

		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);
	}
}


// Вывод пробегающей змейки справа налево
void PrintSnakeMove_Indirect(void)
{
	uint8_t i = 4;

	for (i = 4; i > 0; i--)
	{
		SetDigit(i);

		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);

		HAL_Delay(150);
		ResetLeds();
		HAL_Delay(1);
	}
}


// Вывод "HI" на дисплее
// Дополнительно: аргумент == 1 для дисплеев со светодиодами
// часов в центре - выводит смайлик
void PrintHi(uint8_t led_clock)
{
	SetDigit(1);

	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);

	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	SetDigit(2);

	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);

	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	if (led_clock == 1)
	{
		SetDigit(3);

		HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);

		HAL_Delay(1);
		ResetLeds();
		HAL_Delay(1);

		PrintPoint(2);
	}
}


// Вывод на дисплей градусов по Цельсию (символы)
void PrintDegrees(void)
{
	SetDigit(3);
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	SetDigit(4);
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);
}


/*
// Функция для перевода числа с плавающей точкой в массив символов
static char * _float_to_char(float x, char *p, int mode)
{
    char *s = p + 6; // go to end of buffer

    // Доп. параметр для отрисовки некоторых случаев
    if (mode == 1)
    	s = p + 7;

    uint16_t decimals;  // variable to store the decimals
    int units;  // variable to store the units (part to left of decimal place)
    if (x < 0) { // take care of negative numbers
        decimals = (int)(x * -100) % 100; // make 1000 for 3 decimals etc.
        units = (int)(-1 * x);
    } else { // positive numbers
        decimals = (int)(x * 100) % 100;
        units = (int)x;
    }

    *--s = (decimals % 10) + '0';
    decimals /= 10; // repeat for as many decimal places as you need
    *--s = (decimals % 10) + '0';
    *--s = '.';

    while (units > 0) {
        *--s = (units % 10) + '0';
        units /= 10;
    }
    if (x < 0) *--s = '-'; // unary minus sign for negative numbers
    return s;
}
*/


// Отрисовка числа с плавающей точкой
/*
	В основном работает, но некоторые случаи отлажены не до конца.
	flag_optimization - отбрасывает лишние нули после точки
	(например, число 12.0 при включении флага отобразится как 12)

	Алгоритм работы функции:
	1. Преобразование float числа в массив char
	2. Подсчет нулей перед числом
	   (которые непонятно почему вылазят при преобразовании)
	   и проверка на наличие минуса
	3. Зная количество нулей, положение точки и наличие знака минуса,
	   определяется, как запишется число.
 */
/*
void PrintValueFloat(float value, uint8_t flag_optimization)
{
	char string[5] = "";
	char string4[6] = "";
	uint8_t zeros = 0;
	uint8_t num1 = 0;
	uint8_t num2 = 0;
	uint8_t num3 = 0;
	uint8_t num4 = 0;
	uint8_t flag_point = 0;
	uint8_t flag_minus = 0;
	uint8_t pos_point = 0;


	_float_to_char(value, string, 0);

	for (int i = 0; i < 5; i++)
	{
		if (string[i] == '\0')
			zeros++;

		else
		if (string[i] == '-')
		{
			flag_minus = 1;
		}

		else
		if (string[i] == '.')
		{
			pos_point = i;
			flag_point = 1;
		}
	}


	switch (zeros)
	{
		case 3:

			// 1 цифра со знаком минус
			if (flag_minus)
			{
				char sym1 = string[4];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				PrintMinus(3);
				PrintFigure1(4, num1);
			}

			// 2 цифры без минуса и без точки
			else
			{
				char sym1 = string[3];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				char sym2 = string[4];
				char str3[2] = {sym2 , '\0'};
				char str4[5] = "";
				strcpy(str4,str3);
				num2 = atoi(str4);

				PrintFigure1(3, num1);
				PrintFigure1(4, num2);
			}

		break;


		case 2:

			// 2 цифры с минусом
			if (flag_minus)
			{
				char sym1 = string[3];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				char sym2 = string[4];
				char str3[2] = {sym2 , '\0'};
				char str4[5] = "";
				strcpy(str4,str3);
				num2 = atoi(str4);

				PrintMinus(2);
				PrintFigure1(3, num1);
				PrintFigure1(4, num2);
			}

			// 2 цифры с точкой между ними
			else
			if (pos_point == 3)
			{
				if (flag_optimization)
				{
					if (string[4] == '0')
					{
						char sym1 = string[2];
						char str1[2] = {sym1 , '\0'};
						char str2[5] = "";
						strcpy(str2,str1);
						num1 = atoi(str2);

						PrintFigure1(4, num1);
					}
				}

				else
				{
					char sym1 = string[2];
					char str1[2] = {sym1 , '\0'};
					char str2[5] = "";
					strcpy(str2,str1);
					num1 = atoi(str2);

					char sym2 = string[4];
					char str3[2] = {sym2 , '\0'};
					char str4[5] = "";
					strcpy(str4,str3);
					num2 = atoi(str4);

					PrintFigure1(3, num1);
					PrintPoint(3);
					PrintFigure1(4, num2);
				}
			}

			// 3 цифры без точки и минуса
			else
			if ((!flag_point) && (!flag_minus))
			{
				char sym1 = string[2];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				char sym2 = string[3];
				char str3[2] = {sym2 , '\0'};
				char str4[5] = "";
				strcpy(str4,str3);
				num2 = atoi(str4);

				char sym3 = string[4];
				char str5[2] = {sym3 , '\0'};
				char str6[5] = "";
				strcpy(str6,str5);
				num3 = atoi(str6);

				PrintFigure1(2, num1);
				PrintFigure1(3, num2);
				PrintFigure1(4, num3);
			}

		break;


		case 1:
				// 2 цифры с минусом и точкой между ними
				if (flag_minus && flag_point)
				{
					if (pos_point == 3)
					{
						char sym1 = string[2];
						char str1[2] = {sym1 , '\0'};
						char str2[5] = "";
						strcpy(str2,str1);
						num1 = atoi(str2);

						char sym2 = string[4];
						char str3[2] = {sym2 , '\0'};
						char str4[5] = "";
						strcpy(str4,str3);
						num2 = atoi(str4);

						if (flag_optimization)
						{
							PrintMinus(3);
							PrintFigure1(4, num1);
						}

						else
						{
							PrintMinus(2);
							PrintFigure1(3, num1);
							PrintPoint(3);
							PrintFigure1(4, num2);
						}
					}
				}

				// 3 цифры с точкой
				else
				if (flag_point)
				{
					if (flag_optimization)
					{
						if (pos_point == 2)
						{
							if ((string[3] == '0') && (string[4] == '0'))
							{
								char sym1 = string[1];
								char str1[2] = {sym1 , '\0'};
								char str2[5] = "";
								strcpy(str2,str1);
								num1 = atoi(str2);

								PrintFigure1(4, num1);
							}
						}

						else
						if (pos_point == 3)
						{
							if (string[4] == '0')
							{
								char sym1 = string[1];
								char str1[2] = {sym1 , '\0'};
								char str2[5] = "";
								strcpy(str2,str1);
								num1 = atoi(str2);

								char sym2 = string[2];
								char str3[2] = {sym2 , '\0'};
								char str4[5] = "";
								strcpy(str4,str3);
								num2 = atoi(str4);

								PrintFigure1(3, num1);
								PrintFigure1(4, num2);
							}
						}
					}

					else
					{
						char sym1 = string[1];
						char str1[2] = {sym1 , '\0'};
						char str2[5] = "";
						strcpy(str2,str1);
						num1 = atoi(str2);

						char sym2;
						char str3[2];
						char str4[5] = "";

						switch (pos_point)
						{
							case 2:

								sym2 = string[3];
								str3[0] = sym2;
								str3[1] = '\0';
								//str3[2] = {sym2 , '\0'};
								strcpy(str4,str3);
								num2 = atoi(str4);

							break;


							case 3:

								sym2 = string[2];
								str3[0] = sym2;
								str3[1] = '\0';
								//str3[2] = {sym2 , '\0'};
								strcpy(str4,str3);
								num2 = atoi(str4);

							break;
						}

						char sym3 = string[4];
						char str5[2] = {sym3 , '\0'};
						char str6[5] = "";
						strcpy(str6,str5);
						num3 = atoi(str6);

						PrintFigure1(2, num1);
						PrintPoint(pos_point);
						PrintFigure1(3, num2);
						PrintFigure1(4, num3);
					}

				}

				// 4 цифры без точки и минуса
				else
				if ((!flag_point) && (!flag_minus))
				{
					char sym1 = string[1];
					char str1[2] = {sym1 , '\0'};
					char str2[5] = "";
					strcpy(str2,str1);
					num1 = atoi(str2);

					char sym2 = string[2];
					char str3[2] = {sym2 , '\0'};
					char str4[5] = "";
					strcpy(str4,str3);
					num2 = atoi(str4);

					char sym3 = string[3];
					char str5[2] = {sym3 , '\0'};
					char str6[5] = "";
					strcpy(str6,str5);
					num3 = atoi(str6);

					char sym4 = string[4];
					char str7[2] = {sym4 , '\0'};
					char str8[5] = "";
					strcpy(str8,str7);
					num4 = atoi(str8);

					PrintFigure1(1, num1);
					PrintFigure1(2, num2);
					PrintFigure1(3, num3);
					PrintFigure1(4, num4);
				}
		break;

		case 0:

			if (value > 999.9)
			{
				_float_to_char(value, string4, 1);

				char sym1 = string4[0];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				char sym2 = string4[1];
				char str3[2] = {sym2 , '\0'};
				char str4[5] = "";
				strcpy(str4,str3);
				num2 = atoi(str4);

				char sym3 = string4[2];
				char str5[2] = {sym3 , '\0'};
				char str6[5] = "";
				strcpy(str6,str5);
				num3 = atoi(str6);

				char sym4 = string4[3];
				char str7[2] = {sym4 , '\0'};
				char str8[5] = "";
				strcpy(str8,str7);
				num4 = atoi(str8);

				PrintFigure1(1, num1);
				PrintFigure1(2, num2);
				PrintFigure1(3, num3);
				PrintFigure1(4, num4);
			}

			else
			if (value < -99.9)
			{
				_float_to_char(value, string4, 1);

				char sym1 = string4[1];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				char sym2 = string4[2];
				char str3[2] = {sym2 , '\0'};
				char str4[5] = "";
				strcpy(str4,str3);
				num2 = atoi(str4);

				char sym3 = string4[3];
				char str5[2] = {sym3 , '\0'};
				char str6[5] = "";
				strcpy(str6,str5);
				num3 = atoi(str6);

				PrintMinus(1);
				PrintFigure1(2, num1);
				PrintFigure1(3, num2);
				PrintFigure1(4, num3);
			}

			// 3 цифры с минусом и точкой
			else
			if (flag_minus)
			{
				char sym1 = string[1];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				char sym2;
				char str3[2];
				char str4[5] = "";

				switch (pos_point)
				{
					case 2:

						sym2 = string[3];
						str3[0] = sym2;
						str3[1] = '\0';
						//str3[2] = {sym2 , '\0'};
						strcpy(str4,str3);
						num2 = atoi(str4);

					break;

					case 3:

						sym2 = string[2];
						str3[0] = sym2;
						str3[1] = '\0';
						//str3[2] = {sym2 , '\0'};
						strcpy(str4,str3);
						num2 = atoi(str4);

					break;
				}

				char sym3 = string[4];
				char str5[2] = {sym3 , '\0'};
				char str6[5] = "";
				strcpy(str6,str5);
				num3 = atoi(str6);

				if (flag_optimization)
				{
					PrintMinus(2);
					PrintFigure1(3, num1);
					PrintFigure1(4, num2);
				}

				else
				{
					PrintMinus(1);
					PrintFigure1(2, num1);
					PrintPoint(pos_point);
					PrintFigure1(3, num2);
					PrintFigure1(4, num3);
				}
			}

			// 4 цифры с точкой
			else
			{
				char sym1 = string[0];
				char str1[2] = {sym1 , '\0'};
				char str2[5] = "";
				strcpy(str2,str1);
				num1 = atoi(str2);

				char sym2;
				char str3[2];
				char str4[5] = "";

				char sym3;
				char str5[2];
				char str6[5] = "";

				switch (pos_point)
				{
					case 1:

						if (flag_optimization)
						{
							if ((string[2] == '0') &&
								(string[3] == '0') &&
								(string[4] == '0'))
							{
								PrintFigure1(4, num1);
							}
						}

						else
						{
							sym2 = string[2];
							str3[0] = sym2;
							str3[1] = '\0';
							//str3[2] = {sym2 , '\0'};
							strcpy(str4,str3);
							num2 = atoi(str4);

							sym3 = string[3];
							str5[0] = sym3;
							str5[1] = '\0';
							//str5[2] = {sym3 , '\0'};
							strcpy(str6,str5);
							num3 = atoi(str6);
						}


					break;

					case 2:

						if (flag_optimization)
						{
							if ((string[3] == '0') &&
								(string[4] == '0'))
							{
								sym2 = string[1];
								str3[0] = sym2;
								str3[1] = '\0';
								//str3[2] = {sym2 , '\0'};
								strcpy(str4,str3);
								num2 = atoi(str4);

								PrintFigure1(3, num1);
								PrintFigure1(4, num2);
							}
						}

						else
						{
							sym2 = string[1];
							str3[0] = sym2;
							str3[1] = '\0';
							//str3[2] = {sym2 , '\0'};
							strcpy(str4,str3);
							num2 = atoi(str4);

							sym3 = string[3];
							str5[0] = sym3;
							str5[1] = '\0';
							//str5[2] = {sym3 , '\0'};
							strcpy(str6,str5);
							num3 = atoi(str6);
						}

					break;

					case 3:

						if (flag_optimization)
						{
							if (string[4] == '0')
							{
								sym2 = string[1];
								str3[0] = sym2;
								str3[1] = '\0';
								//str3[2] = {sym2 , '\0'};
								strcpy(str4,str3);
								num2 = atoi(str4);

								sym3 = string[2];
								str5[0] = sym3;
								str5[1] = '\0';
								//str5[2] = {sym3 , '\0'};
								strcpy(str6,str5);
								num3 = atoi(str6);

								PrintFigure1(2, num1);
								PrintFigure1(3, num2);
								PrintFigure1(4, num3);
							}
						}

						sym2 = string[1];
						str3[0] = sym2;
						str3[1] = '\0';
						//str3[2] = {sym2 , '\0'};
						strcpy(str4,str3);
						num2 = atoi(str4);

						sym3 = string[2];
						str5[0] = sym3;
						str5[1] = '\0';
						//str5[2] = {sym3 , '\0'};
						strcpy(str6,str5);
						num3 = atoi(str6);

					break;
				}

				if (!flag_optimization)
				{
					char sym4 = string[4];
					char str7[2] = {sym4 , '\0'};
					char str8[5] = "";
					strcpy(str8,str7);
					num4 = atoi(str8);

					PrintFigure1(1, num1);
					PrintPoint(pos_point);
					PrintFigure1(2, num2);
					PrintFigure1(3, num3);
					PrintFigure1(4, num4);
				}
			}

		break;
	}
}
*/
