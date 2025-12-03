#include "ComInterface.hh"

std::string ComInterface::getCommand_AddObj(const std::string& Name, const Vector3D& Shift, const Vector3D& Scale, const Vector3D& Trans_m, const Vector3D& RotXYZ_deg, const Vector3D& RGB) {
  std::ostringstream ostr;

  ostr << "AddObj Name=" << Name << " Shift=" << Shift << " Scale=" << Scale << " Trans_m=" << Trans_m << " RGB=" << RGB << " RotXYZ_deg=" << RotXYZ_deg << std::endl;
  return ostr.str();
}

std::string ComInterface::getCommand_UpdateObj(const std::string& Name, const Vector3D& Trans_m, const Vector3D& RotXYZ_deg) {
  std::ostringstream ostr;

  ostr << "UpdateObj Name=" << Name << " Trans_m=" << Trans_m << " RotXYZ_deg=" << RotXYZ_deg << std::endl;
  return ostr.str();
}

bool ComInterface::sendCommand(const std::string& cmd){
    const int socket = this->channel.GetSocket();

    std::cout << "Sending: "<< cmd <<std::endl;

    if( write(socket, cmd.c_str(), cmd.length()) != cmd.length() )  {
        return false;
    }

    return true;
}

bool ComInterface::AddObj(const std::string& name, const Vector3D& shift, const Vector3D& scale, const Vector3D& trans, const Vector3D& rotXYZ, const Vector3D& RGB) {
    std::string cmd = getCommand_AddObj(name, shift, scale, trans, rotXYZ, RGB);
    sendCommand(cmd);
}

bool ComInterface::UpdateObj(const std::string& name, const Vector3D& trans, const Vector3D& rotXYZ) {
    std::string cmd = getCommand_AddObj(name, trans, rotXYZ);
    sendCommand(cmd);
}

bool ComInterface::Clear() {
    const char* msg = "Clear \n";
    const int socket = this->channel.GetSocket();

    if( write(socket, msg, strlen(msg)) != strlen(msg) ) {
        return false;
    }

    return true;  
}

bool ComInterface::Close() {
    const char* msg = "Close \n";
    const int socket = this->channel.GetSocket();

    if( write(socket, msg, strlen(msg)) != strlen(msg) ) {
        return false;
    }

    return true;  
}
