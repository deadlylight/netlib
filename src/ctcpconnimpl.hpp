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
    uint16_t mRemotePort;
    string mLocalAddr;

private:
    void connectIpv4();

public:
    CTcpConnImpl(CTcpConn &, string inRemoteAddr, uint16_t inRemotePort, string inLocalAddr);
    ~CTcpConnImpl();
};
