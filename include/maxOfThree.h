#ifndef __MAXOFTHREE_H__
#define __MAXOFTHREE_H__
#include "TMath.h"
using namespace std;
float maxOfThree(double a, double b, double c)
{
  return TMath::Max(TMath::Max(a,b),c);
}
#endif
