/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/
#ifdef SIMULATOR

#include <string.h>
#include <gui/simulator/strfilter.h>

/* Private variables ---------------------------------------------------------*/
static char str_filtered[21];
static char * str_filtered_ptr;


/**
 * @brief Filter non-printable ASCII (0x0~0x19)
 */
char * NonPrintCharFilter(char * str)
{
  int org_str_len = strlen(str);

  str_filtered_ptr = &str_filtered[sizeof(str_filtered)];
  str_filtered_ptr--;
  *str_filtered_ptr = '\0';

  while ((org_str_len >= 0) && (str_filtered_ptr > &str_filtered[0]))
  {
    if (*(str + org_str_len) >= 0x20)
    {
      str_filtered_ptr--;
      *str_filtered_ptr = *(str + org_str_len);
    }
    org_str_len--;
  }
  return str_filtered_ptr;
}

/**
 * @brief Filter non-printable ASCII (0x0~0x19) for barcode
 */
char * NonPrintCharFilter_b(BarcodeRecord_t * bc_r)
{
  int org_str_len = bc_r->length;

  str_filtered_ptr = &str_filtered[sizeof(str_filtered)];
  str_filtered_ptr--;
  *str_filtered_ptr = '\0';

  while ((org_str_len >= 0) && (str_filtered_ptr > &str_filtered[0]))
  {
    if (*(bc_r->data + org_str_len) >= 0x20)
    {
      str_filtered_ptr--;
      *str_filtered_ptr = *(bc_r->data + org_str_len);
    }
    org_str_len--;
  }
  return str_filtered_ptr;
}

/**
 * @brief Filter non-printable ASCII (0x0~0x19) for location
 */
char * NonPrintCharFilter_l(LocRecord_t * loc_r)
{
  int org_str_len = loc_r->length;

  str_filtered_ptr = &str_filtered[sizeof(str_filtered)];
  str_filtered_ptr--;
  *str_filtered_ptr = '\0';

  while ((org_str_len >= 0) && (str_filtered_ptr > &str_filtered[0]))
  {
    if (*(loc_r->data + org_str_len) >= 0x20)
    {
      str_filtered_ptr--;
      *str_filtered_ptr = *(loc_r->data + org_str_len);
    }
    org_str_len--;
  }
  return str_filtered_ptr;
}

#endif
