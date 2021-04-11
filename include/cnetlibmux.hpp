#pragma once
#include <memory>
#include <string>

using namespace std;

class CNetLibMux
{
    friend class CNetLibMuxImpl;

private:
    CNetLibMux();

public:
    ~CNetLibMux();
    void run();
    static CNetLibMux &getInstance();
};
