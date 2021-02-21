#pragma once
#include <cstdint>
#include <string>
#include <memory>

using namespace std;

class IMux;
class ISyncTcpServer;
class IAsyncTcpServer;
class ISyncTcpClient;
class IAsyncTcpClient;

class CTcpFactory
{
public:
    static shared_ptr<ISyncTcpServer> createSyncTcpServer(shared_ptr<IMux>, uint16_t);
    static bool registerAsyncTcpServer(shared_ptr<IMux>, shared_ptr<IAsyncTcpServer>);
    static bool unregisterAsyncTcpServer(shared_ptr<IMux>, shared_ptr<IAsyncTcpServer>);

    static shared_ptr<ISyncTcpClient> createSyncTcpClient(shared_ptr<IMux>, const string &, uint16_t);
    static bool registerAsyncTcpClient(shared_ptr<IMux>);
    static bool unregisterAsyncTcpClient(shared_ptr<IMux>);
};
