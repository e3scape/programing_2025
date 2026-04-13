#include "passform.h"
#include "person.h"
#include <QDir>
#include <QRandomGenerator>
#include <QGraphicsDropShadowEffect>

PassForm::PassForm(Person* person_, QWidget* parent_)
    : QDialog(parent_), person_(person_) {

    // Общий стиль окна
    this->setStyleSheet("QDialog { background-color: #f5f6f7; }");

    setupUI();
    setupImage();

    setWindowTitle("Электронный пропуск");
    setFixedSize(380, 550); // Фиксированный размер лучше для дизайна карточки
    setModal(true);
}

PassForm::~PassForm() {}

void PassForm::setupUI() {
    QVBoxLayout* mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setContentsMargins(20, 20, 20, 20);
    mainLayout_->setSpacing(15);

    // Основной контейнер-карточка
    QFrame* card_ = new QFrame();
    card_->setStyleSheet("QFrame { background-color: white; border-radius: 15px; }");

    // Добавляем эффект тени для карточки
    QGraphicsDropShadowEffect* shadow_ = new QGraphicsDropShadowEffect();
    shadow_->setBlurRadius(15);
    shadow_->setOffset(0, 5);
    shadow_->setColor(QColor(0, 0, 0, 40));
    card_->setGraphicsEffect(shadow_);

    QVBoxLayout* cardLayout_ = new QVBoxLayout(card_);
    cardLayout_->setContentsMargins(15, 20, 15, 20);

    // Заголовок
    QLabel* titleLabel_ = new QLabel("ПРОПУСК");
    titleLabel_->setAlignment(Qt::AlignCenter);
    titleLabel_->setStyleSheet("color: #2c3e50; font-size: 22px; font-weight: bold; letter-spacing: 2px;");
    cardLayout_->addWidget(titleLabel_);

    // Разделитель
    QFrame* line_ = new QFrame();
    line_->setFrameShape(QFrame::HLine);
    line_->setStyleSheet("background-color: #ebedef;");
    cardLayout_->addWidget(line_);

    // Изображение с рамкой
    imageLabel_ = new QLabel();
    imageLabel_->setFixedSize(200, 200);
    imageLabel_->setAlignment(Qt::AlignCenter);
    // Делаем рамку для фото более аккуратной
    imageLabel_->setStyleSheet(
        "border: 2px solid #dfe6e9;"
        "border-radius: 10px;"
        "background-color: #fdfdfd;"
        );
    cardLayout_->addWidget(imageLabel_, 0, Qt::AlignCenter);

    // Информация о человеке
    nameLabel_ = new QLabel(person_->getFullName());
    nameLabel_->setAlignment(Qt::AlignCenter);
    nameLabel_->setWordWrap(true);
    nameLabel_->setStyleSheet("font-size: 18px; font-weight: 600; color: #34495e; margin-top: 10px;");
    cardLayout_->addWidget(nameLabel_);

    birthLabel_ = new QLabel("Дата рождения: " + person_->getFormattedBirthDate());
    birthLabel_->setAlignment(Qt::AlignCenter);
    birthLabel_->setStyleSheet("font-size: 13px; color: #7f8c8d;");
    cardLayout_->addWidget(birthLabel_);

    cardLayout_->addStretch();

    mainLayout_->addWidget(card_);

    // Контейнер для кнопок
    QHBoxLayout* buttonLayout_ = new QHBoxLayout();
    buttonLayout_->setSpacing(15);

    cancelButton_ = new QPushButton("ОТМЕНА");
    cancelButton_->setCursor(Qt::PointingHandCursor);
    cancelButton_->setFixedHeight(40);
    cancelButton_->setStyleSheet(
        "QPushButton { background-color: #ffffff; border: 1px solid #dcdde1; border-radius: 5px; color: #2f3640; font-weight: bold; }"
        "QPushButton:hover { background-color: #f5f6fa; }"
        "QPushButton:pressed { background-color: #dcdde1; }"
        );

    printButton_ = new QPushButton("ПЕЧАТЬ");
    printButton_->setFixedHeight(40);
    printButton_->setStyleSheet(
        "QPushButton { background-color: #3498db; border-radius: 5px; color: white; font-weight: bold; }"
        "QPushButton:hover { background-color: #2980b9; }"
        "QPushButton:pressed { background-color: #21618c; }"
        );

    connect(cancelButton_, &QPushButton::clicked, this, &PassForm::onCancel);
    connect(printButton_, &QPushButton::clicked, this, &PassForm::onPrint);

    buttonLayout_->addWidget(cancelButton_);
    buttonLayout_->addWidget(printButton_);
    mainLayout_->addLayout(buttonLayout_);
}

void PassForm::setupImage() {
    QPixmap pixmap_;

    // Используем упрощенную логику под твою папку img_res
    QDir dir_("img_res");
    QStringList filters_ = {"*.png", "*.jpg", "*.jpeg", "*.bmp"};
    QStringList files_ = dir_.entryList(filters_, QDir::Files);

    if (!files_.isEmpty()) {
        int randomIndex_ = QRandomGenerator::global()->bounded(files_.size());
        pixmap_.load(dir_.filePath(files_[randomIndex_]));
    }

    if (pixmap_.isNull()) {
        pixmap_ = QPixmap(200, 200);
        pixmap_.fill(Qt::lightGray);
    }

    // Ставим IgnoreAspectRatio, чтобы фото всегда ровно заполняло квадрат
    imageLabel_->setPixmap(pixmap_.scaled(200, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void PassForm::onCancel() {
    close();
}

void PassForm::onPrint() {
    emit personDeleted(person_);
    close();
}