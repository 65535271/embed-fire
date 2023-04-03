/******************************�б� 1: �����嵥:RCC-1 ����ϵͳʱ�ӿ⺯��**************************************/
/*
 * ʹ�� HSE ʱ������ϵͳʱ�ӵĲ���
 * 1������ HSE �����ȴ� HSE �ȶ�
 * 2������ AHB�� APB2�� APB1 ��Ԥ��Ƶ����
 * 3������ PLL ��ʱ����Դ
      ���� VCO ����ʱ�� ��Ƶ���� m
      ���� VCO ���ʱ�� ��Ƶ���� n
      ���� PLLCLK ʱ�ӷ�Ƶ����   p
      ���� OTG FS,SDIO,RNG ʱ�ӷ�Ƶ���� q
 * 4������ PLL�����ȴ� PLL �ȶ�
 * 5���� PLLCK �л�Ϊϵͳʱ�� SYSCLK
 * 6����ȡʱ���л�״̬λ��ȷ�� PLLCLK ��ѡΪϵͳʱ��
 */
/*if defined USE_HSE_BPAS  ���������ж�ʹ�õ��Ƿ�Ϊ��Դ����<��������ʹ�õ�����Դ����ͬ������ʱ����Դ����Ҫ����Դ�����Ķ�> */
#define PLL_M 25
#define PLL_N 360   //���Ҫ��Ƶ�Ļ����޸� PLL_N ����꼴�ɣ�ȡֵ��ΧΪ�� 192~432��
#define PLL_P 2
#define PLL_Q 7

void SetSysClock(void)
{
    __IO uint32_t   StartUpCounter = 0, HSEStatus = 0;
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);        //  ʹ�� HSE

    // �ȴ� HSE �����ȶ�
    do 
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus==0)&&(StartUpCounter!=HSE_STARTUP_TIMEOUT));
    if ((RCC->CR & RCC_CR_HSERDY) != RESET) 
    {
        HSEStatus = (uint32_t)0x01;
    } 
    else 
    {
        HSEStatus = (uint32_t)0x00;
    }
    if (HSEStatus == (uint32_t)0x01)    // HSE �����ɹ�
    {
        // ��ѹ����ѹ�����������Ϊ 1���Ա�������Ϊ���Ƶ��
        // ����ʱʹ���ܺ͹���ʵ��ƽ��
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_VOS;

        //  ���� AHB/APB2/APB1 �ķ�Ƶ����
        
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;    // HCLK = SYSCLK / 1
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;   // PCLK2 = HCLK / 2
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;   // PCLK1 = HCLK / 4

        //  ������ PLL ��ʱ����Դ������ M,N,P,Q
        // Configure the main PLL
        RCC->PLLCFGR = PLL_M|(PLL_N<<6)|(((PLL_P >> 1) -1) << 16) |(RCC_PLLCFGR_PLLSRC_HSE) |(PLL_Q << 24);

        RCC->CR |= RCC_CR_PLLON;    //  ʹ���� PLL

        while ((RCC->CR & RCC_CR_PLLRDY) == 0) {}  // �ȴ� PLL �ȶ�
        /*----------------------------------------------------*/
        // ���� OVER-RIDE ģʽ�����ܴﵽ����Ƶ��
        PWR->CR |= PWR_CR_ODEN;
        while ((PWR->CSR & PWR_CSR_ODRDY) == 0) {}
        PWR->CR |= PWR_CR_ODSWEN;
        while ((PWR->CSR & PWR_CSR_ODSWRDY) == 0) {}
        
        // ���� FLASH Ԥȡָ, ָ���, ���ݻ���͵ȴ�״̬
        FLASH->ACR = FLASH_ACR_PRFTEN|FLASH_ACR_ICEN|FLASH_ACR_DCEN|FLASH_ACR_LATENCY_5WS;
        /*---------------------------------------------------*/

        //  ѡ���� PLLCLK ��Ϊϵͳʱ��Դ
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        //  ��ȡʱ���л�״̬λ��ȷ�� PLLCLK ѡΪϵͳʱ��
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS )!= RCC_CFGR_SWS_PLL);{}
    } 
    else 
    {
        // HSE ����������
    }
}

/********************************�б� 3: �����嵥:RCC-2 HSE ��Ϊϵͳʱ����Դ****************************************/

/*
 * ʹ��HSIʱ������ϵͳʱ�ӵĲ���
 * 1������HSI �����ȴ� HSI �ȶ�
 * 2������ AHB��APB2��APB1��Ԥ��Ƶ����
 * 3������PLL��ʱ����Դ
 *    ����VCO����ʱ�� ��Ƶ����    m
 *    ����VCO���ʱ�� ��Ƶ����    n
 *    ����SYSCLKʱ�ӷ�Ƶ����      p
 *    ����OTG FS,SDIO,RNGʱ�ӷ�Ƶ����   q
 * 4������PLL�����ȴ�PLL�ȶ�
 * 5����PLLCK�л�Ϊϵͳʱ��SYSCLK
 * 6����ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
 */

