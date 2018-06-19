#include "scan.h"
#include "stdio.h"
#include "stm32f0xx.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t tmp = 0;
__IO uint8_t pressed = 0;
__IO uint8_t scan_flag;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void scan_init(void);
void scan8(void);
void scan6(void);
void scan5(void);

extern __IO uint8_t keys[];


void scan_init(void)
{
GPIO_InitTypeDef   GPIO_InitStructure;
    /* Enable GPIO */ 
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStructure);

RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOC, &GPIO_InitStructure);

GPIOA->BSRR = GPIO_Pin_6 | GPIO_Pin_7;
GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_12;
}

void scan8(void)
{ 
  
  TIM_Cmd(TIM3, ENABLE);

  tmp = pressed;
  GPIOA->BRR = GPIO_Pin_6 | GPIO_Pin_7;
  GPIOC->BRR = GPIO_Pin_12;
  GPIOC->BSRR = GPIO_Pin_10;
  while(pressed < tmp + 5){
    GPIOA->BRR = GPIO_Pin_7;
    GPIOC->BSRR = GPIO_Pin_10;
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) != RESET){
      keys[1] ++;
    }
    GPIOC->BRR = GPIO_Pin_10;
    GPIOC->BSRR = GPIO_Pin_12;
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) != RESET){
      keys[4] ++;
    }
    GPIOA->BSRR = GPIO_Pin_6;
    GPIOC->BRR = GPIO_Pin_12;
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) != RESET){
      keys[7] ++;
    }
    GPIOA->BRR = GPIO_Pin_6;
    GPIOA->BSRR = GPIO_Pin_7;
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) != RESET){
      keys[10] ++;
    }
  }

  scan_flag = keys[1] > keys[4] ? (keys[1] > keys[7]?(keys[1] > keys[10] ? 1:10):(keys[7] > keys[10] ? 7:10)):(keys[4] > keys[7]?(keys[4] > keys[10] ? 4:10):(keys[7] > keys[10] ? 7:10));
  TIM_Cmd(TIM3, DISABLE);

  GPIOA->BSRR = GPIO_Pin_6 | GPIO_Pin_7;
  GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_12;
}

void scan6(void)
{   
  TIM_Cmd(TIM3, ENABLE);

  tmp = pressed;
  GPIOA->BRR = GPIO_Pin_6 | GPIO_Pin_7;
  GPIOC->BRR = GPIO_Pin_12;
  GPIOC->BSRR = GPIO_Pin_10;
  while(pressed < tmp + 5){
    GPIOA->BRR = GPIO_Pin_7;
    GPIOC->BSRR = GPIO_Pin_10;

    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) != RESET){
      keys[2] ++;
    }
    GPIOC->BRR = GPIO_Pin_10;
    GPIOC->BSRR = GPIO_Pin_12;
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) != RESET){
      keys[5] ++;
    }
    GPIOA->BSRR = GPIO_Pin_6;
    GPIOC->BRR = GPIO_Pin_12;
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) != RESET){
      keys[8] ++;
    }
    GPIOA->BRR = GPIO_Pin_6;
    GPIOA->BSRR = GPIO_Pin_7;
    if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) != RESET){
      keys[0] ++;
    }
  }

  scan_flag = keys[2] > keys[5] ? (keys[2] > keys[8]?(keys[2] > keys[0] ? 2:0):(keys[8] > keys[0] ? 8:0)):(keys[5] > keys[8]?(keys[5] > keys[0] ? 5:0):(keys[8] > keys[0] ? 8:0));

  GPIOA->BSRR = GPIO_Pin_6 | GPIO_Pin_7;
  GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_12;

}

void scan5(void)
{ 
  TIM_Cmd(TIM3, ENABLE);

  tmp = pressed;
  GPIOA->BRR = GPIO_Pin_6 | GPIO_Pin_7;
  GPIOC->BRR = GPIO_Pin_12;
  GPIOC->BSRR = GPIO_Pin_10;
  while(pressed < tmp + 5){
  GPIOA->BRR = GPIO_Pin_7;
  GPIOC->BSRR = GPIO_Pin_10;

  if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) != RESET){
    keys[3] ++;
  }
  GPIOC->BRR = GPIO_Pin_10;
  GPIOC->BSRR = GPIO_Pin_12;
  if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) != RESET){
    keys[6] ++;
  }
  GPIOA->BSRR = GPIO_Pin_6;
  GPIOC->BRR = GPIO_Pin_12;
  if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) != RESET){
    keys[9] ++;
  }
  GPIOA->BRR = GPIO_Pin_6;
  GPIOA->BSRR = GPIO_Pin_7;
  if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) != RESET){
    keys[11] ++;
  }
}

  scan_flag = keys[3] > keys[6] ? (keys[3] > keys[9]?(keys[3] > keys[11] ? 3:11):(keys[9] > keys[11] ? 9:11)):(keys[6] > keys[9]?(keys[6] > keys[11] ? 6:11):(keys[9] > keys[11] ? 9:11));

  GPIOA->BSRR = GPIO_Pin_6 | GPIO_Pin_7;
  GPIOC->BSRR = GPIO_Pin_10 | GPIO_Pin_12;

}


/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
