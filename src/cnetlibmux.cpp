#include <cnetlibmux.hpp>
#include "cnetlibmuximpl.hpp"

CNetLibMux::CNetLibMux()
{
}

CNetLibMux::~CNetLibMux()
{
}

void CNetLibMux::run()
{
    return CNetLibMuxImpl::getInstance().run();
}

CNetLibMux &CNetLibMux::getInstance()
{
    return *(CNetLibMuxImpl::getInstance().mMux);
}
