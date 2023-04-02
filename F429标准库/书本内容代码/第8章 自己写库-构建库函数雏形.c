/*******************�б� 1: �����嵥: ������-1 ��װ�Ĵ����б�************************/
//volatile ��ʾ�ױ�ı�������ֹ�������Ż�
#define __IO volatile
typedef unsigned int    uint32_t;
typedef unsigned short  uint16_t;

/* GPIO �Ĵ����б� */
typedef struct 
{
    __IO uint32_t MODER;    /*GPIO ģʽ�Ĵ���       ��ַƫ��: 0x00 */
    __IO uint32_t OTYPER;   /*GPIO ������ͼĴ���   ��ַƫ��: 0x04 */
    __IO uint32_t OSPEEDR;  /*GPIO ����ٶȼĴ���   ��ַƫ��: 0x08 */
    __IO uint32_t PUPDR;    /*GPIO ����/�����Ĵ���  ��ַƫ��: 0x0C */
    __IO uint32_t IDR;      /*GPIO �������ݼĴ���   ��ַƫ��: 0x10 */
    __IO uint32_t ODR;      /*GPIO ������ݼĴ���   ��ַƫ��: 0x14 */
    __IO uint16_t BSRRL;    /*GPIO ��λ/��λ�Ĵ���  �� 16 λ���� ��ַƫ��: 0x18 */
    __IO uint16_t BSRRH;    /*GPIO ��λ/��λ�Ĵ���  �� 16 λ���ֵ�ַƫ��: 0x1A */
    __IO uint32_t LCKR;     /*GPIO ���������Ĵ���   ��ַƫ��: 0x1C */
    __IO uint32_t AFR[2];   /*GPIO ���ù������üĴ���   ��ַƫ��: 0x20-0x24 */
} GPIO_TypeDef;

/*RCC �Ĵ����б� */
typedef struct 
{
    __IO uint32_t CR;       /*!< RCC ʱ�ӿ��ƼĴ���, ��ַƫ��: 0x00 */
    __IO uint32_t PLLCFGR;  /*!< RCC PLL ���üĴ���, ��ַƫ��: 0x04 */
    __IO uint32_t CFGR;     /*!< RCC ʱ�����üĴ���, ��ַƫ��: 0x08 */
    __IO uint32_t CIR;      /*!< RCC ʱ���жϼĴ���, ��ַƫ��: 0x0C */
    __IO uint32_t AHB1RSTR;     /*!< RCC AHB1 ���踴λ�Ĵ���, ��ַƫ��: 0x10 */
    __IO uint32_t AHB2RSTR;     /*!< RCC AHB2 ���踴λ�Ĵ���, ��ַƫ��: 0x14 */
    __IO uint32_t AHB3RSTR;     /*!< RCC AHB3 ���踴λ�Ĵ���, ��ַƫ��: 0x18 */
    __IO uint32_t RESERVED0;     /*!< ����, ��ַƫ�ƣ� 0x1C */
    __IO uint32_t APB1RSTR;     /*!< RCC APB1 ���踴λ�Ĵ���, ��ַƫ��: 0x20 */
    __IO uint32_t APB2RSTR;     /*!< RCC APB2 ���踴λ�Ĵ���, ��ַƫ��: 0x24*/
    __IO uint32_t RESERVED1[2]; /*!< ����, ��ַƫ�ƣ� 0x28-0x2C*/
    __IO uint32_t AHB1ENR;      /*!< RCC AHB1 ����ʱ�ӼĴ���, ��ַƫ��: 0x30 */
    __IO uint32_t AHB2ENR;      /*!< RCC AHB2 ����ʱ�ӼĴ���, ��ַƫ��: 0x34 */
    __IO uint32_t AHB3ENR;      /*!< RCC AHB3 ����ʱ�ӼĴ���, ��ַƫ��: 0x38 */
    /*RCC ���滹�кܶ�Ĵ������˴�ʡ�� */
} RCC_TypeDef;


