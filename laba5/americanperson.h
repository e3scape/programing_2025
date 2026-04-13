#ifndef AMERICANPERSON_H
#define AMERICANPERSON_H

#include "person.h"

class AmericanPerson : public Person {
private:
    QString middleName_;

protected:
    // ДОБАВЬ ЭТОТ БЛОК (реализация для латиницы)
    bool isValidName(const QString& s) const override {
        return isValidEnglishName(s);
    }

public:
    AmericanPerson();
    AmericanPerson(const QString& firstName_, const QString& middleName_,
                   const QString& lastName_, const Date& birthDate_);

    QString getFullName() const override;
    void craft(QWidget* parent_ = nullptr) override;

    bool setMiddleName(const QString& mid_);
    QString getMiddleName() const { return middleName_; }
};

#endif
