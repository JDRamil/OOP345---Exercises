#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream>
#include <string>

namespace seneca
{
	/// <summary>
	/// Stores information about a single toy (id, name, quantity ordered,
	/// and unit price). HST (13%) is applied when computing totals.
	/// </summary>
	class Toy
	{
		long        m_id{};
		std::string m_name{};
		int         m_numItems{};
		double      m_price{};

		static const double HST_RATE;

		static std::string trim(const std::string& s);

	public:
		Toy() = default;

		/// <summary>Parses "ID:NAME:NUM:PRICE" (tokens may have surrounding spaces).</summary>
		Toy(const std::string& toy);

		/// <summary>Updates how many of this toy are being ordered.</summary>
		void update(int numItems);

		friend std::ostream& operator<<(std::ostream& os, const Toy& toy);
	};
}

#endif
