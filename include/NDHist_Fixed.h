#ifndef __NDHist_Fixed_h__
#define __NDHist_Fixed_h__
// Self
#include "NDHist.h"
// std
#include <tuple>
#include <string>
// ROOT
#include "TAxis.h"
#include "TH2D.h"
class NDHist_Fixed : public NDHist
{
	public:
		NDHist_Fixed(std::vector<std::tuple<int,double,double>>); // nbins, low, high ×N
		NDHist_Fixed(std::vector<std::tuple<int,double*>>); // nbins, array of bin edges [nbins+1] ×N
		NDHist_Fixed(const NDHist_Fixed&);
		bool IsCompatible(const NDHist_Fixed&);
		void SetAxisNames(std::vector<std::string>);
		void SetAxisTitles(std::vector<std::string>);
//		TH1D* Project(int); // dim
//		TH2D* Project(int,int); // dim1,dim2
	protected:
		std::vector<TAxis> axes;
	private:
		void BuildSpline();
		void IterativeAddSample(int, std::vector<int>&, std::vector<double>&, SPLINTER::DataTable&);
		void Initialise(std::vector<int>);
		int FindBin(std::vector<double>);
		int GetBin(std::vector<int>);
		int nDims() { return axes.size(); }
};
NDHist_Fixed operator+ (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs += rhs; return lhs; }
NDHist_Fixed operator- (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs -= rhs; return lhs; }
NDHist_Fixed operator* (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs *= rhs; return lhs; }
NDHist_Fixed operator/ (NDHist_Fixed lhs, const NDHist_Fixed& rhs) { lhs /= rhs; return lhs; }
#endif

