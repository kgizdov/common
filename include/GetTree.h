#ifndef __GETTREE_H__
#define __GETTREE_H__
#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
using std::string;
TTree* GetTree(string);
TTree* GetTree(TFile*);
TTree* GetTree(string, string);
TTree* GetTree(TFile*, string);
TTree* GetTree(string, TCut*);
TTree* GetTree(TFile*, TCut*);
#endif
