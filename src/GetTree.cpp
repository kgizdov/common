#include "GetTree.h"
#include "TCollection.h"
#include "TKey.h"
#include "TDirectoryFile.h"
#include <stdexcept>
#include <vector>
using namespace std;
/*****************************************************************************/
// Overloading the function with all reasonable ways you might want to call it
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
/*****************************************************************************/
TTree* GetTree(TFile* file, TCut* cut)
{
  TFile* tempfile = new TFile("/tmp/temp.root","RECREATE");
  tempfile->cd();
  TTree* tree;
  // This list can be freely extended without having to alter any other lines
  vector<string> treenames = {"DecayTreeTuple/DecayTree"
                             ,"DecayTree"
                             ,"MCDecayTreeTuple/MCDecayTree"
                             ,"MCDecayTree"};
  bool planB = false;
  for(auto name: treenames) // C++11 magic
  {
    // Look for a tree with a name in the list
    tree = (TTree*)file->Get(name.c_str());
    if(tree != (TTree*)0x0) break;
    if(name == treenames.back()) planB = true;
  }
  if(planB)
  {
    printf("Warning: tree with standard name not found. Attempting a search.\n");

    TIter next = file->GetListOfKeys();
    TKey* key;
    TDirectoryFile* directory;
    // Look for any tree or directory
    while((key = (TKey*)next()))
    {
      if(strcmp(key->GetClassName(),"TTree")==0)
      {
        tree = (TTree*)key->ReadObj();
        break;
      }
      else if(strcmp(key->GetClassName(),"TDirectoryFile")==0)
      {
        directory = (TDirectoryFile*)key->ReadObj();
        TIter dirnext = directory->GetListOfKeys();
        TKey* dirkey;
        // Look for any tree in the directory
        while((dirkey = (TKey*)dirnext()))
        {
          tree = (TTree*)key->ReadObj();
        }
      }
      if(tree != (TTree*)0x0) break;
    }
    if(tree == (TTree*)0x0) throw runtime_error("Couldn't find tree.");
    else printf("Tree found with name '%s'\n",tree->GetName());
  }
  return tree->CopyTree(*cut);
}

