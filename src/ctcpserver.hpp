#pragma once
#include <memory>
#include "imuxevent.hpp"

class IAddr;
class ITcpConnectionHandler;

using namespace std;

class CTcpServer : public IMuxEvent
{
    friend class CTcpServerFactory;

private:
    bool mReady;
    int mSk;
    int mLastError;
    shared_ptr<const IAddr> mAddr;
    shared_ptr<ITcpConnectionHandler> mTcpConnectionHandler;

public:
    CTcpServer();
    ~CTcpServer();
    bool initTcpServer();
    bool isReady() override;
    int getFd() override;
    void onError() override;
    void onReadable() override;
    void onWritable() override;
};
