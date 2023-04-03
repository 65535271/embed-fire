/******************************列表 1: 代码清单:RCC-1 设置系统时钟库函数**************************************/
/*
 * 使用 HSE 时，设置系统时钟的步骤
 * 1、开启 HSE ，并等待 HSE 稳定
 * 2、设置 AHB、 APB2、 APB1 的预分频因子
 * 3、设置 PLL 的时钟来源
      设置 VCO 输入时钟 分频因子 m
      设置 VCO 输出时钟 倍频因子 n
      设置 PLLCLK 时钟分频因子   p
      设置 OTG FS,SDIO,RNG 时钟分频因子 q
 * 4、开启 PLL，并等待 PLL 稳定
 * 5、把 PLLCK 切换为系统时钟 SYSCLK
 * 6、读取时钟切换状态位，确保 PLLCLK 被选为系统时钟
 */
/*if defined USE_HSE_BPAS  ————判断使用的是否为有源晶振<本开发板使用的是无源晶振，同等性能时，有源晶振要比无源晶振贵的多> */
#define PLL_M 25
#define PLL_N 360   //如果要超频的话，修改 PLL_N 这个宏即可，取值范围为： 192~432。
#define PLL_P 2
#define PLL_Q 7

void SetSysClock(void)
{
    __IO uint32_t   StartUpCounter = 0, HSEStatus = 0;
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);        //  使能 HSE

    // 等待 HSE 启动稳定
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
    if (HSEStatus == (uint32_t)0x01)    // HSE 启动成功
    {
        // 调压器电压输出级别配置为 1，以便在器件为最大频率
        // 工作时使性能和功耗实现平衡
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_VOS;

        //  设置 AHB/APB2/APB1 的分频因子
        
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;    // HCLK = SYSCLK / 1
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;   // PCLK2 = HCLK / 2
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;   // PCLK1 = HCLK / 4

        //  配置主 PLL 的时钟来源，设置 M,N,P,Q
        // Configure the main PLL
        RCC->PLLCFGR = PLL_M|(PLL_N<<6)|(((PLL_P >> 1) -1) << 16) |(RCC_PLLCFGR_PLLSRC_HSE) |(PLL_Q << 24);

        RCC->CR |= RCC_CR_PLLON;    //  使能主 PLL

        while ((RCC->CR & RCC_CR_PLLRDY) == 0) {}  // 等待 PLL 稳定
        /*----------------------------------------------------*/
        // 开启 OVER-RIDE 模式，以能达到更改频率
        PWR->CR |= PWR_CR_ODEN;
        while ((PWR->CSR & PWR_CSR_ODRDY) == 0) {}
        PWR->CR |= PWR_CR_ODSWEN;
        while ((PWR->CSR & PWR_CSR_ODSWRDY) == 0) {}
        
        // 配置 FLASH 预取指, 指令缓存, 数据缓存和等待状态
        FLASH->ACR = FLASH_ACR_PRFTEN|FLASH_ACR_ICEN|FLASH_ACR_DCEN|FLASH_ACR_LATENCY_5WS;
        /*---------------------------------------------------*/

        //  选择主 PLLCLK 作为系统时钟源
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        //  读取时钟切换状态位，确保 PLLCLK 选为系统时钟
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS )!= RCC_CFGR_SWS_PLL);{}
    } 
    else 
    {
        // HSE 启动出错处理
    }
}

/********************************列表 3: 代码清单:RCC-2 HSE 作为系统时钟来源****************************************/

/*
 * 使用HSI时，设置系统时钟的步骤
 * 1、开启HSI ，并等待 HSI 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源
 *    设置VCO输入时钟 分频因子    m
 *    设置VCO输出时钟 倍频因子    n
 *    设置SYSCLK时钟分频因子      p
 *    设置OTG FS,SDIO,RNG时钟分频因子   q
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/*
 * m: VCO输入时钟 分频因子，取值2~63
 * n: VCO输出时钟 倍频因子，取值192~432
 * p: PLLCLK时钟分频因子  ，取值2，4，6，8
 * q: OTG FS,SDIO,RNG时钟分频因子，取值4~15
 * 函数调用举例，使用HSI设置时钟
 * SYSCLK=HCLK=180M,PCLK2=HCLK/2=90M,PCLK1=HCLK/4=45M
 * HSI_SetSysClock(16, 360, 2, 7);
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 
 * 系统时钟超频到216M爽一下
 * HSI_SetSysClock(16, 432, 2, 9);
 */

