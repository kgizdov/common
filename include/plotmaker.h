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
		enum PlotClass {rooplot, tgraph, th1};
		PlotClass _mainclass;
		PlotClass _pullclass;
		void		 init();
		template<class T> void getaxes(T*, bool);
		void		 makepads();
		// The blurb
		TLatex*	 _blurb;
		string	 _blurbtext;
		double	 _blurbx;
		double	 _blurby;
		// Objects to draw on
		TCanvas* _canvas;
		TPad*		 _mainpad;
		TPad*		 _pullpad;
		// The plots
		void*		 _mainplot;
		void*		 _pullplot;
		// The Axes
		TAxis*	 _mainxaxis;
		TAxis*	 _mainyaxis;
		TAxis*	 _pullxaxis;
		TAxis*	 _pullyaxis;
		// Axis label & unit
		string	 _xtitle;
		string	 _unit;
		bool		 _dimensionless;
		bool		 _logy;
		// Keep track whether or not a pull plot has been given
		bool		 _usepull;
		// Apply LHCb paper style to plot
		void		 setxtitle(TAxis*);
		void		 setytitle(TAxis*,double);
		void		 stylemainaxis(TAxis*);
		void		 stylepullaxes(TAxis*,TAxis*);
		void		 drawplot(void*,int,string);
		void		 drawblurb();
		template<class T> void makesymmetric(T*);
	public:
		// Constructors
		plotmaker(RooPlot*);
		plotmaker(TH1*);
		plotmaker(TGraph*);
		~plotmaker();
		// Get and set variables
		TCanvas* GetCanvas() { return _canvas; }
		string	 GetBlurb()	 { return _blurbtext; }
		void		 SetLogy(bool logy = true) { _logy = logy; }
		void		 SetBlurb(string);
		void		 SetBlurbPosition(double,double);
		void		 SetPullPlot(RooPlot*);
		void		 SetPullPlot(TH1*);
		void		 SetPullPlot(TGraph*);
		void		 SetTitle(string,string);
		// Do stuff
		TCanvas* Draw(string option = "");
};
#endif
