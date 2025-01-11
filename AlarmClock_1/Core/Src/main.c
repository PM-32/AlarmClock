/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "4x_7-seg_display.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

// Обработка нажатий кнопки энкодера
uint32_t time_EncPress = 0;
uint8_t f_EncPress = 1;

// Состояние кнопки
// (0 - кнопка не нажата,
//  1 - кнопка нажата)
uint8_t button_cond = 0;

// Флаг нажатия кнопки
uint8_t press_flag = 0;

// Флаг долгого нажатия на кнопку
uint8_t long_press_flag = 0;

// Время нажатия на кнопку
uint32_t last_press = 0;

// Текущие цифры на дисплее
uint8_t number[4] = {0};

// Структура будильника
typedef struct
{
	uint8_t hours;
	uint8_t minutes;

} ALARM;

ALARM alarm;

// Массив для записи/чтения на flash:
// [0] - часы;
// [1] - минуты;
// [2] - флаг установки будильника;
// [3] - CRC32
uint32_t write_alarm[4] = {0};
uint32_t read_alarm[4] = {0};

// Флаг ошибки при работе с Flash
uint8_t f_FlashError = 0;

// Структура часов
typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
} TIME;

TIME time;

// Текущая температура в градусах
int temperature;

// Флаг часы не откалиброваны
uint8_t f_ClockNotCalibrated = 0;

// Стадия калибровки
// (стадия 1 - калибровка текущей даты,
//  стадия 2 - калибровка текущего времени)
uint8_t stage_calibration = 1;

// Структура будильника
typedef struct
{
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t hours;
	uint8_t minutes;

} CALIBRATION_DATA;

CALIBRATION_DATA calibration;


extern volatile uint16_t t_ENCS1COUNTs;
extern volatile uint16_t t_ENCS2COUNTs;
extern volatile uint8_t current_digit;
extern volatile uint8_t current_number;
extern volatile uint8_t f_SetAlarm;
extern volatile uint8_t f_Alarm;
extern volatile uint8_t f_SaveAlarm;
extern volatile uint8_t f_StartWork;
extern volatile uint8_t data;
extern volatile uint8_t tim2_ResetAlarmMode;
extern volatile uint8_t mode;
extern volatile uint8_t counts;
extern volatile uint8_t counts_long;


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//----------------------------< Часы DS3231 >----------------------------
#define DS3231_ADDRESS 0xD0

// Преобразование чисел из десятичной системы в двоичную
uint8_t decToBcd(int val)
{
  return (uint8_t) ((val/10*16) + (val%10));
}


// Преобразование чисел из двоичной системы в десятичную
int bcdToDec(uint8_t val)
{
  return (int) ((val/16*10) + (val%16));
}


// Функция для установки начального времени DS3231
void Set_Time(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow,
			  uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];

	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}


// Функция для установки начального времени DS3231 при калибровке
void Set_Time_ShortVersion(uint8_t min, uint8_t hour,
						   uint8_t dom, uint8_t month)
{
	uint8_t set_time[7];

	set_time[0] = decToBcd(0);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(1);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(1);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}


// Чтение текущего времени с DS3231
// (не используемые данные закомменчены)
void Get_Time(void)
{
	uint8_t get_time[7];

	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);

	time.seconds = bcdToDec(get_time[0]);
	time.minutes = bcdToDec(get_time[1]);
	time.hour = bcdToDec(get_time[2]);
	//time.dayofweek = bcdToDec(get_time[3]);
	time.dayofmonth = bcdToDec(get_time[4]);
	time.month = bcdToDec(get_time[5]);
	//time.year = bcdToDec(get_time[6]);
}


// Чтение текущей температуры с DS3231
float Get_Temp(void)
{
	uint8_t temp[2];

	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}


// Увеличение скорости обновления температуры
void force_temp_conv(void)
{
	uint8_t status=0;
	uint8_t control=0;

	// Чтение status register
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x0F, 1, &status, 1, 100);

	if (!(status&0x04))
	{
		// Чтение control register
		HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x0E, 1, &control, 1, 100);

		// Запись в control register
		HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x0E, 1, (uint8_t *)(control|(0x20)), 1, 100);
	}
}
//----------------------------< Часы DS3231 >----------------------------

