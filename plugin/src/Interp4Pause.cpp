#include <iostream>
#include "Interp4Pause.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause(): _Speed_mmS(0)
{}


/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _name << " " << _pause_time_ms << endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Pause::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  // speed = 0;
  // rotation_speed = 0;
  rScn.FindMobileObj(sMobObjName)->SetPosition_m(rScn.FindMobileObj(sMobObjName)->GetPosition_m());
  rScn.FindMobileObj(sMobObjName)->SetAng_Pitch_deg(rScn.FindMobileObj(sMobObjName)->GetAng_Pitch_deg());
  rScn.FindMobileObj(sMobObjName)->SetAng_Roll_deg(rScn.FindMobileObj(sMobObjName)->GetAng_Roll_deg());
  rScn.FindMobileObj(sMobObjName)->SetAng_Yaw_deg(rScn.FindMobileObj(sMobObjName)->GetAng_Yaw_deg());

  return true;
}


/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
