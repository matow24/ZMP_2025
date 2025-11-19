#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "PlugInContainer.hh"

using namespace std;

PlugInContainer::PlugInContainer()
{
  mapa["libInterp4Set.so"] = new LibInterface;
  mapa["libInterp4Move.so"] = new LibInterface;
  mapa["libInterp4Rotate.so"] = new LibInterface;
  mapa["libInterp4Pause.so"] = new LibInterface;
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
bool PlugInContainer::openPlugin(std::string plugin_name)
{
  // nazwa biblioteki: libInterp4XXXXX.so
  // zostawiamy XXXXX
  // std::string klucz = plugin_name.substr(10);
  // for(int i=0; i<3; i++) klucz.pop_back();

  for (const auto& [key, value] : mapa){
    if(plugin_name == key){
      if((*value).add_libHandler(plugin_name)) return 1; // blad otwierania biblioteki
      return 0;
    }
  }
  std::cerr << "!!! Nie znaleziono biblioteki " << plugin_name <<  std::endl;
  return 1;
}

AbstractInterp4Command* PlugInContainer::getCmd(std::string klucz)
{
  for (const auto& [key, value] : mapa){
    if(klucz == key){
      if(value != nullptr) 
          return (*value).get_pCreate_Cmd();
      else break;
    }
  }
  return nullptr;
}

