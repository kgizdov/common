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
		bool IsCompatible(const NDHist_Adaptive&) const;
		TTree* SaveToTree() const;
		void LoadFromTree(TTree*);
		void SetDimScales(const std::vector<double>&);
		std::vector<double> GetDimScales() const { return dimscale; }
	protected:
		TKDTreeID* binner;
		std::vector<double> dimscale;
	private:
		void Initialise();
		int FindBin(const std::vector<double>&) const;
		bool CheckDim(const unsigned ndim) const { return ndim == (unsigned)binner->GetNDim(); }
};
#endif

