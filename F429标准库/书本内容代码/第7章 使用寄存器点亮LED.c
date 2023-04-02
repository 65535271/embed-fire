/******************列表 1: 代码清单: 点亮 LED-1 复位后执行的程序*********************/
;Reset handler
Reset_Handler PROC
EXPORT Reset_Handler [WEAK]
IMPORT SystemInit
IMPORT __main

LDR R0, =SystemInit
BLX R0
LDR R0, =__main
BX R0
ENDP


/*********************************列表 2: 代码清单: 点亮 LED-2 外设地址定义**********************************/
/* 片上外设基地址 */
#define PERIPH_BASE     ((unsigned int)0x40000000)
/* 总线基地址 */
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000)
/*GPIO 外设基地址 */
#define GPIOH_BASE      (AHB1PERIPH_BASE + 0x1C00)

/* GPIOH 寄存器地址, 强制转换成指针 */
#define GPIOH_MODER     *(unsigned int*)(GPIOH_BASE+0x00)
#define GPIOH_OTYPER    *(unsigned int*)(GPIOH_BASE+0x04)
#define GPIOH_OSPEEDR   *(unsigned int*)(GPIOH_BASE+0x08)
#define GPIOH_PUPDR     *(unsigned int*)(GPIOH_BASE+0x0C)
#define GPIOH_IDR       *(unsigned int*)(GPIOH_BASE+0x10)
#define GPIOH_ODR       *(unsigned int*)(GPIOH_BASE+0x14)
#define GPIOH_BSRR      *(unsigned int*)(GPIOH_BASE+0x18)
#define GPIOH_LCKR      *(unsigned int*)(GPIOH_BASE+0x1C)
#define GPIOH_AFRL      *(unsigned int*)(GPIOH_BASE+0x20)
#define GPIOH_AFRH      *(unsigned int*)(GPIOH_BASE+0x24)

/*RCC 外设基地址 */
#define RCC_BASE        (AHB1PERIPH_BASE + 0x3800)
/*RCC 的 AHB1 时钟使能寄存器地址, 强制转换成指针 */
#define RCC_AHB1ENR     *(unsigned int*)(RCC_BASE+0x30)

int main (void)
{ 

}

// 函数为空，目的是为了骗过编译器不报错
void SystemInit(void)
{ 

}



/********************表 4: 代码清单: 点亮 LED-4 配置输出模式********************/
/*GPIOH MODER10 清空 */
GPIOH_MODER &= ~( 0x03<< (2*10));
/*PH10 MODER10 = 01b 输出模式 */
GPIOH_MODER |= (1<<2*10);


/*******************列表 5: 代码清单: 点亮 LED-5 设置为推挽模式*****************/
/*GPIOH OTYPER10 清空 */
GPIOH_OTYPER &= ~(1<<1*10);
/*PH10 OTYPER10 = 0b 推挽模式 */
GPIOH_OTYPER |= (0<<1*10);


/*******************列表 6: 代码清单: 点亮 LED-6 设置输出速度为 2MHz*************/
/*GPIOH OSPEEDR10 清空 */
GPIOH_OSPEEDR &= ~(0x03<<2*10);
/*PH10 OSPEEDR10 = 0b 速率 2MHz*/
GPIOH_OSPEEDR |= (0<<2*10);


/*******************列表 7: 代码清单: 点亮 LED-7 设置为下拉模式******************/
/*GPIOH PUPDR10 清空 */
GPIOH_PUPDR &= ~(0x03<<2*10);
/*PH10 PUPDR10 = 01b 下拉模式 */
GPIOH_PUPDR |= (1<<2*10);


/*******************列表 8: 代码清单: 点亮 LED-8 控制引脚输出电平****************/
/*PH10 BSRR 寄存器的 BR10 置 1，使引脚输出低电平 */
GPIOH_BSRR |= (1<<16<<10);

/*PH10 BSRR 寄存器的 BS10 置 1，使引脚输出高电平 */
GPIOH_BSRR |= (1<<10);


/*******************列表 9: 代码清单: 点亮 LED-9 开启端口时钟*********************/
/* 开启 GPIOH 时钟，使用外设时都要先开启它的时钟 */
RCC_AHB1ENR |= (1<<7);


/*******************列表 10: 代码清单: 点亮 LED-10 main 文件中控制 LED灯的代码*****/
/*
    使用寄存器的方法点亮 LED 灯
*/
#include "stm32f4xx.h"

/**
 * 主函数
*/
int main(void)
{
    /* 开启 GPIOH 时钟，使用外设时都要先开启它的时钟 */
    RCC_AHB1ENR |= (1<<7);

    /* LED 端口初始化 */

    /*GPIOH MODER10 清空 */
    GPIOH_MODER &= ~( 0x03<< (2*10));
    /*PH10 MODER10 = 01b 输出模式 */
    GPIOH_MODER |= (1<<2*10);

    /*GPIOH OTYPER10 清空 */
    GPIOH_OTYPER &= ~(1<<1*10);
    /*PH10 OTYPER10 = 0b 推挽模式 */
    GPIOH_OTYPER |= (0<<1*10);

    /*GPIOH OSPEEDR10 清空 */
    GPIOH_OSPEEDR &= ~(0x03<<2*10);
    /*PH10 OSPEEDR10 = 0b 速率 2MHz*/
    GPIOH_OSPEEDR |= (0<<2*10);

    /*GPIOH PUPDR10 清空 */
    GPIOH_PUPDR &= ~(0x03<<2*10);
    /*PH10 PUPDR10 = 01b 上拉模式 */
    GPIOH_PUPDR |= (1<<2*10);

    /*PH10 BSRR 寄存器的 BR10 置 1，使引脚输出低电平 */
    GPIOH_BSRR |= (1<<16<<10);

    /*PH10 BSRR 寄存器的 BS10 置 1，使引脚输出高电平 */
    //GPIOH_BSRR |= (1<<10);

    while (1);

}

// 函数为空，目的是为了骗过编译器不报错
void SystemInit(void)
{
}