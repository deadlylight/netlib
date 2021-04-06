#pragma once
#include <memory>

using namespace std;

class IMux;

class CMuxFactory
{
public:
    static shared_ptr<IMux> createMux();
};
