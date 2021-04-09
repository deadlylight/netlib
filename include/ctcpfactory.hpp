#pragma once
#include <memory>
#include <string>

using namespace std;

class IMux;
class INetStreamAccepter;
class INetStreamReader;

class CTcpFactory
{
public:
    CTcpFactory() = delete;
    static bool createTcpServer(shared_ptr<IMux>,
                         shared_ptr<INetStreamAccepter>,
                         uint16_t,
                         string = string());

    static bool createTcpConn(shared_ptr<IMux>,
                       shared_ptr<INetStreamReader>,
                       uint16_t,
                       string,
                       string = string());
};
