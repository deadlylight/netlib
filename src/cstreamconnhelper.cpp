#include "cnetlibmuximpl.hpp"
#include "cstreamconnhelper.hpp"

CStreamConnHelper::CStreamConnHelper(shared_ptr<CStreamConn> inStreamConn)
    : mStreamConn(inStreamConn),
      mEnableRead(false),
      mEnableWrite(false),
      mFd(-1)
{
    add2Mux();
}

CStreamConnHelper::~CStreamConnHelper()
{
}

void CStreamConnHelper::add2Mux()
{
    CNetLibMuxImpl::getInstance().addMuxObject(shared_from_this());
}

void CStreamConnHelper::enableRead()
{
    mEnableRead = true;
}

bool CStreamConnHelper::write(shared_ptr<IMsgIn> inMsg)
{
    return true;
}

void CStreamConnHelper::setConnTimeout(uint32_t)
{

}

void CStreamConnHelper::setIoTimeout(uint32_t)
{

}

void CStreamConnHelper::setIdleTimeout(uint32_t)
{

}

int CStreamConnHelper::getFd() 
{
    return mFd;
}

bool CStreamConnHelper::forRead()
{
    return mEnableRead;
}

bool CStreamConnHelper::forWrite()
{
    return mEnableWrite;
}

void CStreamConnHelper::onRead() 
{
    
}

void CStreamConnHelper::onWrite() 
{

}

void CStreamConnHelper::onError() 
{

}

void CStreamConnHelper::onTimeoutCheck() 
{

}

CStreamConnHelper& CStreamConnHelper::create(shared_ptr<CStreamConn> inConn)
{
    shared_ptr<CStreamConnHelper> vHelper = make_shared<CStreamConnHelper>(inConn);
    return *vHelper;
}
