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

#endif
