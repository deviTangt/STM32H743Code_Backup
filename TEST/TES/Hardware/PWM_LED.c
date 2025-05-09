#include "PWM_LED.h"
//
uint32_t cmp_val;
//
void PWM_LED(){ // Prescale = 639  Period = 999 (100Hz) 
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, cmp_val);

	cmp_val = uwTick % 1000;
	//HAL_Delay(500);
}//