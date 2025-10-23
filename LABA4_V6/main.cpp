#include <iostream>
#include <cmath>

int main() {
    //Задание 1 
    /*
    int x[9];
    for (int i = 0; i < 9; ++i) {
        std::cout << "Введите число " << i+1 << ": ";
        std::cin >> x[i];
    }
    std::cout << "Введенные числа: ";
    for (int i = 0; i < 9; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    bool Tri = false;

    for (int i = 0; i < 9; i++) {
        int num = abs(x[i]);

        int fDigit = num;
        while (fDigit >= 10) {
            fDigit = fDigit/10;
        }

        //Проверка на первую цифру 3
        if (fDigit == 3) {
            Tri = true;
            break; //выводим из цикла если первое число не три
        }
    }

    // Выводим если есть число, начинающееся на 3
    if (Tri) {
        std::cout << "В массиве есть число, начинающееся на 3. Сортируем массив."<< std::endl;

        for (int i = 0; i < 8; ++i) {
            for (int j = i + 1; j < 9; ++j) { //Сортировка массива
                if (x[i] > x[j]) {
                    std::swap(x[i],x[j]);
                }
            }
        }
    for (int i = 0; i < 9; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << "The End" << std::endl;
    }
    else {
        std:: cout << "В последовательности нет числа, начинающегося на 3. Сортировка не выполнена." << std::endl;
    }

    return 0;
    */

    // Задание 2

    int f[3][4];

    for (int i = 0; i < 3; i++) {
        std::cout << "Введите " << i + 1 << " строку из четырех чисел: ";
        for (int j = 0; j < 4; j++) {
            std::cin >> f[i][j];
        }
    }


    // Найдем строку с максимальной абсолютной суммой элементов
    int max = -1;
    int str = -1;

    for (int i = 0; i < 3; i++) {
        int sum = 0;
        // Считаем сумму элементов строки
        for (int j = 0; j < 4; j++) {
            sum += f[i][j];
        }

        // Находим абсолютное значение суммы
        int dist = abs(sum);

        // Если текущая строка имеет большую абсолютную сумму, обновляем данные
        if (dist > max) {
            max = dist;
            str = i;
        }
    }
    // Заменяем элементы строки с максимальной суммой на 999
    for (int j = 0; j < 4; j++) {
        f[str][j] = 999;
    }
    // Выводим результат
    std::cout << "Строка с максимальной абсолютной суммой: " << str + 1 << std::endl;

    std::cout << "Обновленная матрица: " << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << f[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
