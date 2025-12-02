#include <iostream>
#include "Interp4Move.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _speed_mmS(0), _path_len(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " " << _name << " " << _speed_mmS << " " << _path_len << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  if(_path_len < 0) {
    std::cerr << "!!! " << _name << ": droga nie moze byc ujemna" << std::endl;
    return false;
  }

  Vector3D init_pos = rScn.FindMobileObj(sMobObjName)->GetPosition_m();
  int step_time_s;
  
  while((rScn.FindMobileObj(sMobObjName)->GetPosition_m() - init_pos).Length() != _path_len) {
    Vector3D new_Position = rScn.FindMobileObj(sMobObjName)->GetPosition_m();
    new_Position[0] += (_speed_mmS/1000.0*step_time_s); //przesun X+

    rScn.FindMobileObj(sMobObjName)->SetPosition_m(new_Position);
  }
  
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */

  Strm_CmdsList >> _name >> _speed_mmS >> _path_len;
  return Strm_CmdsList.fail();
}


/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
