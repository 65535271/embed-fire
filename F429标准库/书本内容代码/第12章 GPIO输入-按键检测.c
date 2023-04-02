/********************列表 1: 代码清单:GPIO 输入-1 按键检测引脚相关的宏**********************/
//引脚定义
/*******************************************************/
#define KEY1_PIN                  GPIO_Pin_0                 
#define KEY1_GPIO_PORT            GPIOA                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define KEY2_PIN                  GPIO_Pin_13                 
#define KEY2_GPIO_PORT            GPIOC                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOC
/*******************************************************/


/********************列表 2: 代码清单:GPIO 输入-2 按键 GPIO 初始化函数**********************/
/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);   /*开启按键GPIO口的时钟*/
	
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;         /*选择按键的引脚*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;     /*设置引脚为输入模式*/
 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; /*设置引脚不上拉也不下拉*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);  /*使用上面的结构体初始化按键*/
  
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;          /*选择按键的引脚*/
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);  /*使用上面的结构体初始化按键*/
}


/********************列表 3: 代码清单:GPIO 输入-3 检测按键的状态**********************/
/**
  * @brief  检测是否有按键按下     
  *	@param 	GPIOx:具体的端口, x可以是（A...K） 
	*	@param 	GPIO_PIN:具体的端口位， 可以是GPIO_PIN_x（x可以是0...15）
  * @retval 按键的状态
  *		@arg KEY_ON:按键按下
  *		@arg KEY_OFF:按键没按下
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
    {	 
      /*等待按键释放 */
      while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
      return 	KEY_ON;	 
    }
	else
		return KEY_OFF;
}
/*********************************************END OF FILE**********************/


/********************列表 4: 代码清单:GPIO 输入-4 按键检测主函数**********************/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	LED_GPIO_Config();	 	/* LED 端口初始化 */
  Key_GPIO_Config();    /*初始化按键*/
	
	/* 轮询按键状态，若按键按下则反转LED */ 
	while(1)                            
	{	   
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			LED1_TOGGLE;  /*LED1反转*/
		}   
    
    if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
		{
			LED2_TOGGLE;  /*LED2反转*/
		}   
	}
}