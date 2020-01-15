/*
                 __    ___ __       
      ____  ____/ /___/ (_) /___  __
     / __ \/ __  / __  / / __/ / / /    [ LED matrix VFX core ] 
    / /_/ / /_/ / /_/ / / /_/ /_/ / 
    \____/\__,_/\__,_/_/\__/\__, /     [ john & harry ] [ 2012 ]
                           /____/   
*/

#pragma once
#include "fixmath.h"

class Fxp3D
{
public:

  Fxp3D() {}

  Fxp3D(float _x, float _y, float _z) :
    x(_x),
    y(_y),
    z(_z)
  {
  }

  Fxp3D(int16_t _x, int16_t _y, int16_t _z) :
    x(_x),
    y(_y),
    z(_z)
  {
  }

  Fxp3D(Fix16 _x, Fix16 _y, Fix16 _z) :
    x(_x),
    y(_y),
    z(_z)
  {
  }

  Fxp3D(const Fxp3D& rhs) :
    x(rhs.x),
    y(rhs.y),
    z(rhs.z)
  {
  }

  Fix16 x, y, z;

  Fxp3D eulerProject(Fix16 rotX, Fix16 rotY, Fix16 rotZ, Fix16 fov, Fix16 dist) const
  {
    Fix16 toRadians(0.0174532925f);
    rotX *= toRadians;
    rotY *= toRadians;
    rotZ *= toRadians;

    Fix16 sina_x = rotX.sin();
    Fix16 cosa_x = rotX.cos();
    Fix16 sina_y = rotY.sin();
    Fix16 cosa_y = rotY.cos();
    Fix16 sina_z = rotZ.sin();
    Fix16 cosa_z = rotZ.cos();

    Fix16 halfViewSize(int16_t(Constants::FrameWidth >> 1));

    Fix16 _y = (y * cosa_x) - (z * sina_x);
    Fix16 _z = (y * sina_x) + (z * cosa_x);

    Fix16 __z = (_z * cosa_y) - (x * sina_y);
    Fix16 _x = (_z * sina_y) + (x * cosa_y);

    Fix16 __x = (_x * cosa_z) - (_y * sina_z);
    Fix16 __y = (_x * sina_z) + (_y * cosa_z);

    Fix16 fac = fov / (dist + __z);
    Fix16 nx = (__x * fac) + halfViewSize;
    Fix16 ny = (__y * fac * -1.0f) + halfViewSize;

    return Fxp3D(nx, ny, __z * fac);
  }
};

/*
    def rotateX(self, angle):
        """ Rotates the point around the X axis by the given angle in degrees. """
        rad = angle * math.pi / 180
        cosa = math.cos(rad)
        sina = math.sin(rad)
        y = self.y * cosa - self.z * sina
        z = self.y * sina + self.z * cosa
        return Point3D(self.x, y, z)
 
    def rotateY(self, angle):
        """ Rotates the point around the Y axis by the given angle in degrees. """
        rad = angle * math.pi / 180
        cosa = math.cos(rad)
        sina = math.sin(rad)
        z = self.z * cosa - self.x * sina
        x = self.z * sina + self.x * cosa
        return Point3D(x, self.y, z)
 
    def rotateZ(self, angle):
        """ Rotates the point around the Z axis by the given angle in degrees. """
        rad = angle * math.pi / 180
        cosa = math.cos(rad)
        sina = math.sin(rad)
        x = self.x * cosa - self.y * sina
        y = self.x * sina + self.y * cosa
        return Point3D(x, y, self.z)
*/