#include "main.hh"

using namespace std;
using namespace xercesc;


int main (int argc, char* args[]) 
{
  if (!checkArgs(argc, args)) return 1;

  if (!preprocessCmdFile(args[1])) return 2;

  Configuration   Config;
  if (!ReadXMLFile(args[2], Config))   return 3;

  PlugInContainer bazaPluginow;
  if (!openPluginsFromXML(bazaPluginow, Config))  return 4;

  //otwórz połaczenie z serwerem
  int                 Socket4Sending;   
  if (!OpenConnection(Socket4Sending)) return 5;

  ComChannel ComCh;
  ComCh.Init(Socket4Sending);
  // cout << "Connected to socket " << ComCh.GetSocket() << endl;
  ComInterface ComFace(ComCh);
  Scene Scena;
  setUpScene(Scena, Config, ComFace);

  //if(!openCommandFile(args[1], cmds_filename)) return 6;

  std::string cmds_filename(args[1]);
  cmds_filename += ".pp";    // wynik po preprocesorze

  // Wczytanie przetworzonego pliku
  std::ifstream istr(cmds_filename);
  if (!istr) {
      std::cerr << "!!! Nie mozna otworzyc pliku wynikowego: " << cmds_filename << std::endl;
      return 6;
  }

  bazaPluginow.ExecInput(istr, Scena, ComCh);

  /************************* */
  
  // AbstractInterp4Command *pSetCmd = bazaPluginow.getCmd("Move");
  // if(pSetCmd==nullptr) {
  //   cerr << "!!! Blad: stworzona wtyczka jest pusta" << endl;
  //   return 6;
  // }
    
  // // exec zadane polecenia
  // cout << endl;
  // cout << pSetCmd->GetCmdName() << endl;
  // cout << endl;
  // pSetCmd->PrintSyntax();
  // cout << endl;
  // pSetCmd->PrintCmd();
  // cout << endl;
  // /*********/
  
  // delete pSetCmd;


  ComFace.Close();
}
