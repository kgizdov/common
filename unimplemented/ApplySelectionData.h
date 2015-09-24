#include <string>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TChain.h"
#include "TMath.h"
/* 
*  Example of how to write a reduced ntuple
*  Two selections, Matts (add on to roadmap):
*  Use: .L ApplySelection.C+
*        ApplySelection("theFile.root")
* Giving extra arguments allows to change ntuple and output name
*        ApplySelection("EtaDown.root", "rhoGammaDown/rhoGammaDown", "_Selected.root");
*/ 


/** First some helpers to avoid duplicating code */

std::string createOutputName(std::string& name, std::string& trailer){
  // helper for making the output name
  std::string outputName = name.substr(0,name.size() - 5);
  outputName += trailer;
  return outputName;
}

TFile* openOutput(std::string& tree, std::string& input, std::string& output) {
  // helper for opening the file
  TFile* outFile  =new TFile(output.c_str(),"RECREATE");
  std::cout << "Reading: " << tree << " from " << input  << " to " << output << std::endl;
  return outFile;
}

void finalize(TTree* cutTree, TFile* output){
  // helper for finalizing
  TTree*  newtree = cutTree->CloneTree(-1);
  newtree->Write();
  output->Close();
}

/* Now the main business */

std::string ApplySelectionData(std::string fileName, std::string treeName, std::string trailer,std::string cutString){

  // Matts selection, generally applied on top of the road map

  // get the input
  TChain* decaytree = new TChain(treeName.c_str());
  decaytree->Add(fileName.c_str());
	
  // make the output file name 
  std::string outputName = createOutputName(fileName, trailer);;
 
  // make the output file
  TFile* outFile = openOutput(treeName,fileName,outputName); 
 
  //&& (hlt2JPsiDetached || hlt2JPsi) && (hlt1DiMuonHighMass || hlt1TrackMuon || hlt1TrackAllL) && (l0Muon || l0DiMuon )
  
  // && ipk1 > 4 && ipk2 >4 && ipk3 >4 && PT > 2000 && sqrt(px3*px3 + py3*py3) > 200 && sqrt(px4*px4 + py4*py4) > 200  && sqrt(px4*px4 + py4*py4) > 200 " ; 
  TCut cut = cutString.c_str();

  TTree* smalltree = decaytree->CopyTree(cut);
  finalize(smalltree,outFile);  

  return outputName;
}

