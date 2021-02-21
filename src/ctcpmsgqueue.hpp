#pragma once
#include <itcpqueue.hpp>
#include "tqueue.hpp"

class CTcpMsgQueue : public TQueue<ITcpMsgQueue, ITcpMsg>
{
};
