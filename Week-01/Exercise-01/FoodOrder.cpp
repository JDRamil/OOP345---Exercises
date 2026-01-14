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

static void copyCstr(char*& dst, const char* src) {
    delete[] dst;
    dst = nullptr;
    if (src && src[0]) {
        size_t n = std::strlen(src);
        dst = new char[n + 1];
        std::strcpy(dst, src);
    }
}

FoodOrder::FoodOrder(const FoodOrder& src) {
    std::strncpy(m_name, src.m_name, 9);
    m_name[9] = '\0';
    m_price = src.m_price;
    m_dailySpecial = src.m_dailySpecial;
    copyCstr(m_desc, src.m_desc);
}

FoodOrder& FoodOrder::operator=(const FoodOrder& src) {
    if (this != &src) {
        std::strncpy(m_name, src.m_name, 9);
        m_name[9] = '\0';
        m_price = src.m_price;
        m_dailySpecial = src.m_dailySpecial;
        copyCstr(m_desc, src.m_desc);
    }
    return *this;
}

FoodOrder::FoodOrder(FoodOrder&& src) noexcept {
    std::strncpy(m_name, src.m_name, 9);
    m_name[9] = '\0';
    m_desc = src.m_desc;
    m_price = src.m_price;
    m_dailySpecial = src.m_dailySpecial;

    src.m_desc = nullptr;
    src.m_name[0] = '\0';
    src.m_price = 0.0;
    src.m_dailySpecial = false;
}

FoodOrder& FoodOrder::operator=(FoodOrder&& src) noexcept {
    if (this != &src) {
        delete[] m_desc;

        std::strncpy(m_name, src.m_name, 9);
        m_name[9] = '\0';
        m_desc = src.m_desc;
        m_price = src.m_price;
        m_dailySpecial = src.m_dailySpecial;

        src.m_desc = nullptr;
        src.m_name[0] = '\0';
        src.m_price = 0.0;
        src.m_dailySpecial = false;
    }
    return *this;
}

void FoodOrder::read(std::istream& in) {
    if (!in.good()) return;

    std::string name, desc;
    double price{};
    char special{};

    // expected: name,desc,price,Y/N\n
    std::getline(in, name, ',');
    std::getline(in, desc, ',');
    in >> price;
    in.ignore(1, ',');
    in >> special;
    in.ignore(10000, '\n');

    // store
    std::strncpy(m_name, name.c_str(), 9);
    m_name[9] = '\0';

    copyCstr(m_desc, desc.c_str());

    m_price = price;
    m_dailySpecial = (special == 'Y');
}

void FoodOrder::display() const {
    static int counter = 1;

    std::cout << std::left << std::setw(2) << counter << ". ";

    if (m_name[0] == '\0') {
        std::cout << "No Order" << std::endl;
    } else {
        double taxed = m_price * (1.0 + g_taxrate);

        std::cout << std::left
                  << std::setw(10) << m_name << "|"
                  << std::setw(25) << (m_desc ? m_desc : "") << "|"
                  << std::setw(12) << std::fixed << std::setprecision(2) << taxed << "|";

        if (m_dailySpecial) {
            double specialPrice = taxed - g_dailydiscount;
            std::cout << std::right << std::setw(13) << std::fixed << std::setprecision(2) << specialPrice;
        }

        std::cout << std::endl;
    }

    counter++;
}

}
