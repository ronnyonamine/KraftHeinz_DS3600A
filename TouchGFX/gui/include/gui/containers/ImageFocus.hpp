#ifndef IMAGEFOCUS_HPP
#define IMAGEFOCUS_HPP

#include <gui_generated/containers/ImageFocusBase.hpp>

class ImageFocus : public ImageFocusBase
{
public:
    ImageFocus();
    virtual ~ImageFocus() {}

    virtual void initialize();
protected:
};

#endif // IMAGEFOCUS_HPP
