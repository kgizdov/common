#include "TLatex.h"
#include "TAxis.h"
#include "TStyle.h"
#include "plotmaker.h"
#include <sstream>
using namespace std;
/*****************************************************************************/
// Constructor without pull plot
plotmaker::plotmaker(TCanvas* canvas, RooPlot* mainplot) :
  _canvas(canvas),
  _mainplot(mainplot)
{
  _usepull = false;
  init();
}
// Constructor with pull plot
plotmaker::plotmaker(TCanvas* canvas, RooPlot* mainplot, RooPlot* pullplot) :
  _canvas(canvas),
  _mainplot(mainplot),
  _pullplot(pullplot)
{
  _usepull = true;
  init();
}
// Make sure to delete all the "new" objects
plotmaker::~plotmaker()
{
  delete _blurb;
  delete _mainpad;
  if(_usepull)
  {
    delete _pullpad;
  }
}
/*****************************************************************************/
// Set default values for variables and set things up for drawing.
void plotmaker::init()
{
  _canvas->Draw();
  _blurbx    = 0.55;
  _blurby    = 0.80;
  _blurbtext = "LHCb";
  _xtitle    = "#font[132]{}m(K^+K^-K^+K^-)";
  _unit      = "MeV/#font[12]{c}#font[132]{^{2}}";
  if(_usepull)
  {
    _mainpad = new TPad("mainpad", "", 0.00, 0.25, 1.00, 1.00);
    _mainpad->SetMargin(0.15,0.05,0.02,0.05);
    _mainpad->Draw();
    _pullpad = new TPad("pullpad", "", 0.00, 0.00, 1.00, 0.25);
    _pullpad->SetMargin(0.15,0.05,0.50,0.00);
    _pullpad->Draw();
  }
  else
  {
    _mainpad = new TPad("mainpad", "", 0.00, 0.00, 1.00, 1.00);
    _mainpad->SetMargin(0.15,0.05,0.15,0.05);
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
  frame->GetYaxis()->CenterTitle();
  frame->SetXTitle(("#font[132]{}"+_xtitle+" #font[132]{}["+_unit+"]").c_str());
}
/*****************************************************************************/

/*****************************************************************************/
void plotmaker::Draw()
{
  gStyle->SetOptStat(0);
  // Main frame style
  styleframe(_mainplot);
  // Axis titles
  stringstream ytitle;
  ytitle << "#font[132]{}Candidates / (" << setprecision(1) << fixed << _mainplot->getFitRangeBinW() << " " << _unit << ")";
  _mainplot->SetYTitle(ytitle.str().c_str());
  _mainplot->SetTitleOffset(1.20,"x");
  _mainplot->SetTitleOffset(1.20,"y");
  _mainplot->SetTitleSize  (0.07,"x");
  _mainplot->SetTitleSize  (0.07,"y");
  // Axis labels
  _mainplot->SetLabelSize  (0.07,"x");
  _mainplot->SetLabelSize  (0.07,"y");
  // Pull frame style
  if(_usepull)
  {
    // Get rid of the stuff under the main plot
    _mainplot->SetLabelSize(0,"x");
    // Style the pull plot
    styleframe(_pullplot);
    // Axis titles
    _pullplot->SetYTitle("Pull");
    _pullplot->SetTitleOffset(1.20,"x");
    _pullplot->SetTitleOffset(0.35,"y");
    _pullplot->SetTitleSize  (0.20,"x");
    _pullplot->SetTitleSize  (0.20,"y");
    // Axis labels
    _pullplot->SetLabelSize  (0.20,"x");
    _pullplot->SetLabelSize  (0.15,"y");
    // Ticks
    _pullplot->SetTickLength(0.1,"x");
    _pullpad->SetTicks(1,0);
    // Finish
    _pullpad->cd();
    _pullplot->Draw();
  }
  _mainpad->cd();
  _mainplot->Draw();
  // Blurb
  _blurb = new TLatex(_blurbx,_blurby,_blurbtext.c_str());
  _blurb->SetTextFont(132);
  _blurb->SetTextColor(1);
  _blurb->SetNDC(kTRUE);
  _blurb->SetTextAlign(11);
  _blurb->SetTextSize(0.06);
  _mainpad->cd();
  _blurb->Draw();
}
