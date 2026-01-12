/*
 * prot.c
 *
 *  Created on: Nov 7, 2025
 *      Author: hutoman
 */
#include "main.h"
#include "prot.h"
#include "string.h"
#include "stdio.h"

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim3;
extern CAN_HandleTypeDef hcan1;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;


char duty_str[10];
uint32_t duty_int;
uint32_t param;
int arr;
char extra;


enum Command getCommand(const char *str)
{
    if (strcmp(str, "set") == 0)
        return cmd_set;
    else if (strcmp(str, "get") == 0)
               return cmd_get;
    else
        return cmd_unknown;
}

enum Argument getArgument(const char *str)
{
    if (strcmp(str, "LED0") == 0)
        return LED0;
    else if (strcmp(str, "LED1") == 0)
            return LED1;
    else if (strcmp(str, "LED2") == 0)
            return LED2;
    else if (strcmp(str, "LED.ALL") == 0)
    		return LED_ALL;
    else if (strcmp(str, "PWM0") == 0)
    		return PWM0;
    else if (strcmp(str, "PWM1") == 0)
    		return PWM1;
    else if (strcmp(str, "PWM2") == 0)
			return PWM2;
    else if (strcmp(str, "PWM3") == 0)
		  	return PWM3;
    else if (strcmp(str, "PWM0.DUTY") == 0)
			return PWM0_DUTY;
    else if (strcmp(str, "PWM1.DUTY") == 0)
			return PWM1_DUTY;
    else if (strcmp(str, "PWM2.DUTY") == 0)
			return PWM2_DUTY;
    else if (strcmp(str, "PWM3.DUTY") == 0)
			return PWM3_DUTY;
    else if (strcmp(str, "CAN1") == 0)
			return ARG_CAN1;
    else if (strcmp(str, "CAN1.SPEED") == 0)
    	return CAN1_SPEED;
    else if (strcmp(str, "SPI1") == 0)
			return ARG_SPI1;
    else if (strcmp(str, "SPI2") == 0)
			return ARG_SPI2;
    else if (strcmp(str, "SPI1.CS1") == 0)
   			return ARG_SPI1_CS1;
    else if (strcmp(str, "SPI1.CS2") == 0)
			return ARG_SPI1_CS2;
    else if (strcmp(str, "SPI1.CS3") == 0)
			return ARG_SPI1_CS3;
    else if (strcmp(str, "SPI2.CS1") == 0)
			return ARG_SPI2_CS1;
    else if (strcmp(str, "SPI2.CS2") == 0)
			return ARG_SPI2_CS2;
    else if (strcmp(str, "SPI2.CS3") == 0)
			return ARG_SPI2_CS3;
    else if (strcmp(str, "I2C1") == 0)
			return ARG_I2C1;
    else if (strcmp(str, "I2C2") == 0)
			return ARG_I2C2;
    else if (strcmp(str, "I2C1.SPEED") == 0)
			return I2C1_SPEED;
    else if (strcmp(str, "I2C2.SPEED") == 0)
			return I2C2_SPEED;
    else
        return arg_unknown;
}

enum State getState(const char *str)
{
    if (strcmp(str, "ON") == 0 || strcmp(str, "HIGH") == 0 || strcmp(str, "1") == 0 || strcmp(str, "TRUE") == 0)
        return ON;
    else if (strcmp(str, "OFF") == 0 || strcmp(str, "LOW") == 0 || strcmp(str, "0") == 0 || strcmp(str, "FALSE") == 0)
               return OFF;
    else
        return state_unknown;
}

enum Speed getSpeed(const char *str)
{
    if (strcmp(str, "LOW") == 0)
        return LOW;
    else if (strcmp(str, "MEDIUM") == 0)
        return MEDIUM;
    else if (strcmp(str, "HIGH") == 0)
            return HIGH;
    else
    	return spd_unknown;
}

void LED0_Turn_On()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
}

void LED1_Turn_On()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
}

void LED2_Turn_On()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
}
void LED0_Turn_Off()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
}

