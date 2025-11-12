#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "PlugInContainer.hh"
#include "xmlinterp.hh"

using namespace std;
using namespace xercesc;


int main (int argc, char* args[]) 
{
  PlugInContainer bazaPluginow;
  bazaPluginow.openPlugin("Set");
  bazaPluginow.openPlugin("Move");
  bazaPluginow.openPlugin("Rotate");
  bazaPluginow.openPlugin("Pause");
  
  AbstractInterp4Command *pSetCmd = bazaPluginow.getCmd("Set");
  if(pSetCmd==nullptr) 
    return 1;

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


  /***** Etap 2 *****/
  Configuration   Config;

  if (!ReadFile("config/config.xml",Config)) return 1;
}
