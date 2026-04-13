#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QWidget>
#include <QRegularExpression>
#include <QDebug>
#include "date.h"

class Person {
protected:
    QString firstName_;
    QString lastName_;
    Date birthDate_;

    DateFormat format_ = DateFormat::Russian;

    // Проверка для РУССКОГО языка (Код 1)
    bool isValidRussianName(const QString& s) const {
        if (s.isEmpty()) return false;
        // Только кириллица, первая буква заглавная
        QRegularExpression re("^[А-ЯЁ][а-яё\\s-]+$");
        return re.match(s).hasMatch();
    }

    // Проверка для АНГЛИЙСКОГО языка (Код 2)
    bool isValidEnglishName(const QString& s) const {
        if (s.isEmpty()) return false;
        // Только латиница, первая буква заглавная
        QRegularExpression re("^[A-Z][a-z\\s-]+$");
        return re.match(s).hasMatch();
    }

    // Общая заглушка (будет переопределена в наследниках)
    virtual bool isValidName(const QString& s) const = 0;

public:
    Person() : birthDate_() {}
    virtual ~Person() {}

    void setFormat(DateFormat f) { format_ = f; }

    virtual QString getFullName() const {
        return QString("%1 %2").arg(lastName_).arg(firstName_);
    }

    virtual void craft(QWidget* parent_ = nullptr) = 0;

    virtual QString getFormattedBirthDate() const {
        return birthDate_.toString(format_);
    }

    // Добавляем метод получения даты для таблицы (dd.mm.yyyy)
    Date getBirthDate() const { return birthDate_; }

    void setBirthDate(const Date& date_) { birthDate_ = date_; }

    // Эти методы теперь используют виртуальную проверку isValidName
    bool setFirstName(const QString& name_) {
        if (isValidName(name_)) {
            firstName_ = name_;
            return true;
        }
        return false;
    }

    bool setLastName(const QString& name_) {
        if (isValidName(name_)) {
            lastName_ = name_;
            return true;
        }
        return false;
    }
};

#endif