/*
 * m: VCO����ʱ�� ��Ƶ���ӣ�ȡֵ2~63
 * n: VCO���ʱ�� ��Ƶ���ӣ�ȡֵ192~432
 * p: PLLCLKʱ�ӷ�Ƶ����  ��ȡֵ2��4��6��8
 * q: OTG FS,SDIO,RNGʱ�ӷ�Ƶ���ӣ�ȡֵ4~15
 * �������þ�����ʹ��HSI����ʱ��
 * SYSCLK=HCLK=180M,PCLK2=HCLK/2=90M,PCLK1=HCLK/4=45M
 * HSI_SetSysClock(16, 360, 2, 7);
 * HSE��Ϊʱ����Դ������PLL��Ƶ��Ϊϵͳʱ�ӣ�����ͨ��������
 
 * ϵͳʱ�ӳ�Ƶ��216Mˬһ��
 * HSI_SetSysClock(16, 432, 2, 9);
 */

void HSI_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q)	
{
  __IO uint32_t HSIStartUpStatus = 0;
  RCC_DeInit();	        // ��RCC�����ʼ���ɸ�λ״̬
	RCC_HSICmd(ENABLE);   //ʹ��HSI, HSI=16M
	HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY; // �ȴ� HSI ����
	
  if (HSIStartUpStatus == RCC_CR_HSIRDY)      // ֻ�� HSI����֮�����������ִ��
  {
    // ��ѹ����ѹ�����������Ϊ1���Ա�������Ϊ���Ƶ��
		// ����ʱʹ���ܺ͹���ʵ��ƽ��
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
	
		RCC_HCLKConfig(RCC_SYSCLK_Div1);  // HCLK = SYSCLK / 1
		RCC_PCLK2Config(RCC_HCLK_Div2);   // PCLK2 = HCLK / 2
		RCC_PCLK1Config(RCC_HCLK_Div4);	  // PCLK1 = HCLK / 4
		
    // ���Ҫ��Ƶ�͵�������������
		// ����PLL��Դʱ�ӣ�����VCO��Ƶ����m������VCO��Ƶ����n��
		//  ����ϵͳʱ�ӷ�Ƶ����p������OTG FS,SDIO,RNG��Ƶ����q
		RCC_PLLConfig(RCC_PLLSource_HSI, m, n, p, q);
		RCC_PLLCmd(ENABLE); // ʹ��PLL
  
	  // �ȴ� PLL�ȶ�
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }   

    /*-----------------------------------------------------*/
    //���� OVER-RIDEģʽ�����ܴﵽ����Ƶ��
    PWR->CR |= PWR_CR_ODEN;
    while((PWR->CSR & PWR_CSR_ODRDY) == 0)
    {
    }
    PWR->CR |= PWR_CR_ODSWEN;
    while((PWR->CSR & PWR_CSR_ODSWRDY) == 0)
    {
    }      
    // ����FLASHԤȡָ,ָ���,���ݻ���͵ȴ�״̬
    FLASH->ACR = FLASH_ACR_PRFTEN 
		            |FLASH_ACR_ICEN 
		            |FLASH_ACR_DCEN 
		            |FLASH_ACR_LATENCY_5WS;
/*-----------------------------------------------------*/
		
		// ��PLL�ȶ�֮�󣬰�PLLʱ���л�Ϊϵͳʱ��SYSCLK
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // ��ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else    // HSI����������
  { 
    while (1)
    {
    }
  }
}


/**************************�б� 3: �����嵥:RCC-3 ʹ�� HSI ����ϵͳʱ��*****************************/
// MCO1 PA8 GPIO ��ʼ��
void MCO1_GPIO_Config(void)       
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // MCO1 GPIO ����
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
}

// MCO2 PC9 GPIO ��ʼ��
void MCO2_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // MCO2 GPIO ����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


/***************************�б� 5: �����嵥:RCC-5 MCO ���ʱ��ѡ��****************************/
RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1); 	// MCO1 ���PLLCLK
RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO1Div_1);	// MCO2 ���SYSCLK


/*****************************�б� 6: �����嵥:RCC-6 main ����***********************************/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	// ��������main����֮ǰ�������ļ���statup_stm32f429_439xx.s�Ѿ�����
	// SystemInit()������ϵͳʱ�ӳ�ʼ����72MHZ
	// SystemInit()��system_stm32f4xx.c�ж���
	// ����û����޸�ϵͳʱ�ӣ������б�д�����޸�	
	// ��������ϵͳʱ�ӣ���ʱ�����ѡ��ʹ��HSE����HSI
	
	
	/*  ע�� �������� PLL ʹ�ܺ��� PLL ���ò����㲻�ɸ��ģ���ϵͳ�ϵ���
	 *  �Զ����г�ʼ��������ڶ�HES���³�ʼ��֮ǰ����Ҫ��system_stm32f4xx.c	  
	 *  ��line506��SetSysClock();ע�͵�,����HSE���³�ʼ��֮����Ч��
	 */
	
	// MCO GPIO  ��ʼ��
 	 MCO1_GPIO_Config();
 	 MCO2_GPIO_Config();	

  	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1); 	// MCO1 ���PLLCLK
	RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO1Div_1);	// MCO2 ���SYSCLK
	
	// ʹ��HSE������ϵͳʱ��Ϊ180M
	//HSE_SetSysClock(25, 360, 2, 7);
	
	//ϵͳʱ�ӳ�Ƶ��216Mˬһ�£������216M������������
  	HSE_SetSysClock(25, 432, 2, 9);
	
	// ʹ��HSI������ϵͳʱ��Ϊ180M
	//HSI_SetSysClock(16, 432, 2, 7);

	LED_GPIO_Config();	// LED �˿ڳ�ʼ�� 
	
	while (1)
	{
		LED1( ON );			// �� 
		Delay(0x4FFFFF);
		LED1( OFF );		// ��
		Delay(0x4FFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/