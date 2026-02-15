#pragma once
#include <string>
#include <vector>

namespace mt
{
    using str    = std::string;
    using strVec = std::vector<std::string>;

    class Country
    {
        str     title;
        str     maincity;
        double  territory;
        strVec  towns;

    public:
        Country();
        Country(str name, str capital, double area, const strVec& cities = {});
        Country(const Country& other);
        ~Country();

        Country& operator=(const Country& other);

        str get_name() const;
        str get_capital() const;
        double get_area() const;
        const strVec& get_cities() const;

        Country operator+(const Country& rhs) const;
        Country operator*(const Country& rhs) const;
        Country& operator+=(const Country& rhs);

        void set_capital(str v);
        void set_name(str v);
        void set_area(double v);
        void set_city_at_index(size_t p, const str& v);

        void print_info() const;
    };
}