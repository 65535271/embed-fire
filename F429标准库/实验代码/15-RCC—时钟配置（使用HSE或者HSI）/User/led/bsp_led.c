/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|
	                           LED2_GPIO_CLK|
	                           LED3_GPIO_CLK, ENABLE); 

		GPIO_InitStructure.GPIO_Pin   = LED1_PIN;		      /*ѡ��Ҫ���Ƶ�GPIO����*/	
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;    /*��������ģʽΪ���ģʽ*/ 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    /*�������ŵ��������Ϊ�������*/
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;     /*��������Ϊ����ģʽ*/
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 	/*������������Ϊ2MHz */   

		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);	
    
    /*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = LED3_PIN;	
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	

		LED_RGBOFF;		/*�ر�RGB��*/
}
/*********************************************END OF FILE**********************/
