/********************�б� 1: �����嵥:GPIO ����-1 �������������صĺ�**********************/
//���Ŷ���
/*******************************************************/
#define KEY1_PIN                  GPIO_Pin_0                 
#define KEY1_GPIO_PORT            GPIOA                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define KEY2_PIN                  GPIO_Pin_13                 
#define KEY2_GPIO_PORT            GPIOC                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOC
/*******************************************************/


/********************�б� 2: �����嵥:GPIO ����-2 ���� GPIO ��ʼ������**********************/
/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);   /*��������GPIO�ڵ�ʱ��*/
	
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;         /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;     /*��������Ϊ����ģʽ*/
 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; /*�������Ų�����Ҳ������*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);  /*ʹ������Ľṹ���ʼ������*/
  
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;          /*ѡ�񰴼�������*/
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);  /*ʹ������Ľṹ���ʼ������*/
}


/********************�б� 3: �����嵥:GPIO ����-3 ��ⰴ����״̬**********************/
/**
  * @brief  ����Ƿ��а�������     
  *	@param 	GPIOx:����Ķ˿�, x�����ǣ�A...K�� 
	*	@param 	GPIO_PIN:����Ķ˿�λ�� ������GPIO_PIN_x��x������0...15��
  * @retval ������״̬
  *		@arg KEY_ON:��������
  *		@arg KEY_OFF:����û����
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
    {	 
      /*�ȴ������ͷ� */
      while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
      return 	KEY_ON;	 
    }
	else
		return KEY_OFF;
}
/*********************************************END OF FILE**********************/


/********************�б� 4: �����嵥:GPIO ����-4 �������������**********************/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	LED_GPIO_Config();	 	/* LED �˿ڳ�ʼ�� */
  Key_GPIO_Config();    /*��ʼ������*/
	
	/* ��ѯ����״̬��������������תLED */ 
	while(1)                            
	{	   
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			LED1_TOGGLE;  /*LED1��ת*/
		}   
    
    if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
		{
			LED2_TOGGLE;  /*LED2��ת*/
		}   
	}
}