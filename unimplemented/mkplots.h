#include "TCanvas.h"
#include "TSystem.h"
#include <string>
#include <sstream>

void mkplots(TCanvas* canv, string filename)
{
    stringstream epsfilename, pngfilename;
    epsfilename << filename << ".eps";
    pngfilename << filename << ".png";
    canv->Print(epsfilename.str().c_str());
    canv->Print(pngfilename.str().c_str());
    gSystem->Setenv("FILE",filename.c_str());
    gSystem->Exec("epstopdf $FILE.eps");
    gSystem->Exec("rm $FILE.eps");
    gSystem->Exec("convert $FILE.pdf $FILE.eps");
    gSystem->Unsetenv("FILE");
}
