#include "CloneInfo.h"
using namespace std;
CloneInfo::CloneInfo(int i_key1, int i_key2, int i_key3, int i_key4, int i_i) :
  m_key1(i_key1),
  m_key2(i_key2),
  m_key3(i_key3),
  m_key4(i_key4),
  m_i(i_i),
  m_isAlive(true)
{
}
CloneInfo::CloneInfo(const CloneInfo& cl) :
  m_key1(cl.m_key1),
  m_key2(cl.m_key2),
  m_key3(cl.m_key3),
  m_key4(cl.m_key4),
  m_i(cl.m_i),
  m_isAlive(cl.m_isAlive)
{
}
CloneInfo::CloneInfo()
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
void CloneInfo::setDead()
{
  m_isAlive = false;
}
int CloneInfo::key1()
{
  return m_key1;
}
int CloneInfo::key2()
{
  return m_key2;
}
int CloneInfo::key3()
{
  return m_key3;
}
int CloneInfo::key4()
{
  return m_key4;
}
int CloneInfo::sum() const
{
  return m_key1 + m_key2 + m_key3 + m_key4;
} 
bool CloneInfo::Less_by_sum::operator() (const CloneInfo& c1, const CloneInfo& c2) const
{
  return c1.sum() < c2.sum();
}
