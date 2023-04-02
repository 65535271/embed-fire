/*******************列表 1: 代码清单: 构建库-1 封装寄存器列表************************/
//volatile 表示易变的变量，防止编译器优化
#define __IO volatile
typedef unsigned int    uint32_t;
typedef unsigned short  uint16_t;

/* GPIO 寄存器列表 */
typedef struct 
{
    __IO uint32_t MODER;    /*GPIO 模式寄存器       地址偏移: 0x00 */
    __IO uint32_t OTYPER;   /*GPIO 输出类型寄存器   地址偏移: 0x04 */
    __IO uint32_t OSPEEDR;  /*GPIO 输出速度寄存器   地址偏移: 0x08 */
    __IO uint32_t PUPDR;    /*GPIO 上拉/下拉寄存器  地址偏移: 0x0C */
    __IO uint32_t IDR;      /*GPIO 输入数据寄存器   地址偏移: 0x10 */
    __IO uint32_t ODR;      /*GPIO 输出数据寄存器   地址偏移: 0x14 */
    __IO uint16_t BSRRL;    /*GPIO 置位/复位寄存器  低 16 位部分 地址偏移: 0x18 */
    __IO uint16_t BSRRH;    /*GPIO 置位/复位寄存器  高 16 位部分地址偏移: 0x1A */
    __IO uint32_t LCKR;     /*GPIO 配置锁定寄存器   地址偏移: 0x1C */
    __IO uint32_t AFR[2];   /*GPIO 复用功能配置寄存器   地址偏移: 0x20-0x24 */
} GPIO_TypeDef;

/*RCC 寄存器列表 */
typedef struct 
{
    __IO uint32_t CR;       /*!< RCC 时钟控制寄存器, 地址偏移: 0x00 */
    __IO uint32_t PLLCFGR;  /*!< RCC PLL 配置寄存器, 地址偏移: 0x04 */
    __IO uint32_t CFGR;     /*!< RCC 时钟配置寄存器, 地址偏移: 0x08 */
    __IO uint32_t CIR;      /*!< RCC 时钟中断寄存器, 地址偏移: 0x0C */
    __IO uint32_t AHB1RSTR;     /*!< RCC AHB1 外设复位寄存器, 地址偏移: 0x10 */
    __IO uint32_t AHB2RSTR;     /*!< RCC AHB2 外设复位寄存器, 地址偏移: 0x14 */
    __IO uint32_t AHB3RSTR;     /*!< RCC AHB3 外设复位寄存器, 地址偏移: 0x18 */
    __IO uint32_t RESERVED0;     /*!< 保留, 地址偏移： 0x1C */
    __IO uint32_t APB1RSTR;     /*!< RCC APB1 外设复位寄存器, 地址偏移: 0x20 */
    __IO uint32_t APB2RSTR;     /*!< RCC APB2 外设复位寄存器, 地址偏移: 0x24*/
    __IO uint32_t RESERVED1[2]; /*!< 保留, 地址偏移： 0x28-0x2C*/
    __IO uint32_t AHB1ENR;      /*!< RCC AHB1 外设时钟寄存器, 地址偏移: 0x30 */
    __IO uint32_t AHB2ENR;      /*!< RCC AHB2 外设时钟寄存器, 地址偏移: 0x34 */
    __IO uint32_t AHB3ENR;      /*!< RCC AHB3 外设时钟寄存器, 地址偏移: 0x38 */
    /*RCC 后面还有很多寄存器，此处省略 */
} RCC_TypeDef;


/*******************列表 2: 代码清单: 构建库-2 指向外设首地址的结构体指针***************/
/* 定义 GPIOA-H 寄存器结构体指针 */
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *) GPIOH_BASE)
/* 定义 RCC 外设 寄存器结构体指针 */
#define RCC ((RCC_TypeDef *) RCC_BASE)


