/*#include <iostream>
#include <vector>
#include <algorithm>

// Функция для просмотра вектора
void displayVector(const std::vector<int>& data) 
{
    std::cout << "[";
    for (int idx = 0; idx < data.size(); ++idx) 
    {
        std::cout << data[idx];
        if (idx < data.size() - 1) 
        {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

// Добавление элемента в начало
void insertAtStart(std::vector<int>& data, int num) 
{
    std::cout << "До: ";
    displayVector(data);
    data.insert(data.begin(), num);
    std::cout << "После: ";
    displayVector(data);
}

// Добавление элемента в конец
void insertAtEnd(std::vector<int>& data, int num) 
{
    std::cout << "До: ";
    displayVector(data);
    data.push_back(num);
    std::cout << "После: ";
    displayVector(data);
}

// Очистка вектора
void emptyVector(std::vector<int>& data) 
{
    std::cout << "До: ";
    displayVector(data);
    data.clear();
    std::cout << "После: ";
    displayVector(data);
    std::cout << "Вектор очищен!" << std::endl;
}

// Поиск элемента в векторе
void searchElement(const std::vector<int>& data, int num) 
{
    std::vector<int> positions;
    for (int idx = 0; idx < data.size(); ++idx) 
    {
        if (data[idx] == num) 
        {
            positions.push_back(idx);
        }
    }

    if (positions.empty()) 
    {
        std::cout << "[]" << std::endl;
    } 
    else 
    {
        std::cout << "[";
        for (int idx = 0; idx < positions.size(); ++idx) 
        {
            std::cout << positions[idx];
            if (idx < positions.size() - 1) 
            {
                std::cout << ",";
            }
        }
        std::cout << "]" << std::endl;
    }
}


void performVariant(std::vector<int>& data) 
{
    std::cout << "Вектор до преобразования: ";
    displayVector(data);

    bool hasOddEvenPos = false;

    for (int idx = 0; idx < data.size(); idx += 2) 
    {
        if (idx < data.size() && data[idx] % 2 != 0) 
        {
            hasOddEvenPos = true;
            break;
        }
    }

    if (!hasOddEvenPos) 
    {
        data.insert(data.begin(), -1);
        data.push_back(-1);
    } 
    else 
    {
        for (int idx = 0; idx < data.size(); idx += 2) 
        {
            if (idx < data.size() && data[idx] % 2 != 0) 
            {
                data.insert(data.begin() + idx + 1, 0);
                idx++;
            }
        }
    }

    std::cout << "Вектор после преобразования: ";
    displayVector(data);
}

int main() 
{
    std::vector<int> numbers;
    numbers.reserve(100'000);
    int userChoice;

    do 
    {
        std::cout << "\n=== Меню ===" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "1. Просмотр вектора" << std::endl;
        std::cout << "2. Добавить элемент в начало" << std::endl;
        std::cout << "3. Добавить элемент в конец" << std::endl;
        std::cout << "4. Очистка всего вектора" << std::endl;
        std::cout << "5. Поиск элемента в векторе" << std::endl;
        std::cout << "6. Задание варианта" << std::endl;
        std::cout << "Выберите пункт: ";
        std::cin >> userChoice;

        switch (userChoice) 
        {
        case 0:
            std::cout << "Выход из программы" << std::endl;
            break;

        case 1:
            std::cout << "Текущий вектор: ";
            displayVector(numbers);
            break;

        case 2: 
        {
            int val;
            std::cout << "Введите значение для добавления в начало: ";
            std::cin >> val;
            insertAtStart(numbers, val);
            break;
        }

        case 3: 
        {
            int val;
            std::cout << "Введите значение для добавления в конец: ";
            std::cin >> val;
            insertAtEnd(numbers, val);
            break;
        }

        case 4:
        {
            emptyVector(numbers);
            break;
        }

        case 5: 
        {
            int val;
            std::cout << "Введите значение для поиска: ";
            std::cin >> val;
            std::cout << "Индексы элемента " << val << ": ";
            searchElement(numbers, val);
            break;
        }

        case 6:
            performVariant(numbers);
            break;

        default:
            std::cout << "Неверный выбор" << std::endl;
        }

    } while (userChoice != 0);

    return 0;
}
*/
 
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using IntVector = std::vector<int>;  
using IntArray = std::array<int, 10>; 

void sortByValue(IntArray arr) {
    std::sort(arr.begin(), arr.end());
}

void sortByReference(IntArray& arr) {
    std::sort(arr.begin(), arr.end());
}

void sortByPointer(IntArray* arr) {
    std::sort((*arr).begin(), (*arr).end());
}

int main() {
    IntArray numbers = { 1, 0, 2, 9, 3, 8, 4, 7, 5, 6 };

    std::cout << "Массив: " << std::endl;
    for (int idx = 0; idx < 10; idx++) {
        std::cout << numbers[idx] << " ";
    }
    std::cout << std::endl;

    sortByValue(numbers);
    std::cout << "Отсортированный массив по значению:" << std::endl;
    for (int idx = 0; idx < 10; idx++) {
        std::cout << numbers[idx] << " ";
    }
    std::cout << std::endl;

    numbers = { 1, 0, 2, 9, 3, 8, 4, 7, 5, 6 };

    std::cout << "Массив: " << std::endl;
    for (int idx = 0; idx < 10; idx++) {
        std::cout << numbers[idx] << " ";
    }
    std::cout << std::endl;

    sortByReference(numbers);
    std::cout << "Отсортированный массив по ссылке:" << std::endl;
    for (int idx = 0; idx < 10; idx++) {
        std::cout << numbers[idx] << " ";
    }
    std::cout << std::endl;

    numbers = { 1, 0, 2, 9, 3, 8, 4, 7, 5, 6 };

    std::cout << "Массив: " << std::endl;
    for (int idx = 0; idx < 10; idx++) {
        std::cout << numbers[idx] << " ";
    }
    std::cout << std::endl;

    sortByPointer(&numbers);
    std::cout << "Отсортированный массив по указателю:" << std::endl;
    for (int idx = 0; idx < 10; idx++) {
        std::cout << numbers[idx] << " ";
    }
    std::cout << std::endl;

    return 0;
}
