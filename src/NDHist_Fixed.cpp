#include "NDHist_Fixed.h"
#include "itoa.h"
#include <stdexcept>
#include <assert.h>
NDHist_Fixed::NDHist_Fixed(const TH1& hist)
	: NDHist()
{
	int ndim = hist.GetDimension();
	switch(ndim)
	{
		case 1:
			axes = {*hist.GetXaxis()};
			Initialise({hist.GetNbinsX()});
			break;
		case 2:
			axes = {*hist.GetXaxis(),*hist.GetYaxis()};
			Initialise({hist.GetNbinsX()*hist.GetNbinsY()});
			break;
		case 3:
			axes = {*hist.GetXaxis(),*hist.GetYaxis(),*hist.GetZaxis()};
			Initialise({hist.GetNbinsX()*hist.GetNbinsY()*hist.GetNbinsZ()});
			break;
		default:
			throw std::out_of_range("NDHist_Fixed ERROR: This ROOT histogram claims to be neither 1D, 2D nor 3D.");
	}
	under = hist.GetBinContent(0);
	over = hist.GetBinContent(nbins+1);
	// Loop over bins in the hist object. I have no idea if my global bin number scheme is the same as in ROOT, however I do know that the TAxis objects are the same.
	for(int histbin = nbins; histbin-->0;)
	{
		int localbin, binx, biny, binz;
		// Decompose the current index of the loop into TAxis indices
		hist.GetBinXYZ(histbin, binx, biny, binz);
		// Convert the TAxis indices to a global bin number in my scheme
		switch(ndim)
		{
			case 1:
				localbin = GetBin({binx});
				break;
			case 2:
				localbin = GetBin({binx,biny});
				break;
			case 3:
				localbin = GetBin({binx,biny,binz});
				break;
			default:
				throw std::out_of_range("NDHist_Fixed ERROR: This ROOT histogram claims to be neither 1D, 2D nor 3D. Something is really weird.");
		}
		bincontent[localbin] = hist.GetBinContent(histbin+1);
	}
}
NDHist_Fixed::NDHist_Fixed(const std::vector<std::tuple<int,double,double>>& params)
	: NDHist()
{
	std::vector<int> nbinsx;
	for(auto param : params)
	{
		int nb = std::get<0>(param);
		double xlo = std::get<1>(param);
		double xhi = std::get<2>(param);
		nbinsx.push_back(nb);
		axes.push_back(TAxis(nb, xlo, xhi));
	}
	Initialise(nbinsx);
}
NDHist_Fixed::NDHist_Fixed(const std::vector<std::tuple<int,double*>>& params)
	: NDHist()
{
	std::vector<int> nbinsx;
	for(auto param : params)
	{
		int nb = std::get<0>(param);
		double* xbs = std::get<1>(param);
		nbinsx.push_back(nb);
		axes.push_back(TAxis(nb, xbs));
	}
	Initialise(nbinsx);
}
void NDHist_Fixed::Initialise(const std::vector<int>& nbins_axes)
{
	nbins = 1;
	for(auto nbinsx : nbins_axes)
	{
		nbins *= nbinsx;
		if(!nbinsx)
			throw std::out_of_range("NDHist_Fixed ERROR: Can't have 0 bins in any dimension.");
	}
	for(int ibin = nbins; ibin-->0;)
		bincontent.push_back(0);
	Clear();
	for(unsigned idim = axes.size(); idim-->0;)
		axes[idim].SetNameTitle(("ax"+itoa(idim)).c_str(),("Axis "+itoa(idim)).c_str());
}
// Copy constructor
NDHist_Fixed::NDHist_Fixed(const NDHist_Fixed& orig)
	: NDHist((NDHist)orig)
	, axes(orig.axes)
{
}
// Names
void NDHist_Fixed::SetAxisNames(const std::vector<std::string>& names)
{
	if(!CheckDim(names.size()))
		throw std::runtime_error("NDHist_Fixed ERROR: Number of names doesn't match number of axes.");
	for(unsigned idim = axes.size(); idim-->0;)
		axes[idim].SetName(names[idim].c_str());
}
// Titles
void NDHist_Fixed::SetAxisTitles(const std::vector<std::string>& titles)
{
	if(!CheckDim(titles.size()))
		throw std::runtime_error("NDHist_Fixed ERROR: Number of titles doesn't match number of axes.");
	for(unsigned idim = axes.size(); idim-->0;)
		axes[idim].SetTitle(titles[idim].c_str());
}
// Find a bin
int NDHist_Fixed::FindBin(const std::vector<double>& x) const
{
	std::vector<int> binx;
	for(auto& axis : axes)
	{
		int bin = axis.FindBin(x[&axis - &axes[0]]) - 1;
		binx.push_back(bin);
		if(bin < 0)
			return -1; // underflow
		else if(bin >= axis.GetNbins())
			return nbins; // overflow
	}
	return GetBin(binx);
}
// Get overall bin index from individual axis indices
int NDHist_Fixed::GetBin(const std::vector<int>& binx) const
{
//	return binw + waxis.GetNbins() * (binx + xaxis.GetNbins() * (biny + yaxis.GetNbins() * (binz)));
	if(!CheckDim(binx.size()))
		throw std::runtime_error("NDHist_Fixed ERROR: Number of bin indices does not match number of axes.");
	int bin = binx.back(); // Start with the nth dimension
	for(unsigned idim = axes.size()-1; idim-->0;) // Loop from (n-1)th dimension to first
		bin = binx[idim] + axes[idim].GetNbins() * bin;
	return bin;
}
// Comparison of bins and ranges to allow arithmetic
bool NDHist_Fixed::IsCompatible(const NDHist_Fixed& other) const
{
	if(nbins != other.nbins || !CheckDim(other.axes.size()))
		return false;
	bool compatability = true;
	for(unsigned idim = axes.size(); idim-->0;)
		compatability = compatability && axes[idim].GetNbins() == other.axes[idim].GetNbins()
		                              && axes[idim].GetXmin()  == other.axes[idim].GetXmin()
		                              && axes[idim].GetXmax()  == other.axes[idim].GetXmax();
	return compatability;
}

