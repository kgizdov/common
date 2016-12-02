#include "NDHist_Fixed.h"
#include "itoa.h"
#include <stdexcept>
#include <assert.h>
NDHist_Fixed::NDHist_Fixed(std::vector<std::tuple<int,double,double>> params)
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
NDHist_Fixed::NDHist_Fixed(std::vector<std::tuple<int,double*>> params)
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
void NDHist_Fixed::Initialise(std::vector<int> nbins_axes)
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
{
	axes = orig.axes;
	nbins = orig.nbins;
	bincontent = orig.bincontent;
}
// Names
void NDHist_Fixed::SetAxisNames(std::vector<std::string> names)
{
	if(!CheckDim(names.size()))
		throw std::runtime_error("NDHist_Fixed ERROR: Number of names doesn't match number of axes.");
	for(unsigned idim = axes.size(); idim-->0;)
		axes[idim].SetName(names[idim].c_str());
}
// Titles
void NDHist_Fixed::SetAxisTitles(std::vector<std::string> titles)
{
	if(!CheckDim(titles.size()))
		throw std::runtime_error("NDHist_Fixed ERROR: Number of titles doesn't match number of axes.");
	for(unsigned idim = axes.size(); idim-->0;)
		axes[idim].SetTitle(titles[idim].c_str());
}
// Find a bin
int NDHist_Fixed::FindBin(std::vector<double> x)
{
	if(!CheckDim(x.size()))
		throw std::runtime_error("NDHist ERROR: Datapoint has the wrong dimension.");
	std::vector<int> binx;
	for(unsigned idim = axes.size(); idim-->0;)
	{
		binx.push_back(axes[idim].FindBin(x[idim])-1);
		if(binx[idim] == -1 || binx[idim] >= axes[idim].GetNbins())
			return -1;
	}
	return GetBin(binx);
}
// Get overall bin index from individual axis indices
int NDHist_Fixed::GetBin(std::vector<int> binx)
{
//	return binw + waxis.GetNbins() * (binx + xaxis.GetNbins() * (biny + yaxis.GetNbins() * (binz)));
	if(!CheckDim(binx.size()))
		throw std::runtime_error("NDHist_Fixed ERROR: Number of bin indices does not match number of axes.");
	int bin = binx.back();
	for(unsigned idim = axes.size()-1; idim-->0;)
		bin = binx[idim] + axes[idim].GetNbins() * bin;
	return bin;
}
// Comparison of bins and ranges to allow arithmetic
bool NDHist_Fixed::IsCompatible(const NDHist_Fixed& other)
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
/* OH GOD NO
// 1D projection
TH1D* NDHist_Fixed::Project(int axisindex)
{
  assert(axisindex >= 0 && axisindex < 4);
  TH1D* hist; // the return quantity
  // Axis pointers
  TAxis* axes[] =
  {
     &waxis
    ,&xaxis
    ,&yaxis
    ,&zaxis
  };
  TAxis* projaxis
      ,* intaxis1
      ,* intaxis2
      ,* intaxis3;
  // Choose which axis is to be projected on, and which are to be integrated over.
  projaxis = axes[axisindex];
  intaxis1 = axes[(axisindex+1)%4];
  intaxis2 = axes[(axisindex+2)%4];
  intaxis3 = axes[(axisindex+3)%4];
  // Now we know the projection axis, we can make the hist object
  hist = new TH1D(("projection1D_"+(string)projaxis->GetName()).c_str(),"",projaxis->GetNbins(),projaxis->GetXmin(),projaxis->GetXmax());
  hist->GetXaxis()->SetTitle(projaxis->GetTitle());
  // Bin interators
  int binw,binx,biny,binz;
  int* bins[] =
  {
     &binw
    ,&binx
    ,&biny
    ,&binz
  };
  // Choose which iterator is assigned to which axis
  int* ibin = bins[axisindex];
  int* i1 = bins[(axisindex+1)%4];
  int* i2 = bins[(axisindex+2)%4];
  int* i3 = bins[(axisindex+3)%4];
  for(*ibin = 0; *ibin < projaxis->GetNbins(); *ibin += 1) // Use += instead of ++ because of operator precedence!
  {
    double bintegral = 0; // bin integral :)
    // Integrate over the axes that aren't being projected
    for(*i1 = 0; *i1 < intaxis1->GetNbins(); *i1 += 1)
    {
      for(*i2 = 0; *i2 < intaxis2->GetNbins(); *i2 += 1)
      {
        for(*i3 = 0; *i3 < intaxis3->GetNbins(); *i3 += 1)
        {
          bintegral += bincontent[GetBin(binw,binx,biny,binz)];
        }
      }
    }
    // Fill the 1D histogram
    hist->SetBinContent(*ibin+1,bintegral);
  }
  return hist;
}
// 2D projection
TH2D* NDHist_Fixed::Project(int axisindex1, int axisindex2)
{
  assert(axisindex1 != axisindex2);
  assert(axisindex1 >= 0 && axisindex1 < 4);
  assert(axisindex2 >= 0 && axisindex2 < 4);
  TH2D* hist; // the return quantity
  // Axis pointers
  TAxis* axes[] =
  {
     &waxis
    ,&xaxis
    ,&yaxis
    ,&zaxis
  };
  TAxis* projaxis1
      ,* projaxis2
      ,* intaxis1
      ,* intaxis2;
  // Choose which axes are to be projected on, and which are to be integrated over.
  projaxis1 = axes[axisindex1];
  projaxis2 = axes[axisindex2];
  int iaxis, iint1(0);
  for(iaxis = 0; iaxis == axisindex1 || iaxis == axisindex2; iaxis++)
    iint1 = iaxis+1;
  int iint2(iint1+1);
  for(iaxis = iint1+1; iaxis == axisindex1 || iaxis == axisindex2; iaxis++)
    iint2 = iaxis+1;
  assert(iint1 != axisindex1 && iint1 != axisindex2);
  assert(iint2 != axisindex1 && iint2 != axisindex2);
  assert(iint1 != iint2);
  assert(iint1 < 4);
  assert(iint2 < 4);
  intaxis1 = axes[iint1];
  intaxis2 = axes[iint2];
  // Now we know the projection axis, we can make the hist object
  hist = new TH2D
  (
     ("projection2D_"+(string)projaxis1->GetName()+"-"+(string)projaxis2->GetName()).c_str()
    ,""
    ,projaxis1->GetNbins(),projaxis1->GetXmin(),projaxis1->GetXmax()
    ,projaxis2->GetNbins(),projaxis2->GetXmin(),projaxis2->GetXmax()
  );
  hist->GetXaxis()->SetTitle(projaxis1->GetTitle());
  hist->GetYaxis()->SetTitle(projaxis2->GetTitle());
  // Bin interators
  int binw,binx,biny,binz;
  int* bins[] =
  {
     &binw
    ,&binx
    ,&biny
    ,&binz
  };
  // Choose which iterator is assigned to which axis
  int* ibin1 = bins[axisindex1];
  int* ibin2 = bins[axisindex2];
  int* i1 = bins[iint1];
  int* i2 = bins[iint2];
  for(*ibin1 = 0; *ibin1 < projaxis1->GetNbins(); *ibin1 += 1) // Use += instead of ++ because of operator precedence!
  {
    for(*ibin2 = 0; *ibin2 < projaxis2->GetNbins(); *ibin2 += 1)
    {
      double bintegral = 0; // bin integral :)
      // Integrate over the axes that aren't being projected
      for(*i1 = 0; *i1 < intaxis1->GetNbins(); *i1 += 1)
      {
        for(*i2 = 0; *i2 < intaxis2->GetNbins(); *i2 += 1)
        {
          bintegral += bincontent[GetBin(binw,binx,biny,binz)];
        }
      }
      // Fill the 2D histogram
      hist->SetBinContent(*ibin1+1,*ibin2+1,bintegral);
    }
  }
  return hist;
}
*/
