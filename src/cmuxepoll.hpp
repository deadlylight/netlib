#pragma once
#include <imux.hpp>

struct epoll_event;
class IMuxEvent;

class CMuxEpoll : public IMux
{
private:
    int mPollFd;
    bool mStopped;

private:
    bool createPollFd();
    bool invokeMainLoop();
    void hanldeEvent(epoll_event &inEvent);
    bool registerMuxEvent(shared_ptr<IMuxEvent> &inMuxEvent, uint32_t inEventBits);

public:
    CMuxEpoll();
    ~CMuxEpoll();

    bool startMux() override;

    bool registerTcpServer(shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>) override;
    bool registerTcpClient(shared_ptr<const IAddr>, shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>) override;
};
