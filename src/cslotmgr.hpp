#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class CSlotMgrImpl;

class CSlotMgr
{
private:
    unique_ptr<CSlotMgrImpl> mImpl;

public:
    CSlotMgr(uint32_t);
    int32_t get();
    void put(int32_t);
};
