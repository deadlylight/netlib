#pragma once
#include <mutex>
#include <itcpconnection.hpp>
#include "imuxevent.hpp"

using namespace std;

class CTcpConnection : public ITcpConnection, public IMuxEvent
{
private:
    int mSk;
    shared_ptr<ITcpMsgQueue> mQueue;
    mutex mMutex;

public:
    CTcpConnection(int);
    ~CTcpConnection();

    void setQueue(shared_ptr<ITcpMsgQueue>) override;
    shared_ptr<ITcpMsgQueue> getQueue() override;
    bool writeMsg(shared_ptr<IMsgOut>) override;
    void closeTcpConnection() override;

    int getFd() override;
    uint32_t getMuxEvents() override;
    void onError() override;
    void onReadable() override;
    void onWritable() override;
};
