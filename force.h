#ifndef FORCE_H_INCLUDED
#define FORCE_H_INCLUDED

#include <cmath>

using namespace std;

const double PI = 3.1415926535;

class force_t
{
private:
  double magnitude;
  double direction;

public:
  void setMagnitude(double m);
  void setDirection(double d);
  double getMagnitude() const;
  double getDirection() const;

  force_t(double mag = 0, double dir = 0);
  void apply(const force_t &);
  force_t add(const force_t &) const;
  force_t operator+(const force_t &) const;
};

const force_t GRAVITY(0.04, PI / 2);

#endif // FORCE_H_INCLUDED