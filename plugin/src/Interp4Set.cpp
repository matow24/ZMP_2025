#include <iostream>
#include "Interp4Set.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
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
  rScn.FindMobileObj(sMobObjName)->SetName(_name.c_str());

  Vector3D Vinit_location;
  Vinit_location[0] = _init_x;
  Vinit_location[1] = _init_y;
  Vinit_location[2] = _init_z;
  rScn.FindMobileObj(sMobObjName)->SetPosition_m(Vinit_location);

  rScn.FindMobileObj(sMobObjName)->SetAng_Roll_deg(_init_roll);
  rScn.FindMobileObj(sMobObjName)->SetAng_Pitch_deg(_init_pitch);
  rScn.FindMobileObj(sMobObjName)->SetAng_Yaw_deg(_init_yaw);
  
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
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
