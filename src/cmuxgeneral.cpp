#include <sys/epoll.h>
#include <unistd.h>
#include <thread>
#include <cmuxgeneral.hpp>
#include "sctlmsg.h"
#include "cctlmsg.hpp"
#include "cmuxpipeevent.hpp"

CMuxGeneral::CMuxGeneral()
    : mControlFd{-1, -1}, mFdCount(0), mStopped(false)
{
}

CMuxGeneral::~CMuxGeneral()
{
    close(mControlFd[0]);
    close(mControlFd[1]);
}

bool CMuxGeneral::startMux()
{
    if (!initMux())
    {
        return false;
    }
    if (!makeMuxCtl())
    {
        return false;
    }
    startMuxThread();
    return true;
}

void CMuxGeneral::stopMux()
{
    mStopped = true;
    sendStopMsg();
}

void CMuxGeneral::sendStopMsg()
{
    lock_guard<mutex> vGuard(mMakeMutex);
    CCtlMsg vCtlMsg(*this);
    vCtlMsg.makeStopCtlMsg();
}

shared_ptr<ITcpServer> CMuxGeneral::makeTcpServer(uint16_t inPort, const string inBindAddr)
{
    lock_guard<mutex> vGuard(mMakeMutex);
    CCtlMsg vCtlMsg(*this);
    bool vRet = vCtlMsg.makeServerCtlMsg(inPort, inBindAddr);
    if (!vRet)
    {
        return nullptr;
    }
    return mMuxIpc.reteiveTcpServer();
}

shared_ptr<ITcpConnection> CMuxGeneral::makeTcpClient(uint16_t inPort, const string &inRemoteAddr, const string inBindAddr)
{
    lock_guard<mutex> vGuard(mMakeMutex);
    CCtlMsg vCtlMsg(*this);
    bool vRet = vCtlMsg.makeClientCtlMsg(inPort, inRemoteAddr, inBindAddr);
    if (!vRet)
    {
        return nullptr;
    }
    return mMuxIpc.reteiveTcpClient();
}

bool CMuxGeneral::makeMuxCtl()
{
    int vRet = pipe(mControlFd);
    if (vRet < 0)
    {
        return false;
    }
    int vFd = mControlFd[0];
    shared_ptr<IMuxEvent> vPipeEvent = make_shared<CMuxPipeEvent>(vFd, mSelf);
    return registerMuxEvent(vPipeEvent);
}

bool CMuxGeneral::registerMuxEvent(shared_ptr<IMuxEvent> inMuxEvent)
{
    int vFd = inMuxEvent->getFd();
    if (!registerMux(vFd))
    {
        return false;
    }
    setMuxEvent(inMuxEvent);
    return true;
}

void CMuxGeneral::startMuxThread()
{
    shared_ptr<CMuxGeneral> vMuxGeneral = mSelf.lock();
    thread vThread(muxLoop, vMuxGeneral);
    vThread.detach();
}

void CMuxGeneral::handleEvent(int inFd, uint32_t inType)
{
    shared_ptr<IMuxEvent> vMuxEvent = getMuxEvent(inFd);
    if (inType & EMuxEventError)
    {
        vMuxEvent->onError();
        return; // stop when error happens
    }
    if (inType & EMuxEventRead)
    {
        vMuxEvent->onReadable();
    }
    if (inType & EMuxEventWrite)
    {
        vMuxEvent->onWritable();
    }
}

shared_ptr<IMuxEvent> CMuxGeneral::getMuxEvent(int inFd)
{
    return mFd2Events[inFd];
}

void CMuxGeneral::setMuxEvent(shared_ptr<IMuxEvent> inMuxEvent)
{
    mFd2Events[inMuxEvent->getFd()] = inMuxEvent;
}

void CMuxGeneral::muxLoop(shared_ptr<CMuxGeneral> inMuxGeneral)
{
    inMuxGeneral->mainLoop();
}

shared_ptr<ITcpServer> CMuxGeneral::CMuxIpc::reteiveTcpServer()
{
    unique_lock<mutex> vLock(mMutex);
    while (!mTcpServer)
    {
        mCond.wait(vLock);
    }
    return std::move(mTcpServer);
}

shared_ptr<ITcpConnection> CMuxGeneral::CMuxIpc::reteiveTcpClient()
{
    unique_lock<mutex> vLock(mMutex);
    while (!mTcpClient)
    {
        mCond.wait(vLock);
    }
    return std::move(mTcpClient);
}

void CMuxGeneral::CMuxIpc::provideTcpServer(shared_ptr<ITcpServer> inTcpServer)
{
    unique_lock<mutex> vLock(mMutex);
    mTcpServer = inTcpServer;
    mCond.notify_one();
}

void CMuxGeneral::CMuxIpc::provideTcpClient(shared_ptr<ITcpConnection> inTcpClient)
{
    unique_lock<mutex> vLock(mMutex);
    mTcpClient = inTcpClient;
    mCond.notify_one();
}