//----------------------------< Дисплей >----------------------------

// Отображение текущей температуры на дисплее
void DisplayDegrees(void)
{
	temperature = (int) Get_Temp();

	PrintFigure(1, (uint8_t) temperature / 10);
	PrintFigure(2, (uint8_t) temperature % 10);
	PrintDegrees();
}


// Отображение текущего времени на дисплее
void DisplayTime(void)
{
	PrintFigure(1, time.hour / 10);
	PrintFigure(2, time.hour % 10);
	PrintFigure(3, time.minutes / 10);
	PrintFigure(4, time.minutes % 10);
	PrintPoint(2);
}


// Отображение текущей даты на дисплее
void DisplayDate(void)
{
	PrintFigure(1, time.dayofmonth / 10);
	PrintFigure(2, time.dayofmonth % 10);
	PrintFigure(3, time.month / 10);
	PrintFigure(4, time.month % 10);
	PrintPoint(1);
}
//----------------------------< Дисплей >----------------------------

//----------------------------< Нормальные режимы >----------------------------

// Функция управления пьезопищалкой
void AlarmControl(void)
{
	 if (f_Alarm)
		 GPIOB->BSRR |= 0x4000;
	 else
		 GPIOB->BSRR |= 0x40000000;
}


// Обработка нажатий на сенсорную кнопку
// (переключение режимов работы)
void ButtonPress(void)
{
	uint8_t i = 0;

	// Текущее время и
	// текущее состояние кнопки
	uint32_t ms = HAL_GetTick();
	button_cond = (GPIOC->IDR & 0x4000) >> 14;

	// Если кнопка была нажата и
	// ранее не была нажата
	// и с последнего нажатия
	// прошло 100 мс (защита от дребезга)
	if (button_cond && !press_flag && (ms - last_press) > 100)
	{
		press_flag = 1;
		last_press = ms;
	}

	// Если кнопка зажата более 3 с
	if (button_cond && press_flag && (ms - last_press) > 3000)
	{
		long_press_flag = 1;
		last_press = ms;

		// Действия на долгое нажатие

		// Увеличение счётчика долгих касаний
		counts_long++;

		// Переход в режим калибровки
		// через 3 с после нажатия на кнопку
		if (counts_long == 1)
		{
			// Переход в режим калибровки
			mode = 4;

			// Сброс текущих цифр и разрядов дисплея
			for (i = 0; i < 4; i++)
				number[i] = 0;

			current_digit = 1;
			current_number = 0;

			// Настройка даты
			stage_calibration = 1;
		}

		// Выход из режима калибровки
		else
		if (counts_long == 2)
		{
			// Если введены дата и время
			if (stage_calibration == 2)
			{
				// Установка параметров, если они введены корректно
				if (!(((calibration.month > 12) || (calibration.month < 1)) ||
				   ((calibration.dayofmonth > 31) || (calibration.dayofmonth < 1)) ||
				   ((calibration.hours > 23) || (calibration.hours < 0))	||
				   ((calibration.minutes > 59) || (calibration.minutes < 0))))
				{
					// Установка даты и времени
					Set_Time_ShortVersion(calibration.minutes,
										  calibration.hours,
										  calibration.dayofmonth,
										  calibration.month);

					// Сброс флага - часы не откалиброваны
					f_ClockNotCalibrated = 0;
				}
			}

			// Сброс счетчика
			counts_long = 0;

			/*
				 Переход в расширенный нормальный режим
			 	 (поскольку при калибровке время устанавливается
				 последним параметром, то при переходе в обычный
				 нормальный режим становится трудно понять,
				 что произошёл выход из режима калибровки.
				 В расширенном нормальном режиме индикация
				 постоянно меняется и выход из режима
				 калибровки определить проще)
			*/

			mode = 2;
		}
	}

	// Если кнопка отпущена и
	// была нажата долгое время
	if (!button_cond && press_flag && long_press_flag)
	{
		press_flag = 0;
		long_press_flag = 0;
	}

	// Если кнопка была отпущена и
	// было только короткое нажатие
	if (!button_cond && press_flag && !long_press_flag)
	{
		press_flag = 0;

		// Действия на короткое нажатие

		// Если установлен режим калибровки
		if (mode == 4)
		{
			// Сброс текущих цифр и разрядов дисплея
			for (i = 0; i < 4; i++)
				number[i] = 0;

			current_digit = 1;
			current_number = 0;

			// В режиме калибровки короткое
			// нажатие переключает этапы калибровки
			if (stage_calibration == 1)
				stage_calibration = 2;
			else
				stage_calibration = 1;
		}

		// Если часы откалиброваны и
		// установлен любой режим, кроме калибровки
		if ((!f_ClockNotCalibrated) && (mode != 4))
		{
			counts++;

			switch (counts)
			{
				// Переход в расширенный нормальный режим
				case 1:

					mode = 2;

				break;

				// Переход в режим настройки
				case 2:

					mode = 3;

					// Сброс текущих цифр и разрядов дисплея
					for (i = 0; i < 4; i++)
						number[i] = 0;

					current_digit = 1;
					current_number = 0;

				break;

				// Переход в нормальный режим
				case 3:

					// Смена режима
					mode = 1;

					// Сброс количества нажатий на кнопку
					counts = 0;

					if (current_digit == 4)
					{
						// Будильник в состоянии сброса
						// Кодовое число 8888 используется для сброса будильника
						// Некорректно введённое время также сбрасывает будильник
						if (((alarm.hours == 88) && (alarm.minutes == 88)) ||
							((alarm.hours > 23) || (alarm.hours < 0))	||
							((alarm.minutes > 59) || (alarm.minutes < 0)))
						{
							f_SetAlarm = 0;
						}

						// Будильник установлен
						else
							f_SetAlarm = 1;

						// Установка флага записи данных на flash
						f_SaveAlarm = 1;
					}

				break;

				default:
				break;
			}
		}
	}
}

