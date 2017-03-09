#ifndef __ITOA_H__
#define __ITOA_H__
#include <sstream>
#include <string>
using std::string;
using std::stringstream;
// Convert integer to string.
string itoa(int value)
{
	stringstream temp;
	temp << value;
	return temp.str();
}
#endif
