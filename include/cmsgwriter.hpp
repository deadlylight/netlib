#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IMsgOut;

class CMsgWriter
{
public:
    explicit CMsgWriter(shared_ptr<IMsgOut> &, uint8_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, uint16_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, uint32_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, uint64_t);

    explicit CMsgWriter(shared_ptr<IMsgOut> &, int8_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, int16_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, int32_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, int64_t);

    explicit CMsgWriter(shared_ptr<IMsgOut> &, char *, uint32_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, unsigned char *, uint32_t);
    explicit CMsgWriter(shared_ptr<IMsgOut> &, void *, uint32_t);
};
