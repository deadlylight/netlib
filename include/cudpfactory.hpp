#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IMux;
class ISyncUdp;
class IAsyncUdp;

class CUdpFactory
{
public:
    shared_ptr<ISyncUdp> createSyncUcp(shared_ptr<IMux>, uint16_t);
    bool registerAsyncUcp(shared_ptr<IMux>, shared_ptr<IAsyncUdp>);
};