/*******************�б� 2: �����嵥: ������-2 ָ�������׵�ַ�Ľṹ��ָ��***************/
/* ���� GPIOA-H �Ĵ����ṹ��ָ�� */
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *) GPIOH_BASE)
/* ���� RCC ���� �Ĵ����ṹ��ָ�� */
#define RCC ((RCC_TypeDef *) RCC_BASE)


/******************�б� 3: �����嵥: ������-3 ʹ�ýṹ��ָ�뷽ʽ����LED ��******************/
/**
* ������
*/
int main(void)
{
    RCC->AHB1ENR |= (1<<7);

    /**** LED �˿ڳ�ʼ�� ****/

    GPIOH->MODER &= ~( 0x03<< (2*10));    /*GPIOH MODER10 ��� */
    GPIOH->MODER |= (1<<2*10);            /*PH10 MODER10 = 01b ���ģʽ */

    GPIOH->OTYPER &= ~(1<<1*10);   /*GPIOH OTYPER10 ��� */
    GPIOH->OTYPER |= (0<<1*10);    /*PH10 OTYPER10 = 0b ����ģʽ */

   
    GPIOH->OSPEEDR &= ~(0x03<<2*10); /*GPIOH OSPEEDR10 ��� */
    GPIOH->OSPEEDR |= (0<<2*10);     /*PH10 OSPEEDR10 = 0b ���� 2MHz*/

   
    GPIOH->PUPDR &= ~(0x03<<2*10);  /*GPIOH PUPDR10 ��� */
    GPIOH->PUPDR |= (1<<2*10);      /*PH10 PUPDR10 = 01b ����ģʽ */
    GPIOH->BSRRH |= (1<<10);        /*PH10 BSRR �Ĵ����� BR10 �� 1��ʹ��������͵�ƽ */

    /*PH10 BSRR �Ĵ����� BS10 �� 1��ʹ��������ߵ�ƽ */
    //GPIOH->BSRRL |= (1<<10);

    while (1);
}


/*******************�б� 4: �����嵥: ������-4 GPIO ��λ�����븴λ�����Ķ���********************/
/**
 * �������ܣ���������Ϊ�ߵ�ƽ
 * ����˵���� GPIOx: �ò���Ϊ GPIO_TypeDef ���͵�ָ�룬ָ�� GPIO �˿ڵĵ�ַ
 * GPIO_Pin: ѡ��Ҫ���õ� GPIO �˿����ţ�������� GPIO_Pin_0-15��
 * ��ʾ GPIOx �˿ڵ� 0-15 �����š�
 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    /* ���� GPIOx �˿� BSRRL �Ĵ����ĵ� GPIO_Pin λ��ʹ������ߵ�ƽ */
    /* ��Ϊ BSRR �Ĵ���д 0 ��Ӱ�죬
        �� GPIO_Pin ֻ�Ƕ�ӦλΪ 1������λ��Ϊ 0�����Կ���ֱ�Ӹ�ֵ */

    GPIOx->BSRRL = GPIO_Pin;
}
/**
 * �������ܣ���������Ϊ�͵�ƽ
 * ����˵���� GPIOx: �ò���Ϊ GPIO_TypeDef ���͵�ָ�룬ָ�� GPIO �˿ڵĵ�ַ
 * GPIO_Pin: ѡ��Ҫ���õ� GPIO �˿����ţ�������� GPIO_Pin_0-15��
 * ��ʾ GPIOx �˿ڵ� 0-15 �����š�
 */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
/* ���� GPIOx �˿� BSRRH �Ĵ����ĵ� GPIO_Pin λ, ʹ������͵�ƽ */
/* ��Ϊ BSRR �Ĵ���д 0 ��Ӱ�죬
 �� GPIO_Pin ֻ�Ƕ�ӦλΪ 1������λ��Ϊ 0�����Կ���ֱ�Ӹ�ֵ */

    GPIOx->BSRRH = GPIO_Pin;
}


