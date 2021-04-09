#pragma once
#include <memory>

using namespace std;

class IMux;

class CMuxFactory
{
public:
    CMuxFactory() = delete;
    static shared_ptr<IMux> createMux();
};
