#ifndef __NDHist_h__
#define __NDHist_h__
#include <vector>
#include <string>
#include "TH1D.h"
class NDHist
{
	public:
		~NDHist();
		void Fill(std::vector<double>);
		void Clear();
		double Eval(std::vector<double>);
		double MaxBinContent();
		double MinBinContent();
		double GetBinContent(int ibin) { return bincontent[ibin]; }
		double UnderFlow() { return under; }
		double OverFlow() { return over; }
		double Integral();
		TH1D* BinContentHist();
		TH1D* BinContentHist(std::string);
		bool Add(const NDHist&);
		bool Subtract(const NDHist&);
		bool Multiply(const NDHist&);
		bool Divide(const NDHist&);
		virtual bool IsCompatible(const NDHist&);
		void Print();
		NDHist operator= (const NDHist& rhs) { return NDHist(rhs); }
		bool   operator+=(const NDHist& rhs) { return Add(rhs); }
		bool   operator-=(const NDHist& rhs) { return Subtract(rhs); }
		bool   operator*=(const NDHist& rhs) { return Multiply(rhs); }
		bool   operator/=(const NDHist& rhs) { return Divide(rhs); }
	protected:
		int nbins;
		double under;
		double over;
		std::vector<double> bincontent;
	private:
		virtual void Initialise();
		bool Arithmetic(const NDHist&,int);
		virtual int FindBin(std::vector<double>);
		virtual bool CheckDim(unsigned);
};
NDHist operator+ (NDHist lhs, const NDHist& rhs) { lhs += rhs; return lhs; }
NDHist operator- (NDHist lhs, const NDHist& rhs) { lhs -= rhs; return lhs; }
NDHist operator* (NDHist lhs, const NDHist& rhs) { lhs *= rhs; return lhs; }
NDHist operator/ (NDHist lhs, const NDHist& rhs) { lhs /= rhs; return lhs; }
#endif

