#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "LibInterface.hh"

using namespace std;

PlugInContainer::PlugInContainer()
{
  // stworz mape (dodaj elementy/wtyczki, jak zwał)
  for (const auto& [key, value] : mapa)
        std::cout << '[' << key << "] = " << value << "; ";
}

PlugInContainer::~PlugInContainer()
{
  mapa.clear();
}

bool PlugInContainer::openLibInterface()
{
  // otrzymaj nazwe akcji
  // znajdz akcje na mapie po nazwie
  // otworz plugin (add_libHandler())
  // albo stworz komende (createCmd())
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
