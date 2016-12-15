#ifndef __NDHist_Adaptive_h__
#define __NDHist_Adaptive_h__
// Self
#include "NDHist.h"
// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TKDTree.h"
#include "TKDTreeBinning.h"
class NDHist_Adaptive : public NDHist
{
	public:
		NDHist_Adaptive(TKDTreeBinning*); // Pass the binning thing directly
		NDHist_Adaptive(TKDTreeID*);
		NDHist_Adaptive(TFile*); // Load the binning thing from a file
		NDHist_Adaptive(const NDHist_Adaptive&);
		bool IsCompatible(const NDHist_Adaptive&);
		TTree* SaveToTree();
		void LoadFromTree(TTree*);
		void SetDimScales(std::vector<double>);
		std::vector<double> GetDimScales() { return dimscale; }
	protected:
		TKDTreeID* binner;
		std::vector<double> dimscale;
	private:
		void BuildSpline();
		void Initialise();
		int FindBin(std::vector<double>);
		int nDims() { return binner->GetNDim(); }
};
NDHist_Adaptive operator+ (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs += rhs; return lhs; }
NDHist_Adaptive operator- (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs -= rhs; return lhs; }
NDHist_Adaptive operator* (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs *= rhs; return lhs; }
NDHist_Adaptive operator/ (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs /= rhs; return lhs; }
#endif

