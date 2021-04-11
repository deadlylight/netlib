#pragma once

class CStreamServerImpl;

class CStreamServer
{
private:
    unique_ptr<CStreamServerImpl> mImpl;

protected:
    void setMaxConn(uint32_t);

public:
    CStreamServer();
    ~CStreamServer();

    virtual void onStart() = 0;
    virtual void onStop() = 0;
    virtual void onNewConn() = 0;
    virtual void onCloseConn() = 0;
};
