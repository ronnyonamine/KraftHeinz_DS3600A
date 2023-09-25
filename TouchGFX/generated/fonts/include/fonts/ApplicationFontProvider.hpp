/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#ifndef APPLICATIONFONTPROVIDER_HPP
#define APPLICATIONFONTPROVIDER_HPP

#include <touchgfx/FontManager.hpp>

struct Typography
{
    static const touchgfx::FontId TITLEFONT = 0;
    static const touchgfx::FontId SUBTITLEFONT = 1;
    static const touchgfx::FontId MEMUITEMINACTIVE = 2;
    static const touchgfx::FontId MEMUITEMACTIVE = 3;
    static const touchgfx::FontId QTYINPUTFONT = 4;
    static const touchgfx::FontId BARCODEDATANAME = 5;
    static const touchgfx::FontId BARCODEDATASMALL = 6;
    static const touchgfx::FontId BARCODEDATALARGE = 7;
    static const touchgfx::FontId TOASTREGULAE = 8;
    static const touchgfx::FontId TOASTBLOD = 9;
    static const touchgfx::FontId RADIOBTNINACTIVE = 10;
    static const touchgfx::FontId RADIOBTNACTIVE = 11;
    static const touchgfx::FontId LABELFONT = 12;
    static const touchgfx::FontId SUBLABELFONT = 13;
    static const touchgfx::FontId STRINPUTFONT = 14;
    static const touchgfx::FontId TEXTVIEWFONT = 15;
    static const touchgfx::FontId QTYVIEWFONT = 16;
    static const touchgfx::FontId INVTLISTFONT = 17;
    static const touchgfx::FontId INVTLISTBOLDFONT = 18;
    static const touchgfx::FontId MATCHREGULAE_L = 19;
    static const touchgfx::FontId MATCHBLOD_L = 20;
    static const touchgfx::FontId MATCHREGULAE_S = 21;
    static const touchgfx::FontId MATCHBLOD_S = 22;
};

struct TypographyFontIndex
{
    static const touchgfx::FontId TITLEFONT = 0;        // RobotoCondensed_Bold_48_4bpp
    static const touchgfx::FontId SUBTITLEFONT = 1;     // RobotoCondensed_Regular_18_4bpp
    static const touchgfx::FontId MEMUITEMINACTIVE = 2; // RobotoCondensed_Regular_26_4bpp
    static const touchgfx::FontId MEMUITEMACTIVE = 3;   // RobotoCondensed_Regular_36_4bpp
    static const touchgfx::FontId QTYINPUTFONT = 4;     // RobotoCondensed_Bold_40_4bpp
    static const touchgfx::FontId BARCODEDATANAME = 2;  // RobotoCondensed_Regular_26_4bpp
    static const touchgfx::FontId BARCODEDATASMALL = 5; // RobotoMono_Regular_26_4bpp
    static const touchgfx::FontId BARCODEDATALARGE = 6; // RobotoMono_Bold_40_4bpp
    static const touchgfx::FontId TOASTREGULAE = 7;     // RobotoCondensed_Regular_24_4bpp
    static const touchgfx::FontId TOASTBLOD = 8;        // RobotoCondensed_Bold_24_4bpp
    static const touchgfx::FontId RADIOBTNINACTIVE = 2; // RobotoCondensed_Regular_26_4bpp
    static const touchgfx::FontId RADIOBTNACTIVE = 3;   // RobotoCondensed_Regular_36_4bpp
    static const touchgfx::FontId LABELFONT = 9;        // RobotoCondensed_Bold_26_4bpp
    static const touchgfx::FontId SUBLABELFONT = 10;     // RobotoCondensed_Bold_20_4bpp
    static const touchgfx::FontId STRINPUTFONT = 11;     // RobotoMono_Regular_32_4bpp
    static const touchgfx::FontId TEXTVIEWFONT = 2;     // RobotoCondensed_Regular_26_4bpp
    static const touchgfx::FontId QTYVIEWFONT = 12;      // RobotoCondensed_Regular_32_4bpp
    static const touchgfx::FontId INVTLISTFONT = 5;     // RobotoMono_Regular_26_4bpp
    static const touchgfx::FontId INVTLISTBOLDFONT = 6; // RobotoMono_Bold_40_4bpp
    static const touchgfx::FontId MATCHREGULAE_L = 12;   // RobotoCondensed_Regular_32_4bpp
    static const touchgfx::FontId MATCHBLOD_L = 13;      // RobotoCondensed_Bold_32_4bpp
    static const touchgfx::FontId MATCHREGULAE_S = 2;   // RobotoCondensed_Regular_26_4bpp
    static const touchgfx::FontId MATCHBLOD_S = 9;      // RobotoCondensed_Bold_26_4bpp
    static const uint16_t NUMBER_OF_FONTS = 14;
};

class ApplicationFontProvider : public touchgfx::FontProvider
{
public:
    virtual touchgfx::Font* getFont(touchgfx::FontId typography);
};

#endif // APPLICATIONFONTPROVIDER_HPP
