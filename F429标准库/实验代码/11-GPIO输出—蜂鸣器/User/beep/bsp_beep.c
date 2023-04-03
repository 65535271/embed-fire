/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �����������ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./beep/bsp_beep.h"   

 /**
  * @brief  ��ʼ�����Ʒ�������IO
  * @param  ��
  * @retval ��
  */
void BEEP_GPIO_Config(void)
{		
		
		GPIO_InitTypeDef GPIO_InitStructure;              /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		RCC_AHB1PeriphClockCmd( BEEP_GPIO_CLK, ENABLE);   /*�������Ʒ�������GPIO�Ķ˿�ʱ��*/

		GPIO_InitStructure.GPIO_Pin  = BEEP_GPIO_PIN;	    /*ѡ��Ҫ���Ʒ�������GPIO*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	  /*����GPIOģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /*����GPIO����Ϊ50MHz */
		GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);	  /*���ÿ⺯������ʼ�����Ʒ�������GPIO*/		 
    
		GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);	  /* �رշ�����*/
}
/*********************************************END OF FILE**********************/
