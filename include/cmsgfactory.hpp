#pragma once
#include <memory>

using namespace std;

class IMsgOut;

class CMsgFactory
{
public:
    CMsgFactory() = delete;
    static shared_ptr<IMsgOut> createMsg();
};
