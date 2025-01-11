/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

// Переменные для определения поворотов энкодера
volatile uint16_t t_ENCS1COUNTs = 0;
volatile uint16_t t_ENCS2COUNTs = 0;
volatile uint8_t t_ENCS1State = 0;
volatile uint8_t t_ENCS2State = 0;
volatile uint8_t t_LastFALLING_ENCChannel = 0;

// Текущий режим работы
// (начальный режим: нормальный)
volatile uint8_t mode = 1;

// Текущий разряд и цифра на дисплее
volatile uint8_t current_digit = 1;
volatile uint8_t current_number = 0;

// Флаг установки будильника
// (0 - будильник не установлен,
//  1 - будильник установлен)
volatile uint8_t f_SetAlarm = 0;

// Текущее количество коротких нажатий на кнопку
volatile uint8_t counts = 0;

// Текущее количество долгих нажатий на кнопку
volatile uint8_t counts_long = 0;

// Отсчёты таймера 2, применяемые для:
// 1) смены данных в расширенном нормальном режиме;
// 2) автоматической смены режима с настройки на нормальный;
// 3) начала работы устройства;
// 4) автоматического отключения будильника;
// 5) автоматической смены режима с калибровки на нормальный
volatile uint8_t tim2_ChangeData = 0;
volatile uint8_t tim2_ResetAlarmMode = 0;
volatile uint8_t tim2_Hi = 0;
volatile uint16_t tim2_AlarmCounter = 0;
volatile uint16_t tim2_ResetCalibrationMode = 0;

// Флаг включения пьезопищалки
volatile uint8_t f_Alarm = 0;

// Флаг начала работы устройства
// после приветствующей заставки
volatile uint8_t f_StartWork = 0;

// Текущие данные для вывода на дисплей
// в расширенном нормальном режиме
volatile uint8_t data = 1;

// Флаг сохранения данных на flash
volatile uint8_t f_SaveAlarm = 0;

// Структура для будильника
typedef struct
{
	uint8_t hours;
	uint8_t minutes;

} ALARM;

extern ALARM alarm;
extern uint8_t number[4];


/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 break interrupt.
  */
void TIM1_BRK_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_IRQn 0 */

  /* USER CODE END TIM1_BRK_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_BRK_IRQn 1 */

  /* USER CODE END TIM1_BRK_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */

  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */

  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles TIM1 trigger and commutation interrupts.
  */
void TIM1_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 0 */

  /* USER CODE END TIM1_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/* USER CODE BEGIN 1 */


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	// Таймер вращения энкодера
	if(htim->Instance == TIM1)
	{
		// Падение
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	    {
	    	t_LastFALLING_ENCChannel = 1;
			t_ENCS1State = 0;
	    }

		// Подъём
	    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	    {
	    	t_ENCS1State = 1;

	    	if ((t_LastFALLING_ENCChannel == 2) && (t_ENCS2State == 0))
	    	{
	    		t_ENCS1COUNTs++;
	    	}
	    }

	    // Падение
	    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	    {
	    	t_LastFALLING_ENCChannel = 2;
	    	t_ENCS2State = 0;
	    }

	    // Подъём
	    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
	    {
	    	t_ENCS2State = 1;

	    	if ((t_LastFALLING_ENCChannel == 1) && (t_ENCS1State == 0))
	    	{
	    		t_ENCS2COUNTs++;
	    	}
	    }
	}
}


// Прерывание по переполнению таймера 2
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		// Если устройство
		// ещё не начало работу
		if (!f_StartWork)
		{
			tim2_Hi++;

			// При включении 2 секунды отображается "HI",
			// после чего начинается работа устройства
			if (tim2_Hi == 3)
			{
				// Сброс отсчётов
				tim2_Hi = 0;

				// Флаг начала работы
				// (этот флаг не должен сбрасываться)
				f_StartWork = 1;
			}
		}


		// Если будильник включён,
		// то начинается отсчёт
		if (f_Alarm)
		{
			tim2_AlarmCounter++;

			// Автоматическое отключение
			// будильника спустя 5 минут (60*5 с)
			if (tim2_AlarmCounter == 300)
			{
				f_Alarm = 0;
				tim2_AlarmCounter = 0;
			}
		}

		else
			tim2_AlarmCounter = 0;


		switch (mode)
		{
			// Расширенный нормальный режим
			case 2:

				tim2_ChangeData++;

				// Смена отображаемых на дисплее данных через каждые 10 секунд.
				// Возможные значения data: 1 - дата, 2 - время, 3 - температура
				if (tim2_ChangeData == 10)
				{
					data++;

					// Переход с температуры на дату
					if (data == 4)
						data = 1;

					// Сброс отсчётов
					tim2_ChangeData = 0;
				}

			break;


			// Режим настройки
			case 3:

				// Моргание светодиодом через секунду
				if (GPIOA->ODR & 0x8000)
					GPIOA->BSRR |= 0x80000000;
				else
					GPIOA->BSRR |= 0x8000;

				tim2_ResetAlarmMode++;

				// Автоматический выход из режима настройки,
				// если будильник не был установлен за 2 минуты (60*2 с)
				if (tim2_ResetAlarmMode == 120)
				{
					// Смена режима на
					// нормальный режим
					mode = 1;

					// Сброс количества
					// нажатий на кнопку
					counts = 0;

					// Сброс отсчётов
					tim2_ResetAlarmMode = 0;

					// Будильник не установлен
					f_SetAlarm = 0;
				}

			break;


			// Режим калибровки
			case 4:

				tim2_ResetCalibrationMode++;

				// Автоматический выход из режима калибровки,
				// если параметры не были установлены за 4 минуты (60*4 с)
				if (tim2_ResetCalibrationMode == 240)
				{
					// Смена режима на
					// нормальный режим
					mode = 1;

					// Сброс количества
					// нажатий на кнопку
					counts = 0;
					counts_long = 0;

					// Сброс отсчётов
					tim2_ResetCalibrationMode = 0;
				}

			break;

			default:
			break;
		}
	}
}


/* USER CODE END 1 */