/**********************�б� 5: �����嵥: ������-5 ��ֵ��ʽ�Ա�**********************/

GPIOH->BSRRH |= (1<<10);    /* ʹ�� ��|=�� ����ֵ */
GPIOx->BSRRH = GPIO_Pin;    /* ֱ��ʹ�� "=" �Ÿ�ֵ */


/**********************�б� 6: �����嵥: ������-6 BSRR �Ĵ�����ֵ��Ч����************/

GPIOH->BSRRH |= (uint16_t)(1<<10);  /* ʹ�� ��|=�� ����ֵ */
GPIOH->BSRRH = (uint16_t)(1<<10);   /* ֱ��ʹ�á�=�� ����ֵ���������� (0000 0100 0000 0000)*/

/**********************�б� 7: �����嵥: ������-7 λ��������ʹ�÷���*******************/

GPIO_SetBits(GPIOH,(uint16_t)(1<<10));      /* ���� GPIOH ������ 10 ����ߵ�ƽ */
GPIO_ResetBits(GPIOH,(uint16_t)(1<<10));    /* ���� GPIOH ������ 10 ����͵�ƽ */

GPIO_SetBits(GPIOH,(uint16_t)(1<<10)|(uint16_t)(1<<11));    /* ���� GPIOH ������ 10������ 11 ����ߵ�ƽ��ʹ�á�|��ͬʱ���ƶ������ */
GPIO_ResetBits(GPIOH,(uint16_t)(1<<10)|(uint16_t)(1<<10));  /* ���� GPIOH ������ 10������ 11 ����͵�ƽ */


GPIO_SetBits(GPIOA,(uint16_t)(1<<8));   /* ���� GPIOA ������ 8 ����ߵ�ƽ */
GPIO_ResetBits(GPIOB,(uint16_t)(1<<9)); /* ���� GPIOB ������ 9 ����͵�ƽ */


/*********************�б� 8: �����嵥: ������-8 ѡ�����Ų����ĺ�***********************/
/*GPIO ���źŶ��� */
#define GPIO_Pin_0  ((uint16_t)0x0001)/*!< ѡ�� Pin0 (1<<0) */
#define GPIO_Pin_1  ((uint16_t)0x0002) /*!< ѡ�� Pin1 (1<<1)*/
#define GPIO_Pin_2  ((uint16_t)0x0004) /*!< ѡ�� Pin2 (1<<2)*/
#define GPIO_Pin_3  ((uint16_t)0x0008) /*!< ѡ�� Pin3 (1<<3)*/
#define GPIO_Pin_4  ((uint16_t)0x0010) /*!< ѡ�� Pin4 */
#define GPIO_Pin_5  ((uint16_t)0x0020) /*!< ѡ�� Pin5 */
#define GPIO_Pin_6  ((uint16_t)0x0040) /*!< ѡ�� Pin6 */
#define GPIO_Pin_7  ((uint16_t)0x0080) /*!< ѡ�� Pin7 */
#define GPIO_Pin_8  ((uint16_t)0x0100) /*!< ѡ�� Pin8 */
#define GPIO_Pin_9  ((uint16_t)0x0200) /*!< ѡ�� Pin9 */
#define GPIO_Pin_10 ((uint16_t)0x0400) /*!< ѡ�� Pin10 */
#define GPIO_Pin_11 ((uint16_t)0x0800) /*!< ѡ�� Pin11 */
#define GPIO_Pin_12 ((uint16_t)0x1000) /*!< ѡ�� Pin12 */
#define GPIO_Pin_13 ((uint16_t)0x2000) /*!< ѡ�� Pin13 */
#define GPIO_Pin_14 ((uint16_t)0x4000) /*!< ѡ�� Pin14 */
#define GPIO_Pin_15 ((uint16_t)0x8000) /*!< ѡ�� Pin15 */
#define GPIO_Pin_All ((uint16_t)0xFFFF) /*!< ѡ��ȫ������ */


/**********************�б� 9: �����嵥: ������-9 ʹ��λ���������������GPIO***********************/

