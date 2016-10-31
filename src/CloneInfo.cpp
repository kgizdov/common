#include "CloneInfo.h"
using namespace std;
CloneInfo::CloneInfo(vector<int> _keys, int _i, double _q) :
	m_keys(_keys),
	m_i(_i),
	m_q(_q),
	m_isAlive(true)
{
}
CloneInfo::CloneInfo(const CloneInfo& cl) :
	m_keys(cl.m_keys),
	m_i(cl.m_i),
	m_q(cl.m_q),
	m_isAlive(cl.m_isAlive)
{
}
CloneInfo::~CloneInfo()
{
}
bool CloneInfo::isAlive()
{
	return m_isAlive;
}
int CloneInfo::i() const
{
	return m_i;
}
double CloneInfo::q() const
{
	return m_q;
}
void CloneInfo::setDead()
{
	m_isAlive = false;
}
int CloneInfo::GetKey(int i) const
{
	return m_keys[i];
}
bool CloneInfo::operator== (const CloneInfo& c2) const
{
	return *this % c2 == m_keys.size();
}
bool CloneInfo::operator>  (const CloneInfo& c2) const
{
	return m_q>c2.m_q;
}
bool CloneInfo::operator>= (const CloneInfo& c2) const
{
	return m_q>=c2.m_q;
}
bool CloneInfo::operator<  (const CloneInfo& c2) const
{
	return m_q<c2.m_q;
}
bool CloneInfo::operator<= (const CloneInfo& c2) const
{
	return m_q<=c2.m_q;
}
unsigned CloneInfo::operator%  (const CloneInfo& c2) const
{
	unsigned n = 0;
	for(auto key : m_keys)
	{
		for(auto key2 : c2.m_keys)
		{
			if(key == key2)
			{
				n++;
				break;
			}
		}
	}
	// Return number that are same
	return n;
}
bool CloneInfo::ascending::operator() (const CloneInfo& c1, const CloneInfo& c2) const
{
	return c1 < c2;
}
bool CloneInfo::descending::operator() (const CloneInfo& c1, const CloneInfo& c2) const
{
	return c1 > c2;
}

