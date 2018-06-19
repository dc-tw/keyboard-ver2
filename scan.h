/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SCAN_H
#define __SCAN_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "stm32f0xx.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void scan_init(void);
void scan8(void);
void scan6(void);
void scan5(void);

#ifdef __cplusplus
}
#endif

#endif /* __HW_CFG_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
