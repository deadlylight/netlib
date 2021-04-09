#pragma once
#include <cstdint>
#include <string>
#include <queue>
#include "cnetstreamconn.hpp"

using namespace std;

class CMux;

class CTcpConn : public CNetStreamConn
{
private:
    uint16_t mPort;
    string mAddr;
    string mBindAddr;

public:
    CTcpConn(CMux &);
    ~CTcpConn();

    bool connect(uint16_t, string, string);
};
