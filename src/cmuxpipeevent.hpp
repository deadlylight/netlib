#pragma once
#include <memory>
#include "imuxevent.hpp"

using namespace std;

class CMuxGeneral;

class CMuxPipeEvent : public IMuxEvent
{
private:
    int mFd;
    weak_ptr<CMuxGeneral> mMux;

private:
    void readCtlMsg();

public:
    CMuxPipeEvent(int, weak_ptr<CMuxGeneral>);
    ~CMuxPipeEvent();

    int getFd() override;
    uint32_t getMuxEvents() override;
    void onError() override;
    void onReadable() override;
    void onWritable() override;
};
