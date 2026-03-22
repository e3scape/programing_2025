#include "person.h"
#include <QDebug>

// Конструктор
Person::Person(const QString& s, const QString& t,
               const QString& a, int n,
               const QString& l,
               const QList<QString>& e) : p1(s),
    p2(t),
    p3(a),
    p4(n),
    p5(l),
    p6(e)
{
    qDebug() << "Создан объект Person для предмета: " << s;
}

// Деструктор
Person::~Person()
{
    qDebug() << "Удален объект Person для предмета: " << p1;
}

// Запись в файл
void Person::writeToFile(QTextStream& out) const
{
    out << "   Информация о занятии   ";
    out << "Предмет: " << p1 << "\n";
    out << "Преподаватель: " << p2 << "\n";
    out << "Аудитория: " << p3 << "\n";
    out << "Номер пары: " << p4 << "\n";
    out << "Тип занятия: " << p5 << "\n";

    if (!p6.isEmpty()) {
        out << "Ожидания: ";
        for (int i = 0; i < p6.size(); ++i) {
            out << p6[i];
            if (i < p6.size() - 1){
                out << ",";
            }
        }
        out << "\n";
    }
    out << "\n";
}