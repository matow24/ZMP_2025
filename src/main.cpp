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
int openPluginsFromXML(PlugInContainer &bazaPluginow, const char* XML_file_name) {
  Configuration   Config;

  if (!ReadFile(XML_file_name, Config)) return 2;

  for( int i = 0; i<Config.sLibNames.size(); i++){
    if(bazaPluginow.openPlugin(Config.sLibNames.at(i))) 
      return 3;

    cout << " Otwarto bibliotekę " << Config.sLibNames.at(i) <<endl;
  }
  cout << "Zakonczono otwieranie bibliotek" <<endl;
  return 0;
}


int main (int argc, char* args[]) 
{
  // if (argc < 3) {
  //   std::cerr << "!!! Brak argumentow wywolania: .cmd albo .xml\n";
  //   return 1;
  // }

  // int preprocessCmd = preprocessCmdFile(&args[1]);
  // if(preprocessCmd) {
  //   cerr << "!!! Blad preprocesora .cmd" << endl;
  //   return preprocessCmd;
  // }

  PlugInContainer bazaPluginow;
  int openPluginsFromXML_result = openPluginsFromXML(bazaPluginow, "config/config.xml");
  if(openPluginsFromXML_result) return openPluginsFromXML_result;

  /************************* */
  
  AbstractInterp4Command *pSetCmd = bazaPluginow.getCmd("Move");
  if(pSetCmd==nullptr) {
    cerr << "!!! Blad: stworzona wtyczka jest pusta" << endl;
    return 4;
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
