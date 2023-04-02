/***************�б� 1: �����嵥:GPIO ���-1 LED ����������صĺ�****************/
//���Ŷ���
/*******************************************************/
//R ��ɫ��
#define LED1_PIN           GPIO_Pin_10                 
#define LED1_GPIO_PORT     GPIOH                      
#define LED1_GPIO_CLK      RCC_AHB1Periph_GPIOH

//G ��ɫ��
#define LED2_PIN           GPIO_Pin_11                 
#define LED2_GPIO_PORT     GPIOH                      
#define LED2_GPIO_CLK      RCC_AHB1Periph_GPIOH

//B ��ɫ��
#define LED3_PIN           GPIO_Pin_12                 
#define LED3_GPIO_PORT     GPIOH                       
#define LED3_GPIO_CLK      RCC_AHB1Periph_GPIOH
/************************************************************/

/**************�б� 2: �����嵥:GPIO ���-2 ���� LED ����ĺ�************************/
/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  0
#define OFF 1

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);\
					else		\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN)
					
#define LED4(a)	if (a)	\
					GPIO_SetBits(LED4_GPIO_PORT,LED4_PIN);\
					else		\
					GPIO_ResetBits(LED4_GPIO_PORT,LED4_PIN)


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		{p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)		{p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	{p->ODR ^=i;}		//�����ת״̬

/* �������IO�ĺ� */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF		digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON			digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF		digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON			digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF		digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON			digitalLo(LED3_GPIO_PORT,LED3_PIN)

/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  	\
					LED1_ON;	\
					LED2_OFF;	\
					LED3_OFF

//��
#define LED_GREEN	\
					LED1_OFF;	\
					LED2_ON;	\
					LED3_OFF
//��
#define LED_BLUE	\
					LED1_OFF;	\
					LED2_OFF;	\
					LED3_ON
//��(��+��)					
#define LED_YELLOW	\
					LED1_ON;	\
					LED2_ON;	\
					LED3_OFF
//��(��+��)
#define LED_PURPLE	\
					LED1_ON;	\
					LED2_OFF;	\
					LED3_ON
//��(��+��)
#define LED_CYAN 	\
					LED1_OFF;	\
					LED2_ON;	\
					LED3_ON				
//��(��+��+��)
#define LED_WHITE	\
					LED1_ON;	\
					LED2_ON;	\
					LED3_ON			
//��(ȫ���ر�)
#define LED_RGBOFF	\
					LED1_OFF;	\
					LED2_OFF;	\
					LED3_OFF		


/********************�б� 3: �����嵥:GPIO ���-3 LED GPIO ��ʼ������***********************/
 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|LED2_GPIO_CLK|LED3_GPIO_CLK, ENABLE); 
														   
		GPIO_InitStructure.GPIO_Pin = LED1_PIN;	        /*ѡ��Ҫ���Ƶ�GPIO����*/

		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   /*��������ģʽΪ���ģʽ*/
   		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   /*�������ŵ��������Ϊ�������*/
    	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;    /*��������Ϊ����ģʽ*/
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; /*������������Ϊ2MHz */

		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	 /*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/	
    
    	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
    	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);	
    
    	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
		GPIO_InitStructure.GPIO_Pin = LED3_PIN;	
    	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	
		
		LED_RGBOFF;		/*�ر�RGB��*/
}
/*********************************************END OF FILE**********************/


/*****************�б� 4: �����嵥:GPIO ���-4 ���� LED �ƣ� main �ļ�****************/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����LED�� */
	while (1)
	{
		LED1( ON );			// �� 
		Delay(0xFFFFFF);
		LED1( OFF );		// ��

		LED2( ON );			// �� 
		Delay(0xFFFFFF);
		LED2( OFF );		// ��

		LED3( ON );			// �� 
		Delay(0xFFFFFF);
		LED3( OFF );		// ��	

		/*������ʾ ������������� ��ɫ*/
		LED_RED;
		Delay(0xFFFFFF);
		
		LED_GREEN;
		Delay(0xFFFFFF);
		
		LED_BLUE;
		Delay(0xFFFFFF);
		
		LED_YELLOW;
		Delay(0xFFFFFF);
		
		LED_PURPLE;
		Delay(0xFFFFFF);
				
		LED_CYAN;
		Delay(0xFFFFFF);
		
		LED_WHITE;
		Delay(0xFFFFFF);
		
		LED_RGBOFF;
		Delay(0xFFFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


/*************�б� 5: �����嵥:GPIO ���-5 GPIO_Init �����Ķ��Բ��֣�
 * ������ÿ���⺯���Ŀ�ͷ�������������Ƶ����ݣ�
 * ����ġ�assert_param��ʵ����һ���꣬�ڿ⺯���������ڼ����������Ƿ����Ҫ����������Ҫ����ִ��ĳ������������棬
 * ��assert_param���Ķ���������嵥:GPIO ���-6 ��*****************
 * */
#ifdef USE_FULL_ASSERT
	/**
	 * @brief assert_param �����ں���������������
	 * @param expr: �� expr ֵΪ�٣������ assert_failed ����
	 * �����ļ����������к�
	 * �� expr ֵΪ�棬��ִ�в���
	 */
	#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
	/* ����������� ------------------------------------------------------- */
	void assert_failed(uint8_t* file, uint32_t line);
#else
	#define assert_param(expr) ((void)0)
#endif


/********************�б� 7: �����嵥:GPIO ���-7 assert_failed ���������Ϣ**********************/
void assert_failed(uint8_t* file, uint32_t line)
{
	printf(��\r\n ����������󣬴����ļ��� =%s, �к� =%s�� ,file,line);
}
#define IS_GPIO_PIN(PIN) ((PIN) != (uint32_t)0x00)


/********************�б� 8: �����嵥:GPIO ���-8 Doxygen ע�͹淶*******************************/
/**
 * @brief ��ʼ������ LED �� IO
 * @param ��
 * @retval ��
 */


/********************�б� 9: �����嵥:GPIO ���-9 ��ֹͷ�ļ��ظ������ĺ�**************************/
#ifndef __LED_H
#define __LED_H

/* �˴�ʡ��ͷ�ļ��ľ������� */

#endif /* end of __LED_H */