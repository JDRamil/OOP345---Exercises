#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H

#include <iostream>
#include <string>
#include <cstddef>
#include "toy.h"

namespace seneca
{
	/// <summary>
	/// A child's shopping cart: a name, an age, and a COMPOSITION of Toys
	/// (the cart owns its own deep copies, so it manages their lifetime).
	/// </summary>
	class ShoppingCart
	{
		std::string m_name{};
		int         m_age{};
		const Toy** m_toys{ nullptr };
		size_t      m_count{};

		void clear();
		void copyFrom(const ShoppingCart& src);

	public:
		ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);

		ShoppingCart(const ShoppingCart& src);
		ShoppingCart(ShoppingCart&& src) noexcept;
		ShoppingCart& operator=(const ShoppingCart& src);
		ShoppingCart& operator=(ShoppingCart&& src) noexcept;
		~ShoppingCart();

		friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart);
	};
}

#endif
