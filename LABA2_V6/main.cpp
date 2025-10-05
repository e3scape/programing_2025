#include <iostream>
#include <bitset>

int main() {
    short A,i;
    std:: cout <<"Введите число A: "; 
    std:: cin >> A;
    std:: cout <<"Введите бит(0-7): ";
    std:: cin >> i;
    if (i < 0 || i > 7) {
        std:: cout << "Eror"<< std::endl;
        return 1;
    }
    std:: bitset<8> b2 = A;
    std:: cout << "Битовая запись числа А: " << b2.to_string() << std::endl;
    int IBIT = (A >> i)&1;
    std::cout << "Бит i: " << IBIT << std::endl;
    if (IBIT == 0) {
        int otvet = A*A;
        otvet = otvet & ~(1 << i);
        std:: bitset<32>rezult = otvet;
        std::cout << "Квадрат числа А с 0 i-товым битом в 10-ой системе: " << rezult << std::endl;
        std::cout << "Квадрат числа А с 0 i-товым битом в 2-ой системе: " << rezult.to_string() << std::endl;
    }
    else {
        short number = 125;
        std:: bitset<8>number2 = number;
        int chislo = 170; //вводим его так как в двоичной системе 10101010 то есть все четные биты при & будут нулями
        short otvet =number&chislo;
        std:: bitset<8>rezult = otvet;
        std::cout << "Число 125 с измененными четными битами на 0 в десятичной системе счисления: " << otvet << std::endl;
        std::cout <<"Число 125 с измененными четными битами на 0 в двоичной системе счисления: " << rezult.to_string() << std::endl;
    }
} 

// Задание номер 2
/*
int main() {
    int N;
    std::cout << "Введите номер автобуса: ";
    std::cin >> N;
    
    switch(N){
    case 113: std::cout << "Калининград-Чапаево";break;
    case 114: case 141: std::cout << "Калининград-Зеленоградск";break;
    case 117: std::cout << "Калининград-Мамоново";break;
    case 118: std::cout << "Калининград-Светлогорск";break;
    case 119: std::cout << "Калининград-Пионерский";break;
    case 125: std::cout << "Калининград-Донское";break;
    case 136: std::cout << "Калининград-Партизанское";break;
    case 148: case 191: std::cout << "Калининград-Багартионовск";break;
    case 161: std::cout << "Калининград-Светлое";break;
    case 593: std::cout << "Калининград-Морское";break;
    case 802: std::cout << "Калининград-Гданьск";break;
    default: std::cout <<"Такого маршрута не существует";break;

    }

}
*/