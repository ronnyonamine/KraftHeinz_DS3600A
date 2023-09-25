#ifndef FOCUSABLEIETM_HPP
#define FOCUSABLEIETM_HPP

class FocusableIetm {
public:
    virtual ~FocusableIetm() {}

    virtual bool setFocus(bool selected) { return (false); }
    virtual bool setRadioOn(bool on) { return (false); }
    virtual bool GreyItem(bool selected) { return (false); }
};

#endif // FOCUSABLEIETM_HPP
