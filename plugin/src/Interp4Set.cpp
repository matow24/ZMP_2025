#include <iostream>
#include "Interp4Set.hh"
#include "ComInterface.hh"

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}

bool updateScene(AbstractMobileObj* MobObj, AbstractComChannel &rComChan)
{
    ComInterface interface(rComChan);

    Vector3D objPos(MobObj->GetAng_Roll_deg(), MobObj->GetAng_Pitch_deg(), MobObj->GetAng_Yaw_deg());

    if(!interface.UpdateObj(MobObj->GetName(), MobObj->GetPosition_m(), objPos)) {

        std::cerr << "Nie udalo sie zaktualizowac obiektu: "<< MobObj->GetName() <<std::endl;
        MobObj->UnlockAccess();

        return false;
    }
    return true;
}


/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _name(""), _init_x(0), _init_y(0), _init_z(0), _init_roll(0), _init_pitch(0), _init_yaw(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _name<< " " << _init_x << " " << _init_y << " " << _init_z 
                            << " " << _init_roll << " " << _init_pitch << " " << _init_yaw << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  if(_name == ""){
    std::cerr << "!!! Obiekt nie ma nazwy" << std::endl;
    return false;
  }

  AbstractMobileObj* MobObj= rScn.FindMobileObj(_name.c_str());
  
  if(MobObj == nullptr){
    std::cerr << "!!! Nie moge znalezc obiektu: " << this->_name.c_str() << std::endl;
    return false;
  }
  Vector3D Vinit_location(_init_x, _init_y, _init_z);

  MobObj->LockAccess();

  MobObj->SetName(_name.c_str());
  MobObj->SetPosition_m(Vinit_location);
  MobObj->SetAng_Roll_deg(_init_roll);
  MobObj->SetAng_Pitch_deg(_init_pitch);
  MobObj->SetAng_Yaw_deg(_init_yaw);

  if(!updateScene(MobObj, rComChann)) 
          return false;
          
  MobObj->UnlockAccess();
  
  return true;
}

void Interp4Set::PrintParams() const
{
  std:cout << _name<< " " << _init_x << " " << _init_y << " " << _init_z 
            << " " << _init_roll << " " << _init_pitch << " " << _init_yaw << endl;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  // Strm_CmdsList >> _name >> _init_x >> _init_y >> _init_z >> _init_roll >> _init_pitch >> _init_yaw;
  // return !Strm_CmdsList.fail();

  std::string linia;
  std::getline(Strm_CmdsList, linia);

  if (!linia.empty() && linia.back() == '\r')
      linia.pop_back();

  std::istringstream iss(linia);
  iss >> _name >> _init_x >> _init_y >> _init_z
      >> _init_roll >> _init_pitch >> _init_yaw;

  return !iss.fail();
}


/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu   X    Y    Z   Roll  Pitch  Yaw" << endl;
}
