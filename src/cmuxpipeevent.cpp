#include <unistd.h>
#include "cmuxpipeevent.hpp"
#include "cmuxgeneral.hpp"
#include "sctlmsg.h"
#include "cctlmsg.hpp"

CMuxPipeEvent::CMuxPipeEvent(int inFd, weak_ptr<CMuxGeneral> inMux)
    : mFd(inFd), mMux(inMux)
{
}

CMuxPipeEvent::~CMuxPipeEvent()
{
}

int CMuxPipeEvent::getFd()
{
    return mFd;
}

uint32_t CMuxPipeEvent::getMuxEvents()
{
    return EMuxEventRead;
}

void CMuxPipeEvent::onError()
{
}

void CMuxPipeEvent::onReadable()
{
    readCtlMsg();
}

void CMuxPipeEvent::onWritable()
{
}

void CMuxPipeEvent::readCtlMsg()
{
    shared_ptr<CMuxGeneral> vMuxGeneral = mMux.lock();
    if (!vMuxGeneral)
    {
        return;
    }

    int vReadFd = vMuxGeneral->mControlFd[0];
    SCtlMsg vCtlMsg;
    const size_t vSize = sizeof(vCtlMsg);
    int vRet = read(vReadFd, &vCtlMsg, vSize);
    if (vRet != vSize)
    {
        return;
    }

    CCtlMsg vMsg(*vMuxGeneral);
    vMsg.handleCtlMsg(vCtlMsg);
}
