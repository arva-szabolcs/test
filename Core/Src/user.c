/*
 * user.c
 *
 *  Created on: Nov 5, 2025
 *      Author: hutoman
 */

#include "main.h"
#include "user.h"
#include "prot.h"

extern UART_HandleTypeDef huart3;

#define WORD_NR_BUFFER  10
#define WORD_LEN_BUFFER 20

char msg[WORD_NR_BUFFER][WORD_LEN_BUFFER];
int count = 0;
int count2 = 0;

void append_msg(char *RX)
{
	 if (RX[0] > 0b00100000)
	  {
		msg[count][count2++] = RX[0];
	  }
	 else
	   {
	 	  HAL_UART_Transmit(&huart3, "Invalid character!\r\n", strlen("Invalid character!\r\n"), HAL_MAX_DELAY);
	   }
}

void separate_msg(char *RX)
{
	if (RX[0] > 0b00100000)
	  {

	count += 1;
	count2 = 0;
	  }
	 else
	   {
		  HAL_UART_Transmit(&huart3, "Invalid character!\r\n", strlen("Invalid character!\r\n"), HAL_MAX_DELAY);
	   }
}

void end_msg(char *RX)
{

	if (RX[0] > 0b00100000)
	  {
	process_msg();
	  }
	 else
	   {
		  HAL_UART_Transmit(&huart3, "Invalid character!\r\n", strlen("Invalid character!\r\n"), HAL_MAX_DELAY);
	   }
}

void process_msg()
{

	enum Command cmd = getCommand(msg[0]);
	enum Argument arg = getArgument(msg[1]);
	enum State state = getState(msg[2]);
	switch (cmd)
	{
	case cmd_set:

		switch (arg)
		{
		case LED0:
			switch (state)
			{
			case ON:
				LED0_Turn_On();
				break;
			case OFF:
				LED0_Turn_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case LED1:
			switch (state)
			{
			case ON:
				LED1_Turn_On();
				break;
			case OFF:
				LED1_Turn_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case LED2:
			switch (state)
			{
			case ON:
				LED2_Turn_On();
				break;
			case OFF:
				LED2_Turn_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case LED_ALL:
			switch (state)
			{
			case ON:
				LED_ALL_On();
				break;
			case OFF:
				LED_ALL_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case PWM0:
			switch (state)
			{
			case ON:
				PWM0_On();
				break;
			case OFF:
				PWM0_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case PWM1:
			switch (state)
			{
			case ON:
				PWM1_On();
				break;
			case OFF:
				PWM1_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case PWM2:
			switch (state)
			{
			case ON:
				PWM2_On();
				break;
			case OFF:
				PWM2_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case PWM3:
			switch (state)
			{
			case ON:
				PWM3_On();
				break;
			case OFF:
				PWM3_Off();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case PWM0_DUTY:
		{
			PWM0_DUTY_SET(msg[2]);
			break;
		}
		case PWM1_DUTY:
		{
			PWM1_DUTY_SET(msg[2]);
			break;
		}
		case PWM2_DUTY:
		{
			PWM2_DUTY_SET(msg[2]);
			break;
		}
		case PWM3_DUTY:
		{
			PWM3_DUTY_SET(msg[2]);
			break;
		}
		case ARG_CAN1:
			switch (state)
			{
			case ON:
				CAN1_START();
				break;
			case OFF:
				CAN1_STOP();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case CAN1_SPEED:
			{
				enum Speed speed = getSpeed(msg[2]);
				switch(speed)
				{
				case spd_unknown:
					spd_error();
					break;
				CAN1_SET_SPEED(speed);
				}
				break;
			}
		case ARG_SPI1:
			switch (state)
			{
			case ON:
				SPI1_START();
				break;
			case OFF:
				SPI1_STOP();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_SPI2:
			switch (state)
			{
			case ON:
				SPI2_START();
				break;
			case OFF:
				SPI2_STOP();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_SPI1_CS1:
			switch (state)
			{
			case ON:
				SPI1_CS1_HIGH();
				break;
			case OFF:
				SPI1_CS1_LOW();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_SPI1_CS2:
			switch (state)
			{
			case ON:
				SPI1_CS2_HIGH();
				break;
			case OFF:
				SPI1_CS2_LOW();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_SPI1_CS3:
			switch (state)
			{
			case ON:
				SPI1_CS3_HIGH();
				break;
			case OFF:
				SPI1_CS3_LOW();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_SPI2_CS1:
			switch (state)
			{
			case ON:
				SPI2_CS1_HIGH();
				break;
			case OFF:
				SPI2_CS1_LOW();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_SPI2_CS2:
			switch (state)
			{
			case ON:
				SPI2_CS2_HIGH();
				break;
			case OFF:
				SPI2_CS2_LOW();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_SPI2_CS3:
			switch (state)
			{
			case ON:
				SPI2_CS3_HIGH();
				break;
			case OFF:
				SPI2_CS3_LOW();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_I2C1:
			switch (state)
			{
			case ON:
				I2C1_START();
				break;
			case OFF:
				I2C1_STOP();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case ARG_I2C2:
			switch (state)
			{
			case ON:
				I2C2_START();
				break;
			case OFF:
				I2C2_STOP();
				break;
			case state_unknown:
				state_error();
				break;
			}
			break;
		case I2C1_SPEED:
		{
			enum Speed speed = getSpeed(msg[2]);
			switch(speed)
			{
			case spd_unknown:
				spd_error();
				break;
			I2C1_SET_SPEED(speed);
			}
			break;
		}
		case I2C2_SPEED:
		{
			enum Speed speed = getSpeed(msg[2]);
			switch(speed)
			{
			case spd_unknown:
				spd_error();
				break;
			I2C2_SET_SPEED(speed);
			}
			break;
		}
		case arg_unknown:
			arg_error();
			break;
		}
		break;

	case cmd_get:
		switch(arg)
		{
		case PWM0_DUTY:
			PWM0_DUTY_GET();
			break;
		case PWM1_DUTY:
			PWM1_DUTY_GET();
			break;
		case PWM2_DUTY:
			PWM2_DUTY_GET();
			break;
		case PWM3_DUTY:
			PWM3_DUTY_GET();
			break;
		case arg_unknown:
			arg_error();
			break;
		}
		break;


	case cmd_unknown:
		cmd_error();
		break;



	}
	memset(msg, 0, sizeof(msg));
		count = 0;
		count2 = 0;
}

