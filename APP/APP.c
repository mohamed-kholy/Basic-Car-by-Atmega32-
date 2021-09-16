/*
 * APP.c
 *
 * Created: 9/10/2021 12:29:17 AM
 *  Author: Ahmed SemSem
 */ 
#include "APP.h"

/*- GLOBAL EXTERN VARIABLES TO STORE THE BUTTON STATUS
-------------------------------*/
u8  BUTTON_G = Initial_Value;
u8  BUTTON_M = Initial_Value;
u8  BUTTON_R = Initial_Value;
u8  BUTTON_L = Initial_Value;
u8 BUTTON_G_Counter = Initial_Value;
u8 Car_Status = Initial_Value;

/********************************************************************************************************************************
* Parameters:(in) : none
* Parameters:(out): Initialize the PWM, Motors and Buttons
* Return value	  : none
* Description	  : initializes the car module by initializing the modules used in it
**********************************************************************************************************************************/
void APP_init (void)
{

	MPWM_voidPwmInit();
	EUDCMOTOR_voidDcMotorInit();
	EUButton_init(GPIOA,PIN0,PULL_DOWN);
	EUButton_init(GPIOA,PIN1,PULL_DOWN);
	EUButton_init(GPIOA,PIN2,PULL_DOWN);
	EUButton_init(GPIOA,PIN3,PULL_DOWN);
	
}
/************************************************************************************
* Parameters (in): None
* Parameters (out): none
* Return value: none
* Description: main task of the control system, handles all application cases
************************************************************************************/
void APP_voidStateUpdate(void)
{
	/* get readings from the buttons */
	BUTTON_G = EUButtonPressed(GPIOA,PIN0,PULL_DOWN);
	BUTTON_M = EUButtonPressed(GPIOA,PIN1,PULL_DOWN);
	BUTTON_R = EUButtonPressed(GPIOA,PIN2,PULL_DOWN);
	BUTTON_L = EUButtonPressed(GPIOA,PIN3,PULL_DOWN);
	/* check the buttons */
	if (BUTTON_G == HIGH)
	{
		switch(BUTTON_G_Counter)/* check how many the G button is was pressed*/
		{
			case(Initial_Value):
			{
				Car_Status = SPEED_30_FORWARD;
				BUTTON_G_Counter++;
				_delay_ms(300);/* delay to avoid long press*/
				break;
			}
			case(1):
			{
				Car_Status = SPEED_60_FORWARD;
				BUTTON_G_Counter++;
				_delay_ms(300);
				break;
			}
			case(2):
			{
				Car_Status = SPEED_90_FORWARD;
				BUTTON_G_Counter++;
				_delay_ms(300);
				break;
			}
			case(3):
			{
				Car_Status = SPEED_30_BACKWARD;
				BUTTON_G_Counter = Initial_Value;
				_delay_ms(300);
				break;
			}
			default:
			break;
		}
	}
	if (BUTTON_M == HIGH)/* check the move button*/
	{
		switch(Car_Status)
		{
			case(SPEED_30_FORWARD):
			{
				Motor_moveForward(SPEED_30);
				break;
			}
			case(SPEED_60_FORWARD):
			{
				Motor_moveForward(SPEED_60);
				break;
			}
			case(SPEED_90_FORWARD):
			{
				Motor_moveForward(SPEED_90);
				break;
			}
			case(SPEED_30_BACKWARD):
			{
				Motor_moveBackward(SPEED_30);
				break;
			}
			default:
			break;
		}
	}
	if (BUTTON_R == HIGH) /* check the move right button*/
	{
		Motor_moveRight();
	}
	if (BUTTON_L == HIGH)/* check the move left button*/
	{
		Motor_moveLeft();
	}
	if ((BUTTON_G == LOW) && (BUTTON_M == LOW) && (BUTTON_R == LOW) && (BUTTON_L == LOW))/*if any button not pressed stop the car*/
	{
		Motor_StopMove();
	}
	
}

/************************************************************************************
* Parameters (in): the speed as Percentage 
* Parameters (out): none
* Return value: none
* Description: control the motors to move forward with a wanted speed
************************************************************************************/
void Motor_moveForward(u8 u8_speed)
{
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN1_WIRE1,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN2_WIRE1,HIGH);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN1_WIRE2,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN2_WIRE2,HIGH);
	EUDCMOTOR_voidStartMotor();
	EUDCMOTOR_voidSetMotorSpeed(u8_speed);
	
}
/************************************************************************************
* Parameters (in): the speed as Percentage
* Parameters (out): none
* Return value: none
* Description: control the motors to move backward with a wanted speed
************************************************************************************/
void Motor_moveBackward(u8 u8_speed)
{
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN1_WIRE1,HIGH);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN2_WIRE1,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN1_WIRE2,HIGH);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN2_WIRE2,LOW);
	EUDCMOTOR_voidStartMotor();
	EUDCMOTOR_voidSetMotorSpeed(u8_speed);
	
}
/************************************************************************************
* Parameters (in): void
* Parameters (out): none
* Return value: none
* Description: control the car to move right with speed of 30%
************************************************************************************/
void Motor_moveRight(void){
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN1_WIRE1,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN2_WIRE1,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN1_WIRE2,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN2_WIRE2,HIGH);
	EUDCMOTOR_voidStartMotor();
	EUDCMOTOR_voidSetMotorSpeed(SPEED_30);
	
}
/************************************************************************************
* Parameters (in): void
* Parameters (out): none
* Return value: none
* Description: control the car to move left with speed of 30%
************************************************************************************/
void Motor_moveLeft(void){
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN1_WIRE1,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN2_WIRE1,HIGH);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN1_WIRE2,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN2_WIRE2,LOW);
	EUDCMOTOR_voidStartMotor();
	EUDCMOTOR_voidSetMotorSpeed(SPEED_30);
	
}
/************************************************************************************
* Parameters (in): void
* Parameters (out): none
* Return value: none
* Description: control the car to stop moving
************************************************************************************/
void Motor_StopMove(void){
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN1_WIRE1,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR1,DCMOTOR_PIN2_WIRE1,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN1_WIRE2,LOW);
	MDIO_voidSetPinValue(DCMOTOR_PORT_MOTOR2,DCMOTOR_PIN2_WIRE2,LOW);
	EUDCMOTOR_voidStopMotor();
}