#include "mainwindow.h"
#include "passform.h"
#include "russianperson.h"
#include "americanperson.h"
#include <QHeaderView>
#include <QDebug>

// Функция для показа ошибок
static void showFormatError(QWidget* parent, const QString& fieldName, const QString& expectedFormat, int lineNumber) {
    QMessageBox::warning(parent, "Ошибка формата",
                         QString("Строка %1: Неверный формат %2\n\n"
                                 "Ожидаемый формат: %3")
                             .arg(lineNumber)
                             .arg(fieldName)
                             .arg(expectedFormat));
}

MainWindow::MainWindow(QWidget* parent_) : QMainWindow(parent_) {
    setupUI();
}

MainWindow::~MainWindow() {
    clearData();
}

void MainWindow::setupUI() {
    QWidget* centralWidget_ = new QWidget(this);
    setCentralWidget(centralWidget_);
    this->setStyleSheet("background-color: white;");

    QVBoxLayout* mainLayout_ = new QVBoxLayout(centralWidget_);
    mainLayout_->setContentsMargins(20, 20, 20, 20);
    mainLayout_->setSpacing(15);

    table_ = new QTableWidget();
    table_->setColumnCount(4);

    QStringList headers;
    headers << "Фамилия" << "Имя" << "Отчество / 2-е имя" << "Дата рождения";
    table_->setHorizontalHeaderLabels(headers);

    table_->horizontalHeader()->setVisible(true);
    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table_->verticalHeader()->setVisible(false);
    table_->setShowGrid(true);
    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table_->setStyleSheet(
        "QTableWidget { "
        "   border: 3px solid black; "
        "   gridline-color: #d0d0d0; "
        "   background-color: white; "
        "   font-weight: bold; "
        "   font-size: 13px; "
        "}"
        "QHeaderView::section { "
        "   background-color: #f0f0f0; "
        "   color: black; "
        "   font-weight: bold; "
        "   border: 1px solid black; "
        "   padding: 5px; "
        "}"
        "QTableWidget::item { padding: 5px; }"
        );

    mainLayout_->addWidget(table_);

    // --- КНОПКА ПО ЦЕНТРУ ---
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch(1); // Пружина слева

    loadButton_ = new QPushButton("Загрузить");
    loadButton_->setFixedSize(160, 40);
    loadButton_->setStyleSheet(
        "QPushButton { background-color: #add8e6; border: 2px solid black; font-weight: bold; color: black; }"
        "QPushButton:hover { background-color: #bfefff; }"
        );
    btnLayout->addWidget(loadButton_);

    btnLayout->addStretch(1); // Пружина справа (теперь кнопка в центре)

    mainLayout_->addLayout(btnLayout);

    connect(loadButton_, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    connect(table_, &QTableWidget::doubleClicked, this, &MainWindow::onTableDoubleClicked);

    setWindowTitle("Регистратор пропусков");
    resize(850, 550);
}

QString MainWindow::getLastNameFromPerson(Person* person_) const {
    RussianPerson* russian = dynamic_cast<RussianPerson*>(person_);
    if (russian) {
        QStringList parts = russian->getFullName().split(" ");
        return parts.size() > 0 ? parts.value(0) : "";
    }

    AmericanPerson* american = dynamic_cast<AmericanPerson*>(person_);
    if (american) {
        QStringList parts = american->getFullName().split(" ");
        return parts.size() > 2 ? parts.value(2) : "";
    }

    return "";
}

QString MainWindow::getFirstNameFromPerson(Person* person_) const {
    RussianPerson* russian = dynamic_cast<RussianPerson*>(person_);
    if (russian) {
        QStringList parts = russian->getFullName().split(" ");
        return parts.size() > 1 ? parts.value(1) : "";
    }

    AmericanPerson* american = dynamic_cast<AmericanPerson*>(person_);
    if (american) {
        QStringList parts = american->getFullName().split(" ");
        return parts.size() > 0 ? parts.value(0) : "";
    }

    return "";
}

QString MainWindow::getMiddleOrPatronymicFromPerson(Person* person_) const {
    RussianPerson* russian = dynamic_cast<RussianPerson*>(person_);
    if (russian) {
        QStringList parts = russian->getFullName().split(" ");
        return parts.size() > 2 ? parts.value(2) : "-";
    }

    AmericanPerson* american = dynamic_cast<AmericanPerson*>(person_);
    if (american) {
        QStringList parts = american->getFullName().split(" ");
        return parts.size() > 1 ? parts.value(1) : "";
    }

    return "";
}

void MainWindow::onLoadButtonClicked() {
    QString filename_ = QFileDialog::getOpenFileName(this, "Выберите файл с данными", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (!filename_.isEmpty()) {
        loadFromFile(filename_);
    }
}

void MainWindow::loadFromFile(const QString& filename_) {
    QFile file_(filename_);
    if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    clearData(); // Очищаем таблицу перед новой загрузкой
    QTextStream in_(&file_);
    in_.setEncoding(QStringConverter::Utf8); // Чтобы русский текст не ломался

    QString oshibki = ""; // Сюда собираем все косяки из файла
    int lineNumber_ = 0;

    while (!in_.atEnd()) {
        QString line_ = in_.readLine().trimmed();
        lineNumber_++;
        if (line_.isEmpty()) continue;

        QStringList parts_ = line_.split(",");
        if (parts_.size() < 7) {
            oshibki += QString("Строка %1: Не хватает данных (нужно 7 полей через запятую)\n").arg(lineNumber_);
            continue;
        }

        int code_ = parts_[0].toInt();
        Person* person = nullptr;

        // --- КОД 1: РУССКИЙ (Фамилия, Имя, Отчество, Д, М, Г) ---
        if (code_ == 1) {
            QString ln = parts_[1].trimmed();
            QString fn = parts_[2].trimmed();
            QString mn = parts_[3].trimmed();
            if (mn == "-" || mn == "—") mn = "";

            int d = parts_[4].toInt();
            int m = parts_[5].toInt();
            int y = parts_[6].toInt();

            if (!Date::isValidDateStatic(d, m, y)) {
                oshibki += QString("Строка %1: Ошибка даты (Пример: 22,01,2001)\n").arg(lineNumber_);
                continue;
            }

            RussianPerson* rp = new RussianPerson();
            bool hasErr = false;
            if (!rp->setLastName(ln)) { oshibki += QString("Строка %1: Ошибка фамилии (Нужны русские буквы)\n").arg(lineNumber_); hasErr = true; }
            if (!rp->setFirstName(fn)) { oshibki += QString("Строка %1: Ошибка имени (Нужны русские буквы)\n").arg(lineNumber_); hasErr = true; }

            if (hasErr) { delete rp; continue; }

            rp->setPatronymic(mn);
            rp->setBirthDate(Date(d, m, y));
            person = rp;
        }
        // --- КОД 2: АМЕРИКАНЕЦ (James-Фамилия, Lebron-Имя, Raymon-Второе, М, Д, Г) ---
        else if (code_ == 2) {
            QString ln = parts_[1].trimmed(); // James (Фамилия)
            QString fn = parts_[2].trimmed(); // Lebron (Имя)
            QString mn = parts_[3].trimmed(); // Raymon (Второе имя)

            int m = parts_[4].toInt(); // Сначала Месяц
            int d = parts_[5].toInt(); // Потом День
            int y = parts_[6].toInt();

            if (!Date::isValidDateStatic(d, m, y)) {
                oshibki += QString("Строка %1: Ошибка даты (Ожидалось: ММ,ДД,ГГГГ)\n").arg(lineNumber_);
                continue;
            }

            AmericanPerson* ap = new AmericanPerson();
            bool hasErr = false;
            if (!ap->setLastName(ln)) { oshibki += QString("Строка %1: Ошибка фамилии '%2' (Нужна латиница)\n").arg(lineNumber_).arg(ln); hasErr = true; }
            if (!ap->setFirstName(fn)) { oshibki += QString("Строка %1: Ошибка имени '%2' (Нужна латиница)\n").arg(lineNumber_).arg(fn); hasErr = true; }
            if (!ap->setMiddleName(mn)) { oshibki += QString("Строка %1: Ошибка 2-го имени '%2' (Нужна латиница)\n").arg(lineNumber_).arg(mn); hasErr = true; }

            if (hasErr) { delete ap; continue; }

            ap->setBirthDate(Date(d, m, y));
            person = ap;
        }

        if (person) {
            persons_.append(person);
        }
    }

    file_.close();
    updateTable(); // Отрисовываем всё, что загрузили

    // Если были ошибки — выводим всё в одном окне
    if (!oshibki.isEmpty()) {
        QMessageBox::critical(this, "Ошибки при загрузке",
                              "В файле найдены ошибки:\n\n" + oshibki);
    } else if (persons_.size() > 0) {
        QMessageBox::information(this, "Успех", "Все данные успешно загружены!");
    }
}
void MainWindow::updateTable() {
    table_->setRowCount(persons_.size());

    for (int i_ = 0; i_ < persons_.size(); ++i_) {
        Person* person_ = persons_[i_];

        // Столбец 0: Фамилия
        QTableWidgetItem* lastNameItem_ = new QTableWidgetItem(getLastNameFromPerson(person_));

        // Столбец 1: Имя
        QTableWidgetItem* firstNameItem_ = new QTableWidgetItem(getFirstNameFromPerson(person_));

        // Столбец 2: Отчество/Middle name
        QTableWidgetItem* middleItem_ = new QTableWidgetItem(getMiddleOrPatronymicFromPerson(person_));

        // Столбец 3: Дата рождения
        QTableWidgetItem* dateItem_ = new QTableWidgetItem(person_->getFormattedBirthDate());

        table_->setItem(i_, 0, lastNameItem_);
        table_->setItem(i_, 1, firstNameItem_);
        table_->setItem(i_, 2, middleItem_);
        table_->setItem(i_, 3, dateItem_);
    }
}

void MainWindow::onTableDoubleClicked(const QModelIndex& index_) {
    if (!index_.isValid()) return;

    int row_ = index_.row();
    if (row_ >= 0 && row_ < persons_.size()) {
        PassForm* form_ = new PassForm(persons_[row_], this);
        connect(form_, &PassForm::personDeleted, this, &MainWindow::onPersonDeleted);
        form_->show();
    }
}

void MainWindow::onPersonDeleted(Person* person_) {
    int index_ = persons_.indexOf(person_);
    if (index_ != -1) {
        delete persons_[index_];
        persons_.remove(index_);
        updateTable();
        QMessageBox::information(this, "Успех", "Пропуск распечатан");
    }
}

void MainWindow::clearData() {
    qDeleteAll(persons_);
    persons_.clear();

    if (table_) {
        table_->setRowCount(0);
    }
}