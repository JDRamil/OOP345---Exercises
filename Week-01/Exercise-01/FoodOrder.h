#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {

class FoodOrder {
    char  m_name[10]{};
    char* m_desc{nullptr};
    double m_price{0.0};
    bool   m_dailySpecial{false};

public:
    FoodOrder();
    FoodOrder(const FoodOrder& src);
    FoodOrder& operator=(const FoodOrder& src);
    FoodOrder(FoodOrder&& src) noexcept;
    FoodOrder& operator=(FoodOrder&& src) noexcept;
    ~FoodOrder();

    void read(std::istream& in);
    void display() const;
};

}

#endif
