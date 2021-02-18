#include "cmuxfactoryimpl.hpp"

CMuxFactoryImpl::CMuxFactoryImpl(const string &inName)
: mName(inName)
{
    registerMuxFactory(this);
}

vector<CMuxFactoryImpl *> &CMuxFactoryImpl::getMuxFactoryList()
{
    static vector<CMuxFactoryImpl *> sMuxFactoryImplList;
    return sMuxFactoryImplList;
}

void CMuxFactoryImpl::registerMuxFactory(CMuxFactoryImpl *inMuxFactoryImpl)
{
    getMuxFactoryList().push_back(inMuxFactoryImpl);
}

shared_ptr<IMux> CMuxFactoryImpl::createMux(const string &inName)
{
    for (auto &vMuxFactoryImpl : getMuxFactoryList())
    {
        if (vMuxFactoryImpl->mName == inName)
        {
            return vMuxFactoryImpl->createMux();
        }
    }
    return nullptr;
}
