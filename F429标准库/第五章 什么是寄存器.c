

/***********列表 1: 代码清单: 寄存器-1 通过绝对地址访问内存单元***********************/
// GPIOH 端口全部输出 高电平
//强制类型转换，把它转换成指针，即 (unsigned int *)0x4002 1C14，然后再对这个指针进行 * 操作
*(unsigned int*)(0x4002 1C14) = 0xFFFF;       


/************列表 2: 代码清单: 寄存器-2 通过寄存器别名方式访问内存单元*****************/
// GPIOH 端口全部输出 高电平
#define GPIOH_ODR (unsigned int*)(GPIOH_BASE+0x14)
* GPIOH_ODR = 0xFF;


/************列表 3: 代码清单: 寄存器-3 通过寄存器别名访问内存单元**********************/
// GPIOH 端口全部输出 高电平
#define GPIOH_ODR *(unsigned int*)(GPIOH_BASE+0x14)
GPIOH_ODR = 0xFF;


/************列表 4: 代码清单: 寄存器-4 总线和外设基址宏定义****************************/
/* 外设基地址 */
#define PERIPH_BASE ((unsigned int)0x40000000)
/* 总线基地址 */
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE (PERIPH_BASE + 0x10000000)

/* GPIO 外设基地址 */
#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE (AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE (AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE (AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00)

/* 寄存器基地址，以 GPIOH 为例 */
#define GPIOH_MODER     (GPIOH_BASE+0x00)
#define GPIOH_OTYPER    (GPIOH_BASE+0x04)
#define GPIOH_OSPEEDR   (GPIOH_BASE+0x08)
#define GPIOH_PUPDR     (GPIOH_BASE+0x0C)
#define GPIOH_IDR       (GPIOH_BASE+0x10)
#define GPIOH_ODR       (GPIOH_BASE+0x14)
#define GPIOH_BSRR      (GPIOH_BASE+0x18)
#define GPIOH_LCKR      (GPIOH_BASE+0x1C)
#define GPIOH_AFRL      (GPIOH_BASE+0x20)
#define GPIOH_AFRH      (GPIOH_BASE+0x24)

**
/******************列表 5: 代码清单: 寄存器-5 使用指针控制 BSRR 寄存器*****************/
/* 控制 GPIOH 引脚 10 输出低电平 (BSRR 寄存器的 BR10 置 1) */
*(unsigned int *)GPIOH_BSRR = (0x01<<(16+10));

/* 控制 GPIOH 引脚 10 输出高电平 (BSRR 寄存器的 BS10 置 1) */
*(unsigned int *)GPIOH_BSRR = 0x01<<10;

unsigned int temp;
/* 控制 GPIOH 端口所有引脚的电平 (读 IDR 寄存器) */
temp = *(unsigned int *)GPIOH_IDR;


/*****************列表 6: 代码清单: 寄存器-6 使用结构体对 GPIO 寄存器组的封装*************/
typedef unsigned int            uint32_t;       /* 无符号 32 位变量 */
typedef unsigned short  int     uint16_t;       /* 无符号 16 位变量 */

/* GPIO 寄存器列表 */
typedef struct 
{
    uint32_t MODER;     /*GPIO 模式寄存器 地址偏移: 0x00 */
    uint32_t OTYPER;    /*GPIO 输出类型寄存器 地址偏移: 0x04 */
    uint32_t OSPEEDR;   /*GPIO 输出速度寄存器 地址偏移: 0x08 */
    uint32_t PUPDR;     /*GPIO 上拉/下拉寄存器 地址偏移: 0x0C */
    uint32_t IDR;       /*GPIO 输入数据寄存器 地址偏移: 0x10 */
    uint32_t ODR;       /*GPIO 输出数据寄存器 地址偏移: 0x14 */
    uint16_t BSRRL;     /*GPIO 置位/复位寄存器低 16 位部分 地址偏移: 0x18 */
    uint16_t BSRRH;     /*GPIO 置位/复位寄存器高 16 位部分 地址偏移: 0x1A */
    uint32_t LCKR;      /*GPIO 配置锁定寄存器 地址偏移: 0x1C */
    uint32_t AFR[2];    /*GPIO 复用功能配置寄存器 地址偏移: 0x20-0x24 */
} GPIO_TypeDef;