/******************列表 3: 代码清单: 构建库-3 使用结构体指针方式控制LED 灯******************/
/**
* 主函数
*/
int main(void)
{
    RCC->AHB1ENR |= (1<<7);

    /**** LED 端口初始化 ****/

    GPIOH->MODER &= ~( 0x03<< (2*10));    /*GPIOH MODER10 清空 */
    GPIOH->MODER |= (1<<2*10);            /*PH10 MODER10 = 01b 输出模式 */

    GPIOH->OTYPER &= ~(1<<1*10);   /*GPIOH OTYPER10 清空 */
    GPIOH->OTYPER |= (0<<1*10);    /*PH10 OTYPER10 = 0b 推挽模式 */

   
    GPIOH->OSPEEDR &= ~(0x03<<2*10); /*GPIOH OSPEEDR10 清空 */
    GPIOH->OSPEEDR |= (0<<2*10);     /*PH10 OSPEEDR10 = 0b 速率 2MHz*/

   
    GPIOH->PUPDR &= ~(0x03<<2*10);  /*GPIOH PUPDR10 清空 */
    GPIOH->PUPDR |= (1<<2*10);      /*PH10 PUPDR10 = 01b 上拉模式 */
    GPIOH->BSRRH |= (1<<10);        /*PH10 BSRR 寄存器的 BR10 置 1，使引脚输出低电平 */

    /*PH10 BSRR 寄存器的 BS10 置 1，使引脚输出高电平 */
    //GPIOH->BSRRL |= (1<<10);

    while (1);
}


/*******************列表 4: 代码清单: 构建库-4 GPIO 置位函数与复位函数的定义********************/
/**
 * 函数功能：设置引脚为高电平
 * 参数说明： GPIOx: 该参数为 GPIO_TypeDef 类型的指针，指向 GPIO 端口的地址
 * GPIO_Pin: 选择要设置的 GPIO 端口引脚，可输入宏 GPIO_Pin_0-15，
 * 表示 GPIOx 端口的 0-15 号引脚。
 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* 设置 GPIOx 端口 BSRRL 寄存器的第 GPIO_Pin 位，使其输出高电平 */
    /* 因为 BSRR 寄存器写 0 不影响，
        宏 GPIO_Pin 只是对应位为 1，其它位均为 0，所以可以直接赋值 */

    GPIOx->BSRRL = GPIO_Pin;
}
/**
 * 函数功能：设置引脚为低电平
 * 参数说明： GPIOx: 该参数为 GPIO_TypeDef 类型的指针，指向 GPIO 端口的地址
 * GPIO_Pin: 选择要设置的 GPIO 端口引脚，可输入宏 GPIO_Pin_0-15，
 * 表示 GPIOx 端口的 0-15 号引脚。
 */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
/* 设置 GPIOx 端口 BSRRH 寄存器的第 GPIO_Pin 位, 使其输出低电平 */
/* 因为 BSRR 寄存器写 0 不影响，
 宏 GPIO_Pin 只是对应位为 1，其它位均为 0，所以可以直接赋值 */

    GPIOx->BSRRH = GPIO_Pin;
}


/**********************列表 5: 代码清单: 构建库-5 赋值方式对比**********************/

GPIOH->BSRRH |= (1<<10);    /* 使用 “|=” 来赋值 */
GPIOx->BSRRH = GPIO_Pin;    /* 直接使用 "=" 号赋值 */


/**********************列表 6: 代码清单: 构建库-6 BSRR 寄存器赋值等效代码************/

GPIOH->BSRRH |= (uint16_t)(1<<10);  /* 使用 “|=” 来赋值 */
GPIOH->BSRRH = (uint16_t)(1<<10);   /* 直接使用“=” 来赋值，二进制数 (0000 0100 0000 0000)*/

/**********************列表 7: 代码清单: 构建库-7 位操作函数使用范例*******************/

GPIO_SetBits(GPIOH,(uint16_t)(1<<10));      /* 控制 GPIOH 的引脚 10 输出高电平 */
GPIO_ResetBits(GPIOH,(uint16_t)(1<<10));    /* 控制 GPIOH 的引脚 10 输出低电平 */

GPIO_SetBits(GPIOH,(uint16_t)(1<<10)|(uint16_t)(1<<11));    /* 控制 GPIOH 的引脚 10、引脚 11 输出高电平，使用“|”同时控制多个引脚 */
GPIO_ResetBits(GPIOH,(uint16_t)(1<<10)|(uint16_t)(1<<10));  /* 控制 GPIOH 的引脚 10、引脚 11 输出低电平 */


GPIO_SetBits(GPIOA,(uint16_t)(1<<8));   /* 控制 GPIOA 的引脚 8 输出高电平 */
GPIO_ResetBits(GPIOB,(uint16_t)(1<<9)); /* 控制 GPIOB 的引脚 9 输出低电平 */


