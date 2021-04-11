#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <chrono>
#include <poll.h>
#include <cnetlibmux.hpp>

using namespace std;

class IMuxObject;

class CNetLibMuxImpl
{
    friend class CNetLibMux;

private:
    unique_ptr<CNetLibMux> mMux;
    map<int, shared_ptr<IMuxObject>> mMuxObjects;
    shared_ptr<pollfd []> mPollFds;
    uint32_t mPollFdCount;
    chrono::system_clock::time_point mLastCheckTime;

private:
    CNetLibMuxImpl();
    void run();
    void collectFds();
    void collectFd(shared_ptr<IMuxObject> &);
    void poll();
    void stop();

    bool needCheckTimeout();
    void checkFds(uint32_t);

public:
    ~CNetLibMuxImpl();

    void addMuxObject(shared_ptr<IMuxObject>);
    void removeMuxObject(shared_ptr<IMuxObject>);

    static CNetLibMuxImpl &getInstance();
};
