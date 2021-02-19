#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "cctlmsg.hpp"
#include "sctlmsg.h"
#include "cmuxgeneral.hpp"
#include "ctcpconnection.hpp"
#include "ctcpserver.hpp"

CCtlMsg::CCtlMsg(CMuxGeneral &inMux)
    : mMux(inMux), mSk(-1), mPort(0)
{
}

CCtlMsg::~CCtlMsg()
{
    close(mSk);
}

void CCtlMsg::handleCtlMsg(const SCtlMsg &inMsg)
{
    switch (inMsg.mType)
    {
    case ECtlMsgServer:
        mPort = inMsg.mSC.mServer.mPort;
        mBindAddr = inMsg.mSC.mServer.mBindAddr;
        makeServer();
        break;
    case ECtlMsgClient:
        mPort = inMsg.mSC.mClient.mPort;
        mRemoteAddr = inMsg.mSC.mClient.mRemoteAddr;
        mBindAddr = inMsg.mSC.mClient.mBindAddr;
        makeClient();
        break;
    case ECtlMsgStopMux:
        mMux.stopMux();
        break;
    default:
        break;
    }
}

bool CCtlMsg::makeServerCtlMsg(uint16_t, const string &)
{
    return true;
}

bool CCtlMsg::makeClientCtlMsg(uint16_t, const string &, const string &)
{
    return true;
}

void CCtlMsg::makeClient()
{
    mSk = socket(AF_INET, SOCK_STREAM, 0);
    if (mSk < 0)
    {
        return;
    }
    int vRet = fcntl(mSk, F_SETFL, O_NONBLOCK);
    if (vRet < 0)
    {
        return;
    }
    if (mBindAddr.length() > 0)
    {
        sockaddr_in vBindAddr = {0};
        vBindAddr.sin_family = AF_INET;
        vBindAddr.sin_addr.s_addr = inet_addr(mBindAddr.c_str());
        vBindAddr.sin_port = 0;
        vRet = bind(mSk, reinterpret_cast<sockaddr *>(&vBindAddr), sizeof(vBindAddr));
        if (vRet < 0)
        {
            return;
        }
    }
    sockaddr_in vAddr = {0};
    vAddr.sin_family = AF_INET;
    vAddr.sin_addr.s_addr = inet_addr(mRemoteAddr.c_str());
    vAddr.sin_port = htons(mPort);
    vRet = connect(mSk, reinterpret_cast<sockaddr *>(&vAddr), sizeof(vAddr));
    if ((vRet < 0) && (errno != EINPROGRESS))
    {
        return;
    }
    shared_ptr<CTcpConnection> vTcpConnection = make_shared<CTcpConnection>(mSk);
    mSk = -1;
    mMux.registerMuxEvent(vTcpConnection);
    mMux.mMuxIpc.provideTcpClient(vTcpConnection);
}

void CCtlMsg::makeServer()
{
    mSk = socket(AF_INET, SOCK_STREAM, 0);
    if (mSk < 0)
    {
        return;
    }
    int vRet = fcntl(mSk, F_SETFL, O_NONBLOCK);
    if (vRet < 0)
    {
        return;
    }
    if (mBindAddr.length() > 0)
    {
        sockaddr_in vBindAddr = {0};
        vBindAddr.sin_family = AF_INET;
        vBindAddr.sin_addr.s_addr = inet_addr(mBindAddr.c_str());
        vBindAddr.sin_port = 0;
        vRet = bind(mSk, reinterpret_cast<sockaddr *>(&vBindAddr), sizeof(vBindAddr));
        if (vRet < 0)
        {
            return;
        }
    }
    vRet = listen(mSk, 64);
    if (vRet < 0)
    {
        return;
    }
    shared_ptr<CTcpServer> vTcpServer = make_shared<CTcpServer>(mSk);
    mSk = -1;
    mMux.registerMuxEvent(vTcpServer);
    mMux.mMuxIpc.provideTcpServer(vTcpServer);
}
