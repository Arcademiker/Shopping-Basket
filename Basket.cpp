//
// Created by arcademiker on 28.01.20.
//

#include "Basket.h"

Basket::Basket(std::unordered_map<std::string, float> *INVENTURY,
               std::unordered_multimap<std::string, std::string> *DISCOUNT)
{
    Basket::INVENTURY = INVENTURY;
    Basket::DISCOUNT  = DISCOUNT;
    this->items       = new std::unordered_multimap<std::string, float>();
}
Basket::~Basket()
{
    delete this->items;
}
void Basket::scan(std::string item)
{
    this->items->insert(std::make_pair(item, INVENTURY->at(item)));
}
void Basket::remove(std::string item)
{
    // check if item exists
    if (this->items->count(item))
    {
        auto position = this->items->equal_range(item).first;
        this->items->erase(position);
    }
}
float Basket::total()
{
    float sum     = 0.;
    int itemCount = 0;
    int get1Free  = 1;
    for (auto i : *this->items)
    {
        // check if Buy1Get1Free deal is active
        if (getDiscounts(i.first).count("Buy1Get1Free"))
        {
            get1Free = 2;
        }

        // just add every other Buy1Get1Free item
        if (itemCount % get1Free == 0)
        {
            float percent = 0.;
            for (auto a : getDiscounts(i.first))
            {
                // if multiple discounts, add them together
                percent += getPercentage(a);
            }

            // apply price reduction if any
            sum += i.second * (100. - percent) / 100.;
        }
        if (this->items->count(i.first) == itemCount + 1)
        {
            itemCount = 0;
        }
        else
        {
            itemCount++;
        }
    }
    return sum;
}
std::set<std::string> Basket::getDiscounts(std::string item)
{
    std::set<std::string> discounts;
    // check if a discount for the item exists
    if (DISCOUNT->count(item))
    {
        auto p = DISCOUNT->equal_range(item);

        // iterate of all discount types
        for (auto &q = p.first; q != p.second; ++q)
        {
            discounts.insert(q->second);
        }
    }
    return discounts;
}
float Basket::getPercentage(std::string discount)
{
    auto position = discount.find('%');
    if (position != std::string::npos)
    {
        return std::stof(discount.substr(0, position));
    }
}
