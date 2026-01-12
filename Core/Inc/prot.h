/*
 * UART_Driver.h
 *
 *  Created on: Nov 2, 2025
 *      Author: hutoman
 */

#ifndef INC_PROT_H_
#define INC_PROT_H_

enum Command {cmd_set, cmd_get, cmd_unknown};
enum Argument {LED0, LED1, LED2, LED_ALL, PWM0, PWM1, PWM2, PWM3, PWM0_DUTY, PWM1_DUTY, PWM2_DUTY, PWM3_DUTY,
	ARG_CAN1, CAN1_SPEED, ARG_SPI1, ARG_SPI2, ARG_SPI1_CS1, ARG_SPI1_CS2, ARG_SPI1_CS3, ARG_SPI2_CS1,
	ARG_SPI2_CS2, ARG_SPI2_CS3, ARG_I2C1, ARG_I2C2, I2C1_SPEED, I2C2_SPEED, arg_unknown};
enum State {ON, OFF, state_unknown};
enum Speed {LOW, MEDIUM, HIGH, spd_unknown};

enum Command getCommand(const char *str);
enum Argument getArgument(const char *str);
enum Speed getSpeed(const char *str);

void LED0_Turn_On();
void LED1_Turn_On();
void LED2_Turn_On();
void LED0_Turn_Off();
void LED1_Turn_Off();
void LED2_Turn_Off();
void LED_ALL_On();
void LED_ALL_Off();
void PWM0_On();
void PWM0_Off();
void PWM1_On();
void PWM1_Off();
void PWM2_On();
void PWM2_Off();
void PWM3_On();
void PWM3_Off();
void PWM0_DUTY_SET(int duty);
void PWM1_DUTY_SET(int duty);
void PWM2_DUTY_SET(int duty);
void PWM3_DUTY_SET(int duty);
void PWM0_DUTY_GET();
void PWM1_DUTY_GET();
void PWM2_DUTY_GET();
void PWM3_DUTY_GET();
void CAN1_START();
void CAN1_STOP();
void CAN1_SET_SPEED(int speed);
void SPI1_START();
void SPI1_STOP();
void SPI2_START();
void SPI2_STOP();
void SPI1_CS1_HIGH();
void SPI1_CS1_LOW();
void SPI1_CS2_HIGH();
void SPI1_CS2_LOW();
void SPI1_CS3_HIGH();
void SPI1_CS3_LOW();
void SPI2_CS1_HIGH();
void SPI2_CS1_LOW();
void SPI2_CS2_HIGH();
void SPI2_CS2_LOW();
void SPI2_CS3_HIGH();
void SPI2_CS3_LOW();
void I2C1_START();
void I2C1_STOP();
void I2C2_START();
void I2C2_STOP();
void I2C1_SET_SPEED(int speed);
void I2C2_SET_SPEED(int speed);

//-----------------------------------------------------
void cmd_error();
void arg_error();
void param_error();
void spd_error();
void state_error();

#endif /* INC_PROT_H_ */
