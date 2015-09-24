#ifndef __MINOFFOUR_H__
#define __MINOFFOUR_H__
#include "TMath.h"
using namespace std;
float minOfFour(double a, double b, double c, double d)
{
  return TMath::Min(TMath::Min(a,b),TMath::Min(c,d));
}
#endif