//----------------------------< Нормальные режимы >----------------------------

//----------------------------< Режим настройки >----------------------------

// Функция для определения поворотов энкодера
// и регулировки текущей цифры
void TurnEncoder(void)
{
	 // Вращение по часовой стрелке
	 if (t_ENCS1COUNTs > 0)
	 {
		t_ENCS1COUNTs = 0;

		// Ограничитель цифр сверху
		if (current_number < 9)
			current_number++;
	 }

	 // Вращение против часовой стрелки
	 if (t_ENCS2COUNTs > 0)
	 {
		t_ENCS2COUNTs = 0;

		// Ограничитель цифр снизу
		if (current_number > 0)
			current_number--;
	 }
}


// Обработка нажатий на кнопку энкодера
// (смена разряда на дисплее в режиме настройки
// и отключение будильника в остальных режимах)
void EncoderButtonPress(void)
{
	 // Нажатие кнопки с антидребезгом
	 if (HAL_GPIO_ReadPin(Enc_Button_GPIO_Port, Enc_Button_Pin) == GPIO_PIN_RESET && f_EncPress)
	 {
		f_EncPress = 0;

		// Режим нормальный или
		// расширенный нормальный
		// (выключение пьезопищалки)
		if (mode < 3)
			f_Alarm = 0;

		// Режим настройки
		// или режим калибровки
		else
		{
			// Смена разряда часов при
			// нажатии на кнопку энкодера
			current_digit++;

			// Разряды меняются от 1 до 4
			if (current_digit == 5)
				current_digit = 1;

			// Сброс текущей цифры
			current_number = 0;
		}

		time_EncPress = HAL_GetTick();
	 }

	 if (!f_EncPress && (HAL_GetTick() - time_EncPress) > 300)
	 {
		 f_EncPress = 1;
	 }
}


// Функция для сборки времени будильника
void BuildTimeAlarmClock(void)
{
	// number[0-1] - Часы
	// number[2-3] - Минуты

	alarm.hours = number[0] * 10 + number[1];
	alarm.minutes = number[2] * 10 + number[3];
}


