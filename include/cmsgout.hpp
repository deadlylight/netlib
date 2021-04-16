#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IMsgIn;
class CMsgImpl;
struct iovec;

class CMsgOut
{
private:
    shared_ptr<CMsgImpl> mImpl;

public:
    CMsgOut(uint32_t = 0);
    ~CMsgOut();
    uint32_t getSize();
    shared_ptr<IMsgIn> getMsgIn();  // move data to IMsgIn

    // write by chunk
    void *preWrite(uint32_t);
    iovec *preWritev(uint32_t &out);
    void commitWrite(uint32_t);
    void cancelWrite();

    void put(void *, uint32_t); // auto commit, auto allocate space

    void merge(IMsgIn &);
    void merge(CMsgOut &);
};
