#pragma once

class INetStreamServer
{
public:
    virtual ~INetStreamServer() = default;
    virtual void stopServer() = 0;
};