// Индикация времени будильника
void IndicationAlarmClock(void)
{
	// Включение центральных светодиодов
	PrintPoint(2);

	// Вывод цифр на дисплей
	switch (current_digit)
	{
		case 1:

			number[0] = current_number;
			PrintFigure(current_digit, number[0]);

		break;

		case 2:

			number[1] = current_number;
			PrintFigure(current_digit-1, number[0]);
			PrintFigure(current_digit, number[1]);

		break;

		case 3:

			number[2] = current_number;
			PrintFigure(current_digit-2, number[0]);
			PrintFigure(current_digit-1, number[1]);
			PrintFigure(current_digit, number[2]);

		break;

		case 4:

			number[3] = current_number;
			PrintFigure(current_digit-3, number[0]);
			PrintFigure(current_digit-2, number[1]);
			PrintFigure(current_digit-1, number[2]);
			PrintFigure(current_digit, number[3]);

			// Формирование времени будильника
			BuildTimeAlarmClock();

		break;
	}
}

//----------------------------< Режим настройки >----------------------------

//----------------------------< Запись на Flash >----------------------------

// Подготовка данных для записи на Flash
void PrepareDataFlash(void)
{
	write_alarm[0] = (uint32_t) alarm.hours;
	write_alarm[1] = (uint32_t) alarm.minutes;
}


// Очистка последней страницы
void EraseFlash(void)
{
	// Структура для очистки flash
	static FLASH_EraseInitTypeDef EraseInitStruct;

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; 	// постраничная очистка
	EraseInitStruct.PageAddress = 0x0801FC00; 			// адрес последней страницы №127
	EraseInitStruct.NbPages = 1;                       	// кол-во страниц для стирания

	// Переменная, в которую запишется адрес
	// страницы при неудачном стирании
	uint32_t page_error = 0;

	// Разблокировка flash
	HAL_FLASH_Unlock();

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK)
	{
		// Установка флага ошибки при работе с Flash
		f_FlashError = 1;
	}

	// Блокировка flash
	HAL_FLASH_Lock();
}


// Запись на последнюю страницу
void WriteFlash(void)
{
	uint8_t i = 0;

	// Адрес начала последней страницы №127
	uint32_t address = 0x0801FC00;

	// Подготовка данных для записи
	PrepareDataFlash();

	// Очистка страницы
	EraseFlash();

	// Разблокировка flash
	HAL_FLASH_Unlock();

	// Запись параметров: часы, минуты,
	// флаг установки будильника
	for (i = 0; i < 3; i++)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, write_alarm[i]) != HAL_OK)
		{
			// Установка флага ошибки при работе с Flash
			f_FlashError = 1;
		}

		address += 4;
	}

	// Расчёт CRC32
	write_alarm[3] = HAL_CRC_Calculate(&hcrc, (uint32_t*) 0x0801FC00, 3);

	// Запись CRC32
	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, write_alarm[3]) != HAL_OK)
	{
		// Установка флага ошибки при работе с Flash
		f_FlashError = 1;
	}

	// Блокировка flash
	HAL_FLASH_Lock();
}


// Чтение последней страницы
void ReadFlash(void)
{
	uint8_t i = 0;

	// Рассчитанное значение CRC32
	uint32_t crc = 0;

	// Адрес начала последней страницы №127
	uint32_t address = 0x0801FC00;

	for (i = 0; i < 4; i++)
	{
		read_alarm[i] = *(uint32_t*) address;
		address += 4;
	}

	// Расчёт CRC32
	crc = HAL_CRC_Calculate(&hcrc, (uint32_t*) 0x0801FC00, 3);

	// Если считанное с Flash значение
	// CRC32 и рассчитанное совпадают
	if (read_alarm[3] == crc)
	{
		// Если будильник уже установлен
		if (read_alarm[2] == 1)
		{
			f_SetAlarm = 1;

			// Сохранение данных из flash
			alarm.hours = (uint8_t) read_alarm[0];
			alarm.minutes = (uint8_t) read_alarm[1];
		}

		else
		if (read_alarm[2] == 0)
			f_SetAlarm = 0;
	}
}


// Индикация при ошибках в работе с Flash
// (вывод на дисплей "FLSH")
void IndicationFlashError(void)
{
	// F
	SetDigit(1);
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	// L
	SetDigit(2);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	// S
	SetDigit(3);
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	// H
	SetDigit(4);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);
}

//----------------------------< Запись на Flash >----------------------------

//----------------------------< Режим настройки >----------------------------


