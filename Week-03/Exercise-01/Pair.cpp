#include "Pair.h"
#include <iomanip>

namespace seneca
{
	bool Pair::operator==(const Pair& other) const
	{
		return m_key == other.m_key;
	}

	std::ostream& operator<<(std::ostream& os, Pair& p)
	{
		os << std::setw(20) << p.getKey() << ": " << p.getValue();
		return os;
	}

	template<>
	Pair Collection<Pair, 100>::stat{ "No Key", "No Value" };
}
