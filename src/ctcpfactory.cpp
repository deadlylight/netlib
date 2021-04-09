#include <cassert>
#include <ctcpfactory.hpp>
#include "inetio.hpp"
#include "cnetstreamconn.hpp"
#include "ctcpconn.hpp"
#include "cmux.hpp"

bool CTcpFactory::createTcpServer(shared_ptr<IMux> inMux,
                                  shared_ptr<INetStreamAccepter> inAccepter,
                                  uint16_t inPort,
                                  string inBindAddr)
{
    return false;
}

bool CTcpFactory::createTcpConn(shared_ptr<IMux> inMux,
                                shared_ptr<INetStreamReader> inReader,
                                uint16_t inPort,
                                string inAddr,
                                string inBindAddr)
{
    CMux *vMux = dynamic_cast<CMux *>(inMux.get());
    assert(vMux);

    shared_ptr<CTcpConn> vTcpConn = make_shared<CTcpConn>(*vMux);

    bool vRet = vTcpConn->connect(inPort, inAddr, inBindAddr);
    if (!vRet)
    {
        return false;
    }

    return vMux->addNetIo(vTcpConn);
}
