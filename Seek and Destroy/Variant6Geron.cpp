#include <iostream>
#include <cmath>

int main() {
    double a, b, c;
    std::cout << "Введите длину стороны a: ";
    std::cin >> a;
    std::cout << "Введите длину стороны b: ";
    std::cin >> b;
    std::cout << "Введите длину стороны c: ";
    std::cin >> c;

    if (a + b <= c || a + c <= b || b + c <= a) {
        std::cout << "Треугольника с такими сторонами не существует." << std::endl;
        return 1;
    }

    double s = (a + b + c) / 2;

    double Geron = sqrt(s * (s - a) * (s - b) * (s - c));

    std::cout << "Площадь треугольника: " << Geron << std::endl;

    return 0;
}