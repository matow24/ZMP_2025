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

  AbstractMobileObj* MobObj = rScn.FindMobileObj(this->_name.c_str());
  if( MobObj == nullptr )  {
      std::cerr << "Nie moge znalezc obiektu: " << this->_name.c_str() << std::endl;
      return false;
  }

  Vector3D init_pos = MobObj->GetPosition_m();
  double init_roll = MobObj->GetAng_Roll_deg();
  double init_pitch = MobObj->GetAng_Pitch_deg();
  double init_yaw = MobObj->GetAng_Yaw_deg();

  double delta_x_m=0, delta_y_m=0, delta_z_m=0;
  double dist_step_m = (double)_path_len /FPS;
  double time_step_us = (((double)_path_len/this->_speed_mmS)*1000000) /FPS;

    for(int i = 0; i < FPS; i++)  {
        MobObj->LockAccess();
  
        delta_x_m += dist_step_m * cos(init_pitch*M_PI/180)*cos(init_yaw*M_PI/180);
        delta_y_m += dist_step_m * (cos(init_roll*M_PI/180)*sin(init_yaw*M_PI/180) + cos(init_yaw*M_PI/180)*sin(init_pitch*M_PI/180)*sin(init_roll*M_PI/180));
        delta_z_m += dist_step_m * (sin(init_roll*M_PI/180)*sin(init_yaw*M_PI/180) - cos(init_roll*M_PI/180)*cos(init_yaw*M_PI/180)*sin(init_pitch*M_PI/180));
        MobObj->SetPosition_m(Vector3D(delta_x_m + init_pos[0], delta_y_m + init_pos[1], delta_z_m + init_pos[2]));

        if(!updateServer(MobObj, rComChann)) 
                return false;

        MobObj->UnlockAccess();
        usleep(time_step_us);
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
