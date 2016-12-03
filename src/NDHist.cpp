#include "NDHist.h"
#include <stdexcept>
#include <assert.h>
#include <iostream>
void NDHist::Initialise()
{
	for(int ibin = nbins; ibin-->0;)
		bincontent.push_back(0);
}
// Destructor
NDHist::~NDHist()
{
}
int NDHist::FindBin(std::vector<double> x)
{
	return 0; // should be overwritten in the child classes
}
void NDHist::Fill(std::vector<double> x)
{
	if(!this->CheckDim(x.size()))
		throw std::runtime_error("NDHist ERROR: Datapoint has the wrong dimension.");
	int bin = this->FindBin(x); // make sure you get the function from the right class
	if(bin < 0)
		under++;
	else if(bin >= nbins)
		over++;
	else
		bincontent[bin]++;
}
double NDHist::Eval(std::vector<double> x)
{
	return bincontent[FindBin(x)];
}
void NDHist::Clear()
{
	for(auto &binc: bincontent)
		binc = 0;
	under = 0;
	over = 0;
}
double NDHist::MaxBinContent()
{
	double maxbincontent = bincontent[0];
	for(auto binc: bincontent)
		if(binc > maxbincontent)
			maxbincontent = binc;
	return maxbincontent;
}
double NDHist::MinBinContent()
{
	double minbincontent = bincontent[0];
	for(auto binc: bincontent)
		if(binc < minbincontent)
			minbincontent = binc;
	return minbincontent;
}
TH1D* NDHist::BinContentHist()
{
	return BinContentHist("BinContentHist");
}
TH1D* NDHist::BinContentHist(std::string name)
{
	TH1D* hist = new TH1D(name.c_str(),"",100,MinBinContent(),MaxBinContent());
	for(auto binc: bincontent)
		hist->Fill(binc);
	return hist;
}

// Arithmetic with histograms
bool NDHist::Add(const NDHist& other)
{
	return Arithmetic(other,0);
}
bool NDHist::Subtract(const NDHist& other)
{
	return Arithmetic(other,1);
}
bool NDHist::Multiply(const NDHist& other)
{
	return Arithmetic(other,2);
}
bool NDHist::Divide(const NDHist& other)
{
	return Arithmetic(other,3);
}
bool NDHist::IsCompatible(const NDHist& other)
{
	return nbins == other.nbins;
}
bool NDHist::Arithmetic(const NDHist& other,int op)
{
	if(!IsCompatible(other))
		throw std::runtime_error("NDHist ERROR: Histograms must have the same ranges and binning schemes to do arithmetic.");
	switch(op)
	{
		case 0:
			for(int ibin = nbins; ibin-->0;)
				bincontent[ibin] += other.bincontent[ibin];
			under += other.under;
			over += other.over;
			break;
		case 1:
			for(int ibin = nbins; ibin-->0;)
				bincontent[ibin] -= other.bincontent[ibin];
			under -= other.under;
			over -= other.over;
			break;
		case 2:
			for(int ibin = nbins; ibin-->0;)
				bincontent[ibin] *= other.bincontent[ibin];
			under *= other.under;
			over *= other.over;
			break;
		case 3:
			for(int ibin = nbins; ibin-->0;)
				bincontent[ibin] /= other.bincontent[ibin];
			under /= other.under;
			over /= other.over;
			break;
		default:
			return false;
	}
	return true;
}
void NDHist::Print()
{
	for(auto binc: bincontent)
		std::cout << binc << std::endl;
}
double NDHist::Integral()
{
	double sum = 0;
	for(auto binc: bincontent)
		sum+=binc;
	return sum;
}
bool NDHist::CheckDim(unsigned ndims)
{
	return true;
}
