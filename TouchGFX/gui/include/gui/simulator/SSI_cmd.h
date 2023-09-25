/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

#ifndef __SSI_CMD_H
#define __SSI_CMD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "string.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>


#define SET_ATTR_FLAG         0x00000001U
#define SET_ATTR_RSP_FLAG     0x00000002U
#define GET_ATTR_FLAG         0x00000003U
#define GET_ATTR_RSP_FLAG     0x00000004U
#define MAX_TRY               3

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

typedef unsigned char      BYTE;
typedef unsigned short     WORD;
typedef signed   short     SWORD;
typedef unsigned long      DWORD;
typedef unsigned char      INT8U;                    /* Unsigned  8 bit quantity                       */
typedef signed   char      INT8S;                    /* Signed    8 bit quantity                       */
typedef unsigned short     INT16U;                   /* Unsigned 16 bit quantity                       */
typedef signed   short     INT16S;                   /* Signed   16 bit quantity                       */
typedef unsigned long      INT32U;                   /* Unsigned 32 bit quantity                       */

#define RSM_CMD_LEN       240 
#define VAR_LENGTH_ARRAY  2

// Attribute types
#define ATT_TYPE_ARRAY   'A'
#define ATT_TYPE_BYTE    'B'
#define ATT_TYPE_CHAR    'C'
#define ATT_TYPE_DWORD   'D'
#define ATT_TYPE_FLAG    'F'
#define ATT_TYPE_INT     'I'
#define ATT_TYPE_LONGINT 'L'
#define ATT_TYPE_STRING  'S'
#define ATT_TYPE_WORD    'W'
#define ATT_TYPE_ACTION  'X'
#define ATT_TYPE_NONE    'N'        /* for special table entries */

extern int SSIsleepFlag;
extern uint8_t InventListFullFlag;
extern uint8_t OutInMatchListFullFlag;

#define PSRAM_BUFFER_SIZE              (0x1000)

#define  DisplayTimeoutOffset                 0
#define  FunctionKeyF1Offset                  DisplayTimeoutOffset + 1
#define  FunctionKeyStringF1Offset            FunctionKeyF1Offset +1
#define  FunctionKeyF2Offset                  FunctionKeyStringF1Offset + 20
#define  FunctionKeyStringF2Offset            FunctionKeyF2Offset + 1
#define  FunctionKeyF3Offset                  FunctionKeyStringF2Offset + 20
#define  FunctionKeyStringF3Offset            FunctionKeyF3Offset + 1
#define  FunctionKeyF4Offset                  FunctionKeyStringF3Offset + 20
#define  FunctionKeyStringF4Offset            FunctionKeyF4Offset + 1
#define  FunctionKeyF5Offset                  FunctionKeyStringF4Offset + 20
#define  FunctionKeyStringF5Offset            FunctionKeyF5Offset + 1
#define  FunctionKeyF6Offset                  FunctionKeyStringF5Offset + 20
#define  FunctionKeyStringF6Offset            FunctionKeyF6Offset + 1
#define  FunctionKeyF7Offset                  FunctionKeyStringF6Offset + 20
#define  FunctionKeyStringF7Offset            FunctionKeyF7Offset + 1
#define  FunctionKeyF8Offset                  FunctionKeyStringF7Offset + 20
#define  FunctionKeyStringF8Offset            FunctionKeyF8Offset + 1
#define  FunctionKeyF9Offset                  FunctionKeyStringF8Offset + 20
#define  FunctionKeyStringF9Offset            FunctionKeyF9Offset + 1
#define  GlobalManualBarcodeEntryOffset       FunctionKeyStringF9Offset + 20
#define  GlobalManualQuantityEntryOffset      GlobalManualBarcodeEntryOffset + 1
#define  AutoDisplayBrightnessOffset          GlobalManualQuantityEntryOffset + 1
#define  KeypadBacklightOffset                AutoDisplayBrightnessOffset + 1
#define  HomeKeyLaunchOffset                  KeypadBacklightOffset + 1
#define  QuantityManualBarcodeEntryOffset     HomeKeyLaunchOffset + 1
#define  QuantityManualQuantityEntryOffset    QuantityManualBarcodeEntryOffset + 1
#define  QuantityTimeoutOffset                QuantityManualQuantityEntryOffset + 1
#define  QuantityTimeoutStringOffset          QuantityTimeoutOffset + 1
#define  LocationManualBarcodeEntryOffset     QuantityTimeoutStringOffset + 1
#define  LocationManualQuantityEntryOffset    LocationManualBarcodeEntryOffset + 1
#define  LocationLOCDelimiterOffset           LocationManualQuantityEntryOffset + 1
#define  LocationLOCDelimiterStingOffset      LocationLOCDelimiterOffset + 1
#define  InventoryManualBarcodeEntryOffset    LocationLOCDelimiterStingOffset + 1
#define  InventoryManualQuantityEntryOffset   InventoryManualBarcodeEntryOffset + 1
#define  InventoryLOCDelimiterOffset          InventoryManualQuantityEntryOffset + 1
#define  InventoryLOCDelimiterStringOffset    InventoryLOCDelimiterOffset + 1
#define  InventoryStoreOffset                 InventoryLOCDelimiterStringOffset + 1
#define  ShowLiveCaptureOffset                InventoryStoreOffset + 1
#define  DisplayOnChargeOffset                ShowLiveCaptureOffset + 1
//Function key user define
#define  FunctionKeyF1UserDefineOffset        DisplayOnChargeOffset + 1
#define  FunctionKeyF2UserDefineOffset        FunctionKeyF1UserDefineOffset + 1
#define  FunctionKeyF3UserDefineOffset        FunctionKeyF2UserDefineOffset + 1
#define  FunctionKeyF4UserDefineOffset        FunctionKeyF3UserDefineOffset + 1
#define  FunctionKeyF5UserDefineOffset        FunctionKeyF4UserDefineOffset + 1
#define  FunctionKeyF6UserDefineOffset        FunctionKeyF5UserDefineOffset + 1
#define  FunctionKeyF7UserDefineOffset        FunctionKeyF6UserDefineOffset + 1
#define  FunctionKeyF8UserDefineOffset        FunctionKeyF7UserDefineOffset + 1
#define  FunctionKeyF9UserDefineOffset        FunctionKeyF8UserDefineOffset + 1
#define  KeyboardInjectOffset                 FunctionKeyF9UserDefineOffset + 1

