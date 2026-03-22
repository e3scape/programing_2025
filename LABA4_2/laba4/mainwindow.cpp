#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRegularExpression>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Пара");
    setMinimumSize(600, 400);
    setupValidators();
    setupUI();
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);
}

MainWindow::~MainWindow()
{
    delete val1;
    delete val2;
    delete val3;
    delete val4;
}

void MainWindow::setupValidators()
{
    QRegularExpression subjectRegex("^[А-Я][а-я]*$");
    val1 = new QRegularExpressionValidator(subjectRegex, this);

    QRegularExpression teacherRegex("^[А-Я][а-я]*\\s[А-Я]\\.([А-Я]\\.)?$");
    val2 = new QRegularExpressionValidator(teacherRegex, this);

    QRegularExpression audienceRegex("^(10[1-9]|1[1-3][0-9]|140|"
                                     "20[1-9]|2[1-3][0-9]|240|"
                                     "30[1-9]|3[1-3][0-9]|340|"
                                     "40[1-9]|4[1-3][0-9]|440)А?$");
    val3 = new QRegularExpressionValidator(audienceRegex, this);

    QRegularExpression scheduleRegex("^[1-8]$");
    val4 = new QRegularExpressionValidator(scheduleRegex, this);
}

void MainWindow::setupUI()
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Группа ввода без заголовка и рамки (стиль как на фото)
    QGroupBox* inputGroup = new QGroupBox();
    inputGroup->setStyleSheet("QGroupBox { border: none; }");
    QGridLayout* grid = new QGridLayout(inputGroup);

    // Создание полей
    edit1 = new QLineEdit(); // Предмет
    edit2 = new QLineEdit(); // Преподаватель
    edit3 = new QLineEdit(); // Аудитория
    edit4 = new QLineEdit(); // Номер в расписании

    // ВАЖНО: Убираем прямую привязку валидаторов, чтобы разрешить свободный ввод.
    // Проверка будет вызываться вручную в методе validateInputs().
    // edit1->setValidator(val1);
    // edit2->setValidator(val2);
    // edit3->setValidator(val3);
    // edit4->setValidator(val4);

    edit4->setMaxLength(1); // Номер пары - 1 цифра

    // Тип занятия
    rad1 = new QRadioButton("Лекция");
    rad2 = new QRadioButton("Практика");
    group1 = new QButtonGroup(this);
    group1->addButton(rad1);
    group1->addButton(rad2);

    QHBoxLayout* typeLayout = new QHBoxLayout();
    typeLayout->addWidget(rad1);
    typeLayout->addWidget(rad2);
    typeLayout->addStretch();

    // Ожидания
    chk1 = new QCheckBox("Контрольная");
    chk2 = new QCheckBox("Проверка посещений");
    chk3 = new QCheckBox("Отмена");

    // Метки ошибок (делаем их красными восклицательными знаками)
    QString errorStyle = "color: red; font-weight: bold;";
    err1 = new QLabel("!"); err1->setStyleSheet(errorStyle); err1->hide();
    err2 = new QLabel("!"); err2->setStyleSheet(errorStyle); err2->hide();
    err3 = new QLabel("!"); err3->setStyleSheet(errorStyle); err3->hide();
    err4 = new QLabel("!"); err4->setStyleSheet(errorStyle); err4->hide();
    err5 = new QLabel("!"); err5->setStyleSheet(errorStyle); err5->hide();

    // Добавление в сетку (Метка | Поле | Ошибка)
    int row = 0;
    grid->addWidget(new QLabel("Предмет"), row, 0);
    grid->addWidget(edit1, row, 1);
    grid->addWidget(err1, row, 2);
    row++;

    grid->addWidget(new QLabel("Преподаватель"), row, 0);
    grid->addWidget(edit2, row, 1);
    grid->addWidget(err2, row, 2);
    row++;

    grid->addWidget(new QLabel("Аудитория"), row, 0);
    grid->addWidget(edit3, row, 1);
    grid->addWidget(err3, row, 2);
    row++;

    grid->addWidget(new QLabel("Номер в расписании"), row, 0);
    grid->addWidget(edit4, row, 1);
    grid->addWidget(err4, row, 2);
    row++;

    grid->addWidget(new QLabel("Тип"), row, 0);
    grid->addLayout(typeLayout, row, 1);
    grid->addWidget(err5, row, 2);
    row++;

    grid->addWidget(new QLabel("Ожидание"), row, 0, Qt::AlignTop);
    QVBoxLayout* chkLayout = new QVBoxLayout(); // Вертикально как на фото
    chkLayout->addWidget(chk1);
    chkLayout->addWidget(chk2);
    chkLayout->addWidget(chk3);
    grid->addLayout(chkLayout, row, 1);
    row++;

    mainLayout->addWidget(inputGroup);

    // Кнопки со стилями как на фото
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    btnReset = new QPushButton("Сброс");
    btnSave = new QPushButton("Сохранить");

    btnReset->setStyleSheet("background-color: #d9534f; color: white; padding: 10px; font-weight: bold; border-radius: 5px;");
    btnSave->setStyleSheet("background-color: #a2e06b; color: black; padding: 10px; font-weight: bold; border-radius: 5px;");

    buttonLayout->addStretch();
    buttonLayout->addWidget(btnReset);
    buttonLayout->addSpacing(50); // Отступ между кнопками
    buttonLayout->addWidget(btnSave);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
}




