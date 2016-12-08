#include "NDHist_Adaptive.h"
#include "TCollection.h"
#include "TKey.h"
#include <stdexcept>
#include <iostream>
NDHist_Adaptive::NDHist_Adaptive(TKDTreeBinning* _b) : binner(_b->GetTree())
{
	Initialise();
}
NDHist_Adaptive::NDHist_Adaptive(TKDTreeID* _b) : binner(_b)
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
		std::cout << key->GetClassName() << std::endl;
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
{
	under = orig.under;
	over = orig.over;
	binner = orig.binner;
	nbins = orig.nbins;
	bincontent = orig.bincontent;
	dimscale = orig.dimscale;
}
void NDHist_Adaptive::Initialise()
{
	nbins = binner->GetNNodes()+1;
	std::cout << "Adaptively-binned " << binner->GetNDim() << "D histogram with " << nbins << " bins" << std::endl;
	for(int ibin = nbins; ibin-->0;)
	{
		bincontent.push_back(0);
		dimscale.push_back(1);
	}
	Clear();
}
int NDHist_Adaptive::FindBin(std::vector<double> x)
{
	for(unsigned idim = dimscale.size(); idim-->0;)
		x[idim] *= dimscale[idim];
	return binner->FindNode(&x[0]) - binner->GetNNodes();
}
bool NDHist_Adaptive::IsCompatible(const NDHist_Adaptive& other)
{
	return binner == other.binner && nbins == other.nbins;
}
TTree* NDHist_Adaptive::SaveToTree()
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
void NDHist_Adaptive::SetDimScales(std::vector<double> newscale)
{
	if(!this->CheckDim(newscale.size()))
		throw std::runtime_error("NDHist_Adaptive ERROR: List of scales has the wrong number of dimensions.");
	dimscale = newscale;
}
