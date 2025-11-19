#include "LibInterface.hh"

using namespace std;

LibInterface::LibInterface() { 
  _libHandler = nullptr;
  cerr << "!!! Tworzenie obiektu LibInterface!!! ==============" << endl;
 }

LibInterface::~LibInterface()
{
  if(_libHandler != nullptr) {
    cerr << "!!! Zamkniecie wtyczki!!! ____ poczatek _____________" << endl;
    dlclose(_libHandler);
    cerr << "!!! Zamkniecie wtyczki!!! _____ koniec_______________" << endl;
  }
}

bool LibInterface::add_libHandler(std::string cmdName)
{
  _libHandler = dlopen(cmdName.c_str(), RTLD_LAZY);
  
  if (!_libHandler) {
    cerr << "!!! Brak biblioteki: " << cmdName.c_str() << endl;
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

  return 0;
}

AbstractInterp4Command* LibInterface::get_pCreate_Cmd()
{
  if(createCmd()) {
    cerr << "Blad tworzenie komendy " <<endl;
    return nullptr;
  }
   
  return _pCreate_Cmd();
}