#include <iostream>

// Главная функция программы
int main() {
    // Создаём двумерный массив 2x2 с динамической памятью
    int** arr = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        arr[i] = (int*)malloc(2 * sizeof(int));
    }

    // Ввод значений для массива
    // Проверяем, чтобы элементы первой строки были неотрицательными
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {

            std::cin >> arr[i][j];

            if (i == 0) {
                do {
                    if (arr[i][j] >= 0) break;

                    std::cout << "Введите новое НЕ отрицательное число: ";
                    std::cin >> arr[i][j];

                } while (arr[i][j] < 0);
            }
        }
    }

    // Сохраняем введённые числа для последующих вычислений
    int A = arr[0][0];
    int B = arr[0][1];
    int C = arr[1][0];
    int D = arr[1][1];

    // Определяем размеры нового расширенного массива
    int rows = 2 + A;
    int cols = 2 + B;

    // Расширяем массив по строкам
    arr = (int**)realloc(arr, rows * sizeof(int*));
    for (int i = 2; i < rows; i++) {
        arr[i] = (int*)malloc(cols * sizeof(int));
    }

    // Расширяем существующие строки и заполняем формулой
    for (int i = 0; i < 2; i++) {
        int old_data[2]; // Сохраняем старые значения строки
        for (int j = 0; j < 2; j++) {
            old_data[j] = arr[i][j];
        }

        arr[i] = (int*)realloc(arr[i], cols * sizeof(int)); 

        // Заполняем всю строку формулой i*C + j*D
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i * C + j * D; 
        }

        // Восстанавливаем старые значения справа
        for (int j = 0; j < 2; j++) {
            arr[i][j + B] = old_data[j];
        }
    }

    // Заполняем новые строки формулой
    for (int i = 2; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i * C + j * D;
        }
    }

    // Сохраняем блок верхнего левого угла для перемещения
    int** blk = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        blk[i] = (int*)malloc(2 * sizeof(int));
        for (int j = 0; j < 2; j++) {
            blk[i][j] = arr[i][j + B];
        }
    }

    // Перемещаем блок в новый угол
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            arr[i + A][j + B] = blk[i][j];
        }
    }

    // Заполняем ячейки, которые находятся левее или выше блока, формулой
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i < A || j < B ) {
                arr[i][j] = i * C + j * D;
            }
        }
    }

    // Вывод всего массива
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Обработка массива: поиск строк с нулями и их удаление
    processMatrix(rows, cols, arr);

    // Освобождаем память блока
    for (int i = 0; i < 2; i++) {
        free(blk[i]);
    }
    free(blk);

    return 0;
}

// Функция обработки массива: находит строки с нулями и создаёт новый массив без них
void processMatrix(int rows, int cols, int** arr) {
    int zeroCount = 0; // Счётчик строк с нулями
    int* zeroRow = 0;

    // Проверяем все строки на наличие нулей
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == 0) {
                zeroCount++;
                break;
            }
        }
    }

    // Если есть строки с нулями
    if (zeroCount > 0) {
        zeroRow = (int*)malloc(zeroCount * sizeof(int));
        int idx = 0;

        // Сохраняем индексы строк с нулями
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (arr[i][j] == 0) {
                    zeroRow[idx] = i;
                    idx++;
                    break;
                }
            }
        }

        // Выводим номера строк с нулями
        std::cout << "Строки с нулями: ";
        for (int i = 0; i < zeroCount; i++) {
            std::cout << zeroRow[i] << " ";
        }
        std::cout << std::endl;

        // Создаём новый массив без строк с нулями
        int newRows = rows - zeroCount;
        int** newArr = (int**)malloc(newRows * sizeof(int*));

        int newIndex = 0;
        for (int i = 0; i < rows; i++) {
            int removeFlag = 0;

            // Проверяем, нужно ли удалить текущую строку
            for (int k = 0; k < zeroCount; k++) {
                if (i == zeroRow[k]) {
                    removeFlag = 1;
                    break;
                }
            }

            // Если строку не нужно удалять, копируем её в новый массив
            if (removeFlag == 0) {
                newArr[newIndex] = (int*)malloc(cols * sizeof(int));
                for (int j = 0; j < cols; j++) {
                    newArr[newIndex][j] = arr[i][j];
                }
                newIndex++;
            }
        }

        // Вывод нового массива
        for (int i = 0; i < newRows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << newArr[i][j] << " ";
            }
            std::cout << std::endl;
        }

        // Освобождение памяти старого массива
        for (int i = 0; i < rows; i++) {
            free(arr[i]);
        }
        free(arr);
        free(zeroRow);
    }
    else {
        // Если нулей нет, выводим исходный массив
        std::cout << "Строки с нулями не найдены" << std::endl;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}





// Задание №2
/* 
#include <iostream>


int main() {
    int a;
    int b;
    std::cout << "Введите число a: ";
    std::cin >> a;
    std::cout << "Введите число b: ";
    std::cin >> b;
    int* ptr_a = new int(a);
    int* ptr_b = new int(b);
    *ptr_a *= 2;
    int sw = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = sw;
    std::cout << "Адрес ptr_a: " << ptr_a << ", значение: " << *ptr_a << std::endl;
    std::cout << "Адрес ptr_b: " << ptr_b << ", значение: " << *ptr_b << std::endl;
    delete ptr_a;
    delete ptr_b;
    return 0;
}
*/