/******************列表 7: 代码清单: 寄存器-7 通过结构体指针访问寄存器*******************/
GPIO_TypeDef * GPIOx;          //定义一个 GPIO_TypeDef 型结构体指针 GPIOx
GPIOx = GPIOH_BASE;            //把指针地址设置为宏 GPIOH_BASE 地址
GPIOx->BSRRL    = 0xFFFF;      //通过指针访问并修改 GPIOH_BSRRL 寄存器
GPIOx->MODER    = 0xFFFFFFFF;  //修改 GPIOH_MODER 寄存器
GPIOx->OTYPER   = 0xFFFFFFFF;  //修改 GPIOH_OTYPER 寄存器

uint32_t temp;
8 temp = GPIOx->IDR; //读取 GPIOH_IDR 寄存器的值到变量 temp 中


/******************列表 8: 代码清单: 寄存器-8 定义好 GPIO 端口首地址址针*****************/
/* 使用 GPIO_TypeDef 把地址强制转换成指针 */
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOG ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *) GPIOH_BASE)

/* 使用定义好的宏直接访问 */
/* 访问 GPIOH 端口的寄存器 */
GPIOH->BSRRL    = 0xFFFF;        //通过指针访问并修改 GPIOH_BSRRL 寄存器
GPIOH->MODER    = 0xFFFFFFF;     //修改 GPIOH_MODER 寄存器
GPIOH->OTYPER   = 0xFFFFFFF;     //修改 GPIOH_OTYPER 寄存器

uint32_t temp;
temp = GPIOH->IDR;               //读取 GPIOH_IDR 寄存器的值到变量 temp 中

/* 访问 GPIOA 端口的寄存器 */
GPIOA->BSRRL    = 0xFFFF;        //通过指针访问并修改 GPIOA_BSRRL 寄存器
GPIOA->MODER    = 0xFFFFFFF;     //修改 GPIOA_MODER 寄存器
GPIOA->OTYPER   = 0xFFFFFFF;     //修改 GPIOA_OTYPER 寄存器

uint32_t temp;
temp = GPIOA->IDR;               //读取 GPIOA_IDR 寄存器的值到变量 temp 中


/***************************列表 9: 代码清单: 寄存器-9 对某位清零*******************************/
//定义一个变量 a = 1001 1111 b (二进制数)
unsigned char a = 0x9f;

//对 bit2 清零

a &= ~(1<<2);

//括号中的 1 左移两位， (1<<2) 得二进制数： 0000 0100 b
//按位取反， ~(1<<2) 得 1111 1011 b
//假如 a 中原来的值为二进制数： a = 1001 1111 b
//所得的数与 a 作”位与&”运算， a = (1001 1111 b)&(1111 1011 b),
//经过运算后， a 的值 a=1001 1011 b
// a 的 bit2 位被被零，而其它位不变。



/**********************列表 10: 代码清单: 寄存器-10 对某几个连续位清零****************************/
//若把 a 中的二进制位分成 2 个一组
//即 bit0、 bit1 为第 0 组， bit2、 bit3 为第 1 组，
// bit4、 bit5 为第 2 组， bit6、 bit7 为第 3 组
//要对第 1 组的 bit2、 bit3 清零

a &= ~(3<<2*1);

//括号中的 3 左移两位， (3<<2*1) 得二进制数： 0000 1100 b
//按位取反， ~(3<<2*1) 得 1111 0011 b
//假如 a 中原来的值为二进制数： a = 1001 1111 b
//所得的数与 a 作”位与&”运算， a = (1001 1111 b)&(1111 0011 b),
//经过运算后， a 的值 a=1001 0011 b
// a 的第 1 组的 bit2、 bit3 被清零，而其它位不变。

//上述 (~(3<<2*1)) 中的 (1) 即为组编号; 如清零第 3 组 bit6、 bit7 此处应为 3
//括号中的 (2) 为每组的位数，每组有 2 个二进制位; 若分成 4 个一组，此处即为 4
//括号中的 (3) 是组内所有位都为 1 时的值; 若分成 4 个一组，此处即为二进制数“1111 b”

//例如对第 2 组 bit4、 bit5 清零
a &= ~(3<<2*2);


/****************************列表 11: 代码清单: 寄存器-11 对某几位进行赋值*********************************/
//a = 1000 0011 b
//此时对清零后的第 2 组 bit4、 bit5 设置成二进制数“01 b ”

a |= (1<<2*2);      //a = 1001 0011 b，成功设置了第 2 组的值，其它组不变



/*********************列表 12: 代码清单: 寄存器-12 对某位进行取反操作***************************/
//a = 1001 0011 b
//把 bit6 取反，其它位不变

a ^=(1<<6);         //a = 1101 0011 b