#define  FinalParameterNumberOffset           KeyboardInjectOffset


#define F_StringDisplacement   9  // index displacement to get from F1 to F1String 
typedef enum
{
  SSI_OK       = 0x00,
  SSI_ERROR    = 0x01,
  SSI_BUSY     = 0x02,
  SSI_TIMEOUT  = 0x03
} SSI_StatusTypeDef;

typedef enum {
  ABORT_MACRO_PDF        = 0x11,
  AIM_OFF                = 0xC4,
  AIM_ON                 = 0xC5,
  BATCH_DATA             = 0xD6,
  BATCH_REQUEST          = 0xD5,
  BEEP                   = 0xE6,
  CAPABILITIES_REQUEST   = 0xD3,
  CAPABILITIES_REPLY     = 0xD4,
  CHANGE_ALL_CODE_TYPES  = 0xC9,
  CMD_ACK                = 0xD0,
  CMD_ACK_ACTION         = 0xD8,
  CMD_NAK                = 0xD1,
  CUSTOM_DEFAULTS        = 0x12,
  DECODE_DATA            = 0xF3,
  EVENT                  = 0xF6,
  FLUSH_MACRO_PDF        = 0x10,
  FLUSH_QUEUE            = 0xD2,
  ILLUMINATION_OFF       = 0xC0,
  ILLUMINATION_ON        = 0xC1,
  IMAGE_DATA             = 0xB1,
  IMAGER_MODE            = 0xF7,
  LED_OFF                = 0xE8,
  LED_ON                 = 0xE7,
  PAGER_MOTOR_ACTIVATION = 0xCA,
  PARAM_DEFAULTS         = 0xC8,
  PARAM_REQUEST          = 0xC7,
  PARAM_SEND             = 0xC6,
  REPLY_REVISION         = 0xA4,
  REQUEST_REVISION       = 0xA3,
  SCAN_DISABLE           = 0xEA,
  SCAN_ENABLE            = 0xE9,
  SLEEP                  = 0xEB,
  SSI_MGMT_COMMAND       = 0x80,
  START_SESSION          = 0xE4,
  STOP_SESSION           = 0xE5,
  VIDEO_DATA             = 0xB4,
  TEST_MODE              = 0x60,
  SESSION_LOCK_REQ       = 0x70,
  SESSION_LOCK_BEG       = 0x71,
  SESSION_LOCK_END       = 0x72
} Opcode_ID;

typedef enum {
  Decoder,
  Host = 0x04,
  SI_Side = 0x01,
  Canopy = 0x04
} MSGSource;

typedef union {
  struct {
    unsigned char Retransmit:1;
    unsigned char intContinuation:1;
    unsigned char intReserved:1;
    unsigned char Change_Type:1;
    unsigned char Unused:4;
  } fields;
  unsigned char value;
} SSI_Status;

typedef struct _SSI_COMD
{
  uint8_t Length;
  Opcode_ID Opcode;
  MSGSource MsgSource;
  uint8_t Status;
  uint8_t Other;
  uint8_t Data[251];
  uint16_t Checksum;
  uint32_t PushMultipleDataSize;
  uint16_t PushDecodeDataQuantity;
  uint8_t RsmDataMode;
} SSI_COMD;

