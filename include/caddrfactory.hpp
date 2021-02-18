#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <iaddr.hpp>

using namespace std;


class CAddrFactory
{
public:
    static shared_ptr<IAddr> createAddr(const IAddr::EAddrType, const uint16_t, const string inAddr = "");
};
