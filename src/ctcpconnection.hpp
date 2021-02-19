#pragma once
#include <itcpconnection.hpp>
#include "imuxevent.hpp"

class CTcpConnection : public ITcpConnection, public IMuxEvent
{
private:
    int mSk;

public:
    CTcpConnection(int);
    ~CTcpConnection();

    shared_ptr<IMsgIn> readMsg(bool) override;
    bool writeMsg(shared_ptr<IMsgOut>) override;
    void closeTcpConnection() override;

    int getFd() override;
    uint32_t getMuxEvents() override;
    void onError() override;
    void onReadable() override;
    void onWritable() override;
};
