#include <cmsgfactory.hpp>
#include "cmsgsimple.hpp"

shared_ptr<IMsgOut> CMsgFactory::createMsg()
{
    return make_shared<CMsgSimple>();
}