GPIO_SetBits(GPIOH,GPIO_Pin_10);        /* ���� GPIOH ������ 10 ����ߵ�ƽ */
GPIO_ResetBits(GPIOH,GPIO_Pin_10);      /* ���� GPIOH ������ 10 ����͵�ƽ */

GPIO_SetBits(GPIOH,GPIO_Pin_10|GPIO_Pin_11);        /* ���� GPIOH ������ 10������ 11 ����ߵ�ƽ��ʹ�á�|����ͬʱ���ƶ������ */
GPIO_ResetBits(GPIOH,GPIO_Pin_10|GPIO_Pin_11);      /* ���� GPIOH ������ 10������ 11 ����͵�ƽ */
GPIO_ResetBits(GPIOH,GPIO_Pin_ALL);     /* ���� GPIOH ����������͵�ƽ */
GPIO_SetBits(GPIOA,GPIO_Pin_8);         /* ���� GPIOA ������ 8 ����ߵ�ƽ */
GPIO_ResetBits(GPIOB,GPIO_Pin_9);       /* ���� GPIOB ������ 9 ����͵�ƽ */


/*******************�б� 10: �����嵥: ������-10 ���� GPIO ��ʼ���ṹ��**********************/
typedef uint8_t unsigned char;
/**
 * GPIO ��ʼ���ṹ�����Ͷ���
 */
typedef struct 
{
    uint32_t GPIO_Pin;   /*!< ѡ��Ҫ���õ� GPIO ���ſ����� GPIO_Pin_ ����ĺ� */
    uint8_t  GPIO_Mode;  /*!< ѡ�� GPIO ���ŵĹ���ģʽ�����������ֵ��00 �� 01�� 10�� 11��ʾ����/���/����/ģ�� */
    uint8_t  GPIO_Speed; /*!< ѡ�� GPIO ���ŵ����ʿ����������ֵ��   00 �� 01�� 10�� 11��ʾ 2/25/50/100MHz */
    uint8_t  GPIO_OType; /*!< ѡ�� GPIO ����������Ϳ����������ֵ��  0 �� 1  ��ʾ����/��© */
    uint8_t  GPIO_PuPd;  /*!< ѡ�� GPIO ���ŵ���/����ģʽ�����������ֵ:00 �� 01�� 10  ��ʾ����/����/���� */
} GPIO_InitTypeDef;


/***********************�б� 11: �����嵥: ������-11 GPIO ���ò�����ö�ٶ���************************/
/**
 * GPIO �˿�����ģʽ��ö�ٶ���
 */
typedef enum 
{
    GPIO_Mode_IN  = 0x00,   /*!< ����ģʽ */
    GPIO_Mode_OUT = 0x01,   /*!< ���ģʽ */
    GPIO_Mode_AF  = 0x02,   /*!< ����ģʽ */
    GPIO_Mode_AN  = 0x03    /*!< ģ��ģʽ */
} GPIOMode_TypeDef;

/**
 * GPIO �������ö�ٶ���
 */
typedef enum 
{
    GPIO_OType_PP = 0x00,   /*!< ����ģʽ */
    GPIO_OType_OD = 0x01    /*!< ��©ģʽ */
} GPIOOType_TypeDef;

/**
 * GPIO �������ö�ٶ���
 */
typedef enum
{
    GPIO_Speed_2MHz   = 0x00, /*!< 2MHz  */
    GPIO_Speed_25MHz  = 0x01, /*!< 25MHz */
    GPIO_Speed_50MHz  = 0x02, /*!< 50MHz */
    GPIO_Speed_100MHz = 0x03  /*!<100MHz */
} GPIOSpeed_TypeDef;

/**
 *GPIO ��/��������ö�ٶ���
 */
typedef enum 
{
    GPIO_PuPd_NOPULL = 0x00,    /* ���� */
    GPIO_PuPd_UP     = 0x01,    /* ���� */
    GPIO_PuPd_DOWN   = 0x02     /* ���� */
} GPIOPuPd_TypeDef;