typedef struct _Image_Preamble
{
  uint32_t imgSize;
  uint16_t imgWidth;
  uint16_t imgHeight;
  uint8_t imgType;
  uint8_t BitsperPixel;
} Image_Preamble;

typedef enum  {
  TEST_LCD=0x01,
  TEST_LCD_PWM,
  TEST_LED,
  TEST_Light_Sensor,
  TEST_Keyboard,
  Enter_Test_Mode = 0xF1,//did't use at bootloader mode
  Exit_Test_Mode,
}Test_mode_type;

//Remote Scanner Management (RSM)
//Attribute command
typedef enum {
  ATTRIBUTE_GETALL = 0x01,
  ATTRIBUTE_GET = 0x02,
  ATTRIBUTE_SET = 0x05,
  ATTRIBUTE_STORE = 0x06,
  //Flash update
  MGMT_FLASH_RECORD = 0x64,
  MGMT_FLASH_START = 0x65,
  ATTRIBUTE_GET_INFO = 0x71
} RSM_Opcode;

typedef enum {
  Ping          = 0x01,
  Session_Start = 0x02,
  Session_End   = 0x03,
  DL_Start      = 0x04,
  DL_Block      = 0x05,
  DL_End        = 0x06,
  Change_Baud   = 0x07,
  Enter_FAT     = 0x08,
  Session_info  = 0x09,
  Jump_Address  = 0x0A,
  Set_GUID      = 0x0B,
  Read_SC       = 0x0C
} Flash_command_Opecode_list;

typedef enum {
  Resp_Ping          = 0x81,
  Resp_Session_Start = 0x82,
  Resp_Session_End   = 0x83,
  Resp_DL_Start      = 0x84,
  Resp_DL_Block      = 0x85,
  Resp_DL_End        = 0x86,
  Resp_Change_Baud   = 0x87,
  Resp_Enter_FAT     = 0x88,
  Resp_Session_info  = 0x89,
  Resp_Jump_Address  = 0x8A,
  Resp_Set_GUID      = 0x8B,
  Resp_Read_SC       = 0x8C
} Flash_command_Opecode_resp;

typedef enum {
  BATTERY_PERCENTAGE = 0x753C,
  BATTERy_CHARGE_STATUS = 0x754A,
  BATTERY_HEALTH = 0x753D,
  SCANNER_BATCH_MODE_STATUS = 0x13A5
}GET_Attribute;

typedef enum {
  BLUETOOTH_STATUS = 0x1770,
  Bootup = 0x1773,
  Reboot = 0x1774,
  FIPS_MODE = 0x02E0,
  BLUETOOTH_AUTORECONNECT = 0x025C
}SET_Attribute;

typedef enum {
  Type_B  = 0x42,
  Type_C  = 0x43,
  Type_F  = 0x46,
  Type_W  = 0x57,
  Type_I  = 0x49,
  Type_D  = 0x44,
  Type_L  = 0x4C,
  Type_A  = 0x41,
  Type_S  = 0x53,
  Type_X  = 0x58
} Attribute_Type;

typedef enum {
  Connect_Attemp   = 0x41,
  Connect_Event    = 0x6D,
  Disconnect_Event = 0x6E,
  Page_Timeout     = 0xC2,
  Connect_Reject   = 0xC3
} BT_Status;

typedef struct _RSM_ATTRIBUTE_COMD
{
  uint8_t Length;
  Opcode_ID Opcode;
  MSGSource MsgSource;
  uint8_t Status;
  uint8_t Other;
  uint8_t Data[251];
  uint16_t Checksum;
  //Attribute
  uint8_t RsmLengthMSB;
  uint8_t RsmLengthLSB;
  uint8_t RsmOpcode;
  uint8_t RsmStatus;
  uint8_t AttributeMSB;
  uint8_t AttributeLSB;
  uint8_t AttributeType;
  uint8_t AttributeProperties;
  uint8_t AttributeValueMSB;
  uint8_t AttributeValueLSB;
  uint8_t AttributeValue;
  uint8_t AttributeStringProperties;
  uint8_t AttributeStringLengthMSB;
  uint8_t AttributeStringLengthLSB;
  uint8_t AttributeStringOffsetMSB;
  uint8_t AttributeStringOffsetLSB;
  uint16_t AttributeStringLength;
}RSM_ATTRIBUTE_COMD;

typedef struct {
   BYTE properties;
   BYTE byteVal;
} BYTE_VAL_T; 

typedef struct {
   BYTE properties;
   BYTE charVal;
} CHAR_VAL_T;  

typedef struct {
   BYTE properties;
   BYTE flagVal;
} FLAG_VAL_T;  

typedef struct {
   BYTE properties;
   BYTE wordVal_MSB;
   BYTE wordVal_LSB;
} WORD_VAL_T;  

typedef struct {
   BYTE properties;
   BYTE swordVal_MSB;
   BYTE swordVal_LSB;
} SWORD_VAL_T; 

