#pragma once
#include <memory>
#include <string>

using namespace std;

class CNetLibMuxImpl;

class CNetLibMux
{
private:
    unique_ptr<CNetLibMuxImpl> mImpl;
    CNetLibMux();

public:
    ~CNetLibMux();

    void run();
    static CNetLibMux &getInstance();
};
