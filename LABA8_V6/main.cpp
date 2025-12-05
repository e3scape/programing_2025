#include <iostream>
#include <string>

using namespace std;

// Структура "Вагон"
struct Car {
    int id;          // Номер вагона
    string cargoType; // Тип груза
    int load;         // Вес груза
    Car* nextCar;     // Указатель на следующий вагон
};

// Структура "Локомотив"
struct Engine {
    char label;       // Код локомотива
    Car* firstCar;    // Первый вагон в составе
    Engine* nextEng;  // Следующий локомотив
};

// Создание нового вагона
Car* createCar(int id, string cargoType, int load) {
    Car* car = new Car;
    car->id = id;
    car->cargoType = cargoType;
    car->load = load;
    car->nextCar = nullptr;
    return car;
}

// Создание нового локомотива
Engine* createEngine(char label) {
    Engine* eng = new Engine;
    eng->label = label;
    eng->firstCar = nullptr;
    eng->nextEng = nullptr;
    return eng;
}

// Прицепка вагона к локомотиву
void addCar(Engine* eng, int id, string cargoType, int load) {
    Car* newCar = createCar(id, cargoType, load);
    if (eng->firstCar == nullptr) {
        eng->firstCar = newCar;
    } else {
        Car* ptr = eng->firstCar;
        while (ptr->nextCar != nullptr) {
            ptr = ptr->nextCar;
        }
        ptr->nextCar = newCar;
    }
}

// Просмотр состава локомотива
void showEngine(Engine* eng) {
    if (eng == nullptr) {
        cout << "Локомотив не найден" << endl;
        return;
    }
    cout << "Локомотив [" << eng->label << "]" << endl;
    if (eng->firstCar == nullptr) {
        cout << "  Вагонов нет" << endl;
    } else {
        Car* ptr = eng->firstCar;
        int count = 0;
        int totalLoad = 0;
        while (ptr != nullptr) {
            count++;
            totalLoad += ptr->load;
            cout << "  Вагон " << count << ": Номер" << ptr->id
                 << ", груз: " << ptr->cargoType
                 << ", вес: " << ptr->load << "т" << endl;
            ptr = ptr->nextCar;
        }
        cout << "  Итого: " << count << " вагонов, общий вес: "
             << totalLoad << "т" << endl;
    }
}

// Отцепка последнего вагона
void detachLastCar(Engine* eng) {
    if (eng == nullptr || eng->firstCar == nullptr) {
        cout << "Нечего отцепить" << endl;
        return;
    }
    if (eng->firstCar->nextCar == nullptr) {
        cout << "Отцеплен вагон Номер" << eng->firstCar->id << endl;
        delete eng->firstCar;
        eng->firstCar = nullptr;
        return;
    }
    Car* ptr = eng->firstCar;
    while (ptr->nextCar->nextCar != nullptr) {
        ptr = ptr->nextCar;
    }
    cout << "Отцеплен вагон Номер" << ptr->nextCar->id << endl;
    delete ptr->nextCar;
    ptr->nextCar = nullptr;
}

// Поиск локомотива по коду
Engine* findEngine(Engine* head, char label) {
    Engine* ptr = head;
    while (ptr != nullptr) {
        if (ptr->label == label) return ptr;
        ptr = ptr->nextEng;
    }
    return nullptr;
}

// Вывод всех локомотивов
void printAllEngines(Engine* head) {
    Engine* ptr = head;
    while (ptr != nullptr) {
        showEngine(ptr);
        cout << endl;
        ptr = ptr->nextEng;
    }
}

// Инициализация тестовых данных
void initEngines(Engine*& head) {
    head = createEngine('A');
    Engine* engB = createEngine('B');
    Engine* engC = createEngine('C');

    head->nextEng = engB;
    engB->nextEng = engC;

    addCar(head, 100, "Уголь", 50);
    addCar(head, 101, "Щебень", 69);
    addCar(head, 102, "Зерно", 45);

    addCar(engB, 200, "Автомобили и запчасти", 75);
    addCar(engB, 201, "Древесина", 55);
    addCar(engB, 202, "Контейнеры", 60);

    addCar(engC, 300, "Металл", 70);
    addCar(engC, 301, "Корма", 65);
    addCar(engC, 302, "Нефтепродукты", 58);
}

// Очистка памяти
void cleanupEngines(Engine* head) {
    Engine* eng = head;
    while (eng != nullptr) {
        Car* car = eng->firstCar;
        while (car != nullptr) {
            Car* tmp = car;
            car = car->nextCar;
            delete tmp;
        }
        Engine* tmpEng = eng;
        eng = eng->nextEng;
        delete tmpEng;
    }
}

int main() {
    Engine* yard = nullptr;
    initEngines(yard);

    int choice;
    do {
        cout << "\n МЕНЮ " << endl;
        cout << "1 - Просмотреть состав" << endl;
        cout << "2 - Создать новый локомотив" << endl;
        cout << "3 - Создать новый вагон" << endl;
        cout << "4 - Вывод всех составов" << endl;
        cout << "5 - Отцепить последний вагон" << endl;
        cout << "0 - Выход" << endl;
        cout << "Выберите: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                char label;
                cout << "Введите код локомотива (A-Z): ";
                cin >> label;
                Engine* eng = findEngine(yard, label);
                showEngine(eng);
                break;
            }
            case 2: {
                char label;
                cout << "Введите код нового локомотива (A-Z): ";
                cin >> label;
                if (findEngine(yard, label) != nullptr) {
                    cout << "Локомотив с таким кодом уже существует" << endl;
                    break;
                }
                Engine* newEng = createEngine(label);
                newEng->nextEng = yard;
                yard = newEng;
                cout << "Локомотив [" << label << "] создан" << endl;
                break;
            }
            case 3: {
                char label;
                int id, load;
                string cargo;
                cout << "К какому локомотиву прицепить (A-Z): ";
                cin >> label;
                Engine* eng = findEngine(yard, label);
                if (!eng) {
                    cout << "Локомотив не найден" << endl;
                    break;
                }
                cout << "Номер вагона (0-999): ";
                cin >> id;
                if (id < 0 || id > 999) {
                    cout << "Некорректный номер" << endl;
                    break;
                }
                cout << "Груз: ";
                cin.ignore();
                getline(cin, cargo);
                cout << "Вес (тонны): ";
                cin >> load;
                addCar(eng, id, cargo, load);
                cout << "Вагон добавлен к локомотиву [" << label << "]" << endl;
                break;
            }
            case 4:
                if (yard == nullptr)
                    cout << "Локомотивов нет" << endl;
                else
                    printAllEngines(yard);
                break;
            case 5: {
                char label;
                cout << "От какого локомотива отцепить (A-Z): ";
                cin >> label;
                Engine* eng = findEngine(yard, label);
                if (eng) detachLastCar(eng);
                else cout << "Локомотив не найден" << endl;
                break;
            }
            case 0:
                cout << "Выход" << endl;
                break;
            default:
                cout << "Неверная команда" << endl;
        }
    } while (choice != 0);

    cleanupEngines(yard);
    return 0;
}