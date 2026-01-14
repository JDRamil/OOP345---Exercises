#include "FoodOrder.h"
#include <iomanip>
#include <string>
#include <cstring>

double g_taxrate = 0.0;
double g_dailydiscount = 0.0;

namespace seneca {

FoodOrder::FoodOrder() {
    m_name[0] = '\0';
}

FoodOrder::~FoodOrder() {
    delete[] m_desc;
}

FoodOrder::FoodOrder(const FoodOrder& src) {
    *this = src;
}

FoodOrder& FoodOrder::operator=(const FoodOrder& src) {
    if (this != &src) {
        std::strncpy(m_name, src.m_name, 9);
        m_name[9] = '\0';

        delete[] m_desc;
        m_desc = nullptr;

        if (src.m_desc) {
            m_desc = new char[std::strlen(src.m_desc) + 1];
            std::strcpy(m_desc, src.m_desc);
        }

        m_price = src.m_price;
        m_dailySpecial = src.m_dailySpecial;
    }
    return *this;
}

void FoodOrder::read(std::istream& in) {
    if (!in) return;

    std::string name, desc;
    double price{};
    char special{};

    std::getline(in, name, ',');
    std::getline(in, desc, ',');
    in >> price;
    in.ignore(1, ',');
    in >> special;
    in.ignore(10000, '\n');

    std::strncpy(m_name, name.c_str(), 9);
    m_name[9] = '\0';

    delete[] m_desc;
    m_desc = new char[desc.length() + 1];
    std::strcpy(m_desc, desc.c_str());

    m_price = price;
    m_dailySpecial = (special == 'Y');
}

void FoodOrder::display() const {
    static int counter = 1;

    std::cout << std::left << std::setw(2) << counter << ". ";

    if (m_name[0] == '\0') {
        std::cout << "No Order\n";
    }
    else {
        double taxed = m_price * (1 + g_taxrate);

        std::cout << std::setw(10) << m_name << "|"
                  << std::setw(25) << m_desc << "|"
                  << std::setw(12) << std::fixed << std::setprecision(2) << taxed << "|";

        if (m_dailySpecial) {
            double specialPrice = taxed - g_dailydiscount;
            std::cout << std::right << std::setw(13)
                      << std::fixed << std::setprecision(2)
                      << specialPrice;
        }

        std::cout << '\n';
    }

    counter++;
}

}
