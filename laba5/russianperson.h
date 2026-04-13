#ifndef RUSSIANPERSON_H
#define RUSSIANPERSON_H

#include "person.h"

class RussianPerson : public Person {
private:
    QString patronymic_;

    // Локальная проверка отчества (уже настроена на русский)
    bool isValidPatronymic(const QString& s) const {
        if (s.isEmpty()) return true;
        QRegularExpression re("^[А-ЯЁ][а-яё]{0,49}$");
        return re.match(s).hasMatch();
    }

protected:
    // ПЕРЕОПРЕДЕЛЯЕМ проверку для этого класса
    // Теперь методы setFirstName и setLastName будут использовать именно русскую проверку
    bool isValidName(const QString& s) const override {
        return isValidRussianName(s);
    }

public:
    RussianPerson();
    RussianPerson(const QString& lastName_, const QString& firstName_,
                  const QString& patronymic_, const Date& birthDate_);

    QString getFullName() const override;
    void craft(QWidget* parent_ = nullptr) override;

    bool setPatronymic(const QString& patr_);
    QString getPatronymic() const { return patronymic_; }
};

#endif // RUSSIANPERSON_H