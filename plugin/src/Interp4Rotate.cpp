#include <iostream>
#include "Interp4Rotate.hh"


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

  int step_time_s; //co ile s wysylany jest update pozycji
  if(_axis == "X") {
    int init_rot_deg = rScn.FindMobileObj(sMobObjName)->GetAng_Roll_deg();
    if(_rot_speed_degS < 0) _rot_deg *= (-1);

    while(rScn.FindMobileObj(sMobObjName)->GetAng_Roll_deg() != init_rot_deg + _rot_deg) {
      rScn.FindMobileObj(sMobObjName)->SetAng_Roll_deg(init_rot_deg + _rot_speed_degS*step_time_s);
    }
  }
  else if(_axis == "Y"){
    rScn.FindMobileObj(sMobObjName)->SetAng_Pitch_deg(_rot_speed_degS);

  }
  else if(_axis == "Z") {
    rScn.FindMobileObj(sMobObjName)->SetAng_Yaw_deg(_rot_speed_degS);

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
