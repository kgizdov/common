#include "CloneTagger.h"
#include <algorithm>
using namespace std;
CloneTagger::CloneTagger(vector<CloneInfo>& i_clones) :
	clones(i_clones)
{
}
CloneTagger::~CloneTagger()
{
}
void CloneTagger::tagClone(CloneInfo& c1, CloneInfo& c2)
{
	if (c1 % c2 != 0)
	{
		c2.setDead();
	}
}
void CloneTagger::tagClones()
{
	vector<CloneInfo>::iterator iter = clones.begin();
	for(;iter != clones.end(); ++iter)
	{
		if(iter->isAlive())
		{
		vector<CloneInfo>::iterator iter2 = iter+1;
			for(;iter2 != clones.end(); ++iter2)
			{
				tagClone(*iter, *iter2);
			}
		}
	}
}
void CloneTagger::sortClones(bool asc)
{
	if(asc)
		sort(clones.begin(), clones.end(), CloneInfo::ascending());
	else
		sort(clones.begin(), clones.end(), CloneInfo::descending());
}
void CloneTagger::addToClones(vector<int> keys, int i, double q)
{
	CloneInfo tclone = CloneInfo(keys, i, q);
	addToClones(tclone);
}
void CloneTagger::addToClones(CloneInfo& tclone)
{
	clones.push_back(tclone);
}