typedef struct {
   BYTE properties;
   BYTE dwordVal_0_MSB;
   BYTE dwordVal_1;
   BYTE dwordVal_2;
   BYTE dwordVal_3_LSB;
} DWORD_VAL_T; 

typedef struct {
   BYTE properties;
   BYTE sdwordVal_0_MSB;
   BYTE sdwordVal_1;
   BYTE sdwordVal_2;
   BYTE sdwordVal_3_LSB;
} SDWORD_VAL_T;

typedef struct {
   BYTE properties;
   BYTE subType;
   BYTE len_MSB;
   BYTE len_LSB;
   BYTE offset_MSB;
   BYTE offset_LSB;
   BYTE arrayVal[VAR_LENGTH_ARRAY]; // Depending on 'sub-type' could be array of 'BYTES' or 'WORDS' or 'DWORDS or ...
} ARRAY_VAL_T;

typedef struct {
   BYTE properties;
   BYTE len_MSB;
   BYTE len_LSB;
   BYTE offset_MSB;
   BYTE offset_LSB;
   BYTE stringVal[VAR_LENGTH_ARRAY];
} STRING_VAL_T;

typedef struct {
   BYTE actionVal;
} ACTION_VAL_T;

typedef struct {
   BYTE attrNum_MSB;
   BYTE attrNum_LSB;
   BYTE type;         // 'B'=Byte, 'C'=Char, 'F'=Flag, 'S'=String ....
   union {
      BYTE_VAL_T   byteVal;
      CHAR_VAL_T   charVal;
      FLAG_VAL_T   flagVal;
      WORD_VAL_T   wordVal;
      SWORD_VAL_T  swordVal;
      DWORD_VAL_T  dwordVal;
      SDWORD_VAL_T sdwordVal;
      ARRAY_VAL_T  arrayVal;
      STRING_VAL_T stringVal;
      ACTION_VAL_T actionVal;
   } u;
} GET_ATTR_VALUE_RSP_T;

typedef struct {
   BYTE attrNum_MSB;
   BYTE attrNum_LSB;
   BYTE type;         // 'B'=Byte, 'C'=Char, 'F'=Flag, 'S'=String ....
   union {
      BYTE_VAL_T   byteVal;
      CHAR_VAL_T   charVal;
      FLAG_VAL_T   flagVal;
      WORD_VAL_T   wordVal;
      SWORD_VAL_T  swordVal;
      DWORD_VAL_T  dwordVal;
      SDWORD_VAL_T sdwordVal;
      ARRAY_VAL_T  arrayVal;
      STRING_VAL_T stringVal;
      ACTION_VAL_T actionVal;
   } u;
} SET_ATTR_VALUE_CMD_T;

typedef struct RSM_SET_ATTR
{
  BYTE attrlen_MSB;
  BYTE attrlen_LSB;
  BYTE attrOp;
  BYTE attrStatus;
  SET_ATTR_VALUE_CMD_T attrInfo;
}SCANNER_RSM_SET_ATTR;

typedef struct RSM_GET_ATTR
{
  BYTE attrlen_MSB;
  BYTE attrlen_LSB;
  BYTE attrOp;
  BYTE attrParamType;
  BYTE attr_MSB;
  BYTE attr_LSB;
}SCANNER_RSM_GET_ATTR;

//PARAM_SEND
typedef enum {
  DataType_String = 0xF3,
  DataType_Word = 0xF4,
  DataType_Array = 0xF6,
  DataType_MultiPacket = 0xF7
} Data_Types;

//Configuration
typedef enum {
  Display_Timeout = 0x0860,
  Function_Key_F1 = 0x0861,
  Function_Key_F2 = 0x0862,
  Function_Key_F3 = 0x0863,
  Function_Key_F4 = 0x0864,
  Function_Key_F5 = 0x0865,
  Function_Key_F6 = 0x0866,
  Function_Key_F7 = 0x0867,
  Function_Key_F8 = 0x0868,
  Function_Key_F9 = 0x0869,
  Global_Manual_Barcode_Entry = 0x086A,
  Global_Manual_Quantity_Entry = 0x086B,
  Auto_Display_Brightness = 0x086C,
  Keypad_Backlight = 0x086D,
  Home_Key_Launch = 0x086E,
  Quantity_Manual_Barcode_Entry = 0x086F,
  Quantity_Manual_Quantity_Entry = 0x0870,
  Quantity_Timeout = 0x0871,
  Location_Manual_Barcode_Entry = 0x0872,
  Location_Manual_Quantity_Entry = 0x0873,
  Location_LOC_Delimiter = 0x0874,
  Inventory_Manual_Barcode_Entry = 0x0875,
  Inventory_Manual_Quantity_Entry = 0x0876,
  Inventory_LOC_Delimiter = 0x0877,
  Inventory_Store = 0x0878,
  Show_Live_Capture = 0x0879,
  Display_On_Charge = 0x087A,
  //Function key custom string
  Function_Key_F1_CustomString = 0x087B,
  Function_Key_F2_CustomString = 0x087C,
  Function_Key_F3_CustomString = 0x087D,
  Function_Key_F4_CustomString = 0x087E,
  Function_Key_F5_CustomString = 0x087F,
  Function_Key_F6_CustomString = 0x0880,
  Function_Key_F7_CustomString = 0x0881,
  Function_Key_F8_CustomString = 0x0882,
  Function_Key_F9_CustomString = 0x0883,
  Keyboard_Inject              = 0x0884,
  FinalParameterNumber = 0x0884,
  All_Defaults = 0xFD,
  All_Parameters = 0xFE
} Parameter_Numbers;

