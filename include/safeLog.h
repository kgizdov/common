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
	float log(int x, float low_bound = -INFINITY)
	{
		if (x > std::exp(low_bound))
		{
			return std::log(x);
		}
		return low_bound;
	}
	float log(float x, float low_bound = -INFINITY)
	{
		if (x > std::exp(low_bound))
		{
			return std::log(x);
		}
		return low_bound;
	}
	double log(double x, double low_bound = -INFINITY)
	{
		if (x > std::exp(low_bound))
		{
			return std::log(x);
		}
		return low_bound;
	}
	long double log(long double x, long double low_bound = -INFINITY)
	{
		if (x > std::exp(low_bound))
		{
			return std::log(x);
		}
		return low_bound;
	}
}  // namespace safe

#endif
