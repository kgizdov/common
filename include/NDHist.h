#ifndef __NDHist_h__
#define __NDHist_h__
#include <vector>
#include <string>
#include "TH1D.h"
class NDHist
{
	public:
		~NDHist();
		void Fill(const std::vector<double>&);
		void Clear();
		double Eval(const std::vector<double>&) const;
		double MaxBinContent() const;
		double MinBinContent() const;
		double GetBinContent(const int ibin) const { return bincontent[ibin]; }
		double UnderFlow() const { return under; }
		double OverFlow() const { return over; }
		double Integral() const;
		TH1D* BinContentHist() const;
		TH1D* BinContentHist(const std::string) const;
		bool Add(const NDHist&);
		bool Subtract(const NDHist&);
		bool Multiply(const NDHist&);
		bool Divide(const NDHist&);
		virtual bool IsCompatible(const NDHist&) const;
		void Print() const;
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
		bool Arithmetic(const NDHist&,const int);
		virtual int FindBin(const std::vector<double>&) const;
		virtual bool CheckDim(const unsigned) const;
};
NDHist operator+ (NDHist lhs, const NDHist& rhs) { lhs += rhs; return lhs; }
NDHist operator- (NDHist lhs, const NDHist& rhs) { lhs -= rhs; return lhs; }
NDHist operator* (NDHist lhs, const NDHist& rhs) { lhs *= rhs; return lhs; }
NDHist operator/ (NDHist lhs, const NDHist& rhs) { lhs /= rhs; return lhs; }
#endif

