#ifndef __ITOA_H__
#define __ITOA_H__
#include <sstream>
#include <string>
using namespace std;
// Convert integer to string.
string itoa(int value)
{
  stringstream temp;
  temp << value;
  return temp.str();
}
#endif
