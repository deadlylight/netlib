#pragma once
#include <memory>
#include "imuxobject.hpp"

using namespace std;

class CStreamConn;
class CMsgIn;

class CStreamConnHelper : public IMuxObject, public enable_shared_from_this<CStreamConnHelper>
{
    friend class CTcpConnImpl;

private:
    shared_ptr<CStreamConn> mStreamConn;
    bool mEnableRead;
    int mFd;

public:
    CStreamConnHelper(shared_ptr<CStreamConn>);
    ~CStreamConnHelper();

    void enableRead();
    bool write(shared_ptr<CMsgIn>);
    void setConnTimeout(uint32_t);
    void setIoTimeout(uint32_t);
    void setIdleTimeout(uint32_t);

    int getFd() override;
    void onRead() override;
    void onWrite() override;
    void onError() override;
    void onTimeoutCheck() override;

    static CStreamConnHelper& create(shared_ptr<CStreamConn>);
};
