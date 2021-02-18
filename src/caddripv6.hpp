#pragma once
#include "caddrcommon.hpp"

using namespace std;

class CAddrIpv6 : public CAddrCommon
{
public:
    CAddrIpv6(const string &inAddr, uint16_t inPort)
    : CAddrCommon(EAddrIpv6, inAddr, inPort)
    {
        
    }
};
