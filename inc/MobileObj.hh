#ifndef MOBILEOBJ__HH_
#define MOBILEOBJ__HH_

#include <string>
#include <mutex>
#include "Vector3D.hh"
#include "AbstractMobileObj.hh"

/*!
 * \brief Liczba stanów każdego z obiektów.
 *
 * Liczba stanów każdego z obiektów.
 * Podział na kolejne stany obiektów wykorzystywany jest
 * do animacji ruchu obiektów.
 */
#define STATES_NUMBER   8

/*!
* \brief Definiuje interfejs dla obiektów mobilnych.
*
* Definiuje interfejs dla obiektów mobilnych.
* Zakładamy, że przód obiektu jest wskazywany przez strzałkę osi OX.
* Nazwy metod są obowiązujące.
*/
class MobileObj : public AbstractMobileObj {

  Vector3D _rotation;
  Vector3D _position;

  std::string _name;
  std::mutex lock;

  int _StateIdx = 0;
  const char** _Cmd4StatDesc = nullptr;

  public:

    ~MobileObj() {}

    void SetCmds(const char *CmdsTab[STATES_NUMBER]) { _Cmd4StatDesc = CmdsTab; }

    const char* GetStateDesc() const { return _Cmd4StatDesc[_StateIdx];  }

    bool IncStateIndex() {
      if (_StateIdx >= STATES_NUMBER-1) return false;
      ++_StateIdx;
      return true;
    }

  
    /*!
    * \brief Udostępnia wartość kąta \e roll.
    *
    *  Udostępnia wartość kąta \e pitch reprezentuje rotację
    *  zgodnie z ruchem wskazówek zegara wokół osi \e OX.
    *  \return Wartość kąta \e roll wyrażona w stopniach.
    */
    double GetAng_Roll_deg() const  { return this->_rotation[0];  }
    /*!
    * \brief Udostępnia wartość kąta \e yaw.
    *
    *  Udostępnia wartość kąta \e pitch reprezentuje rotację
    *  zgodnie z ruchem wskazówek zegara wokół osi \e OY.
    *  \return Wartość kąta \e pitch wyrażona w stopniach.
    */
    double GetAng_Pitch_deg() const  { return this->_rotation[1];  }
    /*!
    * \brief Udostępnia wartość kąta \e yaw.
    *
    *  Udostępnia wartość kąta \e yaw reprezentuje rotację
    *  zgodnie z ruchem wskazówek zegara wokół osi \e OZ.
    *  \return Wartość kąta \e yaw wyrażona w stopniach.
    */
    double GetAng_Yaw_deg() const  { return this->_rotation[2];  }

    /*!
    * \brief Zmienia wartość kąta \e roll.
    *
    *  Zmienia wartość kąta \e roll.
    *  \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
    */
    void SetAng_Roll_deg(double Ang_Roll_deg) { this->_rotation[0] = Ang_Roll_deg;  }
    /*!
    * \brief Zmienia wartość kąta \e pitch.
    *
    *  Zmienia wartość kąta \e pitch.
    *  \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
    */
    void SetAng_Pitch_deg(double Ang_Pitch_deg) { this->_rotation[1] = Ang_Pitch_deg;  }
    /*!
    * \brief Zmienia wartość kąta \e yaw.
    *
    *  Zmienia wartość kąta \e yaw.
    *  \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
    */
    void SetAng_Yaw_deg(double Ang_Yaw_deg) { this->_rotation[2] = Ang_Yaw_deg;  }
    /*!
    * \brief Zmienia wartości kątów \e roll, \e pitch i \e yaw.
    *
    *  \param[in] rRot - nowa wartość kątów obrotu wyrażona w stopniach.
    */
    void SetRotation_deg(const Vector3D &rRot) {  this->_rotation = rRot;  }
    
    /*!
    * \brief Udostępnia współrzędne aktualnej pozycji obiektu.
    *
    * Udostępnia współrzędne aktualnej pozycji obiektu
    * \return Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
    *         że współrzędne wyrażone są w metrach.
    */
    const Vector3D & GetPosition_m() const  {  return this->_position;  }
    /*!
    * \brief Zmienia współrzędne aktualnej pozycji obiektu.
    *
    * Zmienia współrzędne aktualnej pozycji obiektu.
    * \param[in] rPos - nowe współrzędne obiektu. Przyjmuje się,
    *         że współrzędne wyrażone są w metrach.
    */
    void SetPosition_m(const Vector3D &rPos) {  this->_position = rPos;  }

    /*!
    * \brief Zmienia nazwę obiektu.
    *
    *  Zmienia nazwę obiektu, która go identyfikuje.
    *  \param[in]  sName - nowa nazwa obiektu.
    */
    void SetName(const char* sName)  {  this->_name = sName;  }
    /*!
    * \brief Udostępnia nazwę obiektu.
    *  Udostępnia nazwę identyfikującą obiekt.
    *  \return Nazwa obiektu.
    */
    const std::string & GetName() const  {  return this->_name;  }

    /*!
    * \brief Blokuje dostęp do obiektu.
    *  Blokuje dostęp do obiektu.
    */
    void LockAccess()   { this->lock.lock();  }

    /*!
    * \brief Odblokowuje dostęp do obiektu.
    *  Odblokowuje dostęp do obiektu.
    */
    void UnLockAccess() { this->lock.unlock(); }
};

#endif