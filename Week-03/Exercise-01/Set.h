#ifndef SENECA_SET_H
#define SENECA_SET_H

#include "Collection.h"
#include <cmath>

namespace seneca
{
	/// <summary>
	/// A Collection (fixed capacity of 100) where no item appears more than once.
	/// </summary>
	template <typename T>
	class Set : public Collection<T, 100>
	{
	public:
		bool add(const T& item) override
		{
			for (size_t i = 0; i < this->size(); ++i)
				if ((*this)[i] == item)
					return false;
			return Collection<T, 100>::add(item);
		}
	};

	// Specialization: two doubles are considered the same item if they
	// differ by 0.01 or less.
	template <>
	inline bool Set<double>::add(const double& item)
	{
		for (size_t i = 0; i < size(); ++i)
			if (std::fabs((*this)[i] - item) <= 0.01)
				return false;
		return Collection<double, 100>::add(item);
	}
}

#endif
