#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <poll.h>
#include <cnetlibmux.hpp>

using namespace std;

class IMuxObject;

class CNetLibMuxImpl
{
private:
    CNetLibMux &mMux;
    map<int, shared_ptr<IMuxObject>> mMuxObjects;
    shared_ptr<pollfd []> mPollFds;
    uint32_t mPollFdCount;

private:
    bool needCheckTimeout();
    void checkFds(uint32_t);

public:
    CNetLibMuxImpl(CNetLibMux &);
    ~CNetLibMuxImpl();

    void run();
};
