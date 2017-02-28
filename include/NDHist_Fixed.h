#ifndef __NDHist_Fixed_h__
#define __NDHist_Fixed_h__
#include "TAxis.h"
#include "TH1.h"
#include "NDHist.h"
#include <tuple>
#include <string>
class NDHist_Fixed : public NDHist
{
	public:
		NDHist_Fixed();
		NDHist_Fixed(const TH1&);
		NDHist_Fixed(const std::vector<std::tuple<int,double,double>>&); // nbins, low, high ×N
		NDHist_Fixed(const std::vector<std::tuple<int,double*>>&); // nbins, array of bin edges [nbins+1] ×N
		NDHist_Fixed(const NDHist_Fixed&);
		bool IsCompatible(const NDHist_Fixed&) const;
		void SetAxisNames(const std::vector<std::string>&);
		void SetAxisTitles(const std::vector<std::string>&);
	protected:
		std::vector<TAxis> axes;
	private:
		void Initialise(const std::vector<int>&);
		int FindBin(const std::vector<double>&) const;
		int GetBin(const std::vector<int>&) const;
		bool CheckDim(const unsigned idim) const { return idim == axes.size(); }
};
NDHist_Fixed operator+ (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs += rhs; return lhs; }
NDHist_Fixed operator- (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs -= rhs; return lhs; }
NDHist_Fixed operator* (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs *= rhs; return lhs; }
NDHist_Fixed operator/ (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs /= rhs; return lhs; }
#endif

