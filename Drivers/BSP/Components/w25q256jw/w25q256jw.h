/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W25Q256JW_H
#define __W25Q256JW_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Exported types -----------------------------------------------------------*/

/* Exported constants -------------------------------------------------------*/
/* QSPI Error codes */
#define QSPI_OK            ((uint8_t)0x00)
#define QSPI_ERROR         ((uint8_t)0x01)
#define QSPI_BUSY          ((uint8_t)0x02)
#define QSPI_NOT_SUPPORTED ((uint8_t)0x04)
#define QSPI_SUSPENDED     ((uint8_t)0x08)

/* Exported macro -----------------------------------------------------------*/

/* Exported functions prototypes --------------------------------------------*/
uint8_t W25Q256JW_QSPI_Init(OSPI_HandleTypeDef *hqspi);
uint8_t W25Q256JW_QSPI_EnableMemoryMappedMode(OSPI_HandleTypeDef *hqspi);

/* Exported data prototypes -------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __W25Q256JW_H */

