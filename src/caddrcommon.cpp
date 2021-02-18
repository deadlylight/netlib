#include "caddrcommon.hpp"

CAddrCommon::CAddrCommon(EAddrType inType, const string &inAddr, uint16_t inPort)
: mType(inType), mAddr(inAddr), mPort(inPort)
{

}

CAddrCommon::~CAddrCommon()
{
}

IAddr::EAddrType CAddrCommon::getType() const
{
    return mType;
}

const string &CAddrCommon::getAddr() const
{
    return mAddr;
}

uint16_t CAddrCommon::getPort() const
{
    return mPort;
}
