#include "confirmationOrder.h"

namespace seneca
{
	void ConfirmationOrder::clear()
	{
		// Only the pointer array is ours to release; the Toy objects
		// themselves are owned elsewhere (aggregation).
		delete[] m_toys;
		m_toys = nullptr;
		m_count = 0;
	}

	void ConfirmationOrder::copyFrom(const ConfirmationOrder& src)
	{
		m_count = src.m_count;
		if (m_count == 0)
		{
			m_toys = nullptr;
			return;
		}
		m_toys = new const Toy * [m_count];
		for (size_t i = 0; i < m_count; ++i)
			m_toys[i] = src.m_toys[i];   // copy the address only, not the Toy
	}

	ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder& src)
	{
		copyFrom(src);
	}

	ConfirmationOrder::ConfirmationOrder(ConfirmationOrder&& src) noexcept
		: m_toys{ src.m_toys }, m_count{ src.m_count }
	{
		src.m_toys = nullptr;
		src.m_count = 0;
	}

	ConfirmationOrder& ConfirmationOrder::operator=(const ConfirmationOrder& src)
	{
		if (this != &src)
		{
			clear();
			copyFrom(src);
		}
		return *this;
	}

	ConfirmationOrder& ConfirmationOrder::operator=(ConfirmationOrder&& src) noexcept
	{
		if (this != &src)
		{
			clear();
			m_toys = src.m_toys;
			m_count = src.m_count;
			src.m_toys = nullptr;
			src.m_count = 0;
		}
		return *this;
	}

	ConfirmationOrder::~ConfirmationOrder()
	{
		clear();
	}

	ConfirmationOrder& ConfirmationOrder::operator+=(const Toy& toy)
	{
		for (size_t i = 0; i < m_count; ++i)
			if (m_toys[i] == &toy)
				return *this;   // already present

		const Toy** newArr = new const Toy * [m_count + 1];
		for (size_t i = 0; i < m_count; ++i)
			newArr[i] = m_toys[i];
		newArr[m_count] = &toy;

		delete[] m_toys;
		m_toys = newArr;
		++m_count;
		return *this;
	}

	ConfirmationOrder& ConfirmationOrder::operator-=(const Toy& toy)
	{
		size_t idx = m_count;
		for (size_t i = 0; i < m_count; ++i)
			if (m_toys[i] == &toy)
			{
				idx = i;
				break;
			}

		if (idx == m_count)
			return *this;   // not found

		if (m_count == 1)
		{
			delete[] m_toys;
			m_toys = nullptr;
			m_count = 0;
			return *this;
		}

		const Toy** newArr = new const Toy * [m_count - 1];
		for (size_t i = 0, j = 0; i < m_count; ++i)
			if (i != idx)
				newArr[j++] = m_toys[i];

		delete[] m_toys;
		m_toys = newArr;
		--m_count;
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order)
	{
		os << "--------------------------\n";
		os << "Confirmations to Send (" << order.m_count << " toys)\n";
		os << "--------------------------\n";

		if (order.m_count == 0)
			os << "There are no confirmations to send!\n";
		else
			for (size_t i = 0; i < order.m_count; ++i)
				os << *order.m_toys[i];

		os << "--------------------------\n";
		return os;
	}
}
