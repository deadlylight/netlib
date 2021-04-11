#include "ctcpconn.hpp"
#include "ctcpconnimpl.hpp"

CTcpConn::CTcpConn(string inRemoteAddr, uint16_t inPort, string inLocalAddr)
    : mImpl(new CTcpConnImpl(*this, inRemoteAddr, inPort, inLocalAddr))
{
}

CTcpConn::~CTcpConn()
{
}
