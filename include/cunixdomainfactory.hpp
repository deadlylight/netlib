#pragma once
#include <memory>
#include <string>

using namespace std;

class INetStreamAccepter;
class INetStreamReader;

class CUnixDomainFactory
{
public:
    CUDFactory() = delete;
    bool createUnixDomainServer(shared_ptr<INetStreamAccepter>,
                                string);

    bool createUnixDomainConn(shared_ptr<INetStreamReader>,
                              string);
};
