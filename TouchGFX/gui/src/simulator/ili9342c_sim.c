#ifdef SIMULATOR

#include <gui/simulator/ili9342c.h>

void ili9342c_Init(void)
{
    // Do nothing...
}
uint16_t ili9342c_ReadID(void)
{
  return (2);
}
void ili9342c_DisplayOn(void)
{
    // Do nothing...
}
void ili9342c_DisplayOff(void)
{
    // Do nothing...
}
void ili9342c_DisplayOn_Chargemode(void)
{
    // Do nothing...
}
void ili9342c_TimeoutDimming(void)
{
    // Do nothing...
}
void ili9342c_StopTimeoutDimming(void)
{
    // Do nothing...
}
void ili9342c_WriteReg(uint8_t LCD_Reg)
{
    // Do nothing...
}
void ili9342c_WriteData(uint8_t RegValue)
{
    // Do nothing...
}
void ili9342c_WriteMultipleData(uint16_t *pData, uint32_t Size)
{
    // Do nothing...
}
uint32_t ili9342c_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
    return (2);
}
void ili9342c_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
    // Do nothing...
}
uint16_t ili9342c_GetLcdPixelWidth(void)
{
  return (2);
}
uint16_t ili9342c_GetLcdPixelHeight(void)
{
  return (2);
}
#endif
