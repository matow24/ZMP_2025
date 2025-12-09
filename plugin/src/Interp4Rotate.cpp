#include <iostream>
#include "Interp4Rotate.hh"
#include "ComInterface.hh"

using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _axis(""), _rot_speed_degS(0), _rot_deg(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << _name<< " " << _axis << " " << _rot_speed_degS << " " << _rot_deg << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  if(_rot_deg < 0) {
    std::cerr << "!!! " << _name << ": kat obrotu nie moze byc ujemny. Aby zrobic obrot w prawo, zadaj ujemna predkosc katowa" <<std::endl;
    return false;
  }

  AbstractMobileObj* MobObj = rScn.FindMobileObj(this->_name.c_str());

  if( MobObj == nullptr )  {
      std::cerr << "Nie moge znalezc obiektu: " << this->_name.c_str() << std::endl;
      return false;
  }

  double delta_deg = 0;
  double dist_step_deg = (double)_rot_deg /FPS;
  double time_step_us = (abs( ((double)this->_rot_deg / this->_rot_speed_degS) )*1000000) /FPS;

  if(_axis == "OX") {
    double init_rot_deg = MobObj->GetAng_Roll_deg();

    for(int i = 0; i < FPS; i++)    {
      delta_deg += dist_step_deg;

      MobObj->LockAccess();
      
      MobObj->SetAng_Roll_deg(init_rot_deg + delta_deg);
      if(!updateServer(MobObj, rComChann)) 
        return false;

      MobObj->UnlockAccess();

      usleep(time_step_us);
    }
  }
  else if(_axis == "OY"){
    double init_rot_deg = MobObj->GetAng_Pitch_deg();

    for(int i = 0; i < FPS; i++)    {
      delta_deg += dist_step_deg;

      MobObj->LockAccess();
      
      MobObj->SetAng_Pitch_deg(init_rot_deg + delta_deg);
      if(!updateServer(MobObj, rComChann)) 
        return false;

      MobObj->UnlockAccess();

      usleep(time_step_us);
    }

  }
  else if(_axis == "OZ") {
    double init_rot_deg = MobObj->GetAng_Yaw_deg();

    for(int i = 0; i < FPS; i++)    {
      delta_deg += dist_step_deg;

      MobObj->LockAccess();
      
      MobObj->SetAng_Yaw_deg(init_rot_deg + delta_deg);
      if(!updateServer(MobObj, rComChann)) 
        return false;

      MobObj->UnlockAccess();

      usleep(time_step_us);
    }

  }
  else {
    std::cerr << "!!! " << _name << ": nie ma takiej osi: " <<_axis << ", nie wykonano obrotu " <<std::endl;
    return false;
  }

  
  return true;
}


/*!
 * Strm_CmdsList.fail() - true w przypadku błędu
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _name >> _axis >> _rot_speed_degS >> _rot_deg;
  return Strm_CmdsList.fail();
}


/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  OsObrotu  PredkoscObrotu[deg/s]  KatObrotu[deg]" << endl;
}
