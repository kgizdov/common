#include "TLatex.h"
#include "TMath.h"
#include "TAxis.h"
#include "TStyle.h"
#include "RooHist.h"
#include "plotmaker.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace std;
/*****************************************************************************/
// Constructor without pull plot
plotmaker::plotmaker(RooPlot* mainplot) :
  _mainplot(mainplot)
{

  _usepull = false;
  init();
}
// Constructor with pull plot
plotmaker::plotmaker(RooPlot* mainplot, RooPlot* pullplot) :
  _mainplot(mainplot),
  _pullplot(pullplot)
{
  _usepull = true;
  init();
}
// Make sure to delete all the "new" objects
plotmaker::~plotmaker()
{

}
/*****************************************************************************/
// Set default values for variables and set things up for drawing.
void plotmaker::init()
{
  _blurbx        = 0.75;
  _blurby        = 0.80;
  _blurbtext     = "#splitline{LHCb}{#scale[0.75]{Preliminary}}";
  _xtitle        = "#it{m}(#it{K^{#plus}K^{#minus}K^{#plus}K^{#minus}})";
  _unit          = "MeV/#it{c}^{2}";
  _dimensionless = false;
  makepads();
}
void plotmaker::makepads()
{
  if(_usepull)  
  {
    _canvas = new TCanvas("canvas","",1200,1000);
    _canvas->Draw();
    _mainpad = new TPad("mainpad", "", 0.00, 0.3, 1.00, 1.00);
    _mainpad->SetMargin(0.15,0.05,0.03,0.05);
    _mainpad->SetTicks(1,1);
    _mainpad->Draw();
    _pullpad = new TPad("pullpad", "", 0.00, 0.00, 1.00, 0.3);
    _pullpad->SetMargin(0.15,0.05,0.50,0.02);
    _pullpad->SetTicks(1,1);
    _pullpad->Draw();
    // Remove pull plot errors
    for(int i = 0; i < _pullplot->getHist()->GetN(); i++)
    {
      _pullplot->getHist()->SetPointError(i,0,0,0,0);
    }
  }
  else
  {
    _canvas = new TCanvas("canvas","",1200,900);
    _canvas->Draw();
    _mainpad = new TPad("mainpad", "", 0.00, 0.00, 1.00, 1.00);
    _mainpad->SetMargin(0.15,0.05,0.2,0.05);
    _mainpad->SetTicks(1,1);
    _mainpad->Draw();
  }
}
/*****************************************************************************/
void plotmaker::SetBlurb(string text)
{
  _blurbtext = text;
}
void plotmaker::SetBlurbPosition(float x, float y)
{
  _blurbx = x;
  _blurby = y;
}
/*****************************************************************************/
void plotmaker::styleframe(RooPlot* frame)
{
  frame->SetTitle("");
  frame->SetTitleFont(132, "x");
  frame->SetTitleFont(132, "y");
  frame->SetLabelFont(132, "x");
  frame->SetLabelFont(132, "y");
  frame->SetNdivisions(505,"x");
  frame->GetYaxis()->CenterTitle();
  if(_dimensionless)
  {
    frame->SetXTitle(("#font[132]{}"+_xtitle).c_str());
  }
  else
  {
    frame->SetXTitle(("#font[132]{}"+_xtitle+" #font[132]{}["+_unit+"]").c_str());
  }
}
/*****************************************************************************/
void plotmaker::SetPullPlot(RooPlot* pullplot)
{
  _pullplot = pullplot;
  _usepull = true;
  makepads();
}
/*****************************************************************************/
void plotmaker::SetTitle(string xtitle, string unit)
{
  replace(xtitle.begin(), xtitle.end(), '~', ' ');
  _xtitle = xtitle;
  _unit = unit;
  transform(unit.begin(), unit.end(), unit.begin(), ::tolower);
  _dimensionless = (unit == "dimensionless" || unit == "unitless" || unit == "none" || unit == "");
}
/*****************************************************************************/
TCanvas* plotmaker::Draw(bool logy)
{
  gStyle->SetOptStat(0);
  // Main frame style
  styleframe(_mainplot);
  // Axis titles
  stringstream ytitle;
  float binw = _mainplot->getFitRangeBinW();
  ytitle << "#font[132]{}Candidates / (";
  if(binw > 10)
    ytitle << TMath::Nint(binw);
  else if (binw > 0.1)
    ytitle << TMath::Nint(binw*10.0)/10.0;
  else
    ytitle << TMath::Nint(binw*pow(10.0,ceil(-log10(binw))))*pow(10.0,floor(log10(binw)));
  if(!_dimensionless)
  {
    ytitle << " " << _unit;
  }
  ytitle << ")";
  _mainplot->SetYTitle(ytitle.str().c_str());
  _mainplot->SetTitleOffset(1.10,"x");
  _mainplot->SetTitleOffset(1.10,"y");
  _mainplot->SetTitleSize  (0.065,"x");
  _mainplot->SetTitleSize  (0.065,"y");
  // Axis labels
  _mainplot->SetLabelSize  (0.055,"x");
  _mainplot->SetLabelSize  (0.055,"y");
  _mainplot->SetLabelOffset(0.015,"x");
  // Pull frame style
  if(_usepull)
  {
    // Get rid of the stuff under the main plot
    _mainplot->SetLabelSize(0,"x");
    // Style the pull plot
    styleframe(_pullplot);
    // Make symmetric around zero
    double max = _pullplot->GetMaximum();
    double min = _pullplot->GetMinimum()*-1;
    double newmax;
    if(max>min)
    {
      newmax = 1.2*(1+(int)max);
    }
    else
    {
      newmax = 1.2*(1+(int)min);
    }
    _pullplot->SetMaximum(newmax);
    _pullplot->SetMinimum(-newmax);
    // Axis titles
    _pullplot->SetYTitle("Pull");
    _pullplot->SetTitleOffset(1.20,"x");
    _pullplot->SetTitleOffset(0.40,"y");
    _pullplot->SetTitleSize  (0.17,"x");
    _pullplot->SetTitleSize  (0.17,"y");
    // Axis labels
    _pullplot->SetLabelSize  (0.15,"x");
    _pullplot->SetLabelSize  (0.10,"y");
    // Ticks
    _pullplot->SetTickLength(0.1,"x");
    _pullplot->SetNdivisions(5,"y");
    // Finish
    _pullpad->cd();
    _pullplot->Draw();
  }
  _mainpad->cd();
  if(logy) _mainpad->SetLogy();
  _mainplot->Draw();
  // Blurb
  _blurb = new TLatex(_blurbx,_blurby,_blurbtext.c_str());
  _blurb->SetTextFont(132);
  _blurb->SetTextColor(1);
  _blurb->SetNDC(kTRUE);
  _blurb->SetTextAlign(11);
  _blurb->SetTextSize(0.07);
  _mainpad->cd();
  _blurb->Draw();
  return _canvas;
}
/*****************************************************************************/
