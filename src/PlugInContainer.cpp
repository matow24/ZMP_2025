#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "PlugInContainer.hh"

using namespace std;

PlugInContainer::PlugInContainer()
{
  mapa["Set"] = nullptr;
  mapa["Move"] = nullptr;
  mapa["Rotate"] = nullptr;
  mapa["Pause"] = nullptr;
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
  std::string klucz = plugin_name.substr(10);
  for(int i=0; i<3; i++) klucz.pop_back();

  for (const auto& [key, value] : mapa){
    if(klucz == key){
      if(value == nullptr) mapa[klucz] = new LibInterface;
      if(value != nullptr) if((*value).add_libHandler(plugin_name)) return 1; // blad otwierania biblioteki
      return 0;
    }
  }
  std::cerr << "!!! Nie znaleziono polecenia " << klucz <<  std::endl;
  // sprawdź czy taka biblioteka istnieje i dodaj do mapy
  // ...
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

