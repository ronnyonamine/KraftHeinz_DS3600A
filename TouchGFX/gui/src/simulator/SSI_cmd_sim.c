/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/
#ifdef SIMULATOR

#include <gui/simulator/SSI_cmd.h>
#include <gui/simulator/user_cfg.h>
#include <stdio.h>
#include "string.h"
#include <gui/simulator/SSI_cmd_sim.h>

// Codebase update
bool manualEditBarcodeFlag = false;
int TransmitDecodeDataCompleteFlag = 1;
bool sendLocbarcodeFlag =false;

uint8_t InventListFullFlag = 0;

//Session command
#define LARGE_DATA_SIZE     250
#define LARGE_QUANTITY        5
#define SESSION_DATA_TIME     8
#define WAIT_COUNT_NUMBER    11

//Inventory
Invt_Record_t  InventoryRecordData[20];
uint8_t InventoryRecordIndex = 0;
bool invt_in_progress = false;

#define DECODE_DATA_BUFFER_NUMBER 6
uint8_t GuiFilterFlag = 1;

uint16_t sample_multiple_data_size = 0;

bool scannerMsgRx = false;
//Session command
uint32_t SessionLocReqTime=0;
uint32_t DecodeDataSize = 0;
uint32_t TotalDataSize = 0;
int DecodeWaitSessionTimeoutCount = 0;
uint16_t SessionQuantity = 0;
uint8_t LargeDataSizeFlag = 0;
uint8_t SessionLocKReqCheckFlag = 0;
uint8_t SessionLocKReqErrorFlag = 0;
uint8_t SessionLockBegFlag = 0;

//Battery
uint8_t ChargingMode = 0;
uint16_t  BatteryPercentageValue = 0;

//Configuration
//static uint16_t LocationBardcodeQuantity = 0;
uint8_t ResendDecodeDataFlag = 1;
uint8_t LaunchScreenState = 0;
uint8_t FirstBSpQspiInitFlag = 1;
uint8_t ConfigPermanentFlag = 0;
uint8_t GetFlashConfigurationToGUIFlag = 0;


//Configuration command
int TransmitConfigurationDataCompleteFlag = 1;
uint16_t TotalParamSendDataLength = 0;
uint16_t ConfigRxDataIndex = 0;

void SendBootupCommand(void);
uint16_t temp_sendcount = 0;

/**
* @brief This function gets the inventory data from GUI.
*/
void set_invt_record(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity)
{
	strcpy(InventoryRecordData[InventoryRecordIndex].barcode, barcode->data);
	strcpy(InventoryRecordData[InventoryRecordIndex].location, location->data);
	InventoryRecordData[InventoryRecordIndex].BardcodeLength = strlen(barcode->data);
	InventoryRecordData[InventoryRecordIndex].LocationLength = location->length;
	InventoryRecordData[InventoryRecordIndex].quantity = quantity;
	InventoryRecordIndex++;
	return;
}

/**
* @brief This function gets the inventory data from memory.
*/
Invt_Record_t * get_invt_record(uint16_t index)
{
  if (index < InventoryRecordIndex)
  {
    return &InventoryRecordData[index];
  }
  return NULL;
}

/**
* @brief This function will output the inventory data to ICOND.
*/
void submit_invt_list(void)
{
  /* Do nothing */
}

/**
 * @brief Change the location of record use new location.
 */
void change_loc(LocRecord_t *old_loc, LocRecord_t *new_loc)
{
	return;
}

/**
 * @brief Set flag if inventory data in store
 */
void set_invt_in_progress(bool setting)
{
  invt_in_progress = setting;
}

/**
 * @brief The function gets the inventory process status.
 */
bool get_invt_in_progress(void)
{
  return invt_in_progress;
}

/**
 * @brief The function recalls the transmission data .
 */
char *Recall_Barcode(void)
{
  return NULL;
}

void SendAvoidTransmissionDecodeDataCommand(void)
{
	return;
}

void SendInventoryListFullCommand(void)
{
	return;
}

void clear_item_list_flag(void)
{
  return;
}


/**
* @brief This function gets sends the total quantity of the inventory.
*/
uint16_t send_total_qty_invt()
{
    return 37;
}

uint16_t send_count_invt()
{
  return 21;
}

/**
 * @brief The function gets image view command from GUI.
 */
void set_img_view_cmd(uint16_t cmd)
{
	return;
}

/**
 * @brief This function exposes the inventory full flag
 */
uint8_t get_inv_list_full_flag(void)
{
  return 0;
}

uint8_t get_out_in_list_full_flag(void)
{
  return 0;
}

void set_splashscreen_active(bool state)
{
   
}

bool get_scannerMsgRx_status(void)
{
  return(true);
}
/**
* @brief This function sends bootup command to ICOND.
*/
void SendBootupCommand(void)
{
}


#endif // SIMULATOR

