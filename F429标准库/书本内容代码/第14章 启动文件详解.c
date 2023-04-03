/*************************ָ������������****************************/
/*EQU		�����ֳ���ȡһ�����������൱��C�����е�define
AREA	���һ���µĴ���λ������ݶ�
SPACE	�����ڴ�ռ�
PRESERVE8	��ǰ�ļ���ջ�谴��8�ֽڶ���
EXPORT		����һ����ž���ȫ�����ԣ��ɱ��ⲿ���ļ�ʹ��
DCD		����Ϊ��λ�����ڴ棬Ҫ��4�ֽڶ��룬��Ҫ���ʼ����Щ�ڴ�
PROC	�����ӳ�����ENDP�ɶ�ʹ�ã���ʾ�ӳ������
WEAK	�����壬����ⲿ�ļ�������һ����ţ�������ʹ���ⲿ�ļ�����ı�ţ�����ⲿ�ļ�û�ж���Ҳ������
		Ҫע�����:������� ARM��ָ��Ǳ������ģ��������һ��ֻ��Ϊ�˷��㡣
IMPORT	������������ⲿ�ļ�����C�����е�EXTERN�ؼ�������
B		��ת��һ�����
ALIGN	��������ָ��������ݵĴ�ŵ�ַ���ж��룬һ����Ҫ��һ����������ȱʡ��ʾ4�ֽڶ��롣
		Ҫע�����:������� ARM ��ָ��Ǳ������ģ��������һ��ֻ��Ϊ�˷��㡣
END		�����ļ���ĩβ���ļ�����
IF,ELSE,ENDIF		���������֧��䣬��C���Ե�if else����*/

/*********************Stack��ջ*************************************/
/*����ջ�Ĵ�СΪ 0X00000400��1KB��������Ϊ STACK�� NOINIT ������ʼ�����ɶ���д�� 8��2^3���ֽڶ��롣
 *EQU���궨���αָ��൱�ڵ��ڣ������� C �е� define��
 */
Stack_Size 		EQU 	0x00000400
/*AREA�����߻�������һ���µĴ���λ������ݶΡ� 
 *STACK ��ʾ�����������������������
 *NOINIT ��ʾ����ʼ���� 
 *READWRITE ��ʾ�ɶ���д�� 
 *ALIGN=3����ʾ���� 2^3 ���룬�� 8 �ֽڶ��롣*/
				AREA 	STACK, NOINIT, READWRITE, ALIGN=3
/*SPACE�����ڷ���һ����С���ڴ�ռ䣬��λΪ�ֽڡ�����ָ����С���� Stack_Size��*/
Stack_Mem 		SPACE 	Stack_Size
/*��� __initial_sp ������ SPACE �����ã���ʾջ�Ľ�����ַ����ջ����ַ��ջ���ɸ����������*/
__initial_sp

/*************************Heap ��******************************************/
/*���ٶѵĴ�СΪ 0X00000200��512 �ֽڣ���
 *����Ϊ HEAP�� NOINIT ������ʼ�����ɶ���д��
 *8��2^3���ֽڶ��롣 
 *__heap_base ��ʾ�Ե���ʼ��ַ�� 
 *__heap_limit ��ʾ�ѵĽ�����ַ�������ɵ���������ģ���ջ�����������෴��
 *����Ҫ������̬�ڴ�ķ��䣬�� malloc() ����������ڴ���ڶ����档����� STM32 �����õıȽ��١�*/
Heap_Size 	EQU 	0x00000200
			AREA HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem 	SPACE 	Heap_Size
__heap_limit

/*PRESERVE8�� ָ����ǰ�ļ��Ķ�ջ���� 8 �ֽڶ���
 *THUMB�� ��ʾ����ָ����� THUMB ָ� THUBM �� ARM ��ǰ��ָ��� 16bit������ Cortex-M
  ϵ�еĶ�ʹ�� THUMB-2 ָ��� THUMB-2 �� 32 λ�ģ����� 16 λ�� 32 λ��ָ��� THUMB�ĳ�����*/
