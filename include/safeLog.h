#ifndef __SAFELOG_H__
#define __SAFELOG_H__
#include "TMath.h"
float safeLog(float x)
{
  // Keep numbers in a sensible range for the sake of MVA training
  if(x>TMath::Exp(-25)) return TMath::Log(x);
  else return -25;
}
#endif
