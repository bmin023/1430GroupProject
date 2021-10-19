#ifndef FORCE_H_INCLUDED
#define FORCE_H_INCLUDED

#include <cmath>

using namespace std;

class force_t
{
private:
  double magnitude;
  double direction;

public:
  force_t(double mag = 0, double dir = 0);
  void apply(const force_t &);
  force_t add(const force_t &) const;
  force_t operator+(const force_t &) const;
};

#endif // FORCE_H_INCLUDED