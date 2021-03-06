#include "GetTree.h"
#include "TCollection.h"
#include "TKey.h"
#include "TDirectoryFile.h"
#include <iostream>
#include <stdexcept>
#include <vector>
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
using std::vector;
/*****************************************************************************/
// Overloading the function with all reasonable ways you might want to call it
TTree* GetTree(string filename)
{
	cout << "Opening " << filename << endl;
	TTree* tree = GetTree(TFile::Open(filename.c_str()), "");
	return tree;
}
TTree* GetTree(TFile* file)
{
	TTree* tree = GetTree(file, "");
	return tree;
}
TTree* GetTree(string filename, string cutstring)
{
	cout << "Opening " << filename << endl;
	TTree* tree = GetTree(TFile::Open(filename.c_str()), new TCut(cutstring.c_str()));
	return tree;
}
TTree* GetTree(TFile* file, string cutstring)
{
	TTree* tree = GetTree(file, new TCut(cutstring.c_str()));
	return tree;
}
TTree* GetTree(string filename, TCut* cut)
{
	cout << "Opening " << filename << endl;
	TTree* tree = GetTree(TFile::Open(filename.c_str()), cut);
	return tree;
}
/*****************************************************************************/
TTree* GetTree(TFile* file, TCut* cut)
{
	string filename = (string)file->GetName();
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
		if(tree != NULL) break;
		if(name == treenames.back()) planB = true;
	}
	if(planB)
	{
		cout << "Warning: tree with standard name not found. Attempting a search." << endl;
		TIter next = file->GetListOfKeys();
		TKey* key;
		TDirectoryFile* directory;
		// Look for any tree or directory in the file
		int object_counter = 0;
		while((key = (TKey*)next()))
		{
			object_counter++;
			cout << "Object #" << object_counter << " is a " << key->GetClassName() << endl;
			if(strcmp(key->GetClassName(),"TTree")==0)
			{
				// OK, great, you've found a tree. Let's go.
				tree = (TTree*)key->ReadObj();
				break;
			}
			else if(strcmp(key->GetClassName(),"TDirectoryFile")==0)
			{
				// Well, you've found a first-level directory.
				// Maybe there's a tree in here.
				directory = (TDirectoryFile*)key->ReadObj();
				TIter dirnext = directory->GetListOfKeys();
				TKey* dirkey;
				// Look for any tree in the directory.
				while((dirkey = (TKey*)dirnext()))
				{
					object_counter++;
					cout << "Object #" << object_counter << " in the directory " << key->GetName() << " is a " << dirkey->GetClassName() << endl;
					// Found a tree in a first-level directory.
					if(strcmp(dirkey->GetClassName(),"TTree")==0)
					{
						// OK, great, you've found a tree. Let's go.
						tree = (TTree*)dirkey->ReadObj();
						break;
					}
				}
			}
			if(tree != NULL) break;
		}
		cout << "I looked at " << object_counter << " objects" << endl;
		if(tree == NULL) throw runtime_error("Couldn't find tree");
	}
	cout << "Tree found with name " << tree->GetName() << endl;
	if(!((string)cut->GetTitle()).empty())
	{
		size_t mode_start = filename.find('/')==string::npos ? 0 : filename.find_last_of('/') + 1;
		string tempfilename = "/tmp/GetTree_"+filename.substr(mode_start);
		cout << "Making temporary file " << tempfilename << endl;
		TFile* tempfile = new TFile(tempfilename.c_str(),"RECREATE");
		tempfile->cd();
		cout << "Cutting tree." << endl;
		return tree->CopyTree(*cut);
	}
	else
	{
		return tree;
	}
}

