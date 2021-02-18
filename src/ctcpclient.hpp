#pragma once
#include "imuxevent.hpp"

class CTcpClient : public IMuxEvent
{
public:
    CTcpClient(shared_ptr<const IAddr>, shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>);
    ~CTcpClient();
    int getFd() override;
    void onError() override;
    void onReadable() override;
    void onWritable() override;
};
