/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

enum
{
	NO_SPL_FEATURE       = 0x00000000,
	SCAN_QTY_RESEND_DATA = 0x00000001,
	SCAN_QTY_LOC_DATA    = 0x00000002,
	OUT_INSIDE_MATCH     = 0x00000004,
	VIEW_IMAGE           = 0x00000008,
	SCAN_INVENTORY_DATA  = 0x00000010
};

/**
 * @brief Type of status event to notify frontend
 */
enum
{
  STATUS_EVT_BLUETOOTH     = 0x03,
  STATUS_EVT_BATTERY       = 0x04,
  STATUS_EVT_CHARGE_MODE   = 0x05,
  STATUS_EVT_BATCH_MODE    = 0x06,
  STATUS_EVT_INACTIVE      = 0x07,
  STATUS_EVT_AUTORECONNECT = 0x08
};

/**
 * @brief Bluetooth Status notifications
 */
enum
{
  BLUETOOTH_DISCONNECT = 0x00,
  BLUETOOTH_CONNECT    = 0x01
};

/**
 * @brief Battery Status notifications
 */
enum
{
  BATTERY_FULL            = 0x01,
  BATTERY_MED_HIGH        = 0x02,
  BATTERY_MEDIUM_FULL     = 0x03,
  BATTERY_MED_LOW         = 0x04,
  BATTERY_LOW             = 0x05,
  BATTERY_FULL_EOL        = 0x81,
  BATTERY_MED_HIGH_EOL    = 0x82,
  BATTERY_MEDIUM_FULL_EOL = 0x83,
  BATTERY_MED_LOW_EOL     = 0x84,
  BATTERY_LOW_EOL         = 0x85
};

/**
 * @brief Charge Mode Status notifications
 */
enum
{
  CHARGE_MODE_OFF     = 0x00,
  CHARGE_MODE_ON      = 0x01
};

/**
 * @brief Batch Mode Status notifications
 */
enum
{
  BATCH_MODE_OFF     = 0x00,
  BATCH_MODE_ON      = 0x01
};

/*
 * @brief Inactive device notifications
 */
enum
{
  INACTIVITY_OFF    = 0x00,
  INACTIVITY_ON     = 0x01
};

#define Bluetooth_Device           0x03
#define BT_Disconnect              0x00
#define BT_Connect                 0x01
#define Battery_Device             0x04
#define Battery_Full               0x01
#define Battery_Med_high           0x02
#define Battery_Medium_full        0x03
#define Battery_Med_low            0x04
#define Battery_Low                0x05
#define Battery_Full_EndOfLife         0x81
#define Battery_Med_high_EndOfLife     0x82
#define Battery_Medium_full_EndOfLife  0x83
#define Battery_Med_low_EndOfLife      0x84
#define Battery_Low_EndOfLife          0x85
#define Battery_Full_Level         80
#define Battery_Med_high_Level     60
#define Battery_Medium_full_Level  40
#define Battery_Med_low_Level      20
#define Battery_Low_Level          1
