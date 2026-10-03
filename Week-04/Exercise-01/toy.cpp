#include "toy.h"
#include <iomanip>

namespace seneca
{
	const double Toy::HST_RATE = 0.13;

	std::string Toy::trim(const std::string& s)
	{
		size_t start = s.find_first_not_of(' ');
		if (start == std::string::npos)
			return "";
		size_t end = s.find_last_not_of(' ');
		return s.substr(start, end - start + 1);
	}

	Toy::Toy(const std::string& toy)
	{
		std::string data = toy;

		size_t pos = data.find(':');
		std::string idStr = trim(data.substr(0, pos));
		data.erase(0, pos + 1);

		pos = data.find(':');
		m_name = trim(data.substr(0, pos));
		data.erase(0, pos + 1);

		pos = data.find(':');
		std::string numStr = trim(data.substr(0, pos));
		data.erase(0, pos + 1);

		std::string priceStr = trim(data);

		m_id = std::stol(idStr);
		m_numItems = std::stoi(numStr);
		m_price = std::stod(priceStr);
	}

	void Toy::update(int numItems)
	{
		m_numItems = numItems;
	}

	std::ostream& operator<<(std::ostream& os, const Toy& toy)
	{
		// Save the stream's current state so we can restore it before
		// returning (this function must have no side effects).
		std::ios::fmtflags flags = os.flags();
		char fillCh = os.fill();
		std::streamsize prec = os.precision();

		double subtotal = toy.m_price * toy.m_numItems;
		double tax = subtotal * Toy::HST_RATE;
		double total = subtotal + tax;

		os << "Toy " << std::setfill('0') << std::setw(8) << toy.m_id << ": "
		   << std::setfill('.') << std::setw(24) << toy.m_name
		   << std::setfill(' ') << ' ' << std::setw(2) << toy.m_numItems << " items @ "
		   << std::fixed << std::setprecision(2)
		   << std::setw(6) << toy.m_price << "/item  subtotal: "
		   << std::setw(7) << subtotal << "  tax: " << std::setw(6) << tax
		   << "  total: " << std::setw(7) << total << '\n';

		os.flags(flags);
		os.fill(fillCh);
		os.precision(prec);
		return os;
	}
}
