#ifndef PRESSUREPOINT_HH
#define PRESSUREPOINT_HH

#include "Point.hh"

class PressurePoint : public Point
{
public:
  PressurePoint(double x_, double y_, double z_);

  double get_z() const;
  void set_z(double z_);

private:
  double z;
};

#endif /* PRESSUREPOINT_HH */
