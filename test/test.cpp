#include <iostream>
#include <thread>
#include <chrono>
#include <netlib.hpp>

using namespace std;

class TestAsyncTcpServer : public IAsyncTcpServer
{
private:
    uint16_t mTestAsyncTcpServerPort;
    uint32_t mConnectionCount;

public:
    TestAsyncTcpServer(uint16_t inPort)
        : mTestAsyncTcpServerPort(inPort), mConnectionCount(0)
    {
    }
    uint16_t getTcpPort() override
    {
        return mTestAsyncTcpServerPort;
    }
    void onNewTcpConn(shared_ptr<IASyncTcpConn>)
    {
        mConnectionCount++;
        cout << "TestAsyncTcpServer onNewTcpConn" << endl;
    }
    void onShutdown()
    {
        cout << "TestAsyncTcpServer onShutdown" << endl;
    }
    bool done()
    {
        return mConnectionCount > 0;
    }
};

void test1()
{
/*
    cout << "test 1 starts" << endl;
    shared_ptr<IMux> vMux = CMuxFactory::createMux("epoll");
    cout << "mux created" << endl;
    shared_ptr<ISyncTcpServer> vServer50445 = CTcpFactory::createSyncTcpServer(vMux, 50445);
    cout << "create sync tcp server" << endl;

    shared_ptr<ISyncTcpConn> vConn = vServer50445->getNewTcpConn();
    cout << "get new connection" << endl;
    vMux->stopMux();
*/
}

void test2()
{

    cout << "test 2 starts" << endl;
    shared_ptr<IMux> vMux = CMuxFactory::createMux("epoll", "0.0.0.0");
    cout << "mux created" << endl;
    shared_ptr<TestAsyncTcpServer> vServer50445 = make_shared<TestAsyncTcpServer>(50445);
    CTcpFactory::registerAsyncTcpServer(vMux, vServer50445);
    cout << "register async tcp server" << endl;
    while (!vServer50445->done())
    {
        this_thread::sleep_for (chrono::seconds(1));
    }
    vMux->stopMux();
}

int main()
{
    test1();
    return 0;
}
