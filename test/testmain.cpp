#include <iostream>
#include <imux.hpp>
#include <iaddr.hpp>
#include <itcpconnection.hpp>
#include <itcpconnectionhandler.hpp>
#include <itcpdatahandler.hpp>
#include <cmuxfactory.hpp>
#include <caddrfactory.hpp>

class TestTcpDataHandler : public ITcpDataHandler
{
private:
    shared_ptr<ITcpConnection> mTcpConnection;

public:
    ~TestTcpDataHandler() = default;
    void setTcpConnection(shared_ptr<ITcpConnection> inTcpConnection) override
    {
        mTcpConnection = inTcpConnection;
        cout << "TestTcpDataHandler setTcpConnection" << endl;
    }
    void onData() override
    {
        cout << "TestTcpDataHandler on data" << endl;
    }
    void onError() override
    {
        cout << "TestTcpDataHandler on error" << endl;
    }
};

class TestTcpConnectionHandler : public ITcpConnectionHandler
{
public:
    ~TestTcpConnectionHandler() = default;
    void onConnection(shared_ptr<ITcpConnection> inTcpConnection) override
    {
        cout << "TestTcpConnectionHandler onConnection" << endl;
        shared_ptr<ITcpDataHandler> vTcpDataHandler = make_shared<TestTcpDataHandler>();
        inTcpConnection->registerDataHandler(vTcpDataHandler);
    }
};

int main(int argc, char **argv)
{
    shared_ptr<IMux> vMux = CMuxFactory::createMux("epoll");
    shared_ptr<const IAddr> vAddr = CAddrFactory::createAddr(IAddr::EAddrIpv4, 7888);
    shared_ptr<ITcpConnectionHandler> vTcpConnectionHandler = make_shared<TestTcpConnectionHandler>();

    vMux->registerTcpServer(vAddr, vTcpConnectionHandler);
    vMux->startMux();
    return 0;
}
