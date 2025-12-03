#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "ObjectFromXML.hh"
#include <vector>
#include <sstream>


class Configuration {
public:
  std::vector<ObjectFromXML> objects;
  std::vector<std::string> sLibNames;
};


std::string AddObj(const std::string& Name, const Vector3D& Shift, const Vector3D& Scale, const Vector3D& Trans_m, const Vector3D& RotXYZ_deg, const Vector3D& RGB) {
  std::ostringstream ostr;

  ostr << "AddObj Name=" << Name << " Shift=" << Shift << " Scale=" << Scale << " Trans_m=" << Trans_m << " RGB=" << RGB << " RotXYZ_deg=" << RotXYZ_deg << std::endl;
  return ostr.str();
}

std::string UpdateObj(const std::string& Name, const Vector3D& Trans_m, const Vector3D& RotXYZ_deg) {
  std::ostringstream ostr;

  ostr << "UpdateObj Name=" << Name << " Trans_m=" << Trans_m << " RotXYZ_deg=" << RotXYZ_deg << std::endl;
  return ostr.str();
}

#endif
