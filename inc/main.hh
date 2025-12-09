#ifndef MAIN_HH__
#define MAIN_HH__

#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "PlugInContainer.hh"
#include "XML/xmlinterp.hh"
#include "klient/klientmain.hh"
#include "MobileObj.hh"
#include "ComInterface.hh"
#include "Scene.hh"


bool preprocessCmdFile(const char* argv);
bool openCommandFile(std::string sFileName);

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param XML_file_name - (\b we.) nazwa pliku XML z opisem poleceń.
 * \param bazaPluginow - (\b we.) zarządca wczytywanych bibliotek.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym wypadku
 */
bool openPluginsFromXML(PlugInContainer &bazaPluginow, Configuration &Config) {
  for( long unsigned int i = 0; i<Config.sLibNames.size(); i++){
    if(bazaPluginow.openPlugin(Config.sLibNames.at(i))) 
      return false;

    cout << " Otwarto bibliotekę " << Config.sLibNames.at(i) << endl;
  }
  cout << "Zakonczono otwieranie bibliotek" << endl;
  return true;
}

bool isFileType(const char* filetype, const std::string filename) {
  if(filename.substr(filename.length()-4).c_str() == filetype) 
      return true;
  return false;
}

bool checkArgs(int argc, char* args[]) {
  if (argc < 3) {
    std::cerr << "!!! Brak argumentow wywolania: .cmd albo .xml" << endl;
    return false;
  }

  if(isFileType(".cmd", args[1])) {
     cerr << "!!! Blad argumentow wywolania: " << args[1] << " nie jest .cmd" << endl;
     return false;
  }

  if(isFileType(".xml", args[2])) {
     cerr << "!!! Blad argumentow wywolania: " << args[2] << " nie jest .xml" << endl;
     return false;
  }

  return true;
}

#endif