#ifndef EDITABLEBARCODE_HPP
#define EDITABLEBARCODE_HPP

#include <string>
using namespace std;

#define DEFAULT_CAPACITY    200
#define DEFAULT_DISP_SIZE   13

class EditableBarcode {
public:
    // constructor/destructor
    EditableBarcode(std::size_t capacity = DEFAULT_CAPACITY, 
                    std::size_t displayWindowSize = DEFAULT_DISP_SIZE) {
        // assert(capacity > 0);
        // assert(displayWindowSize > 0);
        // assert(capacity >= displayWindowSize);
        this->capacity = capacity;
        this->editWindowSize = displayWindowSize;
        this->reinit();
    }
    ~EditableBarcode() {}

    // set/get whole barcode
    void setContent(const std::string &newContent) {

        if (newContent.size() == 0) {
            this->reinit();
            return;
        }
        std::size_t length = newContent.size();
        if (newContent.size() > this->capacity) {
            length = this->capacity;
        }
        this->content.clear();
        this->content.insert(this->content.end(), newContent.begin(), newContent.begin() + length);
        this->cursorPosition = this->content.size();         //fix for DC-28187.this change is for function keys cursor.earlier this line was this->cursorPosition = this->content.size() - 1;
        this->adjust_window_position();
    }
    char * getContent() {
        std::size_t length = this->content.copy(textBuffer, capacity);
        if (length)
        {
            textBuffer[length] = '\0';
            return this->textBuffer;
        }
        else
        {
            return NULL;
        }
    }

    // edit window related operations
    const std::string& getEWContent() {
        EWcontent.assign("");
        if (this->editWindowPosition < 0) {
            EWcontent.insert(EWcontent.end(), 
                this->content.begin(),
                this->content.begin() + this->editWindowPosition + this->editWindowSize);
        } else {
            EWcontent.insert(EWcontent.end(),
                this->content.begin() + this->editWindowPosition,
                this->content.begin() + this->editWindowPosition + this->editWindowSize);
        }
        return this->EWcontent;
    }
    std::size_t getEWCursorPos() {
        if (content.size() == 0) {
            return (this->editWindowSize);
        } else {
            return (this->cursorPosition - this->editWindowPosition);
        }
    }
    bool isLeftMore() {
        return ((this->editWindowPosition > 0) ? true : false);
    }
    bool isRightMore() {
        if ((std::ptrdiff_t)this->content.size() <= (std::ptrdiff_t)editWindowSize)
            return false;

        if (this->editWindowPosition + (std::ptrdiff_t)editWindowSize != (std::ptrdiff_t)this->content.size())
        {
            if (((this->content.size() - this->editWindowPosition) < editWindowSize) || ((this->content.size() - this->cursorPosition) == 1))

                return false;
            else
                return true;
        }
        else
            return false;
    }
    bool isMaxContent() {
        return ((this->content.size() == this->capacity) ? true : false);
    }
    void shiftCursorLeft() {
        if (this->move_cursor_backward()) {
            this->adjust_window_position();
        }
    }
    void shiftCursorRight() {
        if (this->move_cursor_forward()) {
            this->adjust_window_position();
        }
    }
    void appendChar(char ch) {
        if (this->content.size() < this->capacity) {
            this->content.insert(this->content.begin() + this->cursorPosition, ch);
            this->move_cursor_forward();
            this->adjust_window_position();
        }
    }
    void appendStr(char *str) {
        char ch = *str;
        while ((ch != '\0') && (this->content.size() < this->capacity)) {
            this->content.insert(this->content.begin() + this->cursorPosition, ch);
            this->move_cursor_forward();
            this->adjust_window_position();
            str++;
            ch = *str;
        }
    }
    void removeChar() {
        if ((this->content.size() > 0) && (this->cursorPosition > 0)) {
            this->content.erase(this->content.begin() + this->cursorPosition - 1);
            this->move_cursor_backward();
            this->adjust_window_position();
        }
    }
    void modifyChar(char ch) {
        this->content[this->cursorPosition - 1] = ch;
    }

private:
    std::string content;
    std::string EWcontent;
    std::size_t capacity;
    std::size_t editWindowSize;
    std::ptrdiff_t cursorPosition;
    std::ptrdiff_t editWindowPosition;
    char textBuffer[DEFAULT_CAPACITY + 1];  // +1 for string end '\0'

    void reinit() {
        this->content.assign("");
        this->cursorPosition = 0;
        this->editWindowPosition = this->cursorPosition - this->editWindowSize + 1;
    }
    bool move_cursor_forward() {
        // assert(this->cursorPosition < this->content.size());
        if (this->cursorPosition == (std::ptrdiff_t) this->content.size()) {
            return false;
        }
        this->cursorPosition += 1;
        return true;
    }
    bool move_cursor_backward() {
        // assert(this->cursorPosition >= 0);
        if (this->cursorPosition == 0) {
            return false;
        }
        this->cursorPosition -= 1;
        return true;
    }
    void adjust_window_position() {
        if ((this->content.size() > editWindowSize) )
        {
            if (this->editWindowPosition +(std::ptrdiff_t) this->editWindowSize < this->cursorPosition + 1) {
                this->editWindowPosition = this->cursorPosition - this->editWindowSize + 1;
            } else if (this->editWindowPosition > this->cursorPosition) {
                this->editWindowPosition = this->cursorPosition;
            }
        }
        else
        {
            if (this->editWindowPosition + (std::ptrdiff_t)this->editWindowSize < this->cursorPosition + (std::ptrdiff_t)editWindowSize) {
            this->editWindowPosition = this->cursorPosition - this->editWindowSize + (std::ptrdiff_t)editWindowSize;
            } else if (this->editWindowPosition > this->cursorPosition) {
                this->editWindowPosition = this->cursorPosition;
            }
        }

        if (this->editWindowPosition + (std::ptrdiff_t)this->editWindowSize >(std::ptrdiff_t) this->content.size()) {
            this->editWindowPosition = this->content.size() - this->editWindowSize;
        }
    }
};

#endif // EDITABLEBARCODE_HPP
