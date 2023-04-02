/*************************指令名称与作用****************************/
/*EQU		给数字常量取一个符号名，相当于C语言中的define
AREA	汇编一个新的代码段或者数据段
SPACE	分配内存空间
PRESERVE8	当前文件堆栈需按照8字节对齐
EXPORT		声明一个标号具有全局属性，可被外部的文件使用
DCD		以字为单位分配内存，要求4字节对齐，并要求初始化这些内存
PROC	定义子程序，与ENDP成对使用，表示子程序结束
WEAK	弱定义，如果外部文件声明了一个标号，则优先使用外部文件定义的标号，如果外部文件没有定义也不出错。
		要注意的是:这个不是 ARM的指令，是编译器的，这里放在一起只是为了方便。
IMPORT	声明标号来自外部文件，跟C语言中的EXTERN关键字类似
B		跳转到一个标号
ALIGN	编译器对指令或者数据的存放地址进行对齐，一般需要跟一个立即数，缺省表示4字节对齐。
		要注意的是:这个不是 ARM 的指令，是编译器的，这里放在一起只是为了方便。
END		到达文件的末尾，文件结束
IF,ELSE,ENDIF		汇编条件分支语句，跟C语言的if else类似*/

/*********************Stack—栈*************************************/
/*开辟栈的大小为 0X00000400（1KB），名字为 STACK， NOINIT 即不初始化，可读可写， 8（2^3）字节对齐。
 *EQU：宏定义的伪指令，相当于等于，类似与 C 中的 define。
 */
Stack_Size 		EQU 	0x00000400
/*AREA：告诉汇编器汇编一个新的代码段或者数据段。 
 *STACK 表示段名，这个可以任意命名；
 *NOINIT 表示不初始化； 
 *READWRITE 表示可读可写， 
 *ALIGN=3，表示按照 2^3 对齐，即 8 字节对齐。*/
				AREA 	STACK, NOINIT, READWRITE, ALIGN=3
/*SPACE：用于分配一定大小的内存空间，单位为字节。这里指定大小等于 Stack_Size。*/
Stack_Mem 		SPACE 	Stack_Size
/*标号 __initial_sp 紧挨着 SPACE 语句放置，表示栈的结束地址，即栈顶地址，栈是由高向低生长的*/
__initial_sp

/*************************Heap 堆******************************************/
/*开辟堆的大小为 0X00000200（512 字节），
 *名字为 HEAP， NOINIT 即不初始化，可读可写，
 *8（2^3）字节对齐。 
 *__heap_base 表示对的起始地址， 
 *__heap_limit 表示堆的结束地址。堆是由低向高生长的，跟栈的生长方向相反。
 *堆主要用来动态内存的分配，像 malloc() 函数申请的内存就在堆上面。这个在 STM32 里面用的比较少。*/
Heap_Size 	EQU 	0x00000200
			AREA HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem 	SPACE 	Heap_Size
__heap_limit

/*PRESERVE8： 指定当前文件的堆栈按照 8 字节对齐
 *THUMB： 表示后面指令兼容 THUMB 指令。 THUBM 是 ARM 以前的指令集， 16bit，现在 Cortex-M
  系列的都使用 THUMB-2 指令集， THUMB-2 是 32 位的，兼容 16 位和 32 位的指令，是 THUMB的超级。*/
PRESERVE8
THUMB

/***************************************向量表*****************************************/
/**
 * 定义一个数据段，名字为 RESET，可读。并声明 __Vectors、 __Vectors_End 和 __Vectors_Size 这
   三个标号具有全局属性，可供外部的文件调用。
 *EXPORT： 声明一个标号可被外部的文件使用，使标号具有全局属性。如果是 IAR 编译器，则使用的是 GLOBAL 这个指令。
*/
AREA 	RESET, DATA, READONLY
EXPORT 	__Vectors
EXPORT 	__Vectors_End
EXPORT 	__Vectors_Size


/***************************列表 1: 代码清单: 启动文件-1 F429 向量表******************************/
/*__Vectors 为向量表起始地址， __Vectors_End 为向量表结束地址，两个相减即可算出向量表大小。
 *向量表从 FLASH 的 0 地址开始放置，以 4 个字节为一个单位，地址 0 存放的是栈顶地址， 0X04存放的是复位程序的地址，
  以此类推。从代码上看，向量表中存放的都是中断服务函数的函数名，可我们知道 C 语言中的函数名就是一个地址。
 *DCD：分配一个或者多个以字为单位的内存，以四字节对齐，并要求初始化这些内存。
  在向量表中， DCD 分配了一堆内存，并且以 ESR 的入口地址初始化它们。*/
__Vectors 	DCD 	__initial_sp 	; 栈顶地址
			DCD 	Reset_Handler 	; 复位程序地址
			DCD 	NMI_Handler
			DCD 	HardFault_Handler
			DCD 	MemManage_Handler
			DCD 	BusFault_Handler
			DCD 	UsageFault_Handler
			DCD 	0 ; 0 表示保留
			DCD 	0
			DCD 	0
			DCD 	0
			DCD 	SVC_Handler
			DCD 	DebugMon_Handler
			DCD 	0
			DCD 	PendSV_Handler
			DCD 	SysTick_Handler

; 外部中断开始
			DCD 	WWDG_IRQHandler
			DCD 	PVD_IRQHandler
			DCD 	TAMP_STAMP_IRQHandler

