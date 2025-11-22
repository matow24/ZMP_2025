#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "PlugInContainer.hh"
#include "xmlinterp.hh"

using namespace std;
using namespace xercesc;

int preprocessCmdFile(char** argv);

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param XML_file_name - (\b we.) nazwa pliku XML z opisem poleceń.
 * \param bazaPluginow - (\b we.) zarządca wczytywanych bibliotek.
 * \retval 0 - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval 2 - błąd czytania pliku XML.
 * \retval 3 - błąd otwierania biblioteki.
 */
bool openPluginsFromXML(PlugInContainer &bazaPluginow, Configuration &Config) {
  for( int i = 0; i<Config.sLibNames.size(); i++){
    if(bazaPluginow.openPlugin(Config.sLibNames.at(i))) 
      return false;

    cout << " Otwarto bibliotekę " << Config.sLibNames.at(i) << endl;
  }
  cout << "Zakonczono otwieranie bibliotek" << endl;
  return true;
}

bool isFileType(const char* filetype, const std::string filename) {
  if(filename.substr(filename.length()-3) == filetype) 
      return true;
  return false;
}

bool checkArgs(int argc, char* args[]) {
  if (argc < 3) {
    std::cerr << "!!! Brak argumentow wywolania: .cmd albo .xml\n";
    return false;
  }

  if(isFileType("cmd", args[1])) {
     cerr << "!!! Blad argumentow wywolania: pierwszy plik nie jest .cmd" << endl;
     return false;
  }

  if(isFileType("xml", args[2])) {
     cerr << "!!! Blad argumentow wywolania: drugi plik nie jest .xml" << endl;
     return false;
  }

  return true;
}


int main (int argc, char* args[]) 
{
  // if(!checkArgs(argc, args)) return 1;

  // int preprocessCmd = preprocessCmdFile(&args[1]);
  // if(preprocessCmd) {
  //   cerr << "!!! Blad preprocesora .cmd" << endl;
  //   return preprocessCmd;
  // }

  Configuration   Config;
  if (!ReadFile("config/config.xml", Config))  return 4;
  // if (!ReadFile(args[2], Config))   return 2;

  PlugInContainer bazaPluginow;
  if(!openPluginsFromXML(bazaPluginow, Config)) return 5;

  /************************* */
  
  AbstractInterp4Command *pSetCmd = bazaPluginow.getCmd("Move");
  if(pSetCmd==nullptr) {
    cerr << "!!! Blad: stworzona wtyczka jest pusta" << endl;
    return 6;
  }
    
  // exec zadane polecenia
  cout << endl;
  cout << pSetCmd->GetCmdName() << endl;
  cout << endl;
  pSetCmd->PrintSyntax();
  cout << endl;
  pSetCmd->PrintCmd();
  cout << endl;
  /*********/
  
  delete pSetCmd;


  
}
