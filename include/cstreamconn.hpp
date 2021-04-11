#pragma once
#include <cstdint>
#include <memory>
#include <string>

using namespace std;

class CStreamConnHelper;
class IMsgIn;

class CStreamConn : public enable_shared_from_this<CStreamConn>
{
    friend class CStreamConnHelper;

protected:
    CStreamConnHelper &mHelper;

protected:
    void enableRead();
    bool write(shared_ptr<IMsgIn>); // false when queue full, should wait for onWriteComplete
    void setConnTimeout(uint32_t);
    void setIoTimeout(uint32_t);
    void setIdleTimeout(uint32_t);

    virtual void onConnect() = 0;
    virtual void onDisconnect() = 0;
    virtual void onRead(shared_ptr<IMsgIn>) = 0;    // when data arrive
    virtual void onWriteComplete() = 0; // when queue has space
    virtual void onError() = 0;
    virtual void onTimeout() = 0;

public:
    CStreamConn();
    virtual ~CStreamConn();
};