//----------------------------< Режим калибровки >----------------------------

// Индикация при необходимости
// калибровки часов (вывод на дисплей "CALI")
void IndicationCalibration(void)
{
	// C
	SetDigit(1);
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	// A
	SetDigit(2);
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	// L
	SetDigit(3);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);

	// I
	SetDigit(4);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	ResetLeds();
	HAL_Delay(1);
}

// Функция для сборки времени при калибровке
void BuildTimeCalibration(void)
{
	// number[0-1] - Часы
	// number[2-3] - Минуты

	calibration.hours = number[0] * 10 + number[1];
	calibration.minutes = number[2] * 10 + number[3];
}


// Индикация времени при калибровке
void IndicationCalibration_Time(void)
{
	// Включение центральных светодиодов
	PrintPoint(2);

	// Вывод цифр на дисплей
	switch (current_digit)
	{
		case 1:

			number[0] = current_number;
			PrintFigure(current_digit, number[0]);

		break;

		case 2:

			number[1] = current_number;
			PrintFigure(current_digit-1, number[0]);
			PrintFigure(current_digit, number[1]);

		break;

		case 3:

			number[2] = current_number;
			PrintFigure(current_digit-2, number[0]);
			PrintFigure(current_digit-1, number[1]);
			PrintFigure(current_digit, number[2]);

		break;

		case 4:

			number[3] = current_number;
			PrintFigure(current_digit-3, number[0]);
			PrintFigure(current_digit-2, number[1]);
			PrintFigure(current_digit-1, number[2]);
			PrintFigure(current_digit, number[3]);

			// Формирование времени при калибровке
			BuildTimeCalibration();

		break;
	}
}


// Функция для сборки даты при калибровке
void BuildDateCalibration(void)
{
	// number[0-1] - День месяца
	// number[2-3] - Месяц

	calibration.dayofmonth = number[0] * 10 + number[1];
	calibration.month = number[2] * 10 + number[3];
}


// Индикация даты при калибровке
void IndicationCalibration_Date(void)
{
	// Включение центрального светодиода
	PrintPoint(1);

	// Вывод цифр на дисплей
	switch (current_digit)
	{
		case 1:

			number[0] = current_number;
			PrintFigure(current_digit, number[0]);

		break;

		case 2:

			number[1] = current_number;
			PrintFigure(current_digit-1, number[0]);
			PrintFigure(current_digit, number[1]);

		break;

		case 3:

			number[2] = current_number;
			PrintFigure(current_digit-2, number[0]);
			PrintFigure(current_digit-1, number[1]);
			PrintFigure(current_digit, number[2]);

		break;

		case 4:

			number[3] = current_number;
			PrintFigure(current_digit-3, number[0]);
			PrintFigure(current_digit-2, number[1]);
			PrintFigure(current_digit-1, number[2]);
			PrintFigure(current_digit, number[3]);

			// Формирование даты при калибровке
			BuildDateCalibration();

		break;
	}
}

