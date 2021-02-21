#pragma once
#include <itcpqueue.hpp>
#include "tqueue.hpp"

class ITcpConnection;

class CTcpConnectionQueue : public TQueue<ITcpConnectionQueue, ITcpConnection>
{
};
