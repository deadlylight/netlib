#pragma once
#include <memory>
#include <cstreamconn.hpp>

using namespace std;

class CTcpConnImpl;

class CTcpConn : public CStreamConn
{
    friend class CTcpConnImpl;

private:
    unique_ptr<CTcpConnImpl> mImpl;

public:
    CTcpConn(string inRemoteAddr, uint16_t inPort, string inLocalAddr = string());
    ~CTcpConn();
};
