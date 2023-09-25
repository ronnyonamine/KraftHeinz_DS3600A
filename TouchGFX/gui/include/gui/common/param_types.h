/**
  ******************************************************************************
  * @file    param_types.h
  * @author  SIANA Systems
  * @date    06/21/2021
  * @brief   Helper definitions for Parameter Types callable in C and C++
  *
  * The ConfigParam header contains all the classes and methods needed to
  * subscribe parameter information to be public. The approach followed by
  * this class is similar to the used on ZebraApplication.
  ******************************************************************************
  * @attention
  *
  * <h2><center>© COPYRIGHT 2021 SIANA Systems</center></h2>
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  *
  ******************************************************************************
  */
#ifndef __PARAM_TYPES_HPP__
#define __PARAM_TYPES_HPP__

/**
 * @brief Available parameter types.
 */
typedef enum
{
	PARAM_TYPE_BOOL,
	PARAM_TYPE_NUMERIC,
	PARAM_TYPE_CHARACTER,
        PARAM_TYPE_STRING
} param_type_t;
          
/**
 * @brief Types of names - used in APIs that can work with multiple
  *       type of name identifiers
 */
typedef enum
{
  NAME_TYPE_PARAM,
  NAME_TYPE_SHORT,
  NAME_TYPE_APP
}e_name_type;

#endif
