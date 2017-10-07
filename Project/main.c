/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_tim.h"


volatile uint16_t k;



void move(){
	switch(k){
					//move forward 8
					case 56:
						GPIO_SetBits(GPIOD,GPIO_Pin_15);
						GPIO_ResetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_12);
						TIM4->CCR1 =0;
						TIM4->CCR2 =0;
						TIM4->CCR3 =209;
						TIM4->CCR4 =209;
						break;
					//move right 6
					case 54:
						GPIO_SetBits(GPIOD,GPIO_Pin_12);
						GPIO_ResetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
						TIM4->CCR1 =209;
						TIM4->CCR2 =0;
						TIM4->CCR3 =209;
						TIM4->CCR4 =209;
						break;
					//move left 4
					case 52:
						GPIO_SetBits(GPIOD,GPIO_Pin_14);
						GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15);
						TIM4->CCR1 =0;
						TIM4->CCR2 =209;
						TIM4->CCR2 =209;
						TIM4->CCR2 =209;
						break;
					//move backward 5
					case 53:
						GPIO_SetBits(GPIOD,GPIO_Pin_13);
						GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_15|GPIO_Pin_14);

						TIM4->CCR1 =209;
						TIM4->CCR2 =209;
						TIM4->CCR3 =0;
						TIM4->CCR4 =0;
						break;
					//stop 0
					case 48:
						GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
						TIM4->CCR1 =209;
						TIM4->CCR2 =209;
						TIM4->CCR3 =209;
						TIM4->CCR4 =209;
						break;


	}
}

void USART2_IRQHandler(void){
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
		//GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
		k=USART2->DR;
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}

}

int main(void){
	SystemInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //diody
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //usart
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //pwm
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);


	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_EnableIRQ(USART2_IRQn);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period =209;
	TIM_TimeBaseStructure.TIM_Prescaler=7;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM4, ENABLE);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM4->CCR1 = 419;


	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM4->CCR2 = 419;

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM4->CCR3 = 419;

	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM4->CCR4 = 419;

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	while(1){
		//if (k==50) GPIO_SetBits(GPIOD,GPIO_Pin_13);
		 //GPIO_ResetBits(GPIOD,GPIO_Pin_13);
		move();

	}
}

