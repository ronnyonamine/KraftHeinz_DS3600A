#ifndef KHSENDDATA_HPP
#define KHSENDDATA_HPP

#include <gui_generated/containers/KhSendDataBase.hpp>

class KhSendData : public KhSendDataBase
{
public:
    KhSendData();
    virtual ~KhSendData() {}

    virtual void initialize();
    void sendActivate();
    void sendDeactivate();
    void sendIncrement();
protected:
    int counter;
};

#endif // KHSENDDATA_HPP
