#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H

#include <iostream>
#include <cstddef>
#include "toy.h"

namespace seneca
{
	/// <summary>
	/// Holds the list of toys waiting for parental approval. This is an
	/// AGGREGATION: it manages the array of pointers, but does NOT own the
	/// lifetime of the Toy objects it points to (never new's/delete's a Toy).
	/// </summary>
	class ConfirmationOrder
	{
		const Toy** m_toys{ nullptr };
		size_t      m_count{};

		void clear();
		void copyFrom(const ConfirmationOrder& src);

	public:
		ConfirmationOrder() = default;

		ConfirmationOrder(const ConfirmationOrder& src);
		ConfirmationOrder(ConfirmationOrder&& src) noexcept;
		ConfirmationOrder& operator=(const ConfirmationOrder& src);
		ConfirmationOrder& operator=(ConfirmationOrder&& src) noexcept;
		~ConfirmationOrder();

		/// <summary>Adds the address of `toy` if not already present (resizes as needed).</summary>
		ConfirmationOrder& operator+=(const Toy& toy);

		/// <summary>Removes the address of `toy` if present, shifting later elements left.</summary>
		ConfirmationOrder& operator-=(const Toy& toy);

		friend std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order);
	};
}

#endif
