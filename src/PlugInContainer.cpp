#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "PlugInContainer.hh"

using namespace std;

PlugInContainer::PlugInContainer()
{
  mapa["Set"] = new LibInterface;
  mapa["Move"] = new LibInterface;
  mapa["Rotate"] = new LibInterface;
  mapa["Pause"] = new LibInterface;
}

PlugInContainer::~PlugInContainer()
{
  for (const auto& [key, value] : mapa){
    if(value!=nullptr) delete(value);
  }
  mapa.clear();
}

/*!
  * \brief Otwiera wybrany plugin.
  *
  * Znajduje LibInterface po kluczu i otwiera bibliotekę
  * \param[in] klucz - nazwa komendy.
  * \retval true - operacja nie powiodła się,
  * \retval false - w przypadku przeciwnym.
  */
bool PlugInContainer::openPlugin(std::string klucz)
{
  for (const auto& [key, value] : mapa){
    if(klucz == key){
      if((*value).add_libHandler(klucz)) return 1; // blad otwierania biblioteki
      return 0;
    }
  }
  std::cerr << "!!! Nie znaleziono polecenia " << klucz <<  std::endl;
  return 1;
}

AbstractInterp4Command* PlugInContainer::getCmd(std::string klucz)
{
  for (const auto& [key, value] : mapa){
    if(klucz == key){
      return (*value).get_pCreate_Cmd();
    }
  }
  return nullptr;
}

