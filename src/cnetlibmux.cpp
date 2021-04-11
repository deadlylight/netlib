#include <cnetlibmux.hpp>
#include "cnetlibmuximpl.hpp"

CNetLibMux::CNetLibMux()
    : mImpl(new CNetLibMuxImpl(*this))
{
}

CNetLibMux::~CNetLibMux()
{
}

void CNetLibMux::run()
{
    mImpl->run();
}

CNetLibMux &CNetLibMux::getInstance()
{
    static CNetLibMux sMux;
    return sMux;
}
