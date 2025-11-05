#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "PlugInContainer.hh"

using namespace std;


int main()
{
  PlugInContainer bazaPluginow;
  bazaPluginow.openPlugin("Set");
  bazaPluginow.openPlugin("Move");
  bazaPluginow.openPlugin("Rotate");
  bazaPluginow.openPlugin("Pause");
  
  AbstractInterp4Command *pSetCmd = bazaPluginow.getCmd("Set");

  if(pSetCmd!=nullptr){
    // exec zadane polecenia
    cout << endl;
    cout << pSetCmd->GetCmdName() << endl;
    cout << endl;
    pSetCmd->PrintSyntax();
    cout << endl;
    pSetCmd->PrintCmd();
    cout << endl;
    /*********/
    
    delete pSetCmd;
  }
}
