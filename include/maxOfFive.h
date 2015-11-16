#ifndef __MAXOFFIVE_H__
#define __MAXOFFIVE_H__
#include "TMath.h"
using namespace std;
float maxOfFive(double a, double b, double c, double d, double e)
{
  return TMath::Max(TMath::Max(TMath::Max(a,b),TMath::Max(c,d)),e);
}
#endif
