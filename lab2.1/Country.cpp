#include "Country.hpp"
#include <iostream>
#include <algorithm>

namespace mt
{
    Country::Country()
        : title("Unknown"), maincity("Unknown"), territory(0), towns()
    {}

    Country::Country(str name, str capital, double area, const strVec& cities)
        : title(name), maincity(capital), territory(area), towns(cities)
    {}

    Country::Country(const Country& o)
        : title(o.title), maincity(o.maincity), territory(o.territory), towns(o.towns)
    {}

    Country::~Country() {}

    Country& Country::operator=(const Country& o)
    {
        if (this != &o)
        {
            title = o.title;
            maincity = o.maincity;
            territory = o.territory;
            towns = o.towns;
        }
        return *this;
    }

    str Country::get_name() const { return title; }
    str Country::get_capital() const { return maincity; }
    double Country::get_area() const { return territory; }
    const strVec& Country::get_cities() const { return towns; }

    Country Country::operator+(const Country& rhs) const
    {
        Country r;
        r.title = title + "-" + rhs.title;
        r.maincity = (territory >= rhs.territory) ? maincity : rhs.maincity;
        r.territory = territory + rhs.territory;
        r.towns = towns;

        for (const auto& c : rhs.towns)
        {
            bool dup = false;
            for (const auto& e : r.towns)
                if (e == c) dup = true;
            r.towns.push_back(dup ? c + " new" : c);
        }
        return r;
    }

    Country Country::operator*(const Country& rhs) const
    {
        Country r;
        r.title = "Path " + title + "->" + rhs.title;
        r.maincity = "None";
        r.territory = std::min(territory, rhs.territory);
        r.towns.push_back(maincity);
        r.towns.push_back(rhs.maincity);
        return r;
    }

    Country& Country::operator+=(const Country& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    void Country::set_capital(str v)
    {
        if (v.empty()) throw str("Capital empty");
        if (v[0] < 'A' || v[0] > 'Z') throw str("Capital must start uppercase");
        maincity = v;
    }

    void Country::set_name(str v)
    {
        if (v.empty()) throw str("Name empty");
        if (v[0] < 'A' || v[0] > 'Z') throw str("Name must start uppercase");
        title = v;
    }

    void Country::set_area(double v)
    {
        if (v < 0) throw str("Negative area");
        territory = v;
    }

    void Country::set_city_at_index(size_t p, const str& v)
    {
        if (p >= towns.size()) throw str("Bad index");
        towns[p] = v;
    }

    void Country::print_info() const
    {
        std::cout << "Name: " << title << "\nCapital: " << maincity
            << "\nArea: " << territory << "\nCities: ";
        for (const auto& c : towns) std::cout << c << " ";
        std::cout << "\n";
    }
}