#include "PressurePoint.hh"

#include "util/Error.hh"

PressurePoint::PressurePoint(double x_, double y_, double z_)
  : Point(x_, y_)
{
  set_z(z_);
}

double PressurePoint::get_z() const
{
  return z;
}

void PressurePoint::set_z(double z_)
{
  gj_assert(z >= 0);
  z = z_;
}

