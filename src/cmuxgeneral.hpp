#pragma once
#include <map>
#include <memory>
#include <list>
#include <mutex>
#include <condition_variable>
#include <imux.hpp>

using namespace std;

class CMuxGeneral : public IMux
{
private:
    uint32_t mFdCount;
    bool mStopped;
    list<string> mBindAddrs;
    mutex mBindAddrsMutex;
    map<int, shared_ptr<IMuxEvent>> mFd2Events;

private:
    void muxLoop(shared_ptr<CMuxGeneral>);
    shared_ptr<IMuxEvent> getMuxEvent(int);
    void addMuxEvent(shared_ptr<IMuxEvent>);

protected:
    bool startMuxGeneral(weak_ptr<CMuxGeneral>);
    bool stopMuxGeneral();
    void handleEvent(int, uint32_t);
    virtual void muxLoop() = 0;
    virtual bool registerMux(int) = 0;

public:
    CMuxGeneral();
    ~CMuxGeneral();

    void addBindAddr(const string &) override;
    void removeBindAddr(const string &) override;
};
