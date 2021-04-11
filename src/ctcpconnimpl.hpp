#pragma once
#include <cstdint>
#include <string>

using namespace std;

class CTcpConn;

class CTcpConnImpl
{
private:
    CTcpConn &mConn;
    string mRemoteAddr;
    uint16_t mPort;
    string mLocalAddr;

private:
    bool connect();

public:
    CTcpConnImpl(CTcpConn &, string inRemoteAddr, uint16_t inPort, string inLocalAddr);
    ~CTcpConnImpl();
};
