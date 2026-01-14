#include <iostream>
#include <iomanip>
#include <fstream>
#include "FoodOrder.h"
#include "FoodOrder.h"

// Cheching if header guards exist and follow convention.
#ifndef SENECA_FOODORDER_H
    #error "The header guard for 'FoodOrder.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

/* input file format: a comma-separated set of fields with a consistent format of
<Order Tag>,<Customer Name>,<Order Description>,<Price>,<Daily Special Status>
*/

int main(int argc, char* argv[])   // <-- TODO 1 completed
{
    std::cout << "Command Line:\n";
    std::cout << "--------------------------\n";

    // TODO 2 completed
    for (int i = 1; i < argc; i++) {
        std::cout << i << ": " << argv[i] << std::endl;
    }

    std::cout << "--------------------------\n\n";

    seneca::FoodOrder recordedDeliveryOrders[6];
    size_t numDeliveries = 0;
    seneca::FoodOrder currentOrder;

    for (auto day = 1; day < argc; ++day)
    {
        if (day == 1){
            g_taxrate = 0.13;
            g_dailydiscount = 1.15;
        }
        else{
            g_taxrate = 0.14;
            g_dailydiscount = 1.20;
        }

        std::cout << "--------------------\n";
        std::cout << "    Day " << day << '\n';
        std::cout << "--------------------\n";
        std::cout << "Name          |Order Description        |Price w/Tax |Special Price\n";

        std::ifstream in(argv[day]);
        if (!in) {
            std::cout << "Cannot open file [" << argv[day] << "]. Ignoring it!\n";
            continue;
        }

        char ordertag{};
        while (in) {
            in >> ordertag;
            in.ignore();

            if (in.fail()) break;

            currentOrder.read(in);

            if (ordertag == 'I') {
                seneca::FoodOrder copy = currentOrder;
                copy.display();
            }
            else if (ordertag == 'D') {
                recordedDeliveryOrders[numDeliveries++] = currentOrder;
                currentOrder.display();
            }
        }
    }

    std::cout << "--------------------\n";
    std::cout << "Recorded Delivery Food Orders\n";
    std::cout << "--------------------\n";
    std::cout << "Name          |Order Description        |Price w/Tax |Special Price\n";
    for (auto i = 0u; i < numDeliveries; ++i)
        recordedDeliveryOrders[i].display();
    std::cout << "--------------------\n";

    return cout;
}
