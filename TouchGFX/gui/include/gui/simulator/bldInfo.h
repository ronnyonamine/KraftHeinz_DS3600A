/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
 */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __BLDINFO_H
#define __BLDINFO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

/* Exported types -----------------------------------------------------------*/

/* Exported constants -------------------------------------------------------*/

/* Exported macro -----------------------------------------------------------*/

/* Exported functions prototypes --------------------------------------------*/
void showBuildInfo(void);

/* Exported data prototypes -------------------------------------------------*/
extern const char *bi_proj_name;
// extern const char bi_build_date[];
// extern const char bi_build_time[];
extern const char *bi_board_support;
extern const char bi_bldInfo[];

#ifdef __cplusplus
}
#endif

#endif // __BLDINFO_H
