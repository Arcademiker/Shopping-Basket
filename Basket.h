//
// Created by arcademiker on 28.01.20.
//

#pragma once
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

class Basket
{
private:
    inline static std::unordered_map<std::string, float> *INVENTURY;
    inline static std::unordered_multimap<std::string, std::string> *DISCOUNT;

    // multimap because the same article could be added multiple times
    std::unordered_multimap<std::string, float> *items;

public:
    Basket(std::unordered_map<std::string, float> *INVENTURY,
           std::unordered_multimap<std::string, std::string> *DISCOUNT);
    ~Basket();
    void scan(std::string);
    void remove(std::string item); // added remove item as bonus
    float total();
    static std::set<std::string> getDiscounts(std::string item);
    static float getPercentage(std::string item);
};
