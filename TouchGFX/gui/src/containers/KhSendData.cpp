#include <gui/containers/KhSendData.hpp>

KhSendData::KhSendData()
{
}

void KhSendData::initialize()
{
    KhSendDataBase::initialize();
    counter = 0;
    imageArrow_1.setVisible(false);
    imageArrow_1.invalidate();
    imageArrow_2.setVisible(false);
    imageArrow_2.invalidate();
    imageArrow_3.setVisible(false);
    imageArrow_3.invalidate();
}

void KhSendData::sendActivate()
{
    textSendData.setVisible(false);
    textSendData.invalidate();
    textSending.setVisible(true);
    textSending.invalidate();
    counter = 0;
    sendIncrement();
}

void KhSendData::sendDeactivate()
{
    textSending.setVisible(false);
    textSending.invalidate();
    textSendData.setVisible(true);
    textSendData.invalidate();
    imageArrow_1.setVisible(false);
    imageArrow_1.invalidate();
    imageArrow_2.setVisible(false);
    imageArrow_2.invalidate();
    imageArrow_3.setVisible(false);
    imageArrow_3.invalidate();
}

void KhSendData::sendIncrement()
{
    if ((counter % 4) == 0)
    {
        imageArrow_1.setVisible(false);
        imageArrow_1.invalidate();
        imageArrow_2.setVisible(false);
        imageArrow_2.invalidate();
        imageArrow_3.setVisible(false);
        imageArrow_3.invalidate();
    }
    if ((counter % 4) == 1)
    {
        imageArrow_1.setVisible(true);
        imageArrow_1.invalidate();
    }
    if ((counter % 4) == 2)
    {
        imageArrow_2.setVisible(true);
        imageArrow_2.invalidate();
    }
    if ((counter % 4) == 3)
    {
        imageArrow_3.setVisible(true);
        imageArrow_3.invalidate();
    }
    counter++;
}