/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hw_cfg.h"
#include "stdio.h"
#include "scan.h"

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_TimeBase
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay;
__IO uint32_t counting = 0;
extern __IO uint8_t scan_flag;

__IO uint8_t no_exti = 0;
__IO uint8_t exti_flag = 0;//record which pin has interrupt

__IO uint8_t keys[12] = {0};
uint8_t i;

__IO uint16_t usart_number = 0;//function keys
uint32_t exti_number = 0;
__IO uint8_t usart_count = 0;
__IO uint8_t exti_count = 0;

__IO uint8_t function_flag = 0;
int password = 1234;


/* Private function prototypes -----------------------------------------------*/



/* Private functions ---------------------------------------------------------*/
void init(void);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  NVIC_Config();
  USART_Config();
  USART_ITConfig(EVAL_COM1, USART_IT_RXNE, ENABLE);

	while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
  {}
    
	if (SysTick_Config(SystemCoreClock / 1000))
  {
    /* Capture error */ 
    while (1);
  }

  scan_init();
  
  EXTI4_15_Config();
  TIM_Config();
  TIM_Cmd(TIM3, DISABLE);

	for(i = 0; i < 12; i ++){
    keys[i] = 0;
  }


/*------------------------------------------------------------------------------------------*/  
	while (1)
  {
    if(exti_number == password && exti_count == 4)
    {
      printf("\r\n match\r\n");
      exti_number = 0;
      exti_count = 0;
    }
    else if(exti_count == 4)
    {
      printf("\r\n error password\r\n");
      exti_number = 0;
      exti_count = 0;
    }

    if(function_flag == 0x0023 && usart_number == 10)
    {
      usart_count = 0;
      usart_number = 0;
      EXTI_InitStructure.EXTI_Line = EXTI_Line8|EXTI_Line5|EXTI_Line6;  
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
      EXTI_InitStructure.EXTI_LineCmd = DISABLE;
      EXTI_Init(&EXTI_InitStructure);
      printf("\r\n new password : \r\n");
      while(usart_count < 4)
      {
        password = usart_number;
      }
      password = usart_number;
      EXTI_InitStructure.EXTI_Line = EXTI_Line8|EXTI_Line5|EXTI_Line6;  
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//DISABLE
      EXTI_Init(&EXTI_InitStructure);
      usart_number = 0;
      usart_count = 0;
      function_flag = 0;
      printf("\r\n password changed\r\n");
    }
    else if(function_flag == 0x0023)
    {
      printf("\r\n error function\r\n");
      usart_number = 0;
      usart_count = 0;//­p¼Æ­«¸m
      function_flag = 0;
    }

    switch(exti_flag)
		{
        case 8:
        Delay(2);   

        if( GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) == RESET )
        {

          exti_flag = 0;
        break;
        }

        no_exti = 1;
        scan8();
        exti_count ++;

        if(keys[1] + keys[4] +keys[7] + keys[10] > 0)
        {
          if(scan_flag == 10)
          {
            printf("star");
          }
          else
          {
            printf("%d", scan_flag);
            exti_number = exti_number *10 + scan_flag;
          }
        }  

        while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) != RESET){}
        Delay(5);
        exti_flag = 0;
        no_exti = 0;
        for(i = 0; i < 12; i ++)
        {
          keys[i] = 0;
        }

      break;

      case 6:
        Delay(2);

        if( GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == RESET )
        {

          exti_flag = 0;
          break;
        }
        no_exti = 1;
        scan6();
        exti_count ++;

        if(keys[2] + keys[5] +keys[8] + keys[0] > 1)
        {
          printf("%d", scan_flag);
          exti_number = exti_number *10 + scan_flag;
        }  

        while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) != RESET){}
        Delay(5);
        exti_flag = 0;
        no_exti = 0;

        for(i = 0; i < 12; i ++)
        {
          keys[i] = 0;
        }
      break;

      case 5:
        Delay(2);

        if( GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == RESET )
        {

          exti_flag = 0;
          break;
        }
        no_exti = 1;
        scan5();
        exti_count ++;

        if(keys[3] + keys[6] +keys[9] + keys[11] > 1)
        {
          if(scan_flag == 11)
          {
            printf("number");
          }
          else
          {
            printf("%d", scan_flag);
            exti_number = exti_number *10 + scan_flag;
          }
        }  

        while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) != RESET){}
        Delay(5);
        exti_flag = 0;
        no_exti = 0;
          for(i = 0; i < 12; i ++)
        {
          keys[i] = 0;
        }
      default:
      break;
	}
}

}

void init(void)
{
  usart_number = 0;
  exti_number = 0;
  usart_count = 0;
  exti_count = 0;
}


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
