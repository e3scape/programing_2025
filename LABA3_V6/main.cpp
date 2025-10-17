#include <iostream>
using namespace std;
int main() {
    int N;
    std::cout << "Введите количество чисел в последовательности: ";
    std::cin >> N;
    long int sum = 0;
    int max_number = 0;
    int max_index = -1;
    int count = 0;
    bool found = false;

    std::cout << "Введите числа последовательности:" << std::endl;
    for (int i = 1; i <= N; i++) {
        int num;
        std::cout << "Число " << i << " = ";
        std::cin >> num;
        if (num % 3 != 0 && num % 5 != 0 && num % 7 != 0) {
            sum += num;
            count++;
            if (num > max_number || !found) {
                max_number = num;
                max_index = i;
                found = true;
            }
        }
    }
    if (count == 0) {
        std::cout << "В последовательности нет подходящих чисел" << std::endl;
    }
    else {
        std::cout << "Количество подходящих чисел: " << count << std::endl;
        std::cout << "Числа подходящие условию: " << sum << std::endl;
        std::cout << "Наибольшее число: " << max_number << " Его номер: " << max_index << ::endl;
    }
    return 0;
}

/*
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
*/