typedef enum
{
  DelimiterValue_CR = 0x0D,
  DelimiterValue_LF = 0x0A,
  DelimiterValue_Space = 0x20,
  DelimiterValue_Tab = 0x09,  //Default
  DelimiterValue_Comma = 0x2C,
  DelimiterValue_Colon = 0x3A,
  DelimiterValue_Semicolon = 0x3B,
  DelimiterValue_EqualsSign = 0x3D
} DelimiterValue;

typedef struct _Decode_data_info {
    uint8_t SSIsinglepacketFlag;
    uint8_t SSImultipacketFlag;
    uint32_t multiple_data_size;
}DecodeDataInfo;

bool SSI_Parser(uint8_t *rx_buffer,uint16_t len);
char *Recall_Barcode(void);
extern void PushDecodeDataBuffer(SSI_COMD *ssi_decode_rx_cmd);

//Configuration
typedef enum {
  KeyF1 = 0x01,
  KeyF2 = 0x02,
  KeyF3 = 0x03,
  KeyF4 = 0x04,
  KeyF5 = 0x05,
  KeyF6 = 0x06,
  KeyF7 = 0x07,
  KeyF8 = 0x08,
  KeyF9 = 0x09,
  KeyF1Str = 0x0a,
  KeyF2Str = 0x0b,
  KeyF3Str = 0x0c,
  KeyF4Str = 0x0d,
  KeyF5Str = 0x0e,
  KeyF6Str = 0x0f,
  KeyF7Str = 0x10,
  KeyF8Str = 0x11,
  KeyF9Str = 0x12
} KeyValue;

//Display Timeout
typedef enum {
  DisplayTimeout_3S = 0x03,
  DisplayTimeout_6S = 0x06,
  DisplayTimeout_12S = 0x0C, //default
  DisplayTimeout_18S = 0x12,
  DisplayTimeout_NoTimeout = 0x00
} Display_Timeout_Item;

typedef enum {
  DisplayTimeout_3S_param = 0x03,
  DisplayTimeout_6S_param = 0x06,  //default
  DisplayTimeout_12S_param = 0x0C,
  DisplayTimeoutParam_18S_param = 0x12,
  DisplayTimeoutParam_NoTimeout_param = 0x00
} Display_Timeout_Param;

//Function Key F1 to F9
typedef enum {
  Unassigned = 0x00,
  Custom_String =0x01,
  FunctionKey_Enter = 0x02,
  FunctionKey_Recall = 0x03,
  FunctionKey_Back = 0x04
} FunctionKey_Item;

typedef enum {
  FunctionKey_Unassigned_param = 0x00,  //default
  FunctionKey_Enter_param = 0x01,
  FunctionKey_Recall_param = 0x02,
  FunctionKey_Back_param = 0x03,
  FunctionKey_UserDefinedString_param = 0x04
} FunctionKey_Param;

//Global Manual Barcode Entry
typedef enum {
  GlobalManualBarcodeEntry_Yes = 0x01,
  GlobalManualBarcodeEntry_No = 0x00   //default
}Global_Manual_Barcode_Entry_Item;

typedef enum {
  GlobalManualBarcodeEntry_No_param = 0x00,   //default
  GlobalManualBarcodeEntry_Yes_param = 0x01
}Global_Manual_Barcode_Entry_Param;

//Global Manual Quantity Entry
typedef enum {
  GlobalManualQuantityEntry_Yes = 0x01,  //default
  GlobalManualQuantityEntry_No = 0x00
}Global_Manual_Quantity_Entry_Item;

typedef enum {
  GlobalManualQuantityEntry_No_param = 0x00,
  GlobalManualQuantityEntry_Yes_param = 0x01  //default
}Global_Manual_Quantity_Entry_Param;

//Auto Display Brightness
typedef enum {
  AutoDisplayBrightness_Enable = 0x01,  //default
  AutoDisplayBrightness_Disable_medium = 0x02,
  AutoDisplayBrightness_Disable_dimmest = 0x03,
  AutoDisplayBrightness_Disable_dim = 0x04,
  AutoDisplayBrightness_Disable_bright = 0x05,
  AutoDisplayBrightness_Disable_brightest = 0x06
} Auto_Display_Brightness_Item;

