#ifndef __SAFELOG_H__
#define __SAFELOG_H__
#include <cmath>
#include <type_traits>
float safeLog(float x)
{
	// Keep numbers in a sensible range for the sake of MVA training
	if(x > std::exp(-25)) return std::log(x);
	else return -25;
}

namespace safe
{
	template<typename T>
	auto log(T x, long double low_bound = static_cast<long double>(-INFINITY))
	{
		typedef typename std::conditional<std::is_integral<T>::value, double, T>::type _type;
		if (x > std::exp(low_bound))
		{
			return std::log(x);
		}
		return static_cast<_type>(low_bound);
	}
}  // namespace safe

#endif
