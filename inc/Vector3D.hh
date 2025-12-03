#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

 /*!
  * \brief Instacja szablonu geom::Vector<typename,int> dla przestrzeni 3D.
  */
 typedef geom::Vector<double,3>  Vector3D;

 std::ostream& operator<<(std::ostream& out, const Vector3D& vec) {
    out<<"("<<vec[0]<<","<<vec[1]<<","<<vec[2]<<")";
    return out;
  }

#endif
