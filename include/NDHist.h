#ifndef __NDHist_h__
#define __NDHist_h__
// std
#include <vector>
#include <string>
#include <algorithm>
// SPLINTER
#include "bsplinebuilder.h"
#include "datatable.h"
// ROOT
#include "TH1D.h"
class NDHist
{
	public:
		~NDHist();
		void Fill(std::vector<double>);
		void Clear();
		double Eval(std::vector<double> x) { return bincontent[FindBin(x)]; }
		double Interpolate(std::vector<double>);
		double MaxBinContent() { return *std::max_element(std::begin(bincontent), std::end(bincontent)); }
		double MinBinContent() { return *std::min_element(std::begin(bincontent), std::end(bincontent)); }
		double GetBinContent(int ibin) { return bincontent[ibin]; }
		virtual std::vector<double> GetBinCentre(int);
		double UnderFlow() { return under; }
		double OverFlow() { return over; }
		double Integral();
		TH1D* BinContentHist() { return BinContentHist("BinContentHist"); }
		TH1D* BinContentHist(std::string);
		bool Add     (const NDHist& rhs) { return Arithmetic(rhs,0); }
		bool Subtract(const NDHist& rhs) { return Arithmetic(rhs,1); }
		bool Multiply(const NDHist& rhs) { return Arithmetic(rhs,2); }
		bool Divide  (const NDHist& rhs) { return Arithmetic(rhs,3); }
		virtual bool IsCompatible(const NDHist&);
		void Print();
		NDHist operator= (const NDHist& rhs) { return NDHist(rhs)  ; }
		bool   operator+=(const NDHist& rhs) { return Add(rhs)     ; }
		bool   operator-=(const NDHist& rhs) { return Subtract(rhs); }
		bool   operator*=(const NDHist& rhs) { return Multiply(rhs); }
		bool   operator/=(const NDHist& rhs) { return Divide(rhs)  ; }
	protected:
		int nbins;
		double under;
		double over;
		std::vector<double> bincontent;
		SPLINTER::BSpline* spline;
		bool CheckDim(int ndims) { return ndims == nDims(); }
	private:
		virtual void BuildSpline();
		virtual void Initialise();
		bool Arithmetic(const NDHist&,int);
		virtual int FindBin(std::vector<double>) { return 0; }
		virtual int nDims() { return 0; }
};
NDHist operator+ (NDHist lhs, const NDHist& rhs) { lhs += rhs; return lhs; }
NDHist operator- (NDHist lhs, const NDHist& rhs) { lhs -= rhs; return lhs; }
NDHist operator* (NDHist lhs, const NDHist& rhs) { lhs *= rhs; return lhs; }
NDHist operator/ (NDHist lhs, const NDHist& rhs) { lhs /= rhs; return lhs; }
#endif

