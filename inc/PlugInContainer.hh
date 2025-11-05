#ifndef PLUGINCONTAINER_HH
#define PLUGINCONTAINER_HH

#include <map>
#include <memory>
#include <vector>
#include "LibInterface.hh"

class PlugInContainer
{
    std::map<std::string,LibInterface*> mapa;

public:
    PlugInContainer();
    ~PlugInContainer();
    bool openPlugin(std::string); 
    AbstractInterp4Command* getCmd(std::string); 
};

#endif