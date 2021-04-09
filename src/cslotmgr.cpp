#include "cslotmgr.hpp"
#include "cslotmgrimpl.hpp"

CSlotMgr::CSlotMgr(uint32_t inCount)
    : mImpl(new CSlotMgrImpl(inCount))
{
}

CSlotMgr::~CSlotMgr()
{
}

int32_t CSlotMgr::get()
{
    return mImpl->get();
}

void CSlotMgr::put(int32_t in)
{
    mImpl->put(in);
}
