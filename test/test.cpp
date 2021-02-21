#include <iostream>
#include <imux.hpp>
#include <imsgin.hpp>
#include <itcpserver.hpp>
#include <itcpconnection.hpp>
#include <itcpqueue.hpp>
#include <itcpmsg.hpp>
#include <ilogger.hpp>
#include <cmuxfactory.hpp>

using namespace std;


void test1()
{
    shared_ptr<IMux> vMux = CMuxFactory::createMux("epoll");
    cout << "mux created" << endl;
    shared_ptr<ITcpServer> vServer50445 = vMux->makeTcpServer(50445);
    cout << "get tcp server" << endl;
    shared_ptr<ITcpConnection> vConn = vServer50445->getQueue()->pop();
    cout << "get new connection" << endl;
    shared_ptr<ITcpMsg> vMsg = vConn->getQueue()->pop();
    cout << "receive msg" << endl;
    vMux->stopMux();
}

int main()
{
    ILogger::inst().level(ELogDbg);

    test1();
    return 0;
}
