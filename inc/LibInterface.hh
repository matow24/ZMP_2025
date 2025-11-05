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
    void *_libHandler;
    AbstractInterp4Command *(*_pCreate_Cmd)(void);

    bool createCmd();

public:
    LibInterface();
    ~LibInterface();
    bool add_libHandler(std::string);
    AbstractInterp4Command* get_pCreate_Cmd();
};

#endif
