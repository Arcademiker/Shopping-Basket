//
// Created by arcademiker on 28.01.20.
//

#include "Basket.h"

#include <iostream>

std::unordered_map<std::string, float> INVENTORY = {{"A0001", 5.99},
                                                    {"A0002", 412.00},
                                                    {"A0003", 30.50},
                                                    {"A0004", 9.50}};

std::unordered_multimap<std::string, std::string> DISCOUNT = {{"A0002", "Buy1Get1Free"},
                                                              {"A0003", "Buy1Get1Free"},
                                                              {"A0003", "50%"},
                                                              {"A0004", "20%"},
                                                              {"A0004", "10%"}};

int main()
{
    std::cout << "basket with discounts" << std::endl;
    Basket basketWithDiscounts(&INVENTORY, &DISCOUNT);
    basketWithDiscounts.scan("A0002");
    basketWithDiscounts.scan("A0002");
    basketWithDiscounts.scan("A0002");
    basketWithDiscounts.scan("A0003");
    basketWithDiscounts.scan("A0003");
    basketWithDiscounts.scan("A0003");
    basketWithDiscounts.scan("A0004");
    std::cout << basketWithDiscounts.total() << std::endl;
    basketWithDiscounts.remove("A0003");
    std::cout << basketWithDiscounts.total() << std::endl;
    std::cout << std::endl;

    DISCOUNT.clear();
    std::cout << "basket without discounts" << std::endl;
    Basket basket(&INVENTORY, &DISCOUNT);
    basket.scan("A0002");
    basket.scan("A0002");
    basket.scan("A0002");
    basket.scan("A0003");
    basket.scan("A0003");
    basket.scan("A0003");
    basket.scan("A0004");
    std::cout << basket.total() << std::endl;
    basket.remove("A0003");
    std::cout << basket.total() << std::endl;

    return 0;
}

// cout: (to compare solution):
// basket with discounts
// 861.15
// 845.9
//
// basket without discounts
// 1337
// 1306.5
//
// Process finished with exit code 0