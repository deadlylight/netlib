#include <cassert>
#include <cstring>
#include <cmsgreader.hpp>
#include <IMsgIn.hpp>

static void readMsg(shared_ptr<IMsgIn> &inMsg, void *inBuf, uint32_t inSize)
{
    if (inSize == 0)
    {
        return;
    }
    uint32_t vBufSize = 0;
    const void *vBuf = inMsg->preRead(inSize, vBufSize);
    assert(vBufSize >= inSize);
    memcpy(inBuf, vBuf, inSize);
    inMsg->commitRead(inSize);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, uint8_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 1);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, uint16_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 2);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, uint32_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 4);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, uint64_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 8);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, int8_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 1);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, int16_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 2);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, int32_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 4);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, int64_t &inVal)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inVal), 8);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, char *inBuf, uint32_t inSize)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inBuf), inSize);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, unsigned char *inBuf, uint32_t inSize)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inBuf), inSize);
}

CMsgReader::CMsgReader(shared_ptr<IMsgIn> &inMsg, void *inBuf, uint32_t inSize)
{
    readMsg(inMsg, reinterpret_cast<void *>(&inBuf), inSize);
}
