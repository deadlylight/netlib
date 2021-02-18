#pragma once
#include "caddrcommon.hpp"

using namespace std;

class CAddrIpv4 : public CAddrCommon
{
public:
    CAddrIpv4(const string &inAddr, uint16_t inPort)
    : CAddrCommon(EAddrIpv4, inAddr, inPort)
    {
        
    }
};
