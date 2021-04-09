#include <cmuxfactory.hpp>
#include "cmux.hpp"

shared_ptr<IMux> CMuxFactory::createMux()
{
    return make_shared<CMux>();
}
