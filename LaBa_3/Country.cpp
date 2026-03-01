#include "Country.hpp"
#include <iostream>
#include <exception>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 

namespace mt {


Country::Country() :
    aaa("unknown"),
    bbb("unknown"),
    ccc(2000),
    ddd(0.0),
    eee(0) {
    std::cerr << "Country default ctor" << std::endl;
}

Country::Country(string_t ag, string_t ah, int ai, double aj, int ak, const std::vector<City>& al) :
    aaa(ag),
    bbb(ah),
    ccc(ai),
    ddd(aj),
    eee(ak),
    fff(al) {
    std::cerr << "Country param ctor" << std::endl;
}

Country::Country(const Country& am) :
    aaa(am.aaa),
    bbb(am.bbb),
    ccc(am.ccc),
    ddd(am.ddd),
    eee(am.eee),
    fff(am.fff) {
    std::cerr << "Country copy ctor" << std::endl;
}

Country::~Country() {
    fff.clear();
    std::cerr << "Country dtor" << std::endl;
}

Country& Country::operator=(const Country& an) {
    if (this != &an) {
        aaa = an.aaa;
        bbb = an.bbb;
        ccc = an.ccc;
        ddd = an.ddd;
        eee = an.eee;
        fff = an.fff;
        std::cerr << "Country operator= called" << std::endl;
    }
    return *this;
}

string_t Country::func1() const { return aaa; }
string_t Country::func2() const { return bbb; }
int Country::func3() const { return ccc; }
double Country::func4() const { return ddd; }
int Country::func5() const { return eee; }
const std::vector<City>& Country::func6() const { return fff; }

int Country::func8() const {
    int ao = 0;
    for (size_t ap = 0; ap < fff.size(); ++ap) {
        ao += fff[ap].population_;
    }
    return ao;
}

City Country::func7(const string_t& aq) const {
    for (size_t ar = 0; ar < fff.size(); ++ar) {
        if (fff[ar].name_ == aq) {
            return fff[ar];
        }
    }
    string_t as = "City not found";
    throw as;
}

void Country::func9(string_t at) {
    if (at.empty()) {
        string_t au = "The name cannot be empty.";
        throw au;
    }
    string_t av = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string_t aw = "abcdefghijklmnopqrstuvwxyz";

    if (av.find(at[0]) == std::string::npos) {
        string_t ax = "Name must start with an uppercase letter";
        throw ax;
    }

    for (int ay = 1; ay < at.length(); ay++) {
        char az = at[ay];
        if (aw.find(az) == std::string::npos) {
            string_t ba = "The name should be without numbers, spaces, punctuation marks and capital letters.";
            throw ba;
        }
    }

    aaa = at;
    std::cerr << "Name changed to: " << aaa << std::endl;
}

void Country::func10(string_t bb) {
    if (bb.empty()) {
        string_t bc = "The capital's name cannot be empty";
        throw bc;
    }
    string_t bd = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string_t be = "abcdefghijklmnopqrstuvwxyz";

    if (bd.find(bb[0]) == std::string::npos) {
        string_t bf = "Capital name must start with an uppercase letter";
        throw bf;
    }

    for (int bg = 1; bg < bb.length(); bg++) {
        char bh = bb[bg];
        if (be.find(bh) == std::string::npos) {
            string_t bi = "The capital should be without numbers, spaces, punctuation marks and capital letters.";
            throw bi;
        }
    }

    bbb = bb;
    std::cerr << "Capital changed to: " << bbb << std::endl;
}

void Country::func11(int bj) {  
    if (bj < 0 || bj > 2025) {
        string_t bk = "Year must be between 0 and 2025";
        throw bk;
    }

    ccc = bj;
    std::cerr << "Foundation year changed to: " << ccc << std::endl;
}

void Country::func12(double bl) {
    if (bl < 0) {
        string_t bm = "Area cannot be negative";
        throw bm;
    }
    ddd = bl;
    std::cerr << "Area after change: " << ddd << std::endl;
}

void Country::func13(int bn) {
    if (bn < 0) {
        string_t bo = "Population cannot be negative";
        throw bo;
    }
    eee = bn;
    std::cerr << "Population changed to: " << eee << std::endl;
}

void Country::func14(const string_t& bp, int bq) {
    if (bq < 0) {
        string_t br = "Population cannot be negative";
        throw br;
    }

    for (size_t bs = 0; bs < fff.size(); ++bs) {
        if (fff[bs].name_ == bp) {
            int bt = fff[bs].population_;
            fff[bs].population_ = bq;
            std::cerr << "Population of " << bp << " changed from " << bt
                << " to " << bq << std::endl;
            return;
        }
    }
    string_t bu = "City not found";
    throw bu;
}

void Country::func15(const string_t& bv, double bw) {
    if (bw < 0) {
        string_t bx = "Budget cannot be negative";
        throw bx;
    }

    for (size_t by = 0; by < fff.size(); ++by) {
        if (fff[by].name_ == bv) {
            fff[by].budget_ = bw;
            std::cerr << "Budget of " << bv << " changed to " << bw << std::endl;
            return;
        }
    }
    string_t bz = "City not found";
    throw bz;
}

// ========== ИСПРАВЛЕННАЯ ФУНКЦИЯ РАСПРЕДЕЛЕНИЯ БЮДЖЕТА ==========
void Country::func19(const Budget& ca) {
    if (fff.empty()) {
        std::cerr << "No cities to distribute budget to" << std::endl;
        return;
    }

    City* cb = nullptr;
    for (size_t cc = 0; cc < fff.size(); ++cc) {
        if (fff[cc].name_ == bbb) {
            cb = &fff[cc];
            break;
        }
    }

    if (!cb) {
        string_t cd = "Capital city not found in cities list";
        throw cd;
    }

    // Считаем эффективное население с учетом коэффициента для столицы
    double effective_total_population = 0.0;
    double ch = ca.get_capital_coefficient();
    
    for (size_t cf = 0; cf < fff.size(); ++cf) {
        if (fff[cf].name_ == bbb) {
            // Для столицы население умножаем на коэффициент
            effective_total_population += fff[cf].population_ * ch;
        } else {
            effective_total_population += fff[cf].population_;
        }
    }

    if (effective_total_population == 0) {
        std::cerr << "Effective total population is zero, cannot distribute budget" << std::endl;
        return;
    }

    double cg = ca.get_money();

    // Распределяем бюджет
    for (size_t ci = 0; ci < fff.size(); ++ci) {
        if (fff[ci].name_ == bbb) {
            // Для столицы: (население × коэффициент) / эффективное общее население
            double effective_share = (fff[ci].population_ * ch) / effective_total_population;
            fff[ci].budget_ = cg * effective_share;
            std::cout << "  " << fff[ci].name_ << " (capital, pop=" << fff[ci].population_
                << ", weighted pop=" << fff[ci].population_ * ch
                << "): " << fff[ci].budget_ << " (with coefficient " << ch << ")" << std::endl;
        }
        else {
            // Для обычных городов: население / эффективное общее население
            double effective_share = static_cast<double>(fff[ci].population_) / effective_total_population;
            fff[ci].budget_ = cg * effective_share;
            std::cout << "  " << fff[ci].name_ << " (pop=" << fff[ci].population_
                << "): " << fff[ci].budget_ << std::endl;
        }
    }

    // Проверка: сумма должна равняться исходному бюджету
    double sum = 0;
    for (size_t ci = 0; ci < fff.size(); ++ci) {
        sum += fff[ci].budget_;
    }
    std::cout << "Total distributed: " << sum << " (original budget: " << cg << ")" << std::endl;
    std::cout << "Budget distributed successfully" << std::endl;
}

void Country::func16(const Country& ck) {
    aaa = aaa + "-" + ck.aaa;

    if (ddd < ck.ddd) {
        bbb = ck.bbb;
    }

    ddd += ck.ddd;

    eee += ck.eee;

    for (size_t cl = 0; cl < ck.fff.size(); ++cl) {
        const City& cm = ck.fff[cl];
        bool cn = false;
        for (size_t co = 0; co < fff.size(); ++co) {
            if (fff[co].name_ == cm.name_) {
                cn = true;
                break;
            }
        }

        if (cn) {
            City cp = cm;
            cp.name_ = cm.name_ + " (new)";
            fff.push_back(cp);
        }
        else {
            fff.push_back(cm);
        }
    }

    std::cerr << "Territory annexed. New name: " << aaa << std::endl;
}

void Country::func17(const string_t& cq, int cr) {
    for (size_t cs = 0; cs < fff.size(); ++cs) {
        if (fff[cs].name_ == cq) {
            int ct = fff[cs].population_ + cr;
            if (ct < 0) {
                string_t cu = "Population cannot become negative";
                throw cu;
            }
            fff[cs].population_ = ct;
            std::cerr << "Population of " << cq << " changed by " << cr
                << ", new population: " << ct << std::endl;
            return;
        }
    }
    string_t cv = "City not found";
    throw cv;
}

void Country::func18(int cw) {
    int cx = eee + cw;
    if (cx < 0) {
        string_t cy = "Total population cannot become negative";
        throw cy;
    }
    eee = cx;
    std::cerr << "Total population changed by " << cw
        << ", new total population: " << eee << std::endl;
}

Country Country::operator+(const Country& cz) const {
    Country da;

    da.aaa = this->aaa + "-" + cz.aaa;

    if (this->ddd >= cz.ddd) {
        da.bbb = this->bbb;
    }
    else {
        da.bbb = cz.bbb;
    }

    da.ddd = this->ddd + cz.ddd;
    da.eee = this->eee + cz.eee;
    da.ccc = 0;

    da.fff = this->fff;

    for (int db = 0; db < cz.fff.size(); db++) {
        const City& dc = cz.fff[db];
        bool dd = false;

        for (int de = 0; de < da.fff.size(); de++) {
            if (da.fff[de].name_ == dc.name_) {
                dd = true;
                break;
            }
        }

        if (dd) {
            City df = dc;
            df.name_ = dc.name_ + " new";
            da.fff.push_back(df);
        }
        else {
            da.fff.push_back(dc);
        }
    }

    return da;
}

Country Country::operator*(const Country& dg) const {
    Country dh;

    dh.aaa = "path " + this->aaa + "->" + dg.aaa;
    dh.bbb = "No";
    dh.ccc = 0;

    if (this->ddd < dg.ddd) {
        dh.ddd = this->ddd;
    }
    else {
        dh.ddd = dg.ddd;
    }

    if (this->eee < dg.eee) {
        dh.eee = this->eee;
    }
    else {
        dh.eee = dg.eee;
    }

    dh.fff.clear();
    dh.fff.push_back(City(this->bbb, 0, 0));
    dh.fff.push_back(City(dg.bbb, 0, 0));

    std::vector<City> di;
    for (size_t dj = 0; dj < this->fff.size(); dj++) {
        if (this->fff[dj].name_ != this->bbb) {
            di.push_back(this->fff[dj]);
        }
    }

    if (!di.empty()) {
        int dk = 0;
        if (di.size() > 1) {
            dk = std::rand() % static_cast<int>(di.size());
        }
        City dl = di[dk];

        bool dm = false;
        for (size_t dn = 0; dn < dh.fff.size(); dn++) {
            if (dh.fff[dn].name_ == dl.name_) {
                dm = true;
                break;
            }
        }

        if (dm) {
            dl.name_ = dl.name_ + " new";
            dh.fff.push_back(dl);
        }
        else {
            dh.fff.push_back(dl);
        }
    }

    std::vector<City> d_o;
    for (size_t dp = 0; dp < dg.fff.size(); dp++) {
        if (dg.fff[dp].name_ != dg.bbb) {
            d_o.push_back(dg.fff[dp]);
        }
    }

    if (!d_o.empty()) {
        int dq = 0;
        if (d_o.size() > 1) {
            dq = std::rand() % static_cast<int>(d_o.size());
        }
        City dr = d_o[dq];

        bool ds = false;
        for (size_t dt = 0; dt < dh.fff.size(); dt++) {
            if (dh.fff[dt].name_ == dr.name_) {
                ds = true;
                break;
            }
        }

        if (ds) {
            dr.name_ = dr.name_ + " new";
            dh.fff.push_back(dr);
        }
        else {
            dh.fff.push_back(dr);
        }
    }

    return dh;
}

Country& Country::operator+=(const Country& du) {
    this->aaa = this->aaa + "-" + du.aaa;

    if (this->ddd < du.ddd) {
        this->bbb = du.bbb;
    }

    this->ddd += du.ddd;
    this->eee += du.eee;

    std::vector<City> dv = this->fff;

    for (size_t dw = 0; dw < du.fff.size(); dw++) {
        const City& dx = du.fff[dw];
        bool dy = false;

        for (size_t dz = 0; dz < this->fff.size(); dz++) {
            if (this->fff[dz].name_ == dx.name_) {
                dy = true;
                break;
            }
        }

        if (dy) {
            City ea = dx;
            ea.name_ = dx.name_ + " new";
            dv.push_back(ea);
        }
        else {
            dv.push_back(dx);
        }
    }

    this->fff = dv;

    return *this;
}

void Country::func20() const {
    std::cout << " Country Information:" << std::endl;
    std::cout << "Name: " << aaa << std::endl;
    std::cout << "Capital: " << bbb << std::endl;
    std::cout << "Foundation date: " << ccc << std::endl;
    std::cout << "Area: " << ddd << " sq. km" << std::endl;
    std::cout << "Total population: " << eee << std::endl;
    std::cout << "Cities (" << fff.size() << "):" << std::endl;

    if (fff.empty()) {
        std::cout << "  none" << std::endl;
    }
    else {
        for (size_t eb = 0; eb < fff.size(); ++eb) {
            const City& ec = fff[eb];
            std::cout << "  - " << ec.name_ << " (pop: " << ec.population_
                << ", budget: " << ec.budget_ << ")" << std::endl;
        }
    }
}

}