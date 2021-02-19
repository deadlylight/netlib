#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <imux.hpp>
#include "imuxevent.hpp"

using namespace std;

class IMuxEvent;
class ITcpServer;
class ITcpConnection;

class CMuxGeneral : public IMux
{
    friend class CMuxFactory;
    friend class CMuxPipeEvent;

public:
    class CMuxIpc
    {
        private:
            mutex mMutex;
            condition_variable mCond;
            shared_ptr<ITcpServer> mTcpServer;
            shared_ptr<ITcpConnection> mTcpClient;

        public:
            shared_ptr<ITcpServer> reteiveTcpServer();
            shared_ptr<ITcpConnection> reteiveTcpClient();
            void provideTcpServer(shared_ptr<ITcpServer>);
            void provideTcpClient(shared_ptr<ITcpConnection>);
    };

protected:
    int mControlFd[2];
    int mFdCount;
    bool mStopped;
    weak_ptr<CMuxGeneral> mSelf;
    mutex mControlMutex;
    mutex mMakeMutex;
    map<int, shared_ptr<IMuxEvent>> mFd2Events;

public:
    CMuxIpc mMuxIpc;

private:
    bool makeMuxCtl();
    void startMuxThread();
    static void muxLoop(shared_ptr<CMuxGeneral>);
    bool registerTcpConnection(int, shared_ptr<IMuxEvent>);

protected:
    shared_ptr<IMuxEvent> getMuxEvent(int);
    void setMuxEvent(shared_ptr<IMuxEvent>);
    void handleEvent(int, uint32_t);

    virtual bool initMux() = 0;
    virtual void mainLoop() = 0;
    virtual bool registerMux(int) = 0;

public:
    CMuxGeneral();
    ~CMuxGeneral();
    bool startMux();
    bool stopMux();
    bool registerMuxEvent(shared_ptr<IMuxEvent>);

    shared_ptr<ITcpServer> makeTcpServer(uint16_t, const string) override;
    shared_ptr<ITcpConnection> makeTcpClient(uint16_t, const string &, const string) override;
};
