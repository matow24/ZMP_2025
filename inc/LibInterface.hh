#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include "AbstractInterp4Command.hh"
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
    // std::string _cmdName; // do wyrzucenia po stworzeniu std::map ||klucz:std::string, LibInterface*||
    void *_libHandler;
    AbstractInterp4Command *(*_pCreate_Cmd)(void);

public:
    LibInterface();
    ~LibInterface();
    bool add_libHandler(std::string);
    bool createCmd();
};

#endif
