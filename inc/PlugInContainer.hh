#ifndef PLUGINCONTAINER_HH
#define PLUGINCONTAINER_HH

#include <map>
#include <memory>
#include <vector>
#include "LibInterface.hh"

class PlugInContainer
{
    // mapa: {polecenie, pointer}
    /*std::shared_ptr<LibInterface> sp_SetInterface = std::make_shared<LibInterface>();
    std::shared_ptr<LibInterface> sp_MoveInterface = std::make_shared<LibInterface>();
    std::shared_ptr<LibInterface> sp_RotateInterface = std::make_shared<LibInterface>();
    std::shared_ptr<LibInterface> sp_PauseInterface = std::make_shared<LibInterface>();*/
    //std::map<std::string,std::shared_ptr<LibInterface>> mapa{ {"Set", sp_SetInterface}, {"Move", sp_MoveInterface}, {"Rotate", sp_RotateInterface}, {"Pause", sp_PauseInterface}};
    // LibInterface* pSetInterface;
    // LibInterface* pMoveInterface;
    // LibInterface* pRotateInterface;
    // LibInterface* pPauseInterface;
    //std::vector<LibInterface> vInterfaces;
    std::map<std::string,LibInterface*> mapa;

public:
    PlugInContainer();
    ~PlugInContainer();
    bool openPlugin(std::string); 
    AbstractInterp4Command* getCmd(std::string); 
};

#endif