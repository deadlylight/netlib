#pragma once
#include <sstream>
#include <imsgin.hpp>
#include <imsgout.hpp>

using namespace std;

class CMsgSimple
    : public IMsgIn,
      public IMsgOut,
      public enable_shared_from_this<CMsgSimple>
{
private:
    char *          mBuffer;
    uint32_t        mBufferSize;
    uint32_t        mReadPos;
    uint32_t        mWritePos;
    uint32_t        mProcessingSize;
    bool            mMutable;

private:
    void extend(uint32_t);
    uint32_t getRoom() const;

public:
    CMsgSimple();
    ~CMsgSimple();

    uint32_t getSize() override;

    shared_ptr<IMsgIn> getMsgIn() override;
    void *preWrite(uint32_t, uint32_t &) override;
    void commitWrite(uint32_t) override;
    void cancelWrite() override;
    void put(void *, uint32_t) override;
    void merge(IMsgIn &) override;

    const void *preRead(uint32_t, uint32_t &) override;
    void commitRead(uint32_t) override;
    void cancelRead() override;
    void *get(uint32_t) override;
};