typedef enum {
  AutoDisplayBrightness_Enable_param = 0x01,  //default
  AutoDisplayBrightness_Disable_medium_param = 0x02,
  AutoDisplayBrightness_Disable_dimmest_param = 0x03,
  AutoDisplayBrightness_Disable_dim_param = 0x04,
  AutoDisplayBrightness_Disable_bright_param = 0x05,
  AutoDisplayBrightness_Disable_brightest_param = 0x06
} Auto_Display_Brightness_Param;

//Keypad Backlight
typedef enum {
  KeypadBacklight_On = 0x01,
  KeypadBacklight_Off = 0x00,
  KeypadBacklight_Auto = 0x02 //default
} Keypad_Backlight_Item;

typedef enum {
  KeypadBacklight_Off_param = 0x00,
  KeypadBacklight_On_param = 0x01,
  KeypadBacklight_Auto_param = 0x02 //default
} Keypad_Backlight_Param;

//Display On Charge
typedef enum {
  DisplayOnCharge_Half = 0x01,
  DisplayOnCharge_3quarter = 0x02,
  DisplayOnCharge_Full = 0x03 //default
}Display_On_Charge_Item;

typedef enum {
  DisplayOnCharge_Half_param = 0x01,
  DisplayOnCharge_3quarter_param = 0x02,
  DisplayOnCharge_Full_param = 0x03 //default
}Display_On_Charge_Param;

//Home Key Launch
typedef enum {
  HomeKeyLaunch_NoneDisable = 0x00,
  HomeKeyLaunch_Navigator = 0x01,  //Default
  HomeKeyLaunch_ScanEnterQTY = 0x02,
  HomeKeyLaunch_ScanQTYLOC = 0x03,
  HomeKeyLaunch_ScanInventory = 0x04,
  HomeKeyLaunch_OIMatch = 0x05,
  HomeKeyLaunch_ImageViewer = 0x06,
} Home_Key_Launch_Item;

typedef enum {
  HomeKeyLaunch_NoneDisable_param = 0x00,
  HomeKeyLaunch_Navigator_param = 0x01,  //Default
  HomeKeyLaunch_ScanEnterQTY_param = 0x02,
  HomeKeyLaunch_ScanQTYLOC_param = 0x03,
  HomeKeyLaunch_ScanInventory_param = 0x04,
  HomeKeyLaunch_OIMatch_param = 0x05,
  HomeKeyLaunch_ImageViewer_param = 0x06
} Home_Key_Launch_Param;

typedef enum
{
  QuantityTransferMode_BCxQTY = 0x01,  //default
  QuantityTransferMode_BC_Delimiter_QTY = 0x02
}Quantity_Transfer_Mode_Item;

typedef enum
{
  QuantityTransferMode_BCxQTY_Param = 0x01,
  QuantityTransferMode_BC_Delimiter_QTY_Param = 0x02
}Quantity_Transfer_Mode_Param;

//Quantity Manual Barcode Entry
typedef enum {
  QuantityManualBarcodeEntry_Yes = 0x01,
  QuantityManualBarcodeEntry_No = 0x00  //default
} Quantity_Manual_Barcode_Entry_Item;

typedef enum {
  QuantityManualBarcodeEntry_No_param = 0x00,  //default
  QuantityManualBarcodeEntry_Yes_param = 0x01
} Quantity_Manual_Barcode_Entry_Param;

//Quantity Manual Quantity
typedef enum {
  QuantityManualQuantity_Yes = 0x01,  //default
  QuantityManualQuantity_No = 0x00
} Quantity_Manual_Quantity_Entry_Item;

typedef enum {
  QuantityManualQuantity_No_param = 0x00,
  QuantityManualQuantity_Yes_param = 0x01  //default
} Quantity_Manual_Quantity_Entry_Param;

//Quantity Timeout
typedef enum
{
  QuantityTimeout_UserConfig = 0x01,
  QuantityTimeout_3S = 0x01,
  QuantityTimeout_6S = 0x01,  //default
  QuantityTimeout_9S = 0x01,
  QuantityTimeout_18S = 0x01,
  QuantityTimeout_30S = 0x01,
  QuantityTimeout_60S = 0x01,
  QuantityTimeout_Non = 0x01
} Quantity_Timeout_Item;

typedef enum
{
  QuantityTimeout_Non_param = 0x00,
  //QuantityTimeout_UserConfig_param = 0x01,
  QuantityTimeout_3S_param = 0x03,
  QuantityTimeout_6S_param = 0x06,  //default
  QuantityTimeout_9S_param = 0x09,
  QuantityTimeout_18S_param = 0x12,
  QuantityTimeout_30S_param = 0x1E,
  QuantityTimeout_60S_param = 0x3C
} Quantity_Timeout_Param;

