#ifndef __PLOTMAKER_H__
#define __PLOTMAKER_H__
#include "TLatex.h"
using namespace std;
class plotmaker
{
  private:
    TLatex blurb;
    int year,xpos,ypos;
    bool paper;
  public:
    plotmaker();
    TLatex* getBlurb();
    
};
#endif
