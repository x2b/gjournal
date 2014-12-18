#ifndef PRESSUREPOINT_HH
#define PRESSUREPOINT_HH

#include "Point.hh"

/**
 * @brief A Point with an attached pressure value
 */
class PressurePoint : public Point
{
public:
  PressurePoint(double x_, double y_, double z_);

  /**
   * Returns this Point%'s pressure.
   */
  double get_z() const;

  /**
   * Sets this Point%'s pressure.
   */
  void set_z(double z_);

private:
  double z;
};

#endif /* PRESSUREPOINT_HH */
