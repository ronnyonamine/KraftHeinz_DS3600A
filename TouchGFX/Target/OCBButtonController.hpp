/**
  ******************************************************************************
  * File Name          : OCBButtonController.hpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* USER CODE BEGIN OCBButtonController */

#ifndef OCBBUTTONCONTROLLER_HPP
#define OCBBUTTONCONTROLLER_HPP

#include <stm32l4xx_hal.h>
#include <main.h>
#include <platform/driver/button/ButtonController.hpp>
#include "../../../Drivers/BSP/Feature/customAPIcallback.h"
/**
 * @class OCBButtonController
 *
 * @brief This class specializes ButtonController Interface.
 *
 * @sa touchgfx::ButtonController
 */
class OCBButtonController : public touchgfx::ButtonController
{
public:

    //OCBButtonController() {}

    /**
      * @fn virtual void OCBButtonController::init() = 0;
      *
      * @brief Initializes button controller.
      *
      *        Initializes button controller.
      */
    virtual void init() {  }

    /**
    * @fn virtual bool OCBButtonController::sample(uint8_t& key) = 0;
    *
    * @brief Checks whether the button is being Pressed, and if so, what coordinates.
    *
    *        Checks whether the button screen is being buttoned, and if so, what coordinates.
    *
    * @param [out] x The x position of the button
    * @param [out] y The y position of the button
    *
    * @return True if a button has been detected, otherwise false.
    */
    virtual bool sample(uint8_t &key)
    {
        uint8_t msg = 0;

        key = CST_APIcbRxKeyData(&msg);

        return ((key != false) ? true : false);
    }
};

#endif // OCBBUTTONCONTROLLER_HPP

/* USER CODE END OCBButtonController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
