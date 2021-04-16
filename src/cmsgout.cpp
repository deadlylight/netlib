#include <cmsgout.hpp>

CMsgOut::CMsgOut(uint32_t inChunkSize)
    : mImpl(new CMsgOutImpl(inChunkSize))
{
}

CMsgOut::~CMsgOut()
{

}

uint32_t CMsgOut::getSize()
{
    return mImpl->getSize();
}

shared_ptr<IMsgIn> CMsgOut::getMsgIn()
{
    return mImpl->getMsgIn();
}

void *CMsgOut::preWrite(uint32_t inSize)
{
    return mImpl->preWrite(inSize);
}

iovec *CMsgOut::preWritev(uint32_t &outCount)
{
    return mImpl->preWrite(outCount);
}

void CMsgOut::commitWrite(uint32_t inSize)
{
    return mImpl->commitWrite(inSize);
}

void CMsgOut::cancelWrite()
{
    return mImpl->cancelWrite();
}

void CMsgOut::put(void *inData, uint32_t inSize)
{
    return mImpl->put(inData, inSize);
}

void CMsgOut::merge(IMsgIn &inMsg)
{
    return mImpl->merge(inMsg);
}

void CMsgOut::merge(CMsgOut &inMsg)
{
    return mImpl->merge(inMsg);
}
