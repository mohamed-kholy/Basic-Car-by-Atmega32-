/*
 * APP.h
 *
 * Created: 9/10/2021 12:29:29 AM
 *  Author: Ahmed SemSem
 */ 
#define F_CPU 1000000UL
#include "../LIB/STD_TYPES/STD_TYPES.h"
#include "../MCAL/DIO/MDIO_interface.h"
#include "../MCAL/PWM/PWM_interface.h"
#include "../ECUAL/BUTTON/BUTTON_interface.h"
#include "../ECUAL/DC Motor/DC_MOTOR_interface.h"
#include "../ECUAL/DC Motor/DC_MOTOR_config.h"
#include "util/delay.h"
#include "APP_Config.h"

#ifndef APP_H_
#define APP_H_

void APP_init (void) ;
void APP_voidStateUpdate(void);
void Motor_moveForward(u8 u8_speed);
void Motor_moveBackward(u8 u8_speed);
void Motor_moveRight(void);
void Motor_moveLeft(void);
void Motor_StopMove(void);
#endif /* APP_H_ */