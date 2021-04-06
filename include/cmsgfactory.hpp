#pragma once
#include <memory>

using namespace std;

class IMsgIn;

class CMsgFactory
{
public:
    CMsgFactory() = delete;
    static shared_ptr<IMsgIn> createMsg();
};
