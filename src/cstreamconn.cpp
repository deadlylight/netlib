#include <cstreamconn.hpp>
#include "cstreamconnhelper.hpp"

CStreamConn::CStreamConn()
    : mHelper(CStreamConnHelper::create(shared_from_this()))
{
}

CStreamConn::~CStreamConn()
{
}

void CStreamConn::enableRead()
{
    return mHelper.enableRead();
}

bool CStreamConn::write(shared_ptr<CMsgIn> in)
{
    return mHelper.write(in);
}

void CStreamConn::setConnTimeout(uint32_t in)
{
    mHelper.setConnTimeout(in);
}

void CStreamConn::setIoTimeout(uint32_t in)
{
    return mHelper.setIoTimeout(in);
}

void CStreamConn::setIdleTimeout(uint32_t in)
{
    return mHelper.setIdleTimeout(in);
}
