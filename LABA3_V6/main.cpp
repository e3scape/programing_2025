#include <iostream>
#include <cmath>
/*int main() {
    int N; // кол-во чисел
    std:: cout << "Введите кол-во чисел: ";
    std::cin >> N;
    int Number = 0; // Счетчик введенных чисел
    int Product = 0; //Сумма чисел подходящих под услвие
    int Max = -2^31; //Максимальное число последовательности
    int i = -1; // Индекс максимального числа
    for (N; N > 0; --N) {
        ++Number;
        std::cout << "Введите число " << Number << ": ";
        int num;
        std::cin >> num;
        if ((num%3 != 0) && (num%5 != 0) && (num%7 != 0)) {
            Product = Product + num;
            if (num > Max) {
                Max = num;
                i = Number;
            }
        }
    }
    if (i != -1) {
    std:: cout << "Cумма чисел подходящих условию: " << Product << std::endl;
    std:: cout << "Максимальное число: " << Max << " Его Индекс: " << i << std::endl;
    }
    else {
        std::cout << "Нету чисел подходящих условию" << std::endl;
    }
    return 0;
}
*/

int main() {
    std::cout << "Введите число: ";
    short N;
    std::cin >> N;

    int kolvo = 0; 
    short N1 = abs(N); 

    if (N1 >= 1000) {
        std::cout << "Всё не ок" << std::endl;
        return 1;
    }

    if (N == 0) {
        std::cout << "Число: 0" << std::endl;
        std::cout << "Количество разрядов: 1" << std::endl;
        std::cout << "Первая цифра: 0" << std::endl;
        return 0;
    }

    while (N1 > 0) {
        kolvo++;
        N1 /= 10; 
    }

    int krot = abs(N);
    while (krot >= 10) {
        krot /= 10; 
    }

    std::cout << "Число: " << abs(N) << std::endl; 
    std::cout << "Количество разрядов: " << kolvo << std::endl;
    std::cout << "Первая цифра числа: " << krot << std::endl;

    return 0;
}