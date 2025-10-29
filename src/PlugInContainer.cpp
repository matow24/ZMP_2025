#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"

using namespace std;

LibInterface::LibInterface(): _cmdName("") {}

LibInterface::~LibInterface()
{
  if(_libHandler != nullptr) dlclose(_libHandler);
  //if(_pCreate_Cmd != nullptr) delete(_pCreate_Cmd);
}

bool LibInterface::add_libHandler()
{
  std::string libName = "Interp4" + _cmdName + ".so"; 
  _libHandler = dlopen(libName.c_str(), RTLD_LAZY);
  
  if (!_libHandler) {
    cerr << "!!! Brak biblioteki: " << libName.c_str() << endl;
    return 1;
  }

  return 0;
}

bool LibInterface::createCmd(){
  void* pFun;
  pFun = dlsym(_libHandler,"CreateCmd");

  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }

  _pCreate_Cmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);
  
  /************/
  AbstractInterp4Command *pCmd = _pCreate_Cmd();

  if(_cmdName != pCmd->GetCmdName()) {
    cerr << "!!! Nazwa stworzonej funkcji nie odpowiada oryginalnej" << endl;
    return 1;
  }
    
  return 0;
}

PlugInContainer::PlugInContainer()
{
  for (const auto& [key, value] : mapa)
        std::cout << '[' << key << "] = " << value << "; ";
}

PlugInContainer::~PlugInContainer()
{
  mapa.clear();
}

int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
  //void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
  //void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  AbstractInterp4Command *(*pCreateCmd_Pause)(void);
  //AbstractInterp4Command *(*pCreateCmd_Set)(void);
  //AbstractInterp4Command *(*pCreateCmd_Rotate)(void);
  void *pFun;
  void *pFunP;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: libInterp4Move.so" << endl;
    return 1;
  }
  if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: libInterp4Pause.so" << endl;
    return 1;
  }
  /*
  if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: libInterp4Set.so" << endl;
    return 1;
  }
  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: libInterp4Rotate.so" << endl;
    return 1;
  }
  */


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);

  /*****************************/
  pFunP = dlsym(pLibHnd_Pause,"CreateCmd");
  if (!pFunP) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Pause = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFunP);

  AbstractInterp4Command *pCmdP = pCreateCmd_Pause();

  cout << endl;
  cout << pCmdP->GetCmdName() << endl;
  cout << endl;
  pCmdP->PrintSyntax();
  cout << endl;
  pCmdP->PrintCmd();
  cout << endl;
  
  delete pCmdP;

  dlclose(pLibHnd_Pause);
}
