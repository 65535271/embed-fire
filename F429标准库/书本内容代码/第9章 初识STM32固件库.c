/**************列表 1: 代码清单: 标准库-1： core_cm4.c 文件中对编译器差异的屏蔽*************/
#if defined ( __CC_ARM )
    #define __ASM __asm         /*!< asm keyword for ARM Compiler */
    #define __INLINE __inline   /*!< inline keyword for ARM Compiler*/
    #define __STATIC_INLINE static __inline
#elif defined ( __GNUC__ )
    #define __ASM __asm         /*!< asm keyword for GNU Compiler */
    #define __INLINE inline     /*!< inline keyword for GNU Compiler */
    define __STATIC_INLINE static inline
#elif defined ( __ICCARM__ )
    #define __ASM __asm         /*!< asm keyword for IAR Compiler */
    /*!< inline keyword for IAR Compiler. */
    #define __STATIC_INLINE static inline
    #define __INLINE inline
#elif defined ( __TMS470__ )
    #define __ASM __asm         /*!< asm keyword for TI CCS Compiler */
    #define __STATIC_INLINE static inline
#elif defined ( __TASKING__ )
    #define __ASM __asm         /*!< asm keyword for TASKING Compiler */
    #define __INLINE inline     /*!< inline keyword for TASKING Compiler
                                    #define __STATIC_INLINE static inline
                                    #elif defined ( __CSMC__ )
                                    #define __packed
                                    #define __ASM _asm /*!< asm keyword for COSMIC Compiler */
                                /*use -pc99 on compile line !< inline keyword for COSMIC Compiler */
    #define __INLINE inline
    #define __STATIC_INLINE static inline
#endif


/***********************列表 2: 代码清单: 标准库-2： stdint.c 文件中的类型定义********************/
/* exact-width signed integer types */
typedef signed  char        int8_t;
typedef signed  short int   int16_t;
typedef signed  int         int32_t;
typedef signed  __int64     int64_t;

/* exact-width unsigned integer types */
typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned __int64    uint64_t;


/******************************列表 3: 代码清单: 标准库-3 stm32f4xx_conf.h 文件配置软件库******************************/
#if defined (STM32F429_439xx) || defined(STM32F446xx)
    #include "stm32f4xx_cryp.h"
    #include "stm32f4xx_hash.h"
    #include "stm32f4xx_rng.h"
    #include "stm32f4xx_can.h"
    #include "stm32f4xx_dac.h"
    #include "stm32f4xx_dcmi.h"
    #include "stm32f4xx_dma2d.h"
    #include "stm32f4xx_fmc.h"
    #include "stm32f4xx_ltdc.h"
    #include "stm32f4xx_sai.h"
#endif /* STM32F429_439xx || STM32F446xx */

#if defined (STM32F427_437xx)
    #include "stm32f4xx_cryp.h"
    #include "stm32f4xx_hash.h"
    #include "stm32f4xx_rng.h"
    #include "stm32f4xx_can.h"
    #include "stm32f4xx_dac.h"
    #include "stm32f4xx_dcmi.h"
    #include "stm32f4xx_dma2d.h"
    #include "stm32f4xx_fmc.h"
    #include "stm32f4xx_sai.h"
#endif /* STM32F427_437xx */

#if defined (STM32F40_41xxx)


/*********************************列表 4: 代码清单: 标准库-4 断言配置*************************************/
#ifdef USE_FULL_ASSERT

    /**
     * @brief The assert_param macro is used for parameters check.
     * @param expr: If expr is false, it calls assert_failed function
     * which reports the name of the source file and the source
     * line number of the call that failed.
     * If expr is true, it returns no value.
     * @retval None
     */
    #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t*)__FILE__, __LINE__))
    /* Exported functions ---------------------------------- */
    void assert_failed(uint8_t* file, uint32_t line);
#else
    #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */