#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <cstddef>

namespace seneca
{
	/// <summary>
	/// Manages a statically allocated array of up to CAPACITY elements of type T.
	/// </summary>
	template <typename T, size_t CAPACITY>
	class Collection
	{
	protected:
		T m_arr[CAPACITY]{};
		size_t m_size{};

	public:
		// The object returned when the client asks for an element that
		// doesn't exist in the collection.
		static T stat;

		Collection() = default;
		virtual ~Collection() = default;

		size_t size() const
		{
			return m_size;
		}

		virtual bool add(const T& item)
		{
			if (m_size >= CAPACITY)
				return false;
			m_arr[m_size++] = item;
			return true;
		}

		T operator[](size_t index) const
		{
			if (index >= m_size)
				return stat;
			return m_arr[index];
		}

		void display(std::ostream& os = std::cout)
		{
			os << "----------------------\n";
			os << "| Collection Content |\n";
			os << "----------------------\n";
			for (size_t i = 0; i < m_size; ++i)
				os << m_arr[i] << '\n';
			os << "----------------------\n";
		}
	};

	template <typename T, size_t CAPACITY>
	T Collection<T, CAPACITY>::stat{};
}

#endif
