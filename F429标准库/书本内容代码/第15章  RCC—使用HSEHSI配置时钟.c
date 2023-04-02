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