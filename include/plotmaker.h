#ifndef __PLOTMAKER_H__
#define __PLOTMAKER_H__
#include "TCanvas.h"
#include "TPad.h"
#include "TH1.h"
#include "TGraph.h"
#include "RooPlot.h"
#include "TLatex.h"
#include <string>
using namespace std;
class plotmaker
{
  private:
    void     init();
    void     makepads();
    // The blurb
    TLatex*  _blurb;
    string   _blurbtext;
    float    _blurbx;
    float    _blurby;
    // Objects to draw on
    TCanvas* _canvas;
    TPad*    _mainpad;
    TPad*    _pullpad;
    // The plots
    RooPlot* _mainplot;
    RooPlot* _pullplot;
    // The Axes
    TAxis*   _mainxaxis;
    TAxis*   _mainyaxis;
    TAxis*   _pullxaxis;
    TAxis*   _pullyaxis;
    // Axis label & unit
    string   _xtitle;
    string   _unit;
    bool     _dimensionless;
    // Keep track whether or not a pull plot has been given
    bool     _usepull;
    // Style options common to main and pull plots
    void     styleframe(RooPlot*);
    void     styleframe(TH1*);
    void     setxtitle(TAxis*);
    void     setytitle(TAxis*);
    void     stylemainaxis(TAxis*);
    void     stylepullaxes(TAxis*,TAxis*);
    void     drawblurb();
    template<class T> void makesymmetric(T*);
  public:
    // Constructors
    plotmaker(RooPlot*);
    plotmaker(RooPlot*,RooPlot*);
    ~plotmaker();
    // Get and set variables
    TCanvas* GetCanvas() {return _canvas;}
    string   GetBlurb()  {return _blurbtext ;}
    void     SetBlurb(string);
    void     SetBlurbPosition(float,float);
    void     SetPullPlot(RooPlot*);
    void     SetTitle(string,string);
    // Do stuff
    TCanvas* Draw(bool logy = false);
};
#endif
