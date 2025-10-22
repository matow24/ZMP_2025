#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include "AbstractInterp4Command.hh"

/*!
 * \file
 * \brief Deklaracja instacji szablonu ...
 */

/*!
 * \brief Instacja szablonu ...
 */
class LibInterface
{
    std::string _cmdName; // do wyrzucenia po stworzeniu std::map ||klucz:std::string, LibInterface*||
    void *_libHandler;
    AbstractInterp4Command *(*_pCreate_Cmd)(void);

public:
    ~LibInterface();
    bool add_libHandler();
    bool createCmd();
};

class PlugInContainer
{
    // mapa - czymkolwiek jest (klucze, słownik?)
    // w ramach klasy otwieranie bilbiotek

    LibInterface lib_interface;
public:
    PlugInContainer();
};

/*
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: libInterp4Move.so" << endl;
    return 1;
  }
  Fun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

  AbstractInterp4Command *pCmd = pCreateCmd_Move();
  
  delete pCmd;

  dlclose(pLibHnd_Move);
  */

#endif
