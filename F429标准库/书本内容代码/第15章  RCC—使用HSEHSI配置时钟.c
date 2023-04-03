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