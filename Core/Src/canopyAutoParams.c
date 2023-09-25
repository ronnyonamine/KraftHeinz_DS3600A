/*
 * Copyright (c) 2020 Zebra Technologies Corporation and/or its affiliates. 
 * All rights reserved.
 */



#include "stdio.h"
#include <stdint.h>
#include "canopyAutoParams.h"
#include "canopyAuto_usercfg.h"

//
//  Access routines to the private allparamlines structure
//

uint16_t   GetCanopyParamCount()
{
   uint16_t retval = (uint16_t) TOTALCANOPYPARAMCOUNT;

   return retval;
}


uint16_t       GetCanopyAttrNumFromIndex(uint16_t index, uint8_t* error)
{
   *error = 0;
   uint16_t retval = 0;

   if (index >= GetCanopyParamCount())
   {
      *error = 1;
   }
   else
   {
      retval = allparamlines[index].attribute_number;
   }
   return retval;
}


uint32_t      GetCanopyDefaultValIntFromIndex(uint16_t index, uint8_t* error)
{
   *error = 0;
   uint32_t retval = 0;
   Attr_Query_t attrqtype = attr_unknown;
   
   if (index >= GetCanopyParamCount())
   {
      *error = 1; // index out of bounds
   }
   else
   {
      attrqtype = GetAttributeQType(allparamlines[index].attribute_number);
      if (attrqtype == attr_string || attrqtype == attr_unknown )
         *error = 1; // attribute not a integer.
      else
      {
         retval = allparamlines[index].default_value;
      }
   }
   return retval;
}

void       GetCanopyDefaultStringFromIndex(uint16_t index, char * p_result, uint8_t plen, uint8_t *error)
{
   uint8_t slen = 0;
   uint16_t local_index = index;
   *error = 0;
   uint16_t canopyParamCount = 0;
   
   canopyParamCount = GetCanopyParamCount();
   if ( canopyParamCount == 0)
   {
      *error = 1;
   }
   else
   {
      if ( ( plen > CONSOLIDATED_STR_MAX_SIZE ) || ( index >=  canopyParamCount ) )
      {
         *error = 1;
      }
      else
      {
         slen = allparamlines[index].defaultvaluelength;
         if ( ( slen > (CONSOLIDATED_STR_MAX_SIZE-1) ) || ( ( slen + 1) > plen ) )
         {
           *error = 1;
         }
         else
         {
            strncpy(p_result, allparamlines[index].default_value_string, slen);
            // null terminate the result
            p_result[slen] = '\0';
         }
      }
   }
}

uint32_t      GetCanopyMinValFromIndex(uint16_t index, uint8_t* error)
{
   *error = 0;
   uint32_t retval = 0;

   if (index >= GetCanopyParamCount())
   {
      *error = 1; // out of bounds;
   }
   else
   {
      retval = allparamlines[index].min_value;
   }
   return retval;
}


uint32_t        GetCanopyMaxValFromIndex(uint16_t index, uint8_t* error)
{
   *error = 0;
   uint32_t retval = 0;

   if (index >= GetCanopyParamCount())
   {
      *error = 1; // out of bounds;
   }
   else
   {
      retval = allparamlines[index].max_value;
   }
   return retval;
}

bool           IsCanopyAttributeVendorType(uint16_t index, uint8_t *error)
{
  *error = 0;
  bool retval = false;
  
  if ( index >= GetCanopyParamCount())
  {
    *error = 1; // out of bounds
  }
  else
  {
    if ( allparamlines[index].specialcase == spc_vendornew )
       retval = true;
  }
  return retval;
}

uint32_t        GetCanopyDefaultValueIntFromAttr(uint16_t AttributeNumber, uint8_t* error)
{
   uint16_t     canopyIndx = 0;
   uint32_t     retval = 0;
   Attr_Query_t attrqtype = attr_unknown;
   *error = 0;

   canopyIndx = GetCanopyIndexFromAttrNum(AttributeNumber, error);
   if (*error == 0)
   {
      attrqtype = GetAttributeQType(AttributeNumber);
      if (attrqtype == attr_unknown || attrqtype == attr_string)
         *error = 1;
   }
   if (*error == 0)
   {
      retval = GetCanopyDefaultValIntFromIndex(canopyIndx, error);
   }
   return retval;
}