/************�б� 12: �����嵥: ������-12 ʹ��ö�����Ͷ����GPIO_InitTypeDef �ṹ���Ա**********/
/**
 * GPIO ��ʼ���ṹ�����Ͷ���
 */
typedef struct 
{
    uint32_t GPIO_Pin;     /*!< ѡ��Ҫ���õ� GPIO ���ſ����� GPIO_Pin_ ����ĺ� */
    GPIOMode_TypeDef    GPIO_Mode;    /*!< ѡ�� GPIO ���ŵĹ���ģʽ������ GPIOMode_TypeDef �����ö��ֵ */
    GPIOSpeed_TypeDef   GPIO_Speed;   /*!< ѡ�� GPIO ���ŵ����ʿ����� GPIOSpeed_TypeDef �����ö��ֵ */
    GPIOOType_TypeDef   GPIO_OType;   /*!< ѡ�� GPIO ����������Ϳ����� GPIOOType_TypeDef �����ö��ֵ */
    GPIOPuPd_TypeDef    GPIO_PuPd;    /*!< ѡ�� GPIO ���ŵ���/����ģʽ������ GPIOPuPd_TypeDef �����ö��ֵ */
} GPIO_InitTypeDef;


/**************�б� 13: �����嵥: ������-13 �� GPIO_InitTypeDef ��ʼ���ṹ�帳ֵ����*********************/
GPIO_InitTypeDef InitStruct;
/* LED �˿ڳ�ʼ�� */
InitStruct.GPIO_Pin     = GPIO_Pin_10;      /* ѡ��Ҫ���Ƶ� GPIO ���� */
InitStruct.GPIO_Mode    = GPIO_Mode_OUT;    /* ��������ģʽΪ���ģʽ */
InitStruct.GPIO_OType   = GPIO_OType_PP;    /* �������ŵ��������Ϊ������� */
InitStruct.GPIO_PuPd    = GPIO_PuPd_UP;     /* ��������Ϊ����ģʽ */
InitStruct.GPIO_Speed   = GPIO_Speed_2MHz;  /* ������������Ϊ 2MHz */



/********************�б� 14: �����嵥: ������-14 GPIO ��ʼ������************************/
/**
 * �������ܣ���ʼ������ģʽ
 * ����˵���� GPIOx���ò���Ϊ GPIO_TypeDef ���͵�ָ�룬ָ�� GPIO �˿ڵĵ�ַ
 * GPIO_InitTypeDef:GPIO_InitTypeDef �ṹ��ָ�룬ָ���ʼ������
 */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
    /*-- GPIO Mode Configuration --*/
    for (pinpos = 0x00; pinpos < 16; pinpos++) 
    {
        /* ����������Ϊ��ͨ�� GPIO_InitStruct->GPIO_Pin ������ź� 0-15*/
        /* ��������� pos �� pinpos λΪ 1������Ϊ 0���� GPIO_Pin_x ���Ӧ��
        pinpos ����ÿ��ѭ���� 1�� */
        pos = ((uint32_t)0x01) << pinpos;
        /* pos �� GPIO_InitStruct->GPIO_Pin �� & ���㣬 �������� currentpin == pos��
        ���ʾ GPIO_InitStruct->GPIO_Pin �� pinpos λҲΪ 1��
        �Ӷ���֪ pinpos ���� GPIO_InitStruct->GPIO_Pin ��Ӧ�����źţ� 0-15*/
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        /*currentpin == pos ʱִ�г�ʼ�� */
        if (currentpin == pos) 
        {
            /*GPIOx �˿ڣ� MODER �Ĵ����� GPIO_InitStruct->GPIO_Pin ��Ӧ�����ţ�MODER λ��� */
            GPIOx->MODER &= ~(3 << (2 *pinpos));

            /*GPIOx �˿ڣ� MODER �Ĵ����� GPIO_Pin ���ţ�
            MODER λ����" ����/���/�������/ģ��" ģʽ */
            GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (2 *pinpos));

            /*GPIOx �˿ڣ� PUPDR �Ĵ����� GPIO_Pin ���ţ�PUPDR λ��� */
            GPIOx->PUPDR &= ~(3 << ((2 *pinpos)));

            /*GPIOx �˿ڣ� PUPDR �Ĵ����� GPIO_Pin ���ţ�
            PUPDR λ����" ��/����" ģʽ */
            GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (2 *pinpos));

            /* ��ģʽΪ" ���/�������" ģʽ���������ٶ���������� */
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) ||(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)) 
            {
                /*GPIOx �˿ڣ� OSPEEDR �Ĵ����� GPIO_Pin ���ţ�OSPEEDR λ��� */
                GPIOx->OSPEEDR &= ~(3 << (2 *pinpos));
                /*GPIOx �˿ڣ� OSPEEDR �Ĵ����� GPIO_Pin ���ţ�OSPEEDR λ��������ٶ� */
                GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed)<<(2 *pinpos));

                /*GPIOx �˿ڣ� OTYPER �Ĵ����� GPIO_Pin ���ţ�OTYPER λ��� */
                GPIOx->OTYPER &= ~(1 << (pinpos)) ;
                /*GPIOx �˿ڣ� OTYPER λ�Ĵ����� GPIO_Pin ���ţ�OTYPER λ����" ����/��©" ������� */
                GPIOx->OTYPER |= (uint16_t)(( GPIO_InitStruct->GPIO_OType)<< (pinpos));
            }
        }
    }   
}



