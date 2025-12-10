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

  int                 Socket4Sending;   
  if (!OpenConnection(Socket4Sending)) return 5;

  ComChannel ComCh;
  ComCh.Init(Socket4Sending);
  ComInterface ComFace(ComCh);
  Scene Scena;
  setUpScene(Scena, Config, ComFace);

  // Obsluga pliku .cmd
  std::string cmds_filename(args[1]);
  cmds_filename += ".pp";    // wynik po preprocesorze

  std::ifstream istr(cmds_filename);
  if (!istr) {
      std::cerr << "!!! Nie mozna otworzyc pliku wynikowego: " << cmds_filename << std::endl;
      return 6;
  }

  int execcode = bazaPluginow.ExecInput(istr, Scena, ComCh);

  ComFace.Close();
  if(execcode) return execcode;

  return 0;
}
