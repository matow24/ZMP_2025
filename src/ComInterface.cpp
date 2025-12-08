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

    std::cout << "Sending: "<< cmd << std::endl;

    std::lock_guard<std::mutex> lockmtx(channel.UseGuard());

    if( write(socket, cmd.c_str(), cmd.length()) != cmd.length() )  {
        return false;
    }

    return true;
}

bool ComInterface::AddObj(const std::string& Name, const Vector3D& Shift, const Vector3D& Scale, const Vector3D& Trans_m, const Vector3D& RotXYZ_deg, const Vector3D& RGB) {
    std::string cmd = getCommand_AddObj(Name, Shift, Scale, Trans_m, RotXYZ_deg, RGB);
    return sendCommand(cmd);
}

bool ComInterface::UpdateObj(const std::string& Name, const Vector3D& Trans_m, const Vector3D& RotXYZ_deg) {
    std::string cmd = getCommand_UpdateObj(Name, Trans_m, RotXYZ_deg);
    return sendCommand(cmd);
}

bool ComInterface::Clear() {
    return sendCommand("Clear \n");
}

bool ComInterface::Close() {
    return sendCommand("Close \n");
}
