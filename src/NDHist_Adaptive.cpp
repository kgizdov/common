#include "NDHist_Adaptive.h"
#include "TCollection.h"
#include "TKey.h"
#include <stdexcept>
NDHist_Adaptive::NDHist_Adaptive(TKDTreeBinning* _b)
	: NDHist()
	, binner(_b->GetTree())
{
	Initialise();
}
NDHist_Adaptive::NDHist_Adaptive(TKDTreeID* _b)
	:	NDHist()
	, binner(_b)
{
	Initialise();
}
NDHist_Adaptive::NDHist_Adaptive(TFile* _f)
{
	TIter next = _f->GetListOfKeys();
	TKey* key;
	// Look for any TKDTree object in the file
	while((key = (TKey*)next()))
	{
		if(strcmp(key->GetClassName(),"TKDTree<int,double>")==0)
		{
			binner = (TKDTreeID*)key->ReadObj();
			Initialise();
		}
	}
	if(binner == NULL)
		throw std::runtime_error("NDHist_Adaptive ERROR: Couldn't find a TKDTree object in the file");
}
NDHist_Adaptive::NDHist_Adaptive(const NDHist_Adaptive& orig)
	: NDHist(orig)
	, binner(orig.binner)
	, dimscale(orig.dimscale)
{
}
void NDHist_Adaptive::Initialise()
{
	nbins = binner->GetNNodes()+1;
	for(int ibin = nbins; ibin-->0;)
	{
		bincontent.push_back(0);
		dimscale.push_back(1);
	}
	Clear();
}
int NDHist_Adaptive::FindBin(const std::vector<double>& _x) const
{
	std::vector<double> x = _x; // Copy the vector so we can scale it
	for(unsigned idim = dimscale.size(); idim-->0;)
		x[idim] *= dimscale[idim];
	return binner->FindNode(&x[0]) - binner->GetNNodes();
}
bool NDHist_Adaptive::IsCompatible(const NDHist_Adaptive& other) const
{
	return binner == other.binner && nbins == other.nbins;
}
TTree* NDHist_Adaptive::SaveToTree() const
{
	TTree* tree = new TTree("AccTree","");
	double content; tree->Branch("content",&content);
	for(auto binc : bincontent)
	{
		content = binc;
		tree->Fill();
	}
	return tree;
}
void NDHist_Adaptive::LoadFromTree(TTree* tree)
{
	double content; tree->SetBranchAddress("content",&content);
	if(tree->GetEntries() == nbins)
		for(int ibin = nbins; ibin-->0;)
		{
			tree->GetEntry(ibin);
			bincontent[ibin] = content;
		}
	else
		throw std::out_of_range("NDHist_Adaptive ERROR: Tree does not contain the right number of bins");
}
void NDHist_Adaptive::SetDimScales(const std::vector<double>& newscale)
{
	if(!this->CheckDim(newscale.size()))
		throw std::runtime_error("NDHist_Adaptive ERROR: List of scales has the wrong number of dimensions.");
	dimscale = newscale;
}

