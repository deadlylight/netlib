#pragma once
#include <map>
#include <memory>
#include <mutex>
#include "imuxevent.hpp"
#include "cmuxgeneral.hpp"

using namespace std;

class IMuxEvent;

class CMuxEpoll : public CMuxGeneral
{
private:
    int mEpollFd;

private:
    bool makeEpollFd();
    void epollMuxLoop();
    void handleEvent(void *);
    bool addFd(int);
    bool startMuxEpoll();

protected:
    void muxLoop() override;
    bool registerMux(int) override;

public:
    CMuxEpoll();
    ~CMuxEpoll();
    bool startMuxEpoll(weak_ptr<CMuxEpoll>);
    bool stopMux() override;
};
