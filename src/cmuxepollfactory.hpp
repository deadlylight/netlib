#include "cmuxfactoryimpl.hpp"

class CMuxEpollFactory : public CMuxFactoryImpl
{
public:
    CMuxEpollFactory();
    shared_ptr<IMux> createMux() override;
};