//Location Manual Barcode Entry
typedef enum
{
  LocationManualBarcodeEntry_Yes = 0x01,  //Default
  LocationManualBarcodeEntry_No = 0x00
} Location_Manual_Barcode_Entry_Item;

typedef enum
{
  LocationManualBarcodeEntry_No_param = 0x00,
  LocationManualBarcodeEntry_Yes_param = 0x01  //Default
} Location_Manual_Barcode_Entry_Param;

//Location Manual Quantity Entry
typedef enum
{
  LocationManualQuantityEntry_Yes = 0x01,  //Default
  LocationManualQuantityEntry_No = 0x00
} Location_Manual_Quantity_Entry_Item;

typedef enum
{
  LocationManualQuantityEntry_No_param = 0x00,
  LocationManualQuantityEntry_Yes_param = 0x01  //Default
} Location_Manual_Quantity_Entry_Param;

//Location Loc Delimiter
typedef enum
{
  LocationLocDelimiter_Userspecified = 0x01,
  LocationLocDelimiter_CR = 0x01,
  LocationLocDelimiter_LF = 0x01,
  LocationLocDelimiter_Space = 0x01,
  LocationLocDelimiter_Tab = 0x01,  //Default
  LocationLocDelimiter_Comma = 0x01,
  LocationLocDelimiter_Colon = 0x01,
  LocationLocDelimiter_Semicolon = 0x01,
  LocationLocDelimiter_EqualsSign = 0x01
} LocationLocDelimiter_Item;

typedef enum
{
  LocationLocDelimiter_CR_param = DelimiterValue_CR,
  LocationLocDelimiter_LF_param = DelimiterValue_LF,
  LocationLocDelimiter_Space_param = DelimiterValue_Space,
  LocationLocDelimiter_Tab_param = DelimiterValue_Tab,  //Default
  LocationLocDelimiter_Comma_param = DelimiterValue_Comma,
  LocationLocDelimiter_Colon_param = DelimiterValue_Colon,
  LocationLocDelimiter_Semicolon_param = DelimiterValue_Semicolon,
  LocationLocDelimiter_EqualsSign_param = DelimiterValue_EqualsSign
} LocationLocDelimiter_Param;

//Inventory Manual Barcode Entry
typedef enum
{
  InventoryManualBarcodeEntry_Yes = 0x01,
  InventoryManualBarcodeEntry_No = 0x00  //Default
} InventoryManualBarcodeEntry_Item;

typedef enum
{
  InventoryManualBarcodeEntry_No_param = 0x00,  //Default
  InventoryManualBarcodeEntry_Yes_param = 0x01
} InventoryManualBarcodeEntry_Param;

//Inventory Manual Quantity Entry
typedef enum
{
  InventoryManualQuantityEntry_Yes = 0x01,
  InventoryManualQuantityEntry_No = 0x00  //Default
} InventoryManualQuantityEntry_Item;

typedef enum
{
  InventoryManualQuantityEntry_No_param = 0x00,  //Default
  InventoryManualQuantityEntry_Yes_param = 0x01
} InventoryManualQuantityEntry_Param;

//Inventory LOC Delimiter
typedef enum
{
  Inventory_LOC_Delimiter_Userspecified = 0x01,
  InventoryLocDelimiter_CR = 0x01,
  InventoryLocDelimiter_LF = 0x01,
  InventoryLocDelimiter_Space = 0x01,
  InventoryLocDelimiter_Tab = 0x01,  //Default
  InventoryLocDelimiter_Comma = 0x01,
  InventoryLocDelimiter_Colon = 0x01,
  InventoryLocDelimiter_Semicolon = 0x01,
  InventoryLocDelimiter_EqualsSign = 0x01
} InventoryLOCDelimiter_Item;

typedef enum
{
  InventoryLocDelimiter_CR_param = DelimiterValue_CR,
  InventoryLocDelimiter_LF_param = DelimiterValue_LF,
  InventoryLocDelimiter_Space_param = DelimiterValue_Space,
  InventoryLocDelimiter_Tab_param = DelimiterValue_Tab,  //Default
  InventoryLocDelimiter_Comma_param = DelimiterValue_Comma,
  InventoryLocDelimiter_Colon_param = DelimiterValue_Colon,
  InventoryLocDelimiter_Semicolon_param = DelimiterValue_Semicolon,
  InventoryLocDelimiter_EqualsSign_param = DelimiterValue_EqualsSign
} InventoryLOCDelimiter_Param;

//Inventory Store
typedef enum
{
  InventoryStore_Permanent = 0x01,
  InventoryStore_Temporary = 0x00 //Default
} InventoryStore_Item;

typedef enum
{
  InventoryStore_Temporary_param = 0x00, //Default
  InventoryStore_Permanent_param = 0x01,
} InventoryStore_Param;

//Show Live Capture
typedef enum
{
  ShowLiveCapture_Yes =0x01,
  ShowLiveCapture_No =0x02 //Default
} ShowLiveCapture_Item;

