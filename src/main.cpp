#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "PlugInContainer.hh"
#include "xmlinterp.hh"

using namespace std;
using namespace xercesc;


int main (int argc, char* args[]) 
{
  /***** Etap 2 *****/
  Configuration   Config;

  if (!ReadFile("config/config.xml",Config)) return 1;

  /***** Etap 1 *****/
  PlugInContainer bazaPluginow;

  for( int i = 0; i<Config.sLibNames.size(); i++){
    if(bazaPluginow.openPlugin(Config.sLibNames.at(i))) 
      return 1;

    cout << "Otwarto bibliotekę " << Config.sLibNames.at(i) <<endl;
  }
  cout << " Zakonczono otwieranie bibliotek" <<endl;
  
  AbstractInterp4Command *pSetCmd = bazaPluginow.getCmd("libInterp4Set.so");
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


  
}
