#pragma once
#include <string>
#include <iaddr.hpp>

using namespace std;

class CAddrCommon : public IAddr
{
private:
    const EAddrType mType;
    const string mAddr;
    const uint16_t mPort;

public:
    CAddrCommon(EAddrType, const string &, uint16_t);
    ~CAddrCommon();

    EAddrType getType() const override;
    const string &getAddr() const override;
    uint16_t getPort() const override;
};
