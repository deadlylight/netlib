#pragma once
#include <memory>
#include <string>

using namespace std;

class IMux;

class CMuxFactory
{
public:
    static shared_ptr<IMux> createMux(const string &);
};
