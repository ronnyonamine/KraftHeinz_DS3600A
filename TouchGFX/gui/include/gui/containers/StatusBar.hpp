#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include <gui_generated/containers/StatusBarBase.hpp>
#include <gui/common/IconEnumDefine.hpp>

class StatusBar : public StatusBarBase
{
public:
    StatusBar();
    virtual ~StatusBar() {}

    virtual void initialize();
    void UpdateIcon(IconID_t IconId, IconStateID_t IconState);

protected:
};

#endif // STATUSBAR_HPP
