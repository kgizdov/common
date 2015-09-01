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
  if (c1.sum() == c2.sum())
  {
    c2.setDead();
  }
}
void CloneTagger::tagClones()
{
  vector<CloneInfo>::iterator iter = clones.begin();
  for (;iter != clones.end(); ++iter)
  {
    if (iter->isAlive() == true)
    {
    vector<CloneInfo>::iterator iter2 = iter; ++iter2;
      for (;iter2 != clones.end(); ++iter2)
      {
	      if (iter2->sum() == iter->sum())
	      {
        	iter2->setDead();
	      }
      }
    }
  }
}
void CloneTagger::sortClones()
{
  sort(clones.begin(), clones.end(), CloneInfo::Less_by_sum());
}
void CloneTagger::addToClones(int key1, int key2, int key3, int key4, int i )
{
  CloneInfo tclone = CloneInfo(key1, key2, key3, key4,  i);
  clones.push_back(tclone);
}
