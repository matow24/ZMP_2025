#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

typedef struct {
  std::string name;
  std::string value;
}attribute_t;

class Configuration {
public:
  char* name;
  char* value;
  ~Configuration() { if(name!=nullptr) delete name; if(value!=nullptr) delete value; }
};


#endif
