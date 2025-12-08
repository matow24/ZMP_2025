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
  cout << "Connected to socket " << ComCh.GetSocket() << endl;

  ComInterface ComFace(ComCh);
  ComFace.Clear();

  // wyczyść scenę i wstaw tam obiekty z XMLa

  //std::vector<MobileObj> Objects;
  // Utwórz MobileObj dla każdego obiektu zczytanego z XMLa
  for(const auto& obj : Config.objects) {
    MobileObj obiekt;
    obiekt.SetName(obj.Name.c_str());
    obiekt.SetPosition_m(obj.Trans_m);
    obiekt.SetRotation_deg(obj.RotXYZ_deg);

    if(ComFace.AddObj(obj.Name, obj.Shift, obj.Scale, obj.Trans_m, obj.RotXYZ_deg, obj.RGB)) {
      cout << "Dodano obiekt " << obj.Name <<endl;
    }


    //p_p = obiekt.GetAng_Roll_deg()*obiekt.GetAng_Pitch_deg()*obiekt.GetAng_Yaw_deg()*(obj.Scale*( p +obj.Shift)) + obj.Trans_m;

    //Config.objects.at(i);

    //Objects.push_back(obiekt);
  }

  //if(!openCommandFile(args[1])) return 6;

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


  
}
