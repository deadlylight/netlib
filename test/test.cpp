#include <iostream>
#include <ctcpconn.hpp>
#include <cnetlibmux.hpp>

using namespace std;

class CTcpTest : CTcpConn
{
public:
    CTcpTest()
        : CTcpConn("127.0.0.1", 5566)
    {
    }
    ~CTcpTest() {}

    void onConnect()
    {
        cout << __FUNCTION__ << endl;
    }
    void onDisconnect()
    {
        cout << __FUNCTION__ << endl;
    }
    void onRead(shared_ptr<IMsgIn>)
    {
        cout << __FUNCTION__ << endl;
    }
    void onWriteComplete()
    {
        cout << __FUNCTION__ << endl;
    }
    void onError()
    {
        cout << __FUNCTION__ << endl;
    }
    void onTimeout()
    {
        cout << __FUNCTION__ << endl;
    }
};

void test1()
{
    new CTcpTest;
    CNetLibMux::getInstance().run();
}

void test2()
{
}

void test3()
{
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}