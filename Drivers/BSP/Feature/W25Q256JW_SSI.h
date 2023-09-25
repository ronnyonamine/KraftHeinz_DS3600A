/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W25Q256JW_H
#define __W25Q256JW_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @defgroup W25Q256JW_Exported_Constants
  * @{
  */
#ifdef EXTERNAL_32MB
/**
  * @brief  W25Q256JW Configuration
  */
//32MB
#define W25Q256JW_FLASH_SIZE                  0x2000000   /* 256 MBits => 32 MByte */
#define W25Q256JW_SECTOR_SIZE                 4096        /* 4 kBytes  Per Sector */
#define W25Q256JW_PAGE_SIZE                   256         /* 256 bytes Per page */
#else
/**
  * @brief  W25Q128JW Configuration
  */
//16MB
#define W25Q256JW_FLASH_SIZE                  0x1000000   /* 128 MBits => 16 MByte */
#define W25Q256JW_SECTOR_SIZE                 4096        /* 4 kBytes  Per Sector */
#define W25Q256JW_PAGE_SIZE                   256         /* 256 bytes Per page */
#endif

#define W25Q256JW_DUMMY_CYCLES_READ           		8

#define W25Q256JW_CHIP_ERASE_MAX_TIME         		400000	  	/* 400 sec */
#define W25Q256JW_BLOCK_ERASE_MAX_TIME        		2000        /* 2000 ms */
#define W25Q256JW_SECTOR_ERASE_MAX_TIME       		400         /* 400 ms  */

/**
  * @brief  W25Q256JW Commands
  */

/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

/* Identification Operations */
#define READ_JEDEC_ID_CMD                    0x9F

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define READ_STATUS_REG_2_CMD                0x35
#define READ_STATUS_REG_3_CMD                0x15
#define WRITE_STATUS_REG_CMD                 0x01
#define WRITE_STATUS_REG_2_CMD               0x31
#define WRITE_STATUS_REG_3_CMD               0x11

/* Read Operations */
#define FAST_READ_QUAD_OUT_CMD_4B            0x6C
#define FAST_READ_QUAD_OUT_CMD               0x6B

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define VOL_SR_WRITE_ENABLE_CMD              0x50

/* Program Operations */
#define QUAD_PAGE_PROG_CMD_4B                0x34
#define QUAD_PAGE_PROG_CMD                   0x32

/* Erase Operations */
#define BLOCK_ERASE_64K_CMD_4B               0xDC
#define BLOCK_ERASE_64K_CMD                  0xD8
#define CHIP_ERASE_CMD                       0xC7
#define SECTOR_ERASE_CMD_4B                  0x21
#define SECTOR_ERASE_CMD                     0x20

/* Power-down operations */

/* Other operations */

/**
  * @brief  W25Q256JW Registers
  */
/* Status Register 1 */
#define W25Q256JW_SR_BUSY                     ((uint8_t)0x01)    /*!< Erase/Write in progress */
#define W25Q256JW_SR_WEL                      ((uint8_t)0x02)    /*!< Write enable latch */
#define W25Q256JW_SR_BP                       ((uint8_t)0x3C)    /*!< Block protected bits */
#define W25Q256JW_SR_TB                       ((uint8_t)0x40)    /*!< Top/Bottom protect */
#define W25Q256JW_SR_SRP                      ((uint8_t)0x80)    /*!< Status register protect */

/* Status Register 2 */
#define W25Q256JW_SR2_SRL                     ((uint8_t)0x01)    /*!< Status Register Lock */
#define W25Q256JW_SR2_QE                      ((uint8_t)0x02)    /*!< Quad Enable */
#define W25Q256JW_SR2_LB                      ((uint8_t)0x3C)    /*!< Security Register Lock bits */
#define W25Q256JW_SR2_CMP                     ((uint8_t)0x40)    /*!< Complement protect */
#define W25Q256JW_SR2_SUS                     ((uint8_t)0x80)    /*!< Suspend Status */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __W25Q256JW_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/*****END OF FILE****/