void HSI_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q)	
{
  __IO uint32_t HSIStartUpStatus = 0;
  RCC_DeInit();	        // 把RCC外设初始化成复位状态
	RCC_HSICmd(ENABLE);   //使能HSI, HSI=16M
	HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY; // 等待 HSI 就绪
	
  if (HSIStartUpStatus == RCC_CR_HSIRDY)      // 只有 HSI就绪之后则继续往下执行
  {
    // 调压器电压输出级别配置为1，以便在器件为最大频率
		// 工作时使性能和功耗实现平衡
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;
	
		RCC_HCLKConfig(RCC_SYSCLK_Div1);  // HCLK = SYSCLK / 1
		RCC_PCLK2Config(RCC_HCLK_Div2);   // PCLK2 = HCLK / 2
		RCC_PCLK1Config(RCC_HCLK_Div4);	  // PCLK1 = HCLK / 4
		
    // 如果要超频就得在这里下手啦
		// 设置PLL来源时钟，设置VCO分频因子m，设置VCO倍频因子n，
		//  设置系统时钟分频因子p，设置OTG FS,SDIO,RNG分频因子q
		RCC_PLLConfig(RCC_PLLSource_HSI, m, n, p, q);
		RCC_PLLCmd(ENABLE); // 使能PLL
  
	  // 等待 PLL稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }   

    /*-----------------------------------------------------*/
    //开启 OVER-RIDE模式，以能达到更高频率
    PWR->CR |= PWR_CR_ODEN;
    while((PWR->CSR & PWR_CSR_ODRDY) == 0)
    {
    }
    PWR->CR |= PWR_CR_ODSWEN;
    while((PWR->CSR & PWR_CSR_ODSWRDY) == 0)
    {
    }      
    // 配置FLASH预取指,指令缓存,数据缓存和等待状态
    FLASH->ACR = FLASH_ACR_PRFTEN 
		            |FLASH_ACR_ICEN 
		            |FLASH_ACR_DCEN 
		            |FLASH_ACR_LATENCY_5WS;
/*-----------------------------------------------------*/
		
		// 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else    // HSI启动出错处理
  { 
    while (1)
    {
    }
  }
}


/**************************列表 3: 代码清单:RCC-3 使用 HSI 配置系统时钟*****************************/
// MCO1 PA8 GPIO 初始化
void MCO1_GPIO_Config(void)       
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // MCO1 GPIO 配置
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
}

// MCO2 PC9 GPIO 初始化
void MCO2_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // MCO2 GPIO 配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


/***************************列表 5: 代码清单:RCC-5 MCO 输出时钟选择****************************/
RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1); 	// MCO1 输出PLLCLK
RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO1Div_1);	// MCO2 输出SYSCLK


/*****************************列表 6: 代码清单:RCC-6 main 函数***********************************/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	// 程序来到main函数之前，启动文件：statup_stm32f429_439xx.s已经调用
	// SystemInit()函数把系统时钟初始化成72MHZ
	// SystemInit()在system_stm32f4xx.c中定义
	// 如果用户想修改系统时钟，可自行编写程序修改	
	// 重新设置系统时钟，这时候可以选择使用HSE还是HSI
	
	
	/*  注意 ：由于在 PLL 使能后主 PLL 配置参数便不可更改，而系统上电后会
	 *  自动进行初始化，因此在对HES重新初始化之前，需要将system_stm32f4xx.c	  
	 *  中line506：SetSysClock();注释掉,否则HSE重新初始化之后不生效。
	 */
	
	// MCO GPIO  初始化
 	 MCO1_GPIO_Config();
 	 MCO2_GPIO_Config();	

  	RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1); 	// MCO1 输出PLLCLK
	RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO1Div_1);	// MCO2 输出SYSCLK
	
	// 使用HSE，配置系统时钟为180M
	//HSE_SetSysClock(25, 360, 2, 7);
	
	//系统时钟超频到216M爽一下，最高是216M，别往死里整
  	HSE_SetSysClock(25, 432, 2, 9);
	
	// 使用HSI，配置系统时钟为180M
	//HSI_SetSysClock(16, 432, 2, 7);

	LED_GPIO_Config();	// LED 端口初始化 
	
	while (1)
	{
		LED1( ON );			// 亮 
		Delay(0x4FFFFF);
		LED1( OFF );		// 灭
		Delay(0x4FFFFF);
	}
}

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/