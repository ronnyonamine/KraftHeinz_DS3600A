/******************************************************
 *                     Zebra ....
 ******************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEYCODE_H
#define __KEYCODE_H

#ifndef SIMULATOR

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define KEYCODE_BKSP      8
#define KEYCODE_ENTER    13
// 129~223 reserve for multi tap
#define KEYCODE_UP      224
#define KEYCODE_DOWN    225
#define KEYCODE_LEFT    226
#define KEYCODE_RIGHT   227
#define KEYCODE_BLUE    228
#define KEYCODE_GREEN   229
#define KEYCODE_HOME    230
#define KEYCODE_ESC     231
#define KEYCODE_F1      232
#define KEYCODE_F2      233
#define KEYCODE_F3      234
#define KEYCODE_F4      235
#define KEYCODE_F5      236
#define KEYCODE_F6      237
#define KEYCODE_F7      238
#define KEYCODE_F8      239
#define KEYCODE_F9      240
#define KEYCODE_INC     241
#define KEYCODE_DEC     242
#define KEYCODE_RECALL  243
#define KEYCODE_BACK    244

#ifdef __cplusplus
}
#endif

#endif // SIMULATOR

#endif /* __KEYCODE_H */
