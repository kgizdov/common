#ifndef __CLONETAGGER_H__
#define __CLONETAGGER_H__
#include "CloneInfo.h"
#include <vector>
using namespace std;
class CloneTagger
{
private:
	vector<CloneInfo>& clones;
public:
	CloneTagger(vector<CloneInfo>&);
	CloneTagger();
	~CloneTagger();
	void tagClone(CloneInfo&, CloneInfo&);
	void tagClones();
	void sortClones(bool asc = true);
	void addToClones(vector<int>, int, double);
	void addToClones(CloneInfo&);
};
#endif
