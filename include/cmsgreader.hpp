#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IMsgIn;

class CMsgReader
{
public:
    explicit CMsgReader(shared_ptr<IMsgIn> &, uint8_t &);
    explicit CMsgReader(shared_ptr<IMsgIn> &, uint16_t &);
    explicit CMsgReader(shared_ptr<IMsgIn> &, uint32_t &);
    explicit CMsgReader(shared_ptr<IMsgIn> &, uint64_t &);

    explicit CMsgReader(shared_ptr<IMsgIn> &, int8_t &);
    explicit CMsgReader(shared_ptr<IMsgIn> &, int16_t &);
    explicit CMsgReader(shared_ptr<IMsgIn> &, int32_t &);
    explicit CMsgReader(shared_ptr<IMsgIn> &, int64_t &);

    explicit CMsgReader(shared_ptr<IMsgIn> &, char *, uint32_t);
    explicit CMsgReader(shared_ptr<IMsgIn> &, unsigned char *, uint32_t);
    explicit CMsgReader(shared_ptr<IMsgIn> &, void *, uint32_t);
};
