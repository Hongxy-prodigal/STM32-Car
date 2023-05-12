#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <string.h>
#include "usart.h"
#define  LH GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) 
#define  RH GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)
#define  X1 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)
#define  X2 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)
#define  X3 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)
#define  X4 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)
void go(void);
void back(void);
void stop(void);
void delay(void);
void delay2(void);
void right(void);
void rightback(void);
void left(void);
void leftback(void);
void span(void);
void span2(void);
void avoid(void);
void driver(void);
void xunji(void);
/*�������
  ���--->PB10   �Ҳ�PA11
 */
extern char usart_recv[100];		// ȫ�ֱ���������STM32���ڽ��յ����ַ��������ݣ�
extern int usart_index;			// ȫ�ֱ�����usart_recv���ݵ��±�
extern int usart_flag;	
int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �жϷ���
	driver();
	usart1_init();
	usart1_sendstring("helloworld 1\r\n");
	printf("helloworld 2\r\n");
	while(1)
	{
		if (usart_flag == 1)
		{
			if (strncmp(usart_recv, "left",4) == 0)
			{
				left();
				printf("��ת\r\n");
			}
			else if(strncmp(usart_recv, "go",2) == 0)
			{
				go();
				printf("ֱ��\r\n");
			}
			else if(strncmp(usart_recv, "right",5) == 0)
			{
				right();
				printf("��ת\r\n");
			}
			else if(strncmp(usart_recv, "back",4) == 0)
			{
				back();
				printf("����\r\n");
			}
			else if(strncmp(usart_recv, "span",4) == 0)
			{
				span();
				printf("��ת\r\n");
			}
			else if(strncmp(usart_recv, "stop",4) == 0)
			{
				stop();
				printf("��ת\r\n");
			}
			usart_flag = 0;
		}	
	}
}
//�ҵ�С���������෴�ģ�ʹ�õ�ʱ��ֻ��Ҫ�����ҵ����ֵ������� 
void go(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
}
void back(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}
void stop(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
}
void right(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
}
void rightback(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}
void left(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}
void leftback(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}
void span(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}
void span2(void)
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
}
void delay(void)
{
    int i,j;
		for(i=0;i<1000;i++)
			for(j=0;j<5000;j++);
}
void delay2(void)
{
    int i,j;
		for(i=0;i<1000;i++)
			for(j=0;j<1000;j++);
}

//С��������ʼ������
void driver(void)
{
      
	 GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	 //1.ʱ��ʹ��(GPIOB�����ص�ʱ����ʹ��)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 //2.����GPIO����
	 GPIO_InitStructure.GPIO_Pin= GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
	 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;//�������
	 GPIO_InitStructure.GPIO_Speed=  GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);


}
void avoid(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	 //1.ʱ��ʹ��(GPIOA��GPIOB�����ص�ʱ����ʹ��)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	 //2.����GPIO���� PB10  PA11
	 GPIO_InitStructure.GPIO_Pin= GPIO_Pin_10; 
	 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;//��������
	 GPIO_InitStructure.GPIO_Speed=  GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);//������ָ���Ĳ�����ʼ�����ṹ��
  
     GPIO_InitStructure.GPIO_Pin= GPIO_Pin_11; 
	 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;//��������
	 GPIO_InitStructure.GPIO_Speed=  GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);//������ָ���Ĳ�����ʼ�����ṹ��
  
}
void xunji(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	 //1.ʱ��ʹ��(GPIOA��GPIOB�����ص�ʱ����ʹ��)
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	 GPIO_InitStructure.GPIO_Pin= GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 
	 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;//��������
	 GPIO_InitStructure.GPIO_Speed=  GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);//������ָ���Ĳ�����ʼ�����ṹ��
  
   GPIO_InitStructure.GPIO_Pin= GPIO_Pin_12; 
	 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;//��������
	 GPIO_InitStructure.GPIO_Speed=  GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);//������ָ���Ĳ�����ʼ�����ṹ��
  
}

