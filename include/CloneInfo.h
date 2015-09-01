#ifndef __CLONEINFO_H__
#define __CLONEINFO_H__
using namespace std;
class CloneInfo
{
public:
  CloneInfo();
  CloneInfo(int i_key1, int i_key2, int i_key3, int i_key4, int i_i);
  CloneInfo(const CloneInfo& cl);
  ~CloneInfo();
  bool isAlive();
  int i() const;
  void setDead();
  int key1();
  int key2();
  int key3();
  int key4();
  int sum() const;
  class Less_by_sum;
private:
  int m_key1;
  int m_key2;
  int m_key3;
  int m_key4;
  int m_i;
  bool m_isAlive;
};

class CloneInfo::Less_by_sum
{
  public:
    bool operator() (const CloneInfo&, const CloneInfo&) const;
};
#endif
