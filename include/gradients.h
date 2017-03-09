#ifndef __GRADIENTS_H__
#define __GRADIENTS_H__
#include "TColor.h"
#include "TStyle.h"
void rainbowgradient()
{
	const int NRGBs = 7;
	const int NCont = 255;
	double stops[NRGBs] = { 0.00, 0.20, 0.40, 0.50, 0.60, 0.80, 1.00 };
	double red[NRGBs]   = { 0.00, 0.00, 0.00, 0.00, 1.00, 1.00, 0.50 };
	double green[NRGBs] = { 0.00, 0.00, 1.00, 1.00, 1.00, 0.00, 0.00 };
	double blue[NRGBs]  = { 0.50, 1.00, 1.00, 0.00, 0.00, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	return;
}

void greyscalegradient()
{
	const int NRGBs = 3;
	const int NCont = 10;
	double stops[NRGBs] = { 0.00, 0.90, 1.00 };
	double red[NRGBs]   = { 0.00, 1.00, 1.00 };
	double green[NRGBs] = { 0.00, 1.00, 1.00 };
	double blue[NRGBs]  = { 0.00, 1.00, 1.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	return;
}

void redbluegradient()
{

	const int NRGBs = 3;
	const int NCont = 255;
	double stops[NRGBs] = { 0.00, 0.50, 1.00 };
	double red[NRGBs]   = { 0.00, 1.00, 1.00 };
	double green[NRGBs] = { 0.00, 1.00, 0.00 };
	double blue[NRGBs]  = { 1.00, 1.00, 0.00 };

	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	return;
}

void heatmapgradient()
{
	const int NRGBs = 6;
	const int NCont = 255;
	double stops[NRGBs] = { 0.00, 0.25, 0.50, 0.80, 0.90, 1.00 };
	double red[NRGBs]   = { 0.00, 0.00, 0.60, 1.00, 1.00, 1.00 };
	double green[NRGBs] = { 0.00, 0.00, 0.00, 0.75, 1.00, 1.00 };
	double blue[NRGBs]  = { 0.00, 0.70, 0.60, 0.00, 0.00, 0.00 };

	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	return;
}
void heatmapRB()
{
	const int NRGBs = 4;
	const int NCont = 255;
	double stops[NRGBs] = { 0.00, 0.50, 0.90, 1.00};
	double red[NRGBs]   = { 0.00, 0.25, 1.00, 1.00};
	double green[NRGBs] = { 0.00, 0.00, 0.00, 0.00};
	double blue[NRGBs]  = { 0.50, 0.75, 0.00, 0.00};

	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	return;
}
void DarkBodyRadiator()
{
	const int NRGBs = 3;
	const int NCont = 255;
	double stops[NRGBs] = { 0.00, 0.50, 0.90 };
	double red[NRGBs]   = { 0.00, 1.00, 1.00 };
	double green[NRGBs] = { 0.00, 0.50, 1.00 };
	double blue[NRGBs]  = { 0.00, 0.00, 0.00 };

	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	return;
}
void DarkBodyRadiator2()
{
	const int NRGBs = 4;
	const int NCont = 255;
	double stops[NRGBs] = { 0.00, 0.30, 0.60, 0.90};
	double red[NRGBs]   = { 0.00, 1.00, 1.00, 1.00 };
	double green[NRGBs] = { 0.00, 0.50, 1.00, 1.00 };
	double blue[NRGBs]  = { 0.00, 0.00, 0.00, 1.00 };

	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	return;
}
#endif
