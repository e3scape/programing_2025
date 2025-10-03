#include <iostream>
#include <cmath> // подключаем библиотеку нужную для стандартных математических функций cmath
using namespace std;

int main() {
    // Ввод сторон треугольника
    int a, b, c; //int т.к. нужны целые числа 
    cout << "Введите длины сторон треугольника:" << endl;
    cout << "Сторона a: ";
    cin >> a;
    cout << "Сторона b: ";
    cin >> b;
    cout << "Сторона c: ";
    cin >> c;
    // Вычисление полупериметра
    float p = (a + b + c) / 2.0; //беру float так как нужны вещественные числа и требуется меньше байт

    // Вычисление площади по формуле Герона
    float S = sqrt(p * (p - a) * (p - b) * (p - c)); //беру float так как нужны вещественные числа и требуется меньше байт, подсчёт площади 
    cout << "Размер int в битах: " << sizeof(int) * 8  << " Минимально: " << numeric_limits<int>::min() << " Максимально: " << numeric_limits<int>::max() << endl; // вывод о типе int
    cout << "Размер float в битах: " << sizeof(float) * 8 <<" Минимально: "<< numeric_limits<float>::lowest() << " Максимально: " << numeric_limits<float>::max() << endl; // вывод о типе float

    cout << "Площадь треугольника: " << S << " float" << endl; //вывод площади треугольника
    return 0;
}