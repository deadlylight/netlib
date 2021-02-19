#include <iostream>
#include <imux.hpp>
#include <imsgin.hpp>
#include <itcpserver.hpp>
#include <itcpconnection.hpp>
#include <ilogger.hpp>
#include <cmuxfactory.hpp>

using namespace std;

int main()
{
    ILogger::inst().level(ELogDbg);

    shared_ptr<IMux> vMux = CMuxFactory::createMux("epoll");
    cout << "mux created" << endl;
    shared_ptr<ITcpServer> vServer50445 = vMux->makeTcpServer(50445);
    cout << "get tcp server" << endl;
    shared_ptr<ITcpConnection> vConn = vServer50445->getNewConnection();
    cout << "get new connection" << endl;
    shared_ptr<IMsgIn> vMsg = vConn->readMsg();
    cout << "receive msg" << endl;
    cout << vMsg->getSize() << endl;
    return 0;
}
