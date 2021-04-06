#pragma once
#include <memory>
#include <string>

using namespace std;

class ITcpServer;
class ITcpAccept;
class ITcpConn;
class ITcpRead;

class CTcpFactory
{
public:
    CTcpFactory() = delete;
    // server handler, port, bind
    shared_ptr<ITcpServer> createTcpServer(shared_ptr<ITcpAccept>,
                                           uint16_t,
                                           string = string());

    shared_ptr<ITcpConn> createTcpConn(shared_ptr<ITcpRead>,
                                       uint16_t,
                                       string,
                                       string = string());
};
