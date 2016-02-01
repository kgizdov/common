#include "GetTree.h"
#include <stdexcept>
#include <vector>
using namespace std;
TTree* GetTree(string filename)
{
  TTree* tree = GetTree(new TFile(filename.c_str()), "");
  return tree;
}
TTree* GetTree(TFile* file)
{
  TTree* tree = GetTree(file, "");
  return tree;
}
TTree* GetTree(string filename, string cutstring)
{
  TTree* tree = GetTree(new TFile(filename.c_str()), new TCut(cutstring.c_str()));
  return tree;
}
TTree* GetTree(TFile* file, string cutstring)
{
  TTree* tree = GetTree(file, new TCut(cutstring.c_str()));
  return tree;
}
TTree* GetTree(string filename, TCut* cut)
{
  TTree* tree = GetTree(new TFile(filename.c_str()), cut);
  return tree;
}
TTree* GetTree(TFile* file, TCut* cut)
{
  TTree* tree;
  vector<string> treenames = {"DecayTreeTuple/DecayTree"
                             ,"DecayTree"
                             ,"MCDecayTree"};
  for(auto name: treenames) // C++11 magic
  {
    tree = (TTree*)file->Get(name.c_str());
    if(tree != (TTree*)0x0) break;
    if(name == treenames.back()) throw runtime_error("Couldn't find tree.");
  }
  return tree;
}