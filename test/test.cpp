#include <iostream>
#include <thread>
#include <chrono>

#include <imsgin.hpp>
#include <imsgout.hpp>
#include <cmsgfactory.hpp>
#include <cmsgwriter.hpp>
#include <cmsgreader.hpp>

#include <imux.hpp>
#include <cmuxfactory.hpp>
#include <inetstreamserver.hpp>
#include <inetstreamconn.hpp>
#include <inetstreamaccepter.hpp>
#include <inetstreamreader.hpp>
#include <ctcpfactory.hpp>

using namespace std;

void test1()
{
    cout << "test1 start" << endl;
    shared_ptr<IMsgOut> vMsgOut = CMsgFactory::createMsg();
    uint8_t v1 = 5;
    uint32_t v2 = 0x5678;
    CMsgWriter(vMsgOut, v1);
    CMsgWriter(vMsgOut, v2);
    cout << "out.size " << vMsgOut->getSize() << endl;

    shared_ptr<IMsgIn> vMsgIn = vMsgOut->getMsgIn();
    uint32_t v3 = 0;
    uint8_t v4 = 0;
    uint32_t vReadSize = 0;
    vMsgIn->preRead(5, vReadSize);
    vMsgIn->cancelRead();
    CMsgReader(vMsgIn, v3);
    CMsgReader(vMsgIn, v4);
    cout << "v3=" << v3 << " v4=" << static_cast<uint32_t>(v4) << endl;
}


class CTestTcpReader : public INetStreamReader
{
public:
    CTestTcpReader()
    {
    }
    ~CTestTcpReader()
    {
    }
    void onRead(shared_ptr<IMsgIn> inMsg)
    {
        cout << "CTestTcpReader::onRead" << endl;
    }
    void onConn(shared_ptr<INetStreamConn>)
    {
        cout << "CTestTcpReader::onConn" << endl;
    }
    void onDisconn()
    {
        cout << "CTestTcpReader::onDisconn" << endl;
    }
    void onTimeout()
    {
        cout << "CTestTcpReader::onTimeout" << endl;
    }
    void onError()
    {
        cout << "CTestTcpReader::onError" << endl;
    }
};

void test2()
{
    cout << "test2 start" << endl;
    shared_ptr<IMux> vMux = CMuxFactory::createMux();
    shared_ptr<CTestTcpReader> vReader = make_shared<CTestTcpReader>();
    bool vRet = CTcpFactory::createTcpConn(vMux, vReader, 111, "10.228.84.231");
    if (!vRet)
    {
        cout << "cannot create tcp conn" << endl;
        return;
    }
    vMux->run(3);
}

class CTestTcpAccepter : public INetStreamAccepter
{
public:
    CTestTcpAccepter()
    {
    }
    ~CTestTcpAccepter()
    {
    }
    shared_ptr<INetStreamReader> onNewConn() override
    {
        shared_ptr<CTestTcpReader> vReader = make_shared<CTestTcpReader>();
        return vReader;
    }
    void onServerStarted(shared_ptr<INetStreamServer>) override
    {
        cout << "CTestTcpAccepter::onServerStarted" << endl;
    }
};

void test3()
{
    cout << "test3 start" << endl;
    shared_ptr<IMux> vMux = CMuxFactory::createMux();
    shared_ptr<CTestTcpAccepter> vAccepter5566 = make_shared<CTestTcpAccepter>();
    bool vTcpServer5566 = CTcpFactory::createTcpServer(vMux, vAccepter5566, 5566);
    if (!vTcpServer5566)
    {
        cout << "create tcp server fail" << endl;
        return;
    }
    vMux->run(3);
}

int main()
{
    test1();
    test2();
    return 0;
}