typedef enum
{
  ShowLiveCapture_No_param =0x00, //Default
  ShowLiveCapture_Yes_param =0x01
} ShowLiveCapture_Param;

//Battery
extern uint8_t ChargingMode;
extern uint16_t CheckBatteryStatusLevel(void);

//Inventory
typedef struct _INVT_RECORD
{
  char location[21];
  char qty_delimiter;
  char loc_delimiter;
  char BarCodeType;
  char barcode[4067];
  uint16_t quantity;
  uint16_t LocationLength;
  uint16_t BardcodeLength;
  uint8_t QuantiryTransferMode;
} Invt_Record_t;

//SSI command
typedef struct _SSI_COMMAND_BUFFER
{
  uint16_t length;
  uint8_t SSIcommand[300];
} SSI_Command_Buffer_t;

//Flash update
typedef struct _HEX_struct
{
  uint8_t Length;
  uint8_t Record_types;
  uint8_t Record_data[16];
  uint8_t checksum;
} _HEX_struct;

typedef struct MGMT_FW_Block_Data
{
  uint64_t Block_Size;
  uint16_t CRC_Value;
  uint16_t address;
} MGMT_FW_Block_Data;

//Image viewer
//GUI image viewer command
typedef enum
{
  Gui_ImageAttribute = 0x01,
  Gui_VideoAttribute = 0x02,
  Gui_ImageCapture = 0x03,
  Gui_ImageSave = 0x04,
  Gui_DecodeMode = 0x05
} ImageViewer_GuiCommand;

typedef enum
{
  HostAttribute_ACK = 0x01,
  HostAttribute_NAK = 0x02,
  HostImageCapture_ACK = 0x03,
  HostImageCapture_NAK = 0x04,
  HostSendVideoToGui = 0x05,     //show video
  HostSendFistImageVideoData = 0x06,  //Host send first image data or video data
  HostSendImageCaptureData = 0x07,  //image data
  HostImageSent_ACK = 0x09,
  HostImageSent_NAK = 0x0A
} ImageViewer_AckNakResponse;

//IMAGER_MODE (0xF7)
typedef enum
{
  ImagerMode_DecodeMode = 0x00,
  ImagerMode_ImageCaptureMode =0x01,
  ImagerMode_VideoMode = 0x02,
  ImagerMode_IcondImageCaptureMode = 0x09,
  ImagerMode_IcondImageSaved = 0x0A
} ImagerMode_Data;

//ATTRIBUTE_SET response
typedef enum
{
  AttributeSetResponse_Success = 0x00,
  AttributeSetResponse_Unsuccessful = 0x01
} AttributeSetResponse;

//Number of bits per pixel in image
typedef enum
{
  OneBPP = 0x00,
  FourBPP = 0x01,
  EightBPP = 0x02
}BitsPerPixels;

typedef struct BARCODE_RECORD
{
  char data[4093];
  uint8_t type;
  uint16_t length;
} BarcodeRecord_t;

typedef struct LOCATION_RECORD
{
  char data[20];
  uint16_t length;
} LocRecord_t;

bool SSI_Parser(uint8_t *rx_buffer,uint16_t len);
char *Recall_Barcode(void);
extern void set_splashscreen_active(bool);
extern bool get_scannerMsgRx_status(void);
//Configuration
extern uint8_t GetFlashConfigurationToGUIFlag;
extern void GetFlashConfigurationToGUI(void);
extern void SetGuiConfigurationToFlash(void);

//Inventory
extern void set_invt_record(LocRecord_t *location, BarcodeRecord_t *barcode, uint16_t quantity);
extern Invt_Record_t * get_invt_record(uint16_t index);
extern void submit_invt_list(void);
extern void change_loc(LocRecord_t *old_loc, LocRecord_t *new_loc);
extern void set_invt_in_progress(bool setting);
extern bool get_invt_in_progress(void);
uint16_t send_total_qty_invt(void);
uint16_t send_count_invt(void);
extern void CheckInventoryPermanentFlashData(void);
extern void SendAvoidTransmissionDecodeDataCommand(void);
extern void SendInventoryListFullCommand(void);
uint8_t get_inv_list_full_flag(void);

//Out/Inside Match
extern void clear_item_list_flag(void);
uint8_t get_out_in_list_full_flag(void);

// For Image Viewer
extern void set_img_view_cmd(uint16_t cmd);

//Attribute Set
extern void SendBootupCommand(void);
extern void SendRebootCommand(void);

//SSI command
extern void SSI_Command_Parser(uint8_t *rx_buffer ,uint16_t len);

extern BYTE CST_APISend_ATTR(uint16_t attr_num, BYTE *value, uint16_t length, uint16_t offset, uint8_t type, bool permanent);
extern BYTE CST_APIGet_Attr(WORD attr_num, BYTE *value);

#ifdef __cplusplus
}
#endif

#endif

/**
  * @}
  */
