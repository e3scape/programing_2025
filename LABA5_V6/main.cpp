#include <iostream>
#include <cmath>

//Функция для склеивания двух чисел
int klei(int a, int b) {
    std::cout << "Использовать функцию склеивания 2х чисел" << std::endl;
    // Находим количество цифр во втором числе
    int temp = b;
    int count = 1;
    while (temp >= 10) {
        temp /= 10;
        count *= 10;
    }
    // Склеиваем числа: a * (10 в степени количество_цифр_b) + b
    return a * (count * 10) + b;
}
// Функция для нахождения противоположного числа
int ProtivChislo(int a) {
    std::cout << "Использовать функцию противоположного числа" << std::endl;
    return -a;
} 
// Функция для трех чисел (площадь треугольника по формуле Герона)
void STR(int a, int b, int c) {
    std::cout << "исп. функция площади треугольника по формуле Герона" << std::endl;
    double p = (a + b + c) / 2.0;
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    double result = S;
    std::cout << "Результат: " << result << std::endl;
}
int main() {
    int vibor;
    std::cout << "Выберите пункт для выполнения (1 или 2):";
    std::cin >> vibor;
    if (vibor == 1) {
        std::cout << "-----Пункт 1-----" << std::endl;
        int num1, num2, num3;
        std::cout << "Введите три числа (если число = 0, считаем что его нет): ";
        std::cin >> num1 >> num2 >> num3;
        // Определяем количество ненулевых чисел
        int count = 0;
        if (num1 != 0) count++;
        if (num2 != 0) count++;
        if (num3 != 0) count++;

        int result;

        if (count == 2) {
            // Определяем какие именно два числа ненулевые
            if (num1 != 0 && num2 != 0) {
                result = klei(num1, num2);
                std::cout << "Результат склеивания " << num1 << " и " << num2 << ": " << result << std::endl;
            }
            else if (num1 != 0 && num3 != 0) {
                result = klei(num1, num3);
                std::cout << "Результат склеивания " << num1 << " и " << num3 << ": " << result << std::endl;
            }
            else {
                result = klei(num2, num3);
                std::cout << "Результат склеивания " << num2 << " и " << num3 << ": " << result << std::endl;
            }
        }
        else if (count == 1) {
            // Определяем какое именно число ненулевое
            if (num1 != 0) {
                result = ProtivChislo(num1);
                std::cout << "Противоположное число для " << num1 << ": " << result << std::endl;
            }
            else if (num2 != 0) {
                result = ProtivChislo(num2);
                std::cout << "Противоположное число для " << num2 << ": " << result << std::endl;
            }
            else {
                result = ProtivChislo(num3);
                std::cout << "Противоположное число для " << num3 << ": " << result << std::endl;
            }
        }
        else if (count == 3) {
            // Все три числа ненулевые - склеиваем первые два
            result = klei(num1, num2);
            result = klei(result, num3);
            std::cout << "Результат склеивания трех чисел: " << result << std::endl;
        }
        else {
            std::cout << "Все числа нулевые" << std::endl;
        }
    }
    else if (vibor == 2) {
        std::cout << "---------Пункт 2---------" << std::endl;
        int a, b, c;
        std::cout << "Введите три стороны треугольника: ";
        std::cin >> a >> b >> c;
        // 
        if (a <= 0 || b <= 0 || c <= 0) {
            std::cout << "Ошибка: стороны треугольника должны быть положительными числами!" << std::endl;
            return 1;
        }
        STR(a, b, c);
    }
    else {
        std::cout << "Неверный выбор. Должено быть 1 или 2" << std::endl;
        return 1;
    }
    return 0;
}