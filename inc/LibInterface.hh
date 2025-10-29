#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include "AbstractInterp4Command.hh"
#include <map>
#include <memory>
#include <dlfcn.h>


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
    LibInterface();
    ~LibInterface();
    bool add_libHandler();
    bool createCmd();
};

class PlugInContainer
{
    // mapa - czymkolwiek jest (klucze, słownik?)
    // w ramach klasy otwieranie bilbiotek
    std::map<std::string,std::shared_ptr<LibInterface>> mapa{ {"Set", }, {"Move", }, {"Rotate", }, {"Pause", }};

public:
    PlugInContainer();
    ~PlugInContainer();
    bool openLibInterface();
    bool openPlugin(std::string); //idk?
};

#endif
