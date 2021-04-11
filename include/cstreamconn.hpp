#pragma once
#include <cstdint>
#include <memory>
#include <string>

using namespace std;

class CStreamConnHelper;
class CMsgIn;

class CStreamConn : public enable_shared_from_this<CStreamConn>
{
    friend class CStreamConnHelper;

protected:
    CStreamConnHelper &mHelper;

protected:
    void enableRead();
    bool write(shared_ptr<CMsgIn>);
    void setConnTimeout(uint32_t);
    void setIoTimeout(uint32_t);
    void setIdleTimeout(uint32_t);

    virtual void onConnect() = 0;
    virtual void onDisconnect() = 0;
    virtual void onRead() = 0;
    virtual void onError() = 0;
    virtual void onTimeout() = 0;

public:
    CStreamConn();
    virtual ~CStreamConn();
};
