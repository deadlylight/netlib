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
    friend class CMuxFactory;

private:
    int mEpollFd;

private:
    bool makeEpollFd();
    void epollMainLoop();
    void handleEvent(void *);
    bool addFd(int);

protected:
    bool initMux() override;
    void mainLoop() override;
    bool registerMux(int) override;

public:
    CMuxEpoll();
    ~CMuxEpoll();
};
