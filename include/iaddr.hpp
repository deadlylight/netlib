#pragma once
#include <cstdint>
#include <string>

using namespace std;

class IAddr
{
public:
    enum EAddrType
    {
        EAddrIpv4,
        EAddrIpv6,
    };

public:
    virtual ~IAddr() = default;
    virtual EAddrType getType() const = 0;
    virtual const string &getAddr() const = 0;
    virtual uint16_t getPort() const = 0;
};