void LED1_Turn_Off()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);
}

void LED2_Turn_Off()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
}

void LED_ALL_On()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
}

void LED_ALL_Off()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
}

void PWM0_On()
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void PWM0_Off()
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void PWM1_On()
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void PWM1_Off()
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
}

void PWM2_On()
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void PWM2_Off()
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}

void PWM3_On()
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void PWM3_Off()
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
}

void PWM0_DUTY_SET(int duty)
{
	if ((sscanf(duty, "%d %c", &param, &extra) == 1))
	{
		if ((0 <= param) && (param <= 100))
		{
			arr = htim3.Instance->ARR;
			param = arr*param/100;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, param);
		}
		else
		{
			param_error();
		}
	}
	else
	{
		param_error();
	}

}

void PWM1_DUTY_SET(int duty)
{
	if ((sscanf(duty, "%d %c", &param, &extra) == 1))
	{
		if ((0 <= param) && (param <= 100))
		{
			arr = htim3.Instance->ARR;
			param = arr*param/100;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, param);
		}
		else
		{
			param_error();
		}
	}
	else
	{
		param_error();
	}
}

void PWM2_DUTY_SET(int duty)
{
	if ((sscanf(duty, "%d %c", &param, &extra) == 1))
	{
		if ((0 <= param) && (param <= 100))
		{
			arr = htim3.Instance->ARR;
			param = arr*param/100;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, param);
		}
		else
		{
			param_error();
		}
	}
	else
	{
		param_error();
	}
}

void PWM3_DUTY_SET(int duty)
{
	if ((sscanf(duty, "%d %c", &param, &extra) == 1))
	{
		if ((0 <= param) && (param <= 100))
		{
			arr = htim3.Instance->ARR;
			param = arr*param/100;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, param);
		}
		else
		{
			param_error();
		}
	}
	else
	{
		param_error();
	}

}

void PWM0_DUTY_GET()
{
	arr = htim3.Instance->ARR;
	duty_int = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1);
	duty_int = duty_int*100/arr;
	sprintf(duty_str, "%d", duty_int);
	strcat(duty_str,"\r\n");
	HAL_UART_Transmit(&huart3, duty_str, strlen(duty_str), HAL_MAX_DELAY);
}

void PWM1_DUTY_GET()
{
	arr = htim3.Instance->ARR;
	duty_int = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);
	duty_int = duty_int*100/arr;
	sprintf(duty_str, "%d", duty_int);
	strcat(duty_str,"\r\n");
	HAL_UART_Transmit(&huart3, duty_str, strlen(duty_str), HAL_MAX_DELAY);
}

void PWM2_DUTY_GET()
{
	arr = htim3.Instance->ARR;
	duty_int = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);
	duty_int = duty_int*100/arr;
	sprintf(duty_str, "%d", duty_int);
	strcat(duty_str,"\r\n");
	HAL_UART_Transmit(&huart3, duty_str, strlen(duty_str), HAL_MAX_DELAY);
}

void PWM3_DUTY_GET()
{
	arr = htim3.Instance->ARR;
	duty_int = __HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_4);
	duty_int = duty_int*100/arr;
	sprintf(duty_str, "%d", duty_int);
	strcat(duty_str,"\r\n");
	HAL_UART_Transmit(&huart3, duty_str, strlen(duty_str), HAL_MAX_DELAY);
}

void CAN1_START()
{
	HAL_CAN_Start(&hcan1);
}

void CAN1_STOP()
{
	HAL_CAN_Stop(&hcan1);
}

void CAN1_SET_SPEED(int speed)
{
	HAL_CAN_Stop(&hcan1);
	HAL_CAN_DeInit(&hcan1);

	if (speed == LOW)
	{
		hcan1.Init.Prescaler = 108;
		hcan1.Init.TimeSeg1 = CAN_BS1_8TQ;
		hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
	}
	else if (speed == MEDIUM)
	{
		hcan1.Init.Prescaler = 54;
		hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
		hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
	}
	else if (speed == HIGH)
	{
		hcan1.Init.Prescaler = 10;
		hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
		hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
	}

    HAL_CAN_Init(&hcan1);
    HAL_CAN_Start(&hcan1);
}