QList<QString> MainWindow::getSelectedExpectations()
{
    QList<QString> selected;
    if (chk1->isChecked())
        selected.append("Контрольная");
    if (chk2->isChecked())
        selected.append("Проверка посещений");
    if (chk3->isChecked())
        selected.append("Отмена");
    return selected;
}

bool MainWindow::validateInputs() {
    // Прячем старые ошибки
    err1->hide(); err2->hide(); err3->hide(); err4->hide(); err5->hide();

    bool ok = true;
    int pos = 0;
    QString t;

    // Проверяем каждое поле через валидатор вручную
    t = edit1->text(); if (val1->validate(t, pos) != QValidator::Acceptable) { err1->show(); ok = false; }
    t = edit2->text(); pos = 0; if (val2->validate(t, pos) != QValidator::Acceptable) { err2->show(); ok = false; }
    t = edit3->text(); pos = 0; if (val3->validate(t, pos) != QValidator::Acceptable) { err3->show(); ok = false; }
    t = edit4->text(); pos = 0; if (val4->validate(t, pos) != QValidator::Acceptable) { err4->show(); ok = false; }

    if (!rad1->isChecked() && !rad2->isChecked()) { err5->show(); ok = false; }

    return ok;
}


void MainWindow::saveToFile(const Person& person)
{
    QFile file("result.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    person.writeToFile(out);
    file.close();
    QMessageBox::information(this, "Успех", "Данные сохранены в result.txt");
}

void MainWindow::onSaveButtonClicked()
{
    if (!validateInputs()) {
        QMessageBox::warning(this, "Ошибка", "Исправьте ошибки в форме");
        return;
    }

    QString lessonType = rad1->isChecked() ? "Лекция" : "Практика";
    QList<QString> expectations = getSelectedExpectations();

    Person person(
        edit1->text(),
        edit2->text(),
        edit3->text(),
        edit4->text().toInt(),
        lessonType,
        expectations
        );

    saveToFile(person);
    qDebug() << "Сохранено:" << person.getS();
}

void MainWindow::onResetButtonClicked()
{
    edit1->clear();
    edit2->clear();
    edit3->clear();
    edit4->clear();

    group1->setExclusive(false);
    rad1->setChecked(false);
    rad2->setChecked(false);
    group1->setExclusive(true);

    chk1->setChecked(false);
    chk2->setChecked(false);
    chk3->setChecked(false);
}