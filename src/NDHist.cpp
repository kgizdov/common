// Self
#include "NDHist.h"
// std
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
	if(spline!=NULL) delete spline;
}
std::vector<double> NDHist::GetBinCentre(int ibin)
{
	std::vector<double> centre;
	while(!CheckDim(centre.size()))
		centre.push_back(0);
	return centre;
}
void NDHist::Fill(std::vector<double> x)
{
	if(!CheckDim(x.size()))
		throw std::runtime_error("NDHist ERROR: Datapoint has the wrong dimension.");
	int bin = FindBin(x);
	if(bin < 0)
		under++;
	else if(bin >= nbins)
		over++;
	else
		bincontent[bin]++;
}
double NDHist::Interpolate(std::vector<double> x)
{
	if(!CheckDim(x.size()))
		throw std::runtime_error("NDHist ERROR: Datapoint has the wrong dimension.");
	if(spline == NULL) BuildSpline();
	return spline->eval(x);
}
void NDHist::Clear()
{
	// Set the content of all bins to zero
	for(auto &binc: bincontent)
		binc = 0;
	under = 0;
	over = 0;
}
TH1D* NDHist::BinContentHist(std::string name)
{
	TH1D* hist = new TH1D(name.c_str(),"",100,MinBinContent(),MaxBinContent());
	for(auto binc: bincontent)
		hist->Fill(binc);
	return hist;
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
