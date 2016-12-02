#ifndef __NDHist_Adaptive_h__
#define __NDHist_Adaptive_h__
#include "TFile.h"
#include "TTree.h"
#include "NDHist.h"
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
	protected:
		TKDTreeID* binner;
	private:
		void Initialise();
		int FindBin(std::vector<double>);
		bool CheckDim(unsigned ndim) { return ndim == (unsigned)binner->GetNDim(); }
};
NDHist_Adaptive operator+ (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs += rhs; return lhs; }
NDHist_Adaptive operator- (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs -= rhs; return lhs; }
NDHist_Adaptive operator* (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs *= rhs; return lhs; }
NDHist_Adaptive operator/ (NDHist_Adaptive lhs, const NDHist_Adaptive& rhs) { lhs /= rhs; return lhs; }
#endif

