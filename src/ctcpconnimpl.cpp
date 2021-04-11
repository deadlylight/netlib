#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cnetliblogger.hpp>
#include <ctcpconn.hpp>
#include "ctcpconnimpl.hpp"
#include "cstreamconnhelper.hpp"

CTcpConnImpl::CTcpConnImpl(CTcpConn &inConn,
                           string inRemoteAddr,
                           uint16_t inRemotePort,
                           string inLocalAddr)
    : mConn(inConn),
      mRemoteAddr(inRemoteAddr),
      mRemotePort(inRemotePort),
      mLocalAddr(inLocalAddr)
{
    connectIpv4();
}

CTcpConnImpl::~CTcpConnImpl()
{
}

void CTcpConnImpl::connectIpv4()
{
    int vRet = 0;
    int vFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (vFd < 0)
    {
        LOGERROR("Cannot new socket, errno=%d\n", errno);
        return;
    }
    vRet = ::fcntl(vFd, F_SETFL, O_NONBLOCK);
    if (vRet < 0)
    {
        LOGERROR("Cannot set to non-blocking, errno=%d\n", errno);
        return;
    }

    if (!mLocalAddr.empty())
    {
        sockaddr_in vBindAddr;
        vBindAddr.sin_family = AF_INET;
        vBindAddr.sin_addr.s_addr = inet_addr(mLocalAddr.c_str());
        vBindAddr.sin_port = 0;
        vRet = ::bind(vFd, reinterpret_cast<sockaddr *>(&vBindAddr), sizeof(vBindAddr));
        if (vRet < 0)
        {
            LOGERROR("Cannot bind to %s, errno=%d\n", mLocalAddr.c_str(), errno);
        }
    }

    sockaddr_in vAddr;
    vAddr.sin_family = AF_INET,
    vAddr.sin_addr.s_addr = inet_addr(mRemoteAddr.c_str());
    vAddr.sin_port = htons(mRemotePort);
    vRet = ::connect(vFd, reinterpret_cast<sockaddr *>(&vAddr), sizeof(vAddr));
    if ((vRet < 0) && (errno != EINPROGRESS))
    {
        LOGERROR("Cannot connect to %s:%u\n", mRemoteAddr.c_str(), mRemotePort);
        return;
    }

    CStreamConnHelper &vHelper = mConn.mHelper;
    vHelper.mFd = vFd;
}
