#ifndef __CLONEINFO_H__
#define __CLONEINFO_H__
#include <vector>
using namespace std;
class CloneInfo
{
public:
/*	CloneInfo();*/
	CloneInfo(vector<int>, int, double);
	CloneInfo(const CloneInfo&);
	~CloneInfo();
	bool isAlive();
	int i() const;
	double q() const;
	void setDead();
	int GetKey(int) const;
	bool operator==(const CloneInfo&) const; // do these share track keys?
	// compare "quality" variable
	bool operator> (const CloneInfo&) const;
	bool operator>=(const CloneInfo&) const;
	bool operator< (const CloneInfo&) const;
	bool operator<=(const CloneInfo&) const;
	// returns the number of track keys that are the same
	unsigned operator% (const CloneInfo&) const;
	struct ascending;
	struct descending;
protected:
	vector<int> m_keys;
	int m_i;
	double m_q;
	bool m_isAlive;
};
struct CloneInfo::ascending
{
	bool operator() (const CloneInfo&, const CloneInfo&) const;
};
struct CloneInfo::descending
{
	bool operator() (const CloneInfo&, const CloneInfo&) const;
};
#endif
