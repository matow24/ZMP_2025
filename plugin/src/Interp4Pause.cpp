#include <iostream>
#include <unistd.h>
#include "Interp4Pause.hh"

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif


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
Interp4Pause::Interp4Pause(): _pause_time_ms(0)
{}


/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  cout << GetCmdName() << " " << _pause_time_ms << endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * zawieszenie wątku na _pause_time_ms
 */
bool Interp4Pause::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  rComChann.LockAccess();
  usleep(_pause_time_ms*1000);
  rComChann.UnlockAccess();

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
  Strm_CmdsList >> _pause_time_ms;
  return !Strm_CmdsList.fail();
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
  cout << "   Pause  CzasPauzy[ms]" << endl;
}