/*********************列表 8: 代码清单: 构建库-8 选择引脚参数的宏***********************/
/*GPIO 引脚号定义 */
#define GPIO_Pin_0  ((uint16_t)0x0001)/*!< 选择 Pin0 (1<<0) */
#define GPIO_Pin_1  ((uint16_t)0x0002) /*!< 选择 Pin1 (1<<1)*/
#define GPIO_Pin_2  ((uint16_t)0x0004) /*!< 选择 Pin2 (1<<2)*/
#define GPIO_Pin_3  ((uint16_t)0x0008) /*!< 选择 Pin3 (1<<3)*/
#define GPIO_Pin_4  ((uint16_t)0x0010) /*!< 选择 Pin4 */
#define GPIO_Pin_5  ((uint16_t)0x0020) /*!< 选择 Pin5 */
#define GPIO_Pin_6  ((uint16_t)0x0040) /*!< 选择 Pin6 */
#define GPIO_Pin_7  ((uint16_t)0x0080) /*!< 选择 Pin7 */
#define GPIO_Pin_8  ((uint16_t)0x0100) /*!< 选择 Pin8 */
#define GPIO_Pin_9  ((uint16_t)0x0200) /*!< 选择 Pin9 */
#define GPIO_Pin_10 ((uint16_t)0x0400) /*!< 选择 Pin10 */
#define GPIO_Pin_11 ((uint16_t)0x0800) /*!< 选择 Pin11 */
#define GPIO_Pin_12 ((uint16_t)0x1000) /*!< 选择 Pin12 */
#define GPIO_Pin_13 ((uint16_t)0x2000) /*!< 选择 Pin13 */
#define GPIO_Pin_14 ((uint16_t)0x4000) /*!< 选择 Pin14 */
#define GPIO_Pin_15 ((uint16_t)0x8000) /*!< 选择 Pin15 */
#define GPIO_Pin_All ((uint16_t)0xFFFF) /*!< 选择全部引脚 */


/**********************列表 9: 代码清单: 构建库-9 使用位操作函数及宏控制GPIO***********************/

GPIO_SetBits(GPIOH,GPIO_Pin_10);        /* 控制 GPIOH 的引脚 10 输出高电平 */
GPIO_ResetBits(GPIOH,GPIO_Pin_10);      /* 控制 GPIOH 的引脚 10 输出低电平 */

GPIO_SetBits(GPIOH,GPIO_Pin_10|GPIO_Pin_11);        /* 控制 GPIOH 的引脚 10、引脚 11 输出高电平，使用“|”，同时控制多个引脚 */
GPIO_ResetBits(GPIOH,GPIO_Pin_10|GPIO_Pin_11);      /* 控制 GPIOH 的引脚 10、引脚 11 输出低电平 */
GPIO_ResetBits(GPIOH,GPIO_Pin_ALL);     /* 控制 GPIOH 的所有输出低电平 */
GPIO_SetBits(GPIOA,GPIO_Pin_8);         /* 控制 GPIOA 的引脚 8 输出高电平 */
GPIO_ResetBits(GPIOB,GPIO_Pin_9);       /* 控制 GPIOB 的引脚 9 输出低电平 */


/*******************列表 10: 代码清单: 构建库-10 定义 GPIO 初始化结构体**********************/
typedef uint8_t unsigned char;
/**
 * GPIO 初始化结构体类型定义
 */
typedef struct 
{
    uint32_t GPIO_Pin;   /*!< 选择要配置的 GPIO 引脚可输入 GPIO_Pin_ 定义的宏 */
    uint8_t  GPIO_Mode;  /*!< 选择 GPIO 引脚的工作模式可输入二进制值：00 、 01、 10、 11表示输入/输出/复用/模拟 */
    uint8_t  GPIO_Speed; /*!< 选择 GPIO 引脚的速率可输入二进制值：   00 、 01、 10、 11表示 2/25/50/100MHz */
    uint8_t  GPIO_OType; /*!< 选择 GPIO 引脚输出类型可输入二进制值：  0 、 1  表示推挽/开漏 */
    uint8_t  GPIO_PuPd;  /*!< 选择 GPIO 引脚的上/下拉模式可输入二进制值:00 、 01、 10  表示浮空/上拉/下拉 */
} GPIO_InitTypeDef;


/***********************列表 11: 代码清单: 构建库-11 GPIO 配置参数的枚举定义************************/
/**
 * GPIO 端口配置模式的枚举定义
 */
