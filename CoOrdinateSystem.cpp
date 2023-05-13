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
    // Convert the global x-coordinate to local x-coordinate
    return globalx - this->localx;
}

int CoOrdinateSystem::setGlobalCoOrdinatey(int globaly)
{
    // Convert the global y-coordinate to local y-coordinate
    return globaly - this->localy;
}

CoOrdinateSystem::~CoOrdinateSystem()
{
    delete pointer_to_instance;
    pointer_to_instance = nullptr;
}
