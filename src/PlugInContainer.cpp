#include <iostream>
#include <cassert>
#include "AbstractInterp4Command.hh"
#include "PlugInContainer.hh"

using namespace std;

PlugInContainer::PlugInContainer() : Serial0Parallel1(false)
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

void threadExec(AbstractInterp4Command* cmd, AbstractScene& scene, ComChannel& channel)
{
  cout<<"Watek rozpoczyna prace" << endl;
  cmd->ExecCmd(scene, NULL, channel);   
}

int PlugInContainer::ExecInput(std::istream& StrWe, AbstractScene& scene, ComChannel& channel)
{  
  std::string cmd;
  while(StrWe.good()) {
    cmd.clear();
    StrWe >> cmd;

    if( cmd.empty() ) {
        break;
    }

    if( cmd == "Begin_Parallel_Actions" ) {
      std::cout << "Otrzymano komende pracy wielowatkowej" << std::endl;
      //Serial0Parallel1 = 1;
      continue;
    }
    else if( cmd == "End_Parallel_Actions" ) {
      std::cout << "Otrzymano komende pracy jednowatkowej" << std::endl;
      // for(std::thread& task : this->parralel_tasks) {
      //     task.join();
      // }
      // this->parralel_tasks.clear();
      // Serial0Parallel1 = 0;
      // std::cout << "Zakonczono prace wielowatkowa" << std::endl;

      continue;
    }

    if( this->mapa.count(cmd) == 0 ) {
      break;
    }   

    this->cmd_now = this->getCmd(cmd);

    if( this->cmd_now == nullptr ) {
      std::cerr << "!!! Nie udalo sie stworzyc komendy " << cmd << std::endl;
      return -1;
    }

    if( !this->cmd_now->ReadParams(StrWe) )  {
      std::cerr << "!!! Nie mozna odczytac parametrow komendy " << cmd << std::endl;
      return -2;
    }

    std::cout<<this->cmd_now->GetCmdName()<< " " << std::endl;

    if(Serial0Parallel1 == 0) {
      std::cout << "Rozpoczeto prace jednowatkowa" << std::endl;
      if(!this->cmd_now->ExecCmd(scene, NULL, channel)) {
        return -3;
      }
    }
    else {
      std::cout << "Rozpoczeto prace wielowatkowa" << std::endl;
      std::thread task(threadExec, this->cmd_now, std::ref(scene), std::ref(channel));
      this->parralel_tasks.push_back(std::move(task));
    }

  }

  return 0;
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
      if(value != nullptr) 
        if((*value).add_libHandler(plugin_name)) 
            return 1; // blad otwierania biblioteki
      return 0;
    }
  }
  std::cerr << "!!! Nieznane polecenie " << klucz <<  std::endl;
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
  cerr << "!!! getCmd: Nie znaleziono polecenia " << klucz << endl;
  return nullptr;
}