typedef enum 
{
    GPIO_Mode_IN  = 0x00,   /*!< 输入模式 */
    GPIO_Mode_OUT = 0x01,   /*!< 输出模式 */
    GPIO_Mode_AF  = 0x02,   /*!< 复用模式 */
    GPIO_Mode_AN  = 0x03    /*!< 模拟模式 */
} GPIOMode_TypeDef;

/**
 * GPIO 输出类型枚举定义
 */
typedef enum 
{
    GPIO_OType_PP = 0x00,   /*!< 推挽模式 */
    GPIO_OType_OD = 0x01    /*!< 开漏模式 */
} GPIOOType_TypeDef;

/**
 * GPIO 输出速率枚举定义
 */
typedef enum
{
    GPIO_Speed_2MHz   = 0x00, /*!< 2MHz  */
    GPIO_Speed_25MHz  = 0x01, /*!< 25MHz */
    GPIO_Speed_50MHz  = 0x02, /*!< 50MHz */
    GPIO_Speed_100MHz = 0x03  /*!<100MHz */
} GPIOSpeed_TypeDef;

/**
 *GPIO 上/下拉配置枚举定义
 */
typedef enum 
{
    GPIO_PuPd_NOPULL = 0x00,    /* 浮空 */
    GPIO_PuPd_UP     = 0x01,    /* 上拉 */
    GPIO_PuPd_DOWN   = 0x02     /* 下拉 */
} GPIOPuPd_TypeDef;


/************列表 12: 代码清单: 构建库-12 使用枚举类型定义的GPIO_InitTypeDef 结构体成员**********/
/**
 * GPIO 初始化结构体类型定义
 */
typedef struct 
{
    uint32_t GPIO_Pin;     /*!< 选择要配置的 GPIO 引脚可输入 GPIO_Pin_ 定义的宏 */
    GPIOMode_TypeDef    GPIO_Mode;    /*!< 选择 GPIO 引脚的工作模式可输入 GPIOMode_TypeDef 定义的枚举值 */
    GPIOSpeed_TypeDef   GPIO_Speed;   /*!< 选择 GPIO 引脚的速率可输入 GPIOSpeed_TypeDef 定义的枚举值 */
    GPIOOType_TypeDef   GPIO_OType;   /*!< 选择 GPIO 引脚输出类型可输入 GPIOOType_TypeDef 定义的枚举值 */
    GPIOPuPd_TypeDef    GPIO_PuPd;    /*!< 选择 GPIO 引脚的上/下拉模式可输入 GPIOPuPd_TypeDef 定义的枚举值 */
} GPIO_InitTypeDef;


/**************列表 13: 代码清单: 构建库-13 给 GPIO_InitTypeDef 初始化结构体赋值范例*********************/
GPIO_InitTypeDef InitStruct;
/* LED 端口初始化 */
InitStruct.GPIO_Pin     = GPIO_Pin_10;      /* 选择要控制的 GPIO 引脚 */
InitStruct.GPIO_Mode    = GPIO_Mode_OUT;    /* 设置引脚模式为输出模式 */
InitStruct.GPIO_OType   = GPIO_OType_PP;    /* 设置引脚的输出类型为推挽输出 */
InitStruct.GPIO_PuPd    = GPIO_PuPd_UP;     /* 设置引脚为上拉模式 */
InitStruct.GPIO_Speed   = GPIO_Speed_2MHz;  /* 设置引脚速率为 2MHz */



