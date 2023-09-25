#ifndef KHLISTITEMCONTAINER_HPP
#define KHLISTITEMCONTAINER_HPP

#include <gui_generated/containers/KhListItemContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class KhListItemContainer : public KhListItemContainerBase
{
public:
    KhListItemContainer();
    virtual ~KhListItemContainer() {}

    virtual void initialize();
    void setupListElement(TEXTS iconTextID);
    void selectThis();
    void deselectThis();
protected:
};

#endif // KHLISTITEMCONTAINER_HPP
