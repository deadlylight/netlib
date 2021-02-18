#include <caddrfactory.hpp>
#include "caddripv4.hpp"
#include "caddripv6.hpp"

shared_ptr<IAddr> CAddrFactory::createAddr(const IAddr::EAddrType inType, const uint16_t inPort, const string inAddr)
{
    switch (inType)
    {
        case IAddr::EAddrIpv4:
            return make_shared<CAddrIpv4>(inAddr, inPort);
            break;
        case IAddr::EAddrIpv6:
            return make_shared<CAddrIpv4>(inAddr, inPort);
            break;
        default:
            return nullptr;
    }
}
