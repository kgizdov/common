#ifndef __SAFELOG_H__
#define __SAFELOG_H__
#include <cmath>
float safeLog(float x)
{
	// Keep numbers in a sensible range for the sake of MVA training
	if(x > std::exp(-25)) return std::log(x);
	else return -25;
}

namespace safe
{
	template<typename T>
	T log(T x, T low_bound = static_cast<T>(-INFINITY))
	{
		if (x > std::exp(low_bound))
		{
			return std::log(x);
		}
		return low_bound;
	}
}  // namespace safe

#endif
