#ifndef __EEPROM_EMU_H
#define __EEPROM_EMU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Exported constants --------------------------------------------------------*/
/** @defgroup xported Constants
  * @{
  */
/* Error codes */
typedef enum{
	EEP_SUCCESS = 0,
	EEP_ERROR
}EEPROM_STATUS;

#define EE_ELEMENT_SIZE		(32)
#define EE_VARIABLE_SIZE        (4)			// [16 bit Virtual address] [16 bit Value]
#define EE_BITMAP_SIZE		(EE_ELEMENT_SIZE / 8)

#define BLOCK_TAG_SIZE		(16)
#define BLOCK_PAGES 		(2)
#define BLOCK_SIZE 		(4096)			//4096 Bytes Per Sector [ W25Q256JW ]
#define FL_PAGE_SIZE 		(4096)

#define MAGIC_KEY		(0x55AA)

enum {
	BLOCK_STATUS_ERASED    = 0xFF,
	BLOCK_STATUS_RECEIVING = 0xAA,
	BLOCK_STATUS_ACTIVE    = 0x00
};

enum{
	FROM_BLOCK0_TO_BLOCK1 = 0x80,
	FROM_BLOCK1_TO_BLOCK0,
};

#define StatusIsUnknown(x)  (!(x == BLOCK_STATUS_ERASED 	\
                              || x == BLOCK_STATUS_RECEIVING 	\
                              || x == BLOCK_STATUS_ACTIVE))

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup Exported Types
  * @{
  */
/* EEPROM EMU Info */
/*
@ Limit this structure to 16 bytes (BLOCK_TAG_SIZE)
*/
#pragma pack (1)
typedef struct{
uint8_t 	BlockStatus;
/*uint8_t*/uint16_t 	DeviceID;
uint8_t 	MagicNum[12];
uint8_t		Reserved;
} BlockInfo_t;
#pragma pack ()

typedef struct{
uint16_t 	addr;
uint16_t 	value;
} EE_Element_t;

typedef struct{
uint16_t   	idx;	//0 or 1
uint32_t 	addr; 	//Current block start address
uint32_t 	tail; 	//Current block write pointer offset
} EEPROMInfo_t;

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup Exported Functions
  * @{
  */
void     EEPROM_EMU_Init(uint32_t located_address);
uint32_t EEPROM_EMU_WriteByte(uint32_t virtualaddr, uint8_t value);
uint32_t EEPROM_EMU_WriteMultiByte(uint32_t virtualaddr, uint8_t *wBuf, uint32_t count);
uint32_t EEPROM_EMU_ReadByte(uint32_t virtualaddr, uint8_t *byte);
uint32_t EEPROM_EMU_ReadMultiByte(uint32_t virtualaddr, uint8_t *rBuf, uint32_t count);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
