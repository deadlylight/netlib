#include "ctcpconn.hpp"
#include "ctcpconnimpl.hpp"
#include "cstreamconnhelper.hpp"

CTcpConnImpl::CTcpConnImpl(CTcpConn &inConn,
                           string inRemoteAddr,
                           uint16_t inPort,
                           string inLocalAddr)
    : mConn(inConn),
      mRemoteAddr(inRemoteAddr),
      mPort(inPort),
      mLocalAddr(inLocalAddr)
{
}

CTcpConnImpl::~CTcpConnImpl()
{
}

bool CTcpConnImpl::connect()
{
    CStreamConnHelper &vHelper = mConn.mHelper;
    return vHelper.mFd == -1;
}