PRESERVE8
THUMB

/***************************************������*****************************************/
/**
 * ����һ�����ݶΣ�����Ϊ RESET���ɶ��������� __Vectors�� __Vectors_End �� __Vectors_Size ��
   ������ž���ȫ�����ԣ��ɹ��ⲿ���ļ����á�
 *EXPORT�� ����һ����ſɱ��ⲿ���ļ�ʹ�ã�ʹ��ž���ȫ�����ԡ������ IAR ����������ʹ�õ��� GLOBAL ���ָ�
*/
AREA 	RESET, DATA, READONLY
EXPORT 	__Vectors
EXPORT 	__Vectors_End
EXPORT 	__Vectors_Size


/***************************�б� 1: �����嵥: �����ļ�-1 F429 ������******************************/
/*__Vectors Ϊ��������ʼ��ַ�� __Vectors_End Ϊ�����������ַ�����������������������С��
 *������� FLASH �� 0 ��ַ��ʼ���ã��� 4 ���ֽ�Ϊһ����λ����ַ 0 ��ŵ���ջ����ַ�� 0X04��ŵ��Ǹ�λ����ĵ�ַ��
  �Դ����ơ��Ӵ����Ͽ����������д�ŵĶ����жϷ������ĺ�������������֪�� C �����еĺ���������һ����ַ��
 *DCD������һ�����߶������Ϊ��λ���ڴ棬�����ֽڶ��룬��Ҫ���ʼ����Щ�ڴ档
  ���������У� DCD ������һ���ڴ棬������ ESR ����ڵ�ַ��ʼ�����ǡ�*/
__Vectors 	DCD 	__initial_sp 	; ջ����ַ
			DCD 	Reset_Handler 	; ��λ�����ַ
			DCD 	NMI_Handler
			DCD 	HardFault_Handler
			DCD 	MemManage_Handler
			DCD 	BusFault_Handler
			DCD 	UsageFault_Handler
			DCD 	0 ; 0 ��ʾ����
			DCD 	0
			DCD 	0
			DCD 	0
			DCD 	SVC_Handler
			DCD 	DebugMon_Handler
			DCD 	0
			DCD 	PendSV_Handler
			DCD 	SysTick_Handler

; �ⲿ�жϿ�ʼ
			DCD 	WWDG_IRQHandler
			DCD 	PVD_IRQHandler
			DCD 	TAMP_STAMP_IRQHandler

; ����ƪ�����м����ʡ��
			DCD 	LTDC_IRQHandler
			DCD 	LTDC_ER_IRQHandler
			DCD 	DMA2D_IRQHandler
__Vectors_End
__Vectors_Size 		EQU __Vectors_End 	-	 __Vectors


/**************************��λ����*******************************/
/*��λ�ӳ�����ϵͳ�ϵ���һ��ִ�еĳ��򣬵��� SystemInit ������ʼ��ϵͳʱ�ӣ�
  Ȼ����� C�⺯�� _mian�����յ��� main ����ȥ�� C �����硣*/
Reset_Handler 	PROC
/*WEAK����ʾ�����壬����ⲿ�ļ����ȶ����˸ñ�����������øñ�ţ�����ⲿ�ļ�û����
  ��Ҳ������������ʾ��λ�ӳ���������û��������ļ�����ʵ�֣����ﲢ����Ψһ�ġ�*/
				EXPORT 	Reset_Handler [WEAK]
/*MPORT����ʾ�ñ�������ⲿ�ļ����� C �����е� EXTERN �ؼ������ơ������ʾ SystemInit
  �� __main �����������������ⲿ���ļ���*/
				IMPORT 	SystemInit
				IMPORT 	__main
/*SystemInit() ��һ����׼�Ŀ⺯������ system_stm32f4xx.c ������ļ��ܶ��塣��Ҫ����������ϵ
 ͳʱ�ӣ���������������֮�� F429 ��ϵͳʱ���䱻����Ϊ 180M��*/
				LDR 	R0, =SystemInit
				BLX 	R0
