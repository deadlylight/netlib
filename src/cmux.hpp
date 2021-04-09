#pragma once
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <chrono>
#include <imux.hpp>

using namespace std;

struct pollfd;
class CSlotMgr;
class INetIo;

class CMux : public IMux
{
private:
    unordered_map<int, shared_ptr<INetIo>> mIos;
    unique_ptr<pollfd[]> mPollFds;
    uint32_t mPollFdsCount;
    chrono::system_clock::time_point mStopTime;
    chrono::system_clock::time_point mLastUpdateTime;

private:
    void addPollFd(int, short);
    void collectFds();
    void poll();
    void checkFds();
    void checkFd(const pollfd &inPollFd);
    void checkTimeout();
    bool stopped();

public:
    CMux();
    ~CMux();

    void run(uint32_t) override;

    void stopMux();
    bool addNetIo(shared_ptr<INetIo>);
    bool removeNetIo(shared_ptr<INetIo>);
};
