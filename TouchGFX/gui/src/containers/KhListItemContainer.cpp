#include <gui/containers/KhListItemContainer.hpp>
#include <touchgfx/Color.hpp>

KhListItemContainer::KhListItemContainer()
{

}

void KhListItemContainer::initialize()
{
    KhListItemContainerBase::initialize();
}

void KhListItemContainer::setupListElement(TEXTS iconTextID)
{
    textArea1.setTypedText(TypedText(iconTextID));
    textArea1.resizeToCurrentText();
    invalidate();
}

void KhListItemContainer::selectThis()
{
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(16, 51, 171));
    invalidate();
}

void KhListItemContainer::deselectThis()
{
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(16, 51, 171));
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    invalidate();
}
