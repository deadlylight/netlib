#include <cassert>
#include <cstring>
#include <cmsgwriter.hpp>
#include <imsgout.hpp>

static void writeMsg(shared_ptr<IMsgOut> &inMsg, void *inBuf, uint32_t inSize)
{
    if (inSize == 0)
    {
        return;
    }
    uint32_t vBufSize = 0;
    void *vBuf = inMsg->preWrite(inSize, vBufSize);
    assert(vBufSize >= inSize);
    memcpy(vBuf, inBuf, inSize);
    inMsg->commitWrite(inSize);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, uint8_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 1);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, uint16_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 2);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, uint32_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 4);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, uint64_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 8);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, int8_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 1);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, int16_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 2);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, int32_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 4);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, int64_t inVal)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inVal), 8);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, char *inBuf, uint32_t inSize)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inBuf), inSize);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, unsigned char *inBuf, uint32_t inSize)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inBuf), inSize);
}

CMsgWriter::CMsgWriter(shared_ptr<IMsgOut> &inMsg, void *inBuf, uint32_t inSize)
{
    writeMsg(inMsg, reinterpret_cast<void *>(&inBuf), inSize);
}
