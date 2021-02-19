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
    queue<int> mNewSks;
    mutex mSksMutex;
    condition_variable mSksCond;

    void addNewSk(int);
    int getOneSk(bool);
    shared_ptr<ITcpConnection> makeNewConnection(int);

public:
    CTcpServer(int);
    ~CTcpServer();

    shared_ptr<ITcpConnection> getNewConnection(bool) override;

    int getFd() override;
    uint32_t getMuxEvents() override;
    void onError() override;
    void onReadable() override;
    void onWritable() override;
};
