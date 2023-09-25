#ifndef BARCODE_HPP
#define BARCODE_HPP

#include <string>
using namespace std;

#define LARGE_FONT_SIZE 4
#define SMALL_FONT_SIZE 9
#define TEXT_SIZE (SMALL_FONT_SIZE + LARGE_FONT_SIZE)

class Barcode {
public:
    Barcode() {}

    template <typename T>
    void setText(const T ptr_str) {
        string str;
        str.assign(ptr_str);
        size_t length = str.length();

        if (length <= LARGE_FONT_SIZE) {
            length = str.copy(Lfont, LARGE_FONT_SIZE);
            Lfont[length] = '\0';
            Sfont[0] = '\0';
            Ellipsis = false;
        } else if ((length > LARGE_FONT_SIZE) && (length <= TEXT_SIZE)) {
            length = str.copy(Lfont, LARGE_FONT_SIZE, str.length() - LARGE_FONT_SIZE);
            Lfont[length] = '\0';
            length = str.copy(Sfont, str.length() - LARGE_FONT_SIZE);
            Sfont[length] = '\0';
            Ellipsis = false;
        } else {
            length = str.copy(Lfont, LARGE_FONT_SIZE, str.length() - LARGE_FONT_SIZE);
            Lfont[length] = '\0';
            length = str.copy(Sfont, SMALL_FONT_SIZE, str.length() - TEXT_SIZE);
            Sfont[length] = '\0';
            Ellipsis = true;
        }
    }
    char * getLfont() {return Lfont;}
    char * getSfont() {return Sfont;}
    bool getEllipsis() {return Ellipsis;}

private:
    char Lfont[LARGE_FONT_SIZE + 1];
    char Sfont[SMALL_FONT_SIZE + 1];
    bool Ellipsis;
};

#endif // BARCODE_HPP

