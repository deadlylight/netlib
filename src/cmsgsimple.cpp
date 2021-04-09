#include <cassert>
#include <cstring>
#include <algorithm>
#include "cmsgsimple.hpp"

using namespace std;

static const uint32_t gDefaultSize = 8192;

CMsgSimple::CMsgSimple()
    : mBuffer(new char[gDefaultSize]),
      mBufferSize(gDefaultSize),
      mReadPos(0),
      mWritePos(0),
      mProcessingSize(0),
      mMutable(true)
{
}

CMsgSimple::~CMsgSimple()
{
    assert(mProcessingSize == 0);
    delete [] mBuffer;
}

uint32_t CMsgSimple::getSize()
{
    return mWritePos - mReadPos;
}

uint32_t CMsgSimple::getRoom() const
{
    return mBufferSize - mWritePos;
}

shared_ptr<IMsgIn> CMsgSimple::getMsgIn()
{
    mMutable = false;
    return shared_from_this();
}

void CMsgSimple::extend(uint32_t inDelta)
{
    uint32_t vDeltaRounded = (inDelta + gDefaultSize - 1) / gDefaultSize * gDefaultSize;
    uint32_t vNewSize = vDeltaRounded + mBufferSize;
    char *vNewBuffer = new char[vNewSize];
    assert(mReadPos == 0);
    memcpy(vNewBuffer, mBuffer, mWritePos);
    delete [] mBuffer;
    mBuffer = vNewBuffer;
    mBufferSize = vNewSize;
}

void *CMsgSimple::preWrite(uint32_t inSize, uint32_t &outSize)
{
    assert(mMutable);
    assert(!mProcessingSize);

    if (inSize == 0)
    {
        if (getRoom() == 0)
        {
            extend(gDefaultSize);
        }
    }
    else
    {
        if (getRoom() < inSize)
        {
            extend(inSize - getRoom());
        }
    }

    mProcessingSize = getRoom();
    outSize = mProcessingSize;
    return mBuffer + mWritePos;
}

void CMsgSimple::commitWrite(uint32_t inSize)
{
    assert(mMutable);
    assert(mProcessingSize);
    assert(inSize <= mProcessingSize);
    mWritePos += inSize;
    mProcessingSize = 0;
}

void CMsgSimple::cancelWrite()
{
    assert(mMutable);
    assert(mProcessingSize);
    mProcessingSize = 0;
}

void CMsgSimple::put(void *inBuf, uint32_t inSize)
{
    if (inSize == 0)
    {
        return;
    }
    uint32_t vOutSize = 0;
    void *vTo = preWrite(inSize, vOutSize);
    assert(inSize == vOutSize);
    memcpy(vTo, inBuf, vOutSize);
    commitWrite(vOutSize);
}

void CMsgSimple::merge(IMsgIn &inMsg)
{
    if (inMsg.getSize() == 0)
    {
        return;
    }
    uint32_t vReadSize = 0;
    uint32_t vWriteSize = 0;
    const void *vFrom = inMsg.preRead(inMsg.getSize(), vReadSize);
    assert(inMsg.getSize() == vReadSize);
    void *vTo = preWrite(vReadSize, vWriteSize);
    assert(vReadSize == vWriteSize);
    memcpy(vTo, vFrom, vWriteSize);
    inMsg.commitRead(vReadSize);
    commitWrite(vWriteSize);
}

const void *CMsgSimple::preRead(uint32_t inSize, uint32_t &outSize)
{
    assert(!mMutable);
    assert(!mProcessingSize);
    mProcessingSize = min(inSize, getSize());
    outSize = mProcessingSize;
    return mBuffer + mReadPos;
}

void CMsgSimple::commitRead(uint32_t inSize)
{
    assert(!mMutable);
    assert(mProcessingSize);
    assert(inSize <= mProcessingSize);
    mReadPos += inSize;
    mProcessingSize = 0;

    if (getSize() == 0)
    {
        delete [] mBuffer;
        mBuffer = nullptr;
        mBufferSize = 0;
        mReadPos = mWritePos = 0;
    }
}

void CMsgSimple::cancelRead()
{
    assert(!mMutable);
    assert(mProcessingSize);
    mProcessingSize = 0;
}

void *CMsgSimple::get(uint32_t inSize)
{
    assert(!mMutable);
    if (getSize() < inSize)
    {
        return nullptr;
    }
    void *vRet = mBuffer + mReadPos;
    mReadPos += inSize;
    return vRet;
}
