#pragma once
#include <cstdint>
#include <string>
#include <queue>
#include <chrono>
#include <inetstreamconn.hpp>
#include "inetio.hpp"

using namespace std;

class CMux;
class INetStreamReader;

class CTimeout
{
public:
    uint64_t mConnTimeout;
    uint64_t mIoTimeout;
    uint64_t mIdleTimeout;
    uint64_t mTimerInterval;

public:
    CTimeout();
};

class CNetStreamConn : public INetStreamConn, public INetIo, public enable_shared_from_this<CNetStreamConn>
{
private:
    CMux &mMux;
    bool mIsWrite;
    bool mIsRead;
    bool mIsConnecting;
    CTimeout mTimeout;
    chrono::system_clock::time_point mLastUpdateTime;
    shared_ptr<INetStreamReader> mReader;
    queue<shared_ptr<IMsgIn>> mMsgs;

protected:
    int mSk;
    int mError;

private:
    void dowrite();
    bool sendOneMsg(shared_ptr<IMsgIn> &);

protected:
    bool add2Mux();

public:
    CNetStreamConn(CMux &);
    ~CNetStreamConn();

    bool isConnecting() const;
    void markWrite(bool = true);
    void markRead(bool =true);
    void markBad();

    bool sendMsg(shared_ptr<IMsgIn>) override;
    bool isBad() override;

    int getFd() override;
    bool forWrite() override;
    bool forRead() override;
    void onWrite() override;
    void onRead() override;
    void onConn() override;
    void onDisconn() override;
    void onTimeout() override;
    void onError() override;
};
