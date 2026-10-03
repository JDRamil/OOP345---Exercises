#include "shoppingCart.h"
#include <utility>

namespace seneca
{
	void ShoppingCart::clear()
	{
		if (m_toys)
		{
			for (size_t i = 0; i < m_count; ++i)
				delete m_toys[i];
			delete[] m_toys;
		}
		m_toys = nullptr;
		m_count = 0;
	}

	void ShoppingCart::copyFrom(const ShoppingCart& src)
	{
		if (src.m_toys == nullptr)
		{
			m_toys = nullptr;
			m_count = 0;
			return;
		}
		m_count = src.m_count;
		m_toys = new const Toy * [m_count];
		for (size_t i = 0; i < m_count; ++i)
			m_toys[i] = new Toy(*src.m_toys[i]);   // deep copy: cart owns its toys
	}

	ShoppingCart::ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count)
		: m_name{ name }, m_age{ age }, m_count{ count }
	{
		m_toys = new const Toy * [m_count];
		for (size_t i = 0; i < m_count; ++i)
			m_toys[i] = new Toy(*toys[i]);
	}

	ShoppingCart::ShoppingCart(const ShoppingCart& src)
		: m_name{ src.m_name }, m_age{ src.m_age }
	{
		copyFrom(src);
	}

	ShoppingCart::ShoppingCart(ShoppingCart&& src) noexcept
		: m_name{ std::move(src.m_name) }, m_age{ src.m_age },
		  m_toys{ src.m_toys }, m_count{ src.m_count }
	{
		src.m_toys = nullptr;
		src.m_count = 0;
	}

	ShoppingCart& ShoppingCart::operator=(const ShoppingCart& src)
	{
		if (this != &src)
		{
			clear();
			m_name = src.m_name;
			m_age = src.m_age;
			copyFrom(src);
		}
		return *this;
	}

	ShoppingCart& ShoppingCart::operator=(ShoppingCart&& src) noexcept
	{
		if (this != &src)
		{
			clear();
			m_name = std::move(src.m_name);
			m_age = src.m_age;
			m_toys = src.m_toys;
			m_count = src.m_count;
			src.m_toys = nullptr;
			src.m_count = 0;
		}
		return *this;
	}

	ShoppingCart::~ShoppingCart()
	{
		clear();
	}

	std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart)
	{
		static int CALL_CNT = 0;
		++CALL_CNT;

		os << "--------------------------\n";

		if (cart.m_toys == nullptr)
		{
			os << "Order " << CALL_CNT << ": This shopping cart is invalid.\n";
			os << "--------------------------\n";
			return os;
		}

		os << "Order " << CALL_CNT << ": Shopping for " << cart.m_name << ' '
		   << cart.m_age << " years old (" << cart.m_count << " toys)\n";
		os << "--------------------------\n";

		if (cart.m_count == 0)
			os << "Empty shopping cart!\n";
		else
			for (size_t i = 0; i < cart.m_count; ++i)
				os << *cart.m_toys[i];

		os << "--------------------------\n";
		return os;
	}
}
