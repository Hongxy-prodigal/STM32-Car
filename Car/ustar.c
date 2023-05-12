#include "usart.h"
#include <stdio.h>
// usart1�жϷ������������ڽ��յ�����ʱ�������������

char usart_recv[100];		// ȫ�ֱ���������STM32���ڽ��յ����ַ��������ݣ�
int usart_index;			// ȫ�ֱ�����usart_recv���ݵ��±�
int usart_flag;				// ȫ�ֱ����������������ݺ�usart_flag = 1������usart_flag = 0

// usart1�жϷ������������ڽ��յ�����ʱ���������������������
void USART1_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) 					// �ж��Ƿ���Ľ��յ�������
	{
			usart_recv[usart_index] = USART_ReceiveData(USART1);			// ��ȡ���յ�������
			
			if (usart_recv[usart_index] == '\n')
			{		// �������ַ�����
					usart_index = 0;
					usart_flag = 1;
			}
			else
			{
				usart_index++;
			}
			
	}
}


void usart1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 		// ����USART1����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 		// ����A������ʱ��
	
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;								// ���ź�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					// �����ٶ�
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;						// ���츴�����
	GPIO_Init(GPIOA, &GPIO_InitStruct);			

	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;								// ���ź�
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;					// �����ٶ�
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;			// ��������
	GPIO_Init(GPIOA, &GPIO_InitStruct);			
	
	
	USART_InitStruct.USART_BaudRate   = 115200;			// ������
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;  // 8λ��Ч����
	USART_InitStruct.USART_StopBits   = USART_StopBits_1;		// 1λֹͣλ
	USART_InitStruct.USART_Parity     = USART_Parity_No; 			// ��У��λ
	USART_InitStruct.USART_Mode 			= USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// ��Ӳ��������
	USART_Init(USART1, &USART_InitStruct);
	
	
	NVIC_InitStruct.NVIC_IRQChannel	= USART1_IRQn;   				// �ж�Դ						
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	// �����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;					// �����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;						// ʹ��
	NVIC_Init(&NVIC_InitStruct);					// �ж����ȼ�����

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		// �����������ݵ��жϣ������ڽ��յ�����ʱ������USART1_IRQHandler�������
	USART_Cmd(USART1, ENABLE);	// ����1ʹ��
}

void usart1_sendstring(char *str)
{
	while(*str != '\0')
	{
		USART_SendData(USART1, *str);					// �����������ݷ��ͻ�ȥ
		str++;
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		// �ȴ��������ݼĴ���Ϊ��
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		// �ȴ�������
}

// �ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USART1, (uint8_t) ch);

		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