/*__main ��һ����׼�� C �⺯������Ҫ�����ǳ�ʼ���û���ջ�����յ��� main ����ȥ�� C �����硣
  �����Ϊʲô����д�ĳ�����һ�� main ������ԭ��������������ﲻ���� __main����ô��
  �����վͲ���������� C �ļ������ main������ǵ�Ƥ���û��Ϳ����޸������������ƣ�Ȼ��
  �������� IMPORT ��д�����������Ƽ��ɡ�*/
				LDR 	R0, =__main
				BX 		R0
				ENDP


/*****************************************�޸�__main****************************/
Reset_Handler 	PROC
				EXPORT 	Reset_Handler [WEAK]
				IMPORT 	SystemInit
/*���ʱ������ C �ļ�����д�����������ƾͲ��� main �ˣ����� user_main �ˡ�*/
				IMPORT 	user_main
/*LDR	�Ӵ洢���м����ֵ�һ���Ĵ�����*/
				LDR R0, =SystemInit
/*BL 	��ת���ɼĴ���/��Ÿ����ĵ�ַ��������תǰ������ָ���ַ���浽
 *BLX 	��ת���ɼĴ��������ĵ�ַ�������ݼĴ�����LSEȷ����������״̬����Ҫ����תǰ������ָ���ַ���浽LR
*/
				BLX R0
				LDR R0, =user_main
/*BX	��ת���ɼĴ���/��Ÿ����ĵ�ַ�����÷���*/
				BX R0
				ENDP


/*******************************�жϷ������************************************/
/*�������ļ������Ѿ�������д�������жϵ��жϷ�������������ƽʱд���жϷ�������һ
  ���ľ�����Щ�������ǿյģ��������жϸ����������Ҫ�������ⲿ�� C �ļ���������ʵ�֣���
  ��ֻ����ǰռ��һ��λ�ö��ѡ�
  ���������ʹ��ĳ�������ʱ�򣬿�����ĳ���жϣ����������Ǳ�д���׵��жϷ��������ߺ�
  ����д���ǵ��ж����ٵ�ʱ������ͻ���ת�������ļ�Ԥ��д�õĿյ��жϷ�������У�����
  ������պ���������ѭ������������������
 *B����ת��һ����š�������ת��һ���� .��������ʾ����ѭ����*/
NMI_Handler PROC 	; ϵͳ�쳣
			EXPORT 	NMI_Handler [WEAK]
			B 		.
			ENDP
; ����ƪ�����м����ʡ��

SysTick_Handler 	PROC
					EXPORT 	SysTick_Handler [WEAK]
					B 		.
					ENDP

Default_Handler 	PROC ; 		�ⲿ�ж�
					EXPORT WWDG_IRQHandler [WEAK]
					EXPORT PVD_IRQHandler [WEAK]
					EXPORT TAMP_STAMP_IRQHandler [WEAK]
; ����ƪ�����м����ʡ��

LTDC_IRQHandler
LTDC_ER_IRQHandler
DMA2D_IRQHandler
					B 		.
					ENDP


/**************************�û���ջ��ʼ��***********************************/
/*ALIGN����ָ��������ݴ�ŵĵ�ַ���ж��룬������һ����������ȱʡ��ʾ 4 �ֽڶ���*/
ALIGN
/*�ж��Ƿ����� __MICROLIB ����������������� __initial_sp��ջ����ַ����
   __heap_base������ʼ��ַ���� __heap_limit���ѽ�����ַ��ȫ�����ԣ��ɹ��ⲿ�ļ����á�
 *���û�ж��壨ʵ�ʵ������������û���� __MICROLIB����ʹ��Ĭ�ϵ� C �⣬Ȼ���ʼ���û���ջ��С��
  �ⲿ���� C�⺯�� __main ����ɣ�����ʼ�����ջ֮�󣬾͵��� main ����ȥ�� C �����硣
 *IF,ELSE,ENDIF������������֧��䣬�� C ���Ե� if ,else ����
  END���ļ�������*/
; �û�ջ�Ͷѳ�ʼ��
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