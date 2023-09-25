/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __STRFILTER_H
#define __STRFILTER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SSI_cmd.h"

/* Exported data prototypes --------------------------------------------------*/

/* Function Declarations -----------------------------------------------------*/
extern char * NonPrintCharFilter(char * str);
extern char * NonPrintCharFilter_b(BarcodeRecord_t * bc_r);
extern char * NonPrintCharFilter_l(LocRecord_t * loc_r);

#ifdef __cplusplus
}
#endif

#endif // __STRFILTER_H
