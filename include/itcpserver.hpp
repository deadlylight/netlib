#pragma once
#include <memory>

using namespace std;

class ITcpConnection;

class ITcpServer
{
public:
    virtual ~ITcpServer() = default;
    virtual shared_ptr<ITcpConnection> getNewConnection(bool = false) = 0;  // true for non-block
};
