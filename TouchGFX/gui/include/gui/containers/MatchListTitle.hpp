#ifndef MATCHLISTTITLE_HPP
#define MATCHLISTTITLE_HPP

#include <gui_generated/containers/MatchListTitleBase.hpp>

class MatchListTitle : public MatchListTitleBase
{
public:
    MatchListTitle();
    virtual ~MatchListTitle() {}

    virtual void initialize();
    void setText(uint8_t type);

protected:
};

#endif // MATCHLISTTITLE_HPP