/********************列表 14: 代码清单: 构建库-14 GPIO 初始化函数************************/
/**
 * 函数功能：初始化引脚模式
 * 参数说明： GPIOx，该参数为 GPIO_TypeDef 类型的指针，指向 GPIO 端口的地址
 * GPIO_InitTypeDef:GPIO_InitTypeDef 结构体指针，指向初始化变量
 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
    /*-- GPIO Mode Configuration --*/
    for (pinpos = 0x00; pinpos < 16; pinpos++) 
    {
        /* 以下运算是为了通过 GPIO_InitStruct->GPIO_Pin 算出引脚号 0-15*/
        /* 经过运算后 pos 的 pinpos 位为 1，其余为 0，与 GPIO_Pin_x 宏对应。
        pinpos 变量每次循环加 1， */
        pos = ((uint32_t)0x01) << pinpos;
        /* pos 与 GPIO_InitStruct->GPIO_Pin 做 & 运算， 若运算结果 currentpin == pos，
        则表示 GPIO_InitStruct->GPIO_Pin 的 pinpos 位也为 1，
        从而可知 pinpos 就是 GPIO_InitStruct->GPIO_Pin 对应的引脚号： 0-15*/
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        /*currentpin == pos 时执行初始化 */
        if (currentpin == pos) 
        {
            /*GPIOx 端口， MODER 寄存器的 GPIO_InitStruct->GPIO_Pin 对应的引脚，MODER 位清空 */
            GPIOx->MODER &= ~(3 << (2 *pinpos));

            /*GPIOx 端口， MODER 寄存器的 GPIO_Pin 引脚，
            MODER 位设置" 输入/输出/复用输出/模拟" 模式 */
            GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (2 *pinpos));

            /*GPIOx 端口， PUPDR 寄存器的 GPIO_Pin 引脚，PUPDR 位清空 */
            GPIOx->PUPDR &= ~(3 << ((2 *pinpos)));

            /*GPIOx 端口， PUPDR 寄存器的 GPIO_Pin 引脚，
            PUPDR 位设置" 上/下拉" 模式 */
            GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (2 *pinpos));

            /* 若模式为" 输出/复用输出" 模式，则设置速度与输出类型 */
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) ||(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)) 
            {
                /*GPIOx 端口， OSPEEDR 寄存器的 GPIO_Pin 引脚，OSPEEDR 位清空 */
                GPIOx->OSPEEDR &= ~(3 << (2 *pinpos));
                /*GPIOx 端口， OSPEEDR 寄存器的 GPIO_Pin 引脚，OSPEEDR 位设置输出速度 */
                GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed)<<(2 *pinpos));

                /*GPIOx 端口， OTYPER 寄存器的 GPIO_Pin 引脚，OTYPER 位清空 */
                GPIOx->OTYPER &= ~(1 << (pinpos)) ;
                /*GPIOx 端口， OTYPER 位寄存器的 GPIO_Pin 引脚，OTYPER 位设置" 推挽/开漏" 输出类型 */
                GPIOx->OTYPER |= (uint16_t)(( GPIO_InitStruct->GPIO_OType)<< (pinpos));
            }
        }
    }   
}



/***********************列表 15: 代码清单: 构建库-15 使用函数点亮 LED 灯****************************/
/*
    使用寄存器的方法点亮 LED 灯
 */
#include "stm32f4xx_gpio.h"

void Delay( uint32_t nCount);

/**
 * 主函数，使用封装好的函数来控制 LED 灯
 */
int main(void)
{
    GPIO_InitTypeDef InitStruct;
    /* 开启 GPIOH 时钟，使用外设时都要先开启它的时钟 */
    RCC->AHB1ENR |= (1<<7);

    /* LED 端口初始化,初始化 PH10 引脚 */
    
    InitStruct.GPIO_Pin   = GPIO_Pin_10;     /* 选择要控制的 GPIO 引脚 */
    InitStruct.GPIO_Mode  = GPIO_Mode_OUT;   /* 设置引脚模式为输出模式 */
    InitStruct.GPIO_OType = GPIO_OType_PP;   /* 设置引脚的输出类型为推挽输出 */
    InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;    /* 设置引脚为上拉模式 */
    InitStruct.GPIO_Speed = GPIO_Speed_2MHz; /* 设置引脚速率为 2MHz */
    GPIO_Init(GPIOH, &InitStruct);           /* 调用库函数，使用上面配置的 GPIO_InitStructure 初始化 GPIO*/


    GPIO_ResetBits(GPIOH,GPIO_Pin_10);  /* 使引脚输出低电平, 点亮 LED1*/
    Delay(0xFFFFFF);    /* 延时一段时间 */
    
    GPIO_SetBits(GPIOH,GPIO_Pin_10);    /* 使引脚输出高电平，关闭 LED1*/

    /* 初始化 PH11 引脚 */
    InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOH,&InitStruct);
  
    GPIO_ResetBits(GPIOH,GPIO_Pin_11);  /* 使引脚输出低电平，点亮 LED2*/
   
    while (1);

}

//简单的延时函数，让 cpu 执行无意义指令，消耗时间
//具体延时时间难以计算，以后我们可使用定时器精确延时
void Delay( uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

// 函数为空，目的是为了骗过编译器不报错
void SystemInit(void)
{
}