#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QRegularExpressionValidator>
#include "person.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QRadioButton;
class QPushButton;
class QLabel;
class QButtonGroup;
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSaveButtonClicked();
    void onResetButtonClicked();

private:
    // Поля
    QLineEdit* edit1; // Предмет
    QLineEdit* edit2; // Преподаватель
    QLineEdit* edit3; // Аудитория
    QLineEdit* edit4; // Номер пары

    // Тип занятия
    QRadioButton* rad1; // Лекция
    QRadioButton* rad2; // Практика
    QButtonGroup* group1;

    // Ожидания
    QCheckBox* chk1; // Контрольная
    QCheckBox* chk2; // Посещения
    QCheckBox* chk3; // Отмена

    // Кнопки
    QPushButton* btnSave;
    QPushButton* btnReset;

    // Метки ошибок
    QLabel* err1;
    QLabel* err2;
    QLabel* err3;
    QLabel* err4;
    QLabel* err5;

    // Проверка ввода
    QRegularExpressionValidator* val1;
    QRegularExpressionValidator* val2;
    QRegularExpressionValidator* val3;
    QRegularExpressionValidator* val4;

    // Вспомогательные методы
    void setupValidators();
    void setupUI();
    bool validateInputs();
    void saveToFile(const Person& person);
    QList<QString> getSelectedExpectations();
};

#endif // MAINWINDOW_H