//----------------------------< Режим калибровки >----------------------------

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  // При включении на дисплее
  // пробегает змейка (слева направо)
  PrintSnakeMove_Direct();

  // Для поворотов энкодера
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);
  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);

  // Моргание раз в секунду
  // в режиме настройки будильника
  HAL_TIM_Base_Start_IT(&htim2);

  // Чтение данных из flash
  ReadFlash();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (!f_StartWork)
	  {
		  // При включении 2 секунды отображается "HI",
		  // после чего начинается работа устройства
		  PrintHi(1);
	  }

	  else
	  {
		  if (f_FlashError)
		  {
			  // Индикация ошибки при работе с Flash
			  IndicationFlashError();
		  }

		  else
		  {
			  // Обработка нажатий
			  // на сенсорную кнопку
			  ButtonPress();

			  // Любой режим, кроме режима настройки
			  if (mode != 3)
			  {
				  // Чтение текущего времени
				  Get_Time();

				  // Увеличение скорости обновления температуры
				  force_temp_conv();

				  // Проверка необходимости
				  // обязательной калибровки
				  // (при замене батарейки
				  //  часы точно будут не откалиброваны)
				  if ((time.dayofmonth == 1) &&
					  (time.month == 1) &&
					  (time.hour == 0) &&
					  (time.minutes == 0))
				  {
					  // Установка флага часы не откалиброваны
					  // (нужен для блокировки других действий)
					  f_ClockNotCalibrated = 1;
				  }

				  // Если требуется калибровка
				  if (f_ClockNotCalibrated)
				  {
					  // Индикация необходимости
					  // калибровки часов
					  if (mode != 4)
						 IndicationCalibration();
				  }

				  // Если калибровка не требуется
				  else
				  {
					  tim2_ResetAlarmMode = 0;

					  // Если будильник не установлен
					  if (!f_SetAlarm)
					  {
						  // Выключение светодиода
						  GPIOA->BSRR |= 0x80000000;

						  f_Alarm = 0;
					  }

					  // Если будильник установлен
					  else
					  {
						  // Включение светодиода
						  GPIOA->BSRR |= 0x8000;

						  // Проверка будильника
						  if ((time.hour == alarm.hours) &&
							  (time.minutes == alarm.minutes) &&
							  (time.seconds == 0))
						  {
							  // Установка флага включения пьезопищалки
							  f_Alarm = 1;
						  }

						  // Ручное отключение будильника
						  EncoderButtonPress();

						  // Управление пьезопищалкой
						  AlarmControl();
					  }

					  // Если была установка/
					  // сброс будильника
					  if (f_SaveAlarm)
					  {
						  // Если будильник установлен,
						  // то нужно сохранить данные
						  if (f_SetAlarm)
							  write_alarm[2] = 1;
						  else
							  write_alarm[2] = 0;

						  // Запись данных на flash
						  WriteFlash();

						  f_SaveAlarm = 0;
					  }
				  }
			  }

			  // Если часы откалиброваны
			  if (!f_ClockNotCalibrated)
			  {
				  switch (mode)
				  {
				  	 // Нормальный режим
					 case 1:

						 // Отображение текущего времени
						 DisplayTime();

					 break;

					 // Расширенный нормальный режим
					 case 2:

						switch (data)
						{
							// Отображение текущей даты
							case 1:
									DisplayDate();
							break;

							// Отображение текущего времени
							case 2:
									DisplayTime();
							break;

							// Отображение текущей температуры
							case 3:
									DisplayDegrees();
							break;
						}

					 break;

					 // Режим настройки
					 // (установка будильника)
					 case 3:

						// Изменение текущей цифры
						TurnEncoder();

						// Смена разрядов на дисплее
						EncoderButtonPress();

						// Индикация времени будильника
						IndicationAlarmClock();

					 break;
				  }
			  }

			  // Режим калибровки
			  // (установка текущей
			  // даты и времени)
			  if (mode == 4)
			  {
				  // Изменение текущей цифры
				  TurnEncoder();

				 // Смена разрядов на дисплее
				 EncoderButtonPress();

				 if (stage_calibration == 1)
				 {
					 // Индикация даты при калибровке
					 IndicationCalibration_Date();
				 }

				 else
				 if (stage_calibration == 2)
				 {
					 // Индикация времени при калибровке
					 IndicationCalibration_Time();
				 }
			  }
		  }
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 35999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, B_Pin|Dig4_Pin|Dig3_Pin|G_Pin
                          |Dig2_Pin|C_Pin|F_Pin|DP_Pin
                          |LED_Red_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, A_Pin|D_Pin|Dig1_Pin|E_Pin
                          |Buzzer_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Button_Pin */
  GPIO_InitStruct.Pin = Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : B_Pin Dig4_Pin Dig3_Pin G_Pin
                           Dig2_Pin C_Pin F_Pin DP_Pin
                           LED_Red_Pin */
  GPIO_InitStruct.Pin = B_Pin|Dig4_Pin|Dig3_Pin|G_Pin
                          |Dig2_Pin|C_Pin|F_Pin|DP_Pin
                          |LED_Red_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : A_Pin D_Pin Dig1_Pin E_Pin
                           Buzzer_Pin */
  GPIO_InitStruct.Pin = A_Pin|D_Pin|Dig1_Pin|E_Pin
                          |Buzzer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Enc_Button_Pin */
  GPIO_InitStruct.Pin = Enc_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Enc_Button_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
