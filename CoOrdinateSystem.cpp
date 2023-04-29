#include "CoOrdinateSystem.hpp"

CoOrdinateSystem *CoOrdinateSystem::pointer_to_instance;

CoOrdinateSystem::CoOrdinateSystem(int localx, int localy)
{
    this->localx = localx;
    this->localy = localy;
}

CoOrdinateSystem *CoOrdinateSystem::getInstance(int localx, int localy)
{
    if (pointer_to_instance == nullptr)
    {
        pointer_to_instance = new CoOrdinateSystem(localx, localy);
        return pointer_to_instance;
    }
    else
    {
        return pointer_to_instance;
    }
}

int CoOrdinateSystem::setGlobalCoOrdinatex(int globalx)
{
    return globalx - this->localx;
}
int CoOrdinateSystem::setGlobalCoOrdinatey(int globaly)
{
    return globaly - this->localy;
}
