#include "LibInterface.hh"

using namespace std;

LibInterface::LibInterface(): _cmdName("") {}

LibInterface::~LibInterface()
{
  if(_libHandler != nullptr) dlclose(_libHandler);
}

bool LibInterface::add_libHandler(std::string cmdName)
{
  std::string libName = "Interp4" + cmdName + ".so"; 
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

  /*if(_cmdName != pCmd->GetCmdName()) {
    cerr << "!!! Nazwa stworzonej funkcji nie odpowiada oryginalnej" << endl;
    return 1;
  }*/
    
  return 0;
}