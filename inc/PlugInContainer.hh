#ifndef PLUGINCONTAINER_HH
#define PLUGINCONTAINER_HH

#include <map>
#include <memory>
#include <vector>
#include <list>
#include <thread>
#include "LibInterface.hh"
#include "ComChannel.hh"


class PlugInContainer
{
    std::map<std::string,LibInterface*> mapa;
    std::list<std::thread> parralel_tasks;
    AbstractInterp4Command* cmd_now;

    bool Serial0Parallel1;

public:
    PlugInContainer();
    ~PlugInContainer();
    bool openPlugin(std::string); 
    AbstractInterp4Command* getCmd(std::string); 

    int ExecInput(std::istream& StrWe, AbstractScene& scene, ComChannel& channel);
};

#endif