void SPI1_START()
{
	__HAL_SPI_ENABLE(&hspi1);
}

void SPI1_STOP()
{
	__HAL_SPI_DISABLE(&hspi1);
}

void SPI2_START()
{
	__HAL_SPI_ENABLE(&hspi2);
}

void SPI2_STOP()
{
	__HAL_SPI_DISABLE(&hspi2);
}

void SPI1_CS1_HIGH()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 1);
}

void SPI1_CS1_LOW()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
}

void SPI1_CS2_HIGH()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, 1);
}

void SPI1_CS2_LOW()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, 0);
}

void SPI1_CS3_HIGH()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 1);
}

void SPI1_CS3_LOW()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, 0);
}

void SPI2_CS1_HIGH()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 1);
}

void SPI2_CS1_LOW()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, 0);
}

void SPI2_CS2_HIGH()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 1);
}

void SPI2_CS2_LOW()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, 0);
}

void SPI2_CS3_HIGH()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
}

void SPI2_CS3_LOW()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 0);
}

void I2C1_START()
{
	__HAL_I2C_ENABLE(&hi2c1);
}

void I2C1_STOP()
{
	__HAL_I2C_DISABLE(&hi2c1);
}

void I2C2_START()
{
	__HAL_I2C_ENABLE(&hi2c2);
}

void I2C2_STOP()
{
	__HAL_I2C_DISABLE(&hi2c2);
}

void I2C1_SET_SPEED(int speed)
{
	__HAL_I2C_DISABLE(&hi2c1);
	HAL_I2C_DeInit(&hi2c1);
	if (speed == 0)
	{
		hi2c1.Init.Timing = 0x20404768;
	}
	else if (speed == 1)
	{
		hi2c1.Init.Timing = 0x6000030D;
	}
	else if (speed == 2)
	{
		hi2c1.Init.Timing = 0x00200922;
	}
	HAL_I2C_Init(&hi2c1);
	__HAL_I2C_ENABLE(&hi2c1);

}

void I2C2_SET_SPEED(int speed)
{
	__HAL_I2C_DISABLE(&hi2c2);
	HAL_I2C_DeInit(&hi2c2);
	if (speed = 0)
	{
		hi2c2.Init.Timing = 0x20404768;
	}
	else if (speed = 1)
	{
		hi2c2.Init.Timing = 0x6000030D;
	}
	else if (speed = 2)
	{
		hi2c2.Init.Timing = 0x00200922;
	}
	HAL_I2C_Init(&hi2c2);
	__HAL_I2C_ENABLE(&hi2c2);
}
//-----------------------------------------------------------------------

void cmd_error()
{
	HAL_UART_Transmit(&huart3, "Unknown command! Try set, reset, toggle or get!\r\n", strlen("Unknown command! Try set, reset, toggle or get!\r\n"), HAL_MAX_DELAY);
}
void arg_error()
{
	HAL_UART_Transmit(&huart3, "Unknown or missing argument!\r\n", strlen("Unknown or missing argument!\r\n"), HAL_MAX_DELAY);
}

void param_error()
{
	HAL_UART_Transmit(&huart3, "Parameter unknown or out of range!\r\n", strlen("Parameter unknown or out of range!\r\n"), HAL_MAX_DELAY);
}

void spd_error()
{
	HAL_UART_Transmit(&huart3, "Speed parameter unknown! Try LOW/MEDIUM/HIGH!\r\n", strlen("Speed parameter unknown! Try LOW/MEDIUM/HIGH!\r\n"), HAL_MAX_DELAY);
}

void state_error()
{
	HAL_UART_Transmit(&huart3, "State parameter unknown! Try ON/OFF/HIGH/LOW/1/0!\r\n", strlen("State parameter unknown! Try ON/OFF/HIGH/LOW/1/0!\r\n"), HAL_MAX_DELAY);
}

