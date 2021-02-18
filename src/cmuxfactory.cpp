#include <cmuxfactory.hpp>
#include "cmuxfactoryimpl.hpp"

shared_ptr<IMux> CMuxFactory::createMux(const string &inMuxType)
{
    return CMuxFactoryImpl::createMux(inMuxType);
}
