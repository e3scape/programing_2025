#include <iostream>
#include <string>
#include <vector>
#include "Country.hpp"
#include <cstdlib> 
#include <ctime> 
#include "include/country_lib.hpp"
using string_t = std::string;

void func_rating() {
    std::cout << "Баллы за работу: " << std::endl;
    std::cout << "Интересно: 9/10 - прикольно делить бюджет, чувствую себя главбухом" << std::endl;
    std::cout << "Содержание: 10/10 - всё есть: библиотека, новые классы" << std::endl;
    std::cout << "Сложность: 10/10 - тяжко" << std::endl;
}

int main() {
    using namespace mt;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<City> ed = {
        City("Washington", 7000, 0.0),
        City("NewYork", 8500, 0.0),
        City("LosAngeles", 4000, 0.0),
        City("Chicago", 2700, 0.0),
        City("Houston", 2300, 0.0)
    };

    std::vector<City> ee = {
        City("MexicoCity", 9000, 0.0),
        City("Guadalajara", 1500, 0.0),
        City("Monterrey", 1100, 0.0),
        City("Puebla", 1600, 0.0)
    };

    Country ef("USA", "Washington", 1776, 9834000.0, 331000, ed);
    Country eg("Mexico", "MexicoCity", 1810, 1964000.0, 126000, ee);

    Budget eh(100000.0, 1.5);

    Country* ei = nullptr;
    int ej;
    int ek = -1;

    do {
        std::cout << "ТЕКУЩЕЕ СОСТОЯНИЕ:" << std::endl;
        std::cout << "  Страна А: " << ef.func1()
            << " (столица: " << ef.func2()
            << ", население: " << ef.func5() << ")" << std::endl;
        std::cout << "  Страна Б: " << eg.func1()
            << " (столица: " << eg.func2()
            << ", население: " << eg.func5() << ")" << std::endl;
        std::cout << "  Бюджет: " << eh.get_money()
            << ", коэффициент столицы: " << eh.get_capital_coefficient() << std::endl;

        std::cout << " ===МЕНЮ=== " << std::endl;
        std::cout << "1.  Показать оператор + (А + Б)" << std::endl;
        std::cout << "2.  Показать оператор * (А * Б)" << std::endl;
        std::cout << "3.  Показать оператор += (А += Б или Б += А)" << std::endl;
        std::cout << "4.  Показать геттеры страны" << std::endl;
        std::cout << "5.  Изменить название страны" << std::endl;
        std::cout << "6.  Изменить столицу" << std::endl;
        std::cout << "7.  Изменить дату основания" << std::endl;
        std::cout << "8.  Изменить площадь" << std::endl;
        std::cout << "9.  Изменить общее население" << std::endl;
        std::cout << "10. Изменить население города" << std::endl;
        std::cout << "11. Показать информацию о стране" << std::endl;
        std::cout << "12. Показать информацию о городе" << std::endl;
        std::cout << "13. Показать работу с бюджетом" << std::endl;
        std::cout << "14. Изменить бюджет" << std::endl;
        std::cout << "15. Распределить бюджет по городам" << std::endl;
        std::cout << "16. Показать оценку лабораторной" << std::endl;
        std::cout << "17. Увеличить бюджет на 10000" << std::endl;
        std::cout << "0.  Выход" << std::endl;
        std::cout << "Твой выбор: ";
        std::cin >> ek;

        if (ek >= 4 && ek <= 12 && ek != 1 && ek != 2 && ek != 3 && ek != 13 && ek != 14 && ek != 15 && ek != 16 && ek != 17) {
            std::cout << "Выбери страну:" << std::endl;
            std::cout << "1. Страна А (США)" << std::endl;
            std::cout << "2. Страна Б (Мексика)" << std::endl;

            try {
                std::cin >> ej;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw "Ошибка: Введи число, а не буквы!";
                }
                if (ej != 1 && ej != 2) {
                    throw "Ошибка: Неправильный выбор страны! Введи 1 или 2.";
                }

                if (ej == 1) {
                    ei = &ef;
                    std::cout << "Выбрана страна: США" << std::endl;
                }
                else if (ej == 2) {
                    ei = &eg;
                    std::cout << "Выбрана страна: Мексика" << std::endl;
                }
            }
            catch (const char* el) {
                std::cout << el << std::endl;
                continue;
            }
        }

        switch (ek) {
        case 1: {
            std::cout << "===Оператор + (А + Б)===" << std::endl;
            try {
                Country em = ef + eg;
                em.func20();
            }
            catch (const string_t& en) {
                std::cerr << "Ошибка: " << en << std::endl;
            }
            break;
        }

        case 2: {
            std::cout << "=== Оператор * (А * Б) ===" << std::endl;
            try {
                Country eo = ef * eg;
                eo.func20();
            }
            catch (const string_t& ep) {
                std::cerr << "Ошибка: " << ep << std::endl;
            }
            break;
        }

        case 3: {
            std::cout << "\n=== Оператор += ===" << std::endl;
            std::cout << "Выбери операцию:" << std::endl;
            std::cout << "1. США += Мексика" << std::endl;
            std::cout << "2. Мексика += США" << std::endl;
            int eq;
            std::cin >> eq;

            try {
                if (eq == 1) {
                    std::cout << "До США += Мексика:" << std::endl;
                    ef.func20();
                    ef += eg;
                    std::cout << "После США += Мексика:" << std::endl;
                    ef.func20();
                }
                else if (eq == 2) {
                    std::cout << "До Мексика += США:" << std::endl;
                    eg.func20();
                    eg += ef;
                    std::cout << "После Мексика += США:" << std::endl;
                    eg.func20();
                }
            }
            catch (const string_t& er) {
                std::cerr << "Ошибка: " << er << std::endl;
            }
            break;
        }

        case 4: {
            std::cout << "=== Геттеры для " << ei->func1() << " ===" << std::endl;
            std::cout << "Название: " << ei->func1() << std::endl;
            std::cout << "Столица: " << ei->func2() << std::endl;
            std::cout << "Дата основания: " << ei->func3() << std::endl;
            std::cout << "Площадь: " << ei->func4() << std::endl;
            std::cout << "Население: " << ei->func5() << std::endl;
            std::cout << "Общее население городов: " << ei->func8() << std::endl;

            const std::vector<City>& es = ei->func6();
            std::cout << "Города (" << es.size() << "):" << std::endl;
            for (size_t et = 0; et < es.size(); et++) {
                std::cout << "  " << et + 1 << ". " << es[et].name_
                    << " (нас: " << es[et].population_ << ")" << std::endl;
            }
            break;
        }

        case 5: {
            std::cout << "=== Смена названия ===" << std::endl;
            try {
                string_t eu;
                std::cout << "Введи новое название для " << ei->func1() << ": ";
                std::cin >> eu;
                ei->func9(eu);
                std::cout << "Название успешно изменено!" << std::endl;
            }
            catch (const string_t& ev) {
                std::cerr << "Ошибка: " << ev << std::endl;
            }
            break;
        }

        case 6: {
            std::cout << "=== Смена столицы ===" << std::endl;
            try {
                string_t ew;
                std::cout << "Введи новую столицу для " << ei->func1() << ": ";
                std::cin >> ew;
                ei->func10(ew);
                std::cout << "Столица успешно изменена!" << std::endl;
            }
            catch (const string_t& ex) {
                std::cerr << "Ошибка: " << ex << std::endl;
            }
            break;
        }

        case 7: {
            std::cout << "=== Смена даты основания ===" << std::endl;
            try {
                int ey;
                std::cout << "Введи новую дату основания: ";
                std::cin >> ey;
                ei->func11(ey);
                std::cout << "Дата основания успешно изменена!" << std::endl;
            }
            catch (const string_t& ez) {
                std::cerr << "Ошибка: " << ez << std::endl;
            }
            break;
        }

        case 8: {
            std::cout << "=== Смена площади ===" << std::endl;
            try {
                double fa;
                std::cout << "Введи новую площадь для " << ei->func1() << ": ";
                std::cin >> fa;
                ei->func12(fa);
                std::cout << "Площадь успешно изменена!" << std::endl;
            }
            catch (const string_t& fb) {
                std::cerr << "Ошибка: " << fb << std::endl;
            }
            break;
        }

        case 9: {
            std::cout << "=== Смена общего населения ===" << std::endl;
            try {
                int fc;
                std::cout << "Введи новое население для " << ei->func1() << ": ";
                std::cin >> fc;
                ei->func13(fc);
                std::cout << "Население успешно изменено!" << std::endl;
            }
            catch (const string_t& fd) {
                std::cerr << "Ошибка: " << fd << std::endl;
            }
            break;
        }

        case 10: {
            std::cout << "=== Смена населения города ===" << std::endl;
            try {
                const std::vector<City>& fe = ei->func6();

                if (fe.empty()) {
                    std::cout << "Нет городов для изменения!" << std::endl;
                    break;
                }

                std::cout << "Города страны " << ei->func1() << ":" << std::endl;
                for (size_t ff = 0; ff < fe.size(); ff++) {
                    std::cout << ff + 1 << ". " << fe[ff].name_
                        << " (население: " << fe[ff].population_ << ")" << std::endl;
                }

                std::cout << "Выбери номер города: ";
                size_t fg;
                std::cin >> fg;

                if (fg < 1 || fg > fe.size()) {
                    std::cout << "Неверный номер города!" << std::endl;
                    break;
                }

                int fh;
                std::cout << "Введи новое население для города " << fe[fg - 1].name_ << ": ";
                std::cin >> fh;

                ei->func14(fe[fg - 1].name_, fh);
                std::cout << "Население города успешно изменено!" << std::endl;
            }
            catch (const string_t& fi) {
                std::cerr << "Ошибка: " << fi << std::endl;
            }
            break;
        }

        case 11: {
            std::cout << "=== Информация о стране ===" << std::endl;
            ei->func20();
            break;
        }

        case 12: {
            std::cout << "=== Информация о городе ===" << std::endl;
            try {
                const std::vector<City>& fj = ei->func6();

                if (fj.empty()) {
                    std::cout << "Нет городов для показа!" << std::endl;
                    break;
                }

                std::cout << "Города страны " << ei->func1() << ":" << std::endl;
                for (size_t fk = 0; fk < fj.size(); fk++) {
                    std::cout << fk + 1 << ". " << fj[fk].name_ << std::endl;
                }

                std::cout << "Выбери номер города: ";
                size_t fl;
                std::cin >> fl;

                if (fl < 1 || fl > fj.size()) {
                    std::cout << "Неверный номер города!" << std::endl;
                    break;
                }

                City fm = ei->func7(fj[fl - 1].name_);
                fm.print_info();
            }
            catch (const string_t& fn) {
                std::cerr << "Ошибка: " << fn << std::endl;
            }
            break;
        }

        case 13: {
            std::cout << "=== Демонстрация бюджета ===" << std::endl;
            std::cout << "Текущий бюджет: ";
            eh.print_info();
            break;
        }

        case 14: {
            std::cout << "=== Изменение бюджета ===" << std::endl;
            try {
                std::string fo;
                std::cout << "Введи новую сумму бюджета (только цифры и одна точка): ";
                std::cin >> fo;
                eh.set_money(fo);

                std::string fp;
                std::cout << "Введи новый коэффициент столицы (только цифры и одна точка): ";
                std::cin >> fp;
                eh.set_capital_coefficient(fp);

                std::cout << "Бюджет успешно изменён!" << std::endl;
                eh.print_info();
            }
            catch (const std::string& fq) {
                std::cerr << "Ошибка: " << fq << std::endl;
            }
            break;
        }

        case 15: {
            std::cout << "=== Распределение бюджета ===" << std::endl;
            std::cout << "Выбери страну для распределения бюджета:" << std::endl;
            std::cout << "1. США" << std::endl;
            std::cout << "2. Мексика" << std::endl;
            int fr;
            std::cin >> fr;

            try {
                if (fr == 1) {
                    std::cout << "Распределение бюджета по американским городам:" << std::endl;
                    ef.func19(eh);
                }
                else if (fr == 2) {
                    std::cout << "Распределение бюджета по мексиканским городам:" << std::endl;
                    eg.func19(eh);
                }
            }
            catch (const string_t& fs) {
                std::cerr << "Ошибка: " << fs << std::endl;
            }
            break;
        }
        case 16: {
            func_rating();
            break;
        }

        case 17: {
            std::cout << "=== Увеличение бюджета на 10000 ===" << std::endl;
            eh.change_money(); 
            eh.print_info();
            break;
        }

        case 0: {
            std::cout << "Выход из программы. Пока!" << std::endl;
            break;
        }

        default: {
            std::cout << "Неверный выбор. Попробуй снова." << std::endl;
            break;
        }
        }

    } while (ek != 0);

    return 0;
}