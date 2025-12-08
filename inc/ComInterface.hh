#ifndef COMINTERFACE_HH
#define COMINTERFACE_HH

#include <string>
#include <sstream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ComChannel.hh"
#include "Vector3D.hh"

/*!
* \brief Klasa zapewniająca podstawowe polecenie dla serwera graficznego.
* Klasa zapewniająca podstawowe polecenie dla serwera graficznego.
*/
class ComInterface
{
    AbstractComChannel& channel;

    std::string getCommand_AddObj(const std::string& Name,const Vector3D& shift,const Vector3D& scale,const Vector3D& Trans_m,const Vector3D& RotXYZ_deg,const Vector3D& RGB);

    std::string getCommand_UpdateObj(const std::string& Name,const Vector3D& Trans_m,const Vector3D& RotXYZ_deg);

    bool sendCommand(const std::string& cmd);

    public:

    /*!
    * \brief Konstruktor klasy
    * Konstruktor klasy, blokuje on muteks kanału komunikacyjnego
    * \param _channel - referencja na kanał komunikacyjny z serwerem
    */
    ComInterface(AbstractComChannel& _channel) : channel(_channel) {};

    /*!
    * \brief Funkcja dodająca obiekt do serwera
    * Funkcja dodająca obiekt do serwera
    * \param shift - przesunięcie obiektu
    * \param scale - skala obietku
    * \param Trans_m - pozycja obiektu
    * \param RotXYZ_deg - obrót obiektu względem osi roll, pitch, yaw
    * \param RGB - kolor obiektu
    * 
    * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
    */
    bool AddObj(const std::string& Name,const Vector3D& shift,const Vector3D& scale,const Vector3D& Trans_m,const Vector3D& RotXYZ_deg,const Vector3D& RGB);

    /*!
    * \brief Funkcja aktualizująca parametry obiektu.
    * Funkcja aktualizująca parametry obiektu.
    * \param Name - nazwa obiektu
    * \param Trans_m - pozycja obiektu
    * \param RotXYZ_deg - obrót obiektu względem osi roll, pitch, yaw
    * 
    * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
    */
    bool UpdateObj(const std::string& Name,const Vector3D& Trans_m,const Vector3D& RotXYZ_deg);

    /*!
    * \brief Funkcja czyszcząca zawartość sceny serwera.
    * Funkcja czyszcząca zawartość sceny serwera.
    * 
    * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
    */
    bool Clear();

    /*!
    * \brief Funkcja zamykająca połączenie z serwerem.
    * Funkcja zamykająca połączenie z serwerem.
    * 
    * \return true jeśli polecenie zostało poprawnie wysłane do serwera, false w przeciwnym wypadku
    */
    bool Close();

    /*!
    * \brief Funkcja zwalniająca muteks kanału komunikacyjnego.
    * Funkcja zwalniająca muteks kanału komunikacyjnego.
    */
    void Release() { this->channel.UnlockAccess(); }

    ~ComInterface() { this->channel.UnlockAccess(); }
};

#endif