; 限于篇幅，中间代码省略
			DCD 	LTDC_IRQHandler
			DCD 	LTDC_ER_IRQHandler
			DCD 	DMA2D_IRQHandler
__Vectors_End
__Vectors_Size 		EQU __Vectors_End 	-	 __Vectors


/**************************复位程序*******************************/
/*复位子程序是系统上电后第一个执行的程序，调用 SystemInit 函数初始化系统时钟，
  然后调用 C库函数 _mian，最终调用 main 函数去到 C 的世界。*/
Reset_Handler 	PROC
/*WEAK：表示弱定义，如果外部文件优先定义了该标号则首先引用该标号，如果外部文件没有声
  明也不会出错。这里表示复位子程序可以由用户在其他文件重新实现，这里并不是唯一的。*/
				EXPORT 	Reset_Handler [WEAK]
/*MPORT：表示该标号来自外部文件，跟 C 语言中的 EXTERN 关键字类似。这里表示 SystemInit
  和 __main 这两个函数均来自外部的文件。*/
				IMPORT 	SystemInit
				IMPORT 	__main
/*SystemInit() 是一个标准的库函数，在 system_stm32f4xx.c 这个库文件总定义。主要作用是配置系
 统时钟，这里调用这个函数之后， F429 的系统时钟配被配置为 180M。*/
				LDR 	R0, =SystemInit
				BLX 	R0
/*__main 是一个标准的 C 库函数，主要作用是初始化用户堆栈，最终调用 main 函数去到 C 的世界。
  这就是为什么我们写的程序都有一个 main 函数的原因。如果我们在这里不调用 __main，那么程
  序最终就不会调用我们 C 文件里面的 main，如果是调皮的用户就可以修改主函数的名称，然后
  在这里面 IMPORT 你写的主函数名称即可。*/
				LDR 	R0, =__main
				BX 		R0
				ENDP


/*****************************************修改__main****************************/
Reset_Handler 	PROC
				EXPORT 	Reset_Handler [WEAK]
				IMPORT 	SystemInit
/*这个时候你在 C 文件里面写的主函数名称就不是 main 了，而是 user_main 了。*/
				IMPORT 	user_main
/*LDR	从存储器中加载字到一个寄存器中*/
				LDR R0, =SystemInit
/*BL 	跳转到由寄存器/标号给出的地址，并把跳转前的下条指令地址保存到
 *BLX 	跳转到由寄存器给出的地址，并根据寄存器的LSE确定处理器的状态，还要把跳转前的下条指令地址保存到LR
*/
				BLX R0
				LDR R0, =user_main
/*BX	跳转到由寄存器/标号给出的地址，不用返回*/
				BX R0
				ENDP


/*******************************中断服务程序************************************/
/*在启动文件里面已经帮我们写好所有中断的中断服务函数，跟我们平时写的中断服务函数不一
  样的就是这些函数都是空的，真正的中断复服务程序需要我们在外部的 C 文件里面重新实现，这
  里只是提前占了一个位置而已。
  如果我们在使用某个外设的时候，开启了某个中断，但是又忘记编写配套的中断服务程序或者函
  数名写错，那当中断来临的时，程序就会跳转到启动文件预先写好的空的中断服务程序中，并且
  在这个空函数中无线循环，即程序就死在这里。
 *B：跳转到一个标号。这里跳转到一个‘ .’，即表示无线循环。*/
NMI_Handler PROC 	; 系统异常
			EXPORT 	NMI_Handler [WEAK]
			B 		.
			ENDP
; 限于篇幅，中间代码省略

SysTick_Handler 	PROC
					EXPORT 	SysTick_Handler [WEAK]
					B 		.
					ENDP

Default_Handler 	PROC ; 		外部中断
					EXPORT WWDG_IRQHandler [WEAK]
					EXPORT PVD_IRQHandler [WEAK]
					EXPORT TAMP_STAMP_IRQHandler [WEAK]
; 限于篇幅，中间代码省略

LTDC_IRQHandler
LTDC_ER_IRQHandler
DMA2D_IRQHandler
					B 		.
					ENDP


/**************************用户堆栈初始化***********************************/
/*ALIGN：对指令或者数据存放的地址进行对齐，后面会跟一个立即数。缺省表示 4 字节对齐*/
ALIGN
/*判断是否定义了 __MICROLIB ，如果定义了则赋予标号 __initial_sp（栈顶地址）、
   __heap_base（堆起始地址）、 __heap_limit（堆结束地址）全局属性，可供外部文件调用。
 *如果没有定义（实际的情况就是我们没定义 __MICROLIB）则使用默认的 C 库，然后初始化用户堆栈大小，
  这部分有 C库函数 __main 来完成，当初始化完堆栈之后，就调用 main 函数去到 C 的世界。
 *IF,ELSE,ENDIF：汇编的条件分支语句，跟 C 语言的 if ,else 类似
  END：文件结束。*/
; 用户栈和堆初始化
IF	:DEF:__MICROLIB

	EXPORT		__initial_sp
	EXPORT 		__heap_base
	EXPORT 		__heap_limit
ELSE
	IMPORT 		__use_two_region_memory
	EXPORT 		__user_initial_stackheap
	__user_initial_stackheap
	LDR 		R0, = Heap_Mem
	LDR 		R1, = (Stack_Mem + Stack_Size)
	LDR 		R2, = (Heap_Mem + Heap_Size)
	LDR 		R3, = Stack_Mem
	BX LR
	ALIGN
ENDIF
END