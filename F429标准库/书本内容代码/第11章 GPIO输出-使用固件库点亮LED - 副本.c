/***************列表 1: 代码清单:GPIO 输出-1 LED 控制引脚相关的宏****************/
//引脚定义
/*******************************************************/
//R 红色灯
#define LED1_PIN           GPIO_Pin_10                 
#define LED1_GPIO_PORT     GPIOH                      
#define LED1_GPIO_CLK      RCC_AHB1Periph_GPIOH

//G 绿色灯
#define LED2_PIN           GPIO_Pin_11                 
#define LED2_GPIO_PORT     GPIOH                      
#define LED2_GPIO_CLK      RCC_AHB1Periph_GPIOH

//B 蓝色灯
#define LED3_PIN           GPIO_Pin_12                 
#define LED3_GPIO_PORT     GPIOH                       
#define LED3_GPIO_CLK      RCC_AHB1Periph_GPIOH
/************************************************************/

/**************列表 2: 代码清单:GPIO 输出-2 控制 LED 亮灭的宏************************/
/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
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


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		{p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)		{p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	{p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF		digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON			digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF		digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON			digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF		digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON			digitalLo(LED3_GPIO_PORT,LED3_PIN)

/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  	\
					LED1_ON;	\
					LED2_OFF;	\
					LED3_OFF

//绿
#define LED_GREEN	\
					LED1_OFF;	\
					LED2_ON;	\
					LED3_OFF
//蓝
#define LED_BLUE	\
					LED1_OFF;	\
					LED2_OFF;	\
					LED3_ON
//黄(红+绿)					
#define LED_YELLOW	\
					LED1_ON;	\
					LED2_ON;	\
					LED3_OFF
//紫(红+蓝)
#define LED_PURPLE	\
					LED1_ON;	\
					LED2_OFF;	\
					LED3_ON
//青(绿+蓝)
#define LED_CYAN 	\
					LED1_OFF;	\
					LED2_ON;	\
					LED3_ON				
//白(红+绿+蓝)
#define LED_WHITE	\
					LED1_ON;	\
					LED2_ON;	\
					LED3_ON			
//黑(全部关闭)
#define LED_RGBOFF	\
					LED1_OFF;	\
					LED2_OFF;	\
					LED3_OFF		


/********************列表 3: 代码清单:GPIO 输出-3 LED GPIO 初始化函数***********************/
 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;		/*定义一个GPIO_InitTypeDef类型的结构体*/

		/*开启LED相关的GPIO外设时钟*/
		RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK|LED2_GPIO_CLK|LED3_GPIO_CLK, ENABLE); 
														   
		GPIO_InitStructure.GPIO_Pin = LED1_PIN;	        /*选择要控制的GPIO引脚*/

		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   /*设置引脚模式为输出模式*/
   		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   /*设置引脚的输出类型为推挽输出*/
    	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;    /*设置引脚为上拉模式*/
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; /*设置引脚速率为2MHz */

		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	 /*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/	
    
    	/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
    	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);	
    
    	/*选择要控制的GPIO引脚*/															   
		GPIO_InitStructure.GPIO_Pin = LED3_PIN;	
    	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	
		
		LED_RGBOFF;		/*关闭RGB灯*/
}
/*********************************************END OF FILE**********************/


/*****************列表 4: 代码清单:GPIO 输出-4 控制 LED 灯， main 文件****************/
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 控制LED灯 */
	while (1)
	{
		LED1( ON );			// 亮 
		Delay(0xFFFFFF);
		LED1( OFF );		// 灭

		LED2( ON );			// 亮 
		Delay(0xFFFFFF);
		LED2( OFF );		// 灭

		LED3( ON );			// 亮 
		Delay(0xFFFFFF);
		LED3( OFF );		// 灭	

		/*轮流显示 红绿蓝黄紫青白 颜色*/
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

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/


/*************列表 5: 代码清单:GPIO 输出-5 GPIO_Init 函数的断言部分，
 * 基本上每个库函数的开头都会有这样类似的内容，
 * 这里的“assert_param”实际是一个宏，在库函数中它用于检查输入参数是否符合要求，若不符合要求则执行某个函数输出警告，
 * “assert_param”的定义见代码清单:GPIO 输出-6 。*****************
 * */
#ifdef USE_FULL_ASSERT
	/**
	 * @brief assert_param 宏用于函数的输入参数检查
	 * @param expr: 若 expr 值为假，则调用 assert_failed 函数
	 * 报告文件名及错误行号
	 * 若 expr 值为真，则不执行操作
	 */
	#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
	/* 错误输出函数 ------------------------------------------------------- */
	void assert_failed(uint8_t* file, uint32_t line);
#else
	#define assert_param(expr) ((void)0)
#endif


/********************列表 7: 代码清单:GPIO 输出-7 assert_failed 输出错误信息**********************/
void assert_failed(uint8_t* file, uint32_t line)
{
	printf(“\r\n 输入参数错误，错误文件名 =%s, 行号 =%s” ,file,line);
}
#define IS_GPIO_PIN(PIN) ((PIN) != (uint32_t)0x00)


/********************列表 8: 代码清单:GPIO 输出-8 Doxygen 注释规范*******************************/
/**
 * @brief 初始化控制 LED 的 IO
 * @param 无
 * @retval 无
 */


/********************列表 9: 代码清单:GPIO 输出-9 防止头文件重复包含的宏**************************/
#ifndef __LED_H
#define __LED_H

/* 此处省略头文件的具体内容 */

#endif /* end of __LED_H */