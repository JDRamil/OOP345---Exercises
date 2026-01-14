#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {

class FoodOrder {
    char  m_name[10]{};
    char* m_desc{nullptr};
    double m_price{};
    bool m_dailySpecial{};

public:
    FoodOrder();
    ~FoodOrder();

    FoodOrder(const FoodOrder&);
    FoodOrder& operator=(const FoodOrder&);

    void read(std::istream& in);
    void display() const;
};

}

#endif
