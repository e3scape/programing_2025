#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>

class Person
{
public:
    // Конструктор
    Person(const QString& s, const QString& t,
           const QString& a, int n,
           const QString& l,
           const QList<QString>& e);
    ~Person();

    // Метод для записи в файл
    void writeToFile(QTextStream& out) const;

    // Геттеры
    QString getS() const { return p1; }
    QString getT() const { return p2; }
    QString getA() const { return p3; }
    int getN() const { return p4; }
    QString getL() const { return p5; }
    QList<QString> getE() const { return p6; }

    // Сеттеры
    void setS(const QString& s) { p1 = s; }
    void setT(const QString& t) { p2 = t; }
    void setA(const QString& a) { p3 = a; }
    void setN(int n) { p4 = n; }
    void setL(const QString& l) { p5 = l; }
    void setE(const QList<QString>& e) { p6 = e; }

private:
    QString p1;        // Предмет
    QString p2;        // ФИО
    QString p3;        // Номер аудитории
    int p4;            // Номер пары
    QString p5;        // Тип занятия
    QList<QString> p6; // Список ожиданий
};
#endif // PERSON_H