#ifndef OBJECTFROMXML_HH
#define OBJECTFROMXML_HH

#include "Vector3D.hh"

typedef struct {
  std::string name;
  std::string value;
}attribute_str;

class ObjectFromXML {
public:
  std::string Name;
  Vector3D Shift; 
  Vector3D Scale; 
  Vector3D RotXYZ_deg; 
  Vector3D Trans_m; 
  Vector3D RGB; 

  ObjectFromXML() {
    Shift[0] = 0;      Shift[1] = 0;      Shift[2] = 0;
    Scale[0] = 1;      Scale[1] = 1;      Scale[2] = 1;
    RotXYZ_deg[0] = 0; RotXYZ_deg[1] = 0; RotXYZ_deg[2] = 0;
    Trans_m[0] = 0;    Trans_m[1] = 0;    Trans_m[2] = 0;
    RGB[0] = 128;      RGB[1] = 128;      RGB[2] = 128;
  };

  void print() {
    std::cout << "Name: "       << Name << std::endl;
    std::cout << "Shift: "      << Shift << std::endl;
    std::cout << "Scale: "      << Scale << std::endl;
    std::cout << "RotXYZ_deg: " << RotXYZ_deg << std::endl;
    std::cout << "Trans_m: "    << Trans_m << std::endl;
    std::cout << "RGB: "        << RGB << std::endl;
  };
};

#endif