#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "include/country_lib.hpp"

using string_t = std::string;
using string_list = std::vector<std::string>;

namespace mt
{

class Country
{
private:

    string_t aaa;
    string_t bbb;
    int ccc;
    double ddd;
    int eee;
    std::vector<City> fff;

public:

    Country();
    Country(string_t g,
            string_t h,
            int i,
            double j,
            int k,
            const std::vector<City>& l = {});

    Country(const Country& m);
    ~Country();

    Country& operator=(const Country& n);
    Country  operator+(const Country& o) const;
    Country  operator*(const Country& p) const;
    Country& operator+=(const Country& q);

    string_t func1() const;
    string_t func2() const;
    int      func3() const;
    double   func4() const;
    int      func5() const;
    const std::vector<City>& func6() const;
    City     func7(const string_t& r) const;
    int      func8() const;

    void func9(string_t s);
    void func10(string_t t);
    void func11(int u);
    void func12(double v);
    void func13(int w);

    void func14(const string_t& x, int y);
    void func15(const string_t& z, double aa);

    void func16(const Country& ab);

    void func17(const string_t& ac, int ad);
    void func18(int ae);

    void func19(const Budget& af);

    void func20() const;
};

}