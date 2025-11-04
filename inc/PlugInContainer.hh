#ifndef PLUGINCONTAINER_HH
#define PLUGINCONTAINER_HH

#include <map>
#include <memory>
#include "LibInterface.hh"

class PlugInContainer
{
    // mapa: {polecenie, pointer}
    std::shared_ptr<LibInterface> sp_SetInterface = std::make_shared<LibInterface>();
    std::shared_ptr<LibInterface> sp_MoveInterface = std::make_shared<LibInterface>();
    std::shared_ptr<LibInterface> sp_RotateInterface = std::make_shared<LibInterface>();
    std::shared_ptr<LibInterface> sp_PauseInterface = std::make_shared<LibInterface>();

    std::map<std::string,std::shared_ptr<LibInterface>> mapa{ {"Set", sp_SetInterface}, {"Move", sp_MoveInterface}, {"Rotate", sp_RotateInterface}, {"Pause", sp_PauseInterface}};

public:
    PlugInContainer();
    ~PlugInContainer();
    bool openPlugin(std::string); //idk?
    //bool lugin(std::string); //idk?
};

#endif