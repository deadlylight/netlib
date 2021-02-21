#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <itcpserver.hpp>
#include "imuxevent.hpp"

using namespace std;

class CTcpServer : public ITcpServer, public IMuxEvent
{
private:
    int mListenSk;
    mutex mMutex;
    shared_ptr<ITcpConnectionQueue> mQueue;

private:
    void addNewSk(int);
    int getOneSk(bool);
    shared_ptr<ITcpConnection> makeNewConnection(int);

public:
    CTcpServer(int);
    ~CTcpServer();

    void setQueue(shared_ptr<ITcpConnectionQueue>) override;
    shared_ptr<ITcpConnectionQueue> getQueue() override;
    void shutdownTcpServer() override;

    int getFd() override;
    uint32_t getMuxEvents() override;
    void onError() override;
    void onReadable() override;
    void onWritable() override;
};
