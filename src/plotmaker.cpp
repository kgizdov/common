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
// Constructor
plotmaker::plotmaker(RooPlot* mainplot) :
  _mainplot(mainplot)
{
  _mainclass = rooplot;
  _usepull = false;
  getaxes(mainplot,false);
  init();
}
plotmaker::plotmaker(TGraph* mainplot) :
  _mainplot(mainplot)
{
  _mainclass = tgraph;
  _usepull = false;
  getaxes(mainplot,false);
  init();
}
plotmaker::plotmaker(TH1* mainplot) :
  _mainplot(mainplot)
{
  _mainclass = th1;
  _usepull = false;
  getaxes(mainplot,false);
  init();
}
// Make sure to delete all the "new" objects
plotmaker::~plotmaker()
{
  delete _canvas;
  delete _mainpad;
  if(_usepull)
  {
    delete _pullpad;
  }
  if(_blurb != NULL)
  {
    delete _blurb;
  }
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
template<class T> void plotmaker::getaxes(T* plot, bool pull)
{
  if(pull)
  {
    _pullxaxis = plot->GetXaxis();
    _pullyaxis = plot->GetYaxis();
  }
  else
  {
    _mainxaxis = plot->GetXaxis();
    _mainyaxis = plot->GetYaxis();
  }
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
void plotmaker::SetBlurbPosition(double x, double y)
{
  _blurbx = x;
  _blurby = y;
}
/*****************************************************************************/
void plotmaker::SetPullPlot(RooPlot* pullplot)
{
  _pullplot = pullplot;
  _pullclass = rooplot;
  getaxes(pullplot,true);
  _usepull = true;
  // Remove pull plot errors
  for(int i = 0; i < pullplot->getHist()->GetN(); i++)
  {
    pullplot->getHist()->SetPointError(i,0,0,0,0);
  }
  makesymmetric(pullplot);
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
void plotmaker::stylemainaxis(TAxis* axis)
{
  axis->SetTitleFont(132);
  axis->SetLabelFont(132);
  axis->SetNdivisions(505);
  axis->SetTitleOffset(1.10);
  axis->SetTitleSize  (0.065);
  axis->SetLabelSize  (0.055);
  axis->SetLabelOffset(0.015);
}
void plotmaker::setxtitle(TAxis* axis)
{
  if(_dimensionless)
  {
    axis->SetTitle(("#font[132]{}"+_xtitle).c_str());
  }
  else
  {
    axis->SetTitle(("#font[132]{}"+_xtitle+" #font[132]{}["+_unit+"]").c_str());
  }
}
void plotmaker::setytitle(TAxis* axis)
{
  axis->CenterTitle();
  stringstream ytitle;
  double binw = axis->GetBinWidth(1);
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
  axis->SetTitle(ytitle.str().c_str());
}
void plotmaker::stylepullaxes(TAxis* xaxis, TAxis* yaxis)
{
  stylemainaxis(xaxis);
  stylemainaxis(yaxis);
  // Axis titles
  yaxis->SetTitle("Pull");
  yaxis->CenterTitle();
  xaxis->SetTitleOffset(1.20);
  yaxis->SetTitleOffset(0.40);
  xaxis->SetTitleSize  (0.17);
  yaxis->SetTitleSize  (0.17);
  // Axis labels
  xaxis->SetLabelSize  (0.15);
  yaxis->SetLabelSize  (0.10);
  // Ticks
  xaxis->SetTickLength(0.1);
  yaxis->SetNdivisions(5);
}
void plotmaker::drawblurb()
{
  _blurb = new TLatex(_blurbx,_blurby,_blurbtext.c_str());
  _blurb->SetTextFont(132);
  _blurb->SetTextColor(1);
  _blurb->SetNDC(kTRUE);
  _blurb->SetTextAlign(11);
  _blurb->SetTextSize(0.07);
  _blurb->Draw();
}
template<class T> void plotmaker::makesymmetric(T* plot)
{
  // Make symmetric around zero
  double max = plot->GetMaximum();
  double min = plot->GetMinimum()*-1;
  double newmax = 1.2*(1+(int)std::max(max,min));
  plot->SetMaximum(newmax);
  plot->SetMinimum(-newmax);
}
void plotmaker::drawplot(void* plot, int plotclass)
{
  switch(plotclass)
  {
    case rooplot:
      ((RooPlot*)plot)->Draw();
      break;
    case tgraph:
      ((TGraph*)plot)->Draw();
      break;
    case th1:
      ((TH1*)plot)->Draw();
      break;
  }
}
/*****************************************************************************/
TCanvas* plotmaker::Draw(bool logy)
{
  gStyle->SetOptStat(0);
  setxtitle(_mainxaxis);
  setytitle(_mainyaxis);
  stylemainaxis(_mainxaxis);
  stylemainaxis(_mainyaxis);
  // Pull frame style
  if(_usepull)
  {
    // Get rid of the stuff under the main plot
    _mainxaxis->SetLabelSize(0);
    stylepullaxes(_pullxaxis,_pullyaxis);
    // Finish
    _pullpad->cd();
    drawplot(_pullplot,_pullclass);
  }
  _mainpad->cd();
  if(logy) _mainpad->SetLogy();
  drawplot(_mainplot,_mainclass);
  _mainpad->cd();
  drawblurb();
  return _canvas;
}
/*****************************************************************************/