/***********************�б� 15: �����嵥: ������-15 ʹ�ú������� LED ��****************************/
/*
    ʹ�üĴ����ķ������� LED ��
 */
#include "stm32f4xx_gpio.h"

void Delay( uint32_t nCount);

/**
 * ��������ʹ�÷�װ�õĺ��������� LED ��
 */
int main(void)
{
    GPIO_InitTypeDef InitStruct;
    /* ���� GPIOH ʱ�ӣ�ʹ������ʱ��Ҫ�ȿ�������ʱ�� */
    RCC->AHB1ENR |= (1<<7);

    /* LED �˿ڳ�ʼ��,��ʼ�� PH10 ���� */
    
    InitStruct.GPIO_Pin   = GPIO_Pin_10;     /* ѡ��Ҫ���Ƶ� GPIO ���� */
    InitStruct.GPIO_Mode  = GPIO_Mode_OUT;   /* ��������ģʽΪ���ģʽ */
    InitStruct.GPIO_OType = GPIO_OType_PP;   /* �������ŵ��������Ϊ������� */
    InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;    /* ��������Ϊ����ģʽ */
    InitStruct.GPIO_Speed = GPIO_Speed_2MHz; /* ������������Ϊ 2MHz */
    GPIO_Init(GPIOH, &InitStruct);           /* ���ÿ⺯����ʹ���������õ� GPIO_InitStructure ��ʼ�� GPIO*/


    GPIO_ResetBits(GPIOH,GPIO_Pin_10);  /* ʹ��������͵�ƽ, ���� LED1*/
    Delay(0xFFFFFF);    /* ��ʱһ��ʱ�� */
    
    GPIO_SetBits(GPIOH,GPIO_Pin_10);    /* ʹ��������ߵ�ƽ���ر� LED1*/

    /* ��ʼ�� PH11 ���� */
    InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOH,&InitStruct);
  
    GPIO_ResetBits(GPIOH,GPIO_Pin_11);  /* ʹ��������͵�ƽ������ LED2*/
   
    while (1);

}

//�򵥵���ʱ�������� cpu ִ��������ָ�����ʱ��
//������ʱʱ�����Լ��㣬�Ժ����ǿ�ʹ�ö�ʱ����ȷ��ʱ
void Delay( uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

// ����Ϊ�գ�Ŀ����Ϊ��ƭ��������������
void SystemInit(void)
{
}