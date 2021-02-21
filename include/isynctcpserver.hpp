#pragma once
#include <memory>

using namespace std;

class ISyncTcpConn;

class ISyncTcpServer
{
public:
    shared_ptr<ISyncTcpConn> getNewTcpConn(bool inNonBlock = false);
};
