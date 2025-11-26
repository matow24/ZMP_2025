#ifndef SCENE_HH__
#define SCENE_HH__

#include <vector>
#include "AccessControl.hh"
#include "GeomObj.hh"




/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 1
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj1[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,23)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,26)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,29)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,32)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,35)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,38)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,41)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,44)\n"  
 };


/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 2
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj2[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-48,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-45,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-42,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-39,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-36,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-33,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-30,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-27,0)\n"
 };

/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 3
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj3[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-48,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-51,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-54,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-57,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-60,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-63,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-66,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-69,0)\n"
 };



/*!
 * \brief Namiastka sceny z prostą kolekcją trzech wizualizowanych obiektów.
 */
class Scene: public AccessControl {
  public:
    Scene(): _Container4Objects(3)
    {
      _Container4Objects[0].SetCmds(Cmds4Obj1);
      _Container4Objects[1].SetCmds(Cmds4Obj2);
      _Container4Objects[2].SetCmds(Cmds4Obj3);
    }
  
  /*!
   * \brief Prosta kolekcja obiektów sceny
   */
   std::vector<GeomObject>   _Container4Objects;
};

#endif