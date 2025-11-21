#include <iostream>
#include <cstdlib>
#include <iomanip>


using namespace std;

const int BASE_R = 2;
const int BASE_C = 2;

void printOut(int** t, int h, int w) {
    cout << "\nМатрица (" << h << "x" << w << "):\n";
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            cout << setw(6) << t[x][y] << " ";
        }
        cout << "\n";
    }
}

int* scanZeroColumns(int** m, int h, int w, int& count) {
    count = 0;

    for (int col = 0; col < w; col++) {
        for (int row = 0; row < h; row++) {
            if (m[row][col] == 0) {
                count++;
                break;
            }
        }
    }

    int* buf = (int*)malloc(count * sizeof(int));
    int idx = 0;

    for (int col = 0; col < w; col++) {
        for (int row = 0; row < h; row++) {
            if (m[row][col] == 0) {
                buf[idx++] = col;
                break;
            }
        }
    }

    return buf;
}

void cutColumns(int**& m, int h, int w, int* del, int delCount, int& newWidth) {
    newWidth = w - delCount;

    for (int k = 0; k < delCount; k++) {
        int target = del[k] - k;
        for (int col = target; col < w - 1; col++) {
            for (int row = 0; row < h; row++) {
                m[row][col] = m[row][col + 1];
            }
        }
    }

    for (int r = 0; r < h; r++) {
        m[r] = (int*)realloc(m[r], newWidth * sizeof(int));
    }
}

void expand(int**& m) {
    int newH = m[0][0] + BASE_R;
    int newW = m[0][1] + BASE_C;

    m = (int**)realloc(m, newH * sizeof(int*));

    for (int i = 0; i < newH; i++) {
        if (i < BASE_R)
            m[i] = (int*)realloc(m[i], newW * sizeof(int));
        else
            m[i] = (int*)malloc(newW * sizeof(int));
    }

    for (int r = 0; r < newH; r++) {
        for (int c = 0; c < newW; c++) {
            if (r < BASE_R && c < BASE_C)
                continue;

            m[r][c] = (r - 1) * m[1][0] + (c - 1) * m[1][1];
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    int** arr = (int**)malloc(BASE_R * sizeof(int*));
    for (int i = 0; i < BASE_R; i++) {
        arr[i] = (int*)calloc(BASE_C, sizeof(int));
    }

    for (int i = 0; i < BASE_R; i++) {
        for (int j = 0; j < BASE_C; j++) {
            cin >> arr[i][j];
            while (arr[i][j] < 0) {
                cin >> arr[i][j];
            }
        }
    }

    int totalH = arr[0][0] + BASE_R;
    int totalW = arr[0][1] + BASE_C;

    expand(arr);
    printOut(arr, totalH, totalW);

    int zeroCount;
    int* zeroCols = scanZeroColumns(arr, totalH, totalW, zeroCount);

    int updatedWidth;
    cutColumns(arr, totalH, totalW, zeroCols, zeroCount, updatedWidth);

    printOut(arr, totalH, updatedWidth);

    free(zeroCols);

    for (int i = 0; i < totalH; i++) free(arr[i]);
    free(arr);

    return 0;
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