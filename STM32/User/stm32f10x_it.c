/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include <string.h>
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

receive_stack rx_stack;

void rx_stack_init()
{
    rx_stack.head = '!';         //????,???
    memset(rx_stack.data, 's', sizeof(rx_stack.data));//?tx_stack.data[]???????
	  rx_stack.tail = '~';         //????,???
    rx_stack.data_pt = 0;
    rx_stack.lock_flag = 0;
}

// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
{
  //uint8_t ch;
	//if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	//{		
	//	ch = USART_ReceiveData(DEBUG_USARTx);
	//	printf("%c", ch);
		//ucTemp = USART_ReceiveData(DEBUG_USARTx);
    // USART_SendData(DEBUG_USARTx,ucTemp);
		//Usart_SendString( DEBUG_USARTx, ucTemp);
	//}	 
	u8 receive_data;
	if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET) //??????????
	{
			receive_data = USART_ReceiveData(DEBUG_USARTx);         //???????????
			if(rx_stack.lock_flag == 0)                   //??????????
			{
					if(receive_data == '!')
					{
							rx_stack.head = receive_data;
					}
					else if(receive_data == '~')
					{
							rx_stack.tail = receive_data;
							rx_stack.data_pt = 0;
							rx_stack.lock_flag = 1;
					}
					else
					{
							rx_stack.data[rx_stack.data_pt] = receive_data;
							rx_stack.data_pt++;
							if(rx_stack.data_pt > 5)// && (rx_stack.tail == 0xdd))
							{
									rx_stack.data_pt = 0;
									rx_stack.lock_flag = 1;
							}
					}
			}
			USART_ClearITPendingBit(DEBUG_USARTx, USART_IT_RXNE);//????????
	}
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
