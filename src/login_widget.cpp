#include "login_widget.hpp"
#include "ui_login_widget.h"

#include <argon2.h>

#include <fmt/core.h>

#include <algorithm>
#include <stdexcept>

#include <QByteArray>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <QMessageBox>

#include "constants.hpp"

LoginWidget::LoginWidget(const std::unique_ptr<Client>& client, QWidget *parent) :
    client_(client),
    QWidget(parent),
    ui_(new Ui::LoginWidget)
{
    ui_->setupUi(this);

    setUp();
}

LoginWidget::~LoginWidget()
{
    delete ui_;
}

void LoginWidget::logInButtonClicked(bool checked)
{
    QString username {username_line_edit_->text()};
    QString password {password_line_edit_->text()};

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter your username and password.");
        return;
    }

    std::vector<uint8_t> salt;
    try {
        salt = client_->retrieveMySalt(username.toStdString());
    } catch (const std::runtime_error& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(fmt::format("{:s}\n{:s}", "Could not connect", e.what())));
        return;
    }

    std::vector<uint8_t> hash;
    try {
        hash = computeHash(password.toStdString(), salt);
    } catch (const std::runtime_error& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(fmt::format("{:s}\n{:s}", "Failed to compute hash", e.what())));
        return;
    }

    QByteArray hash_as_byte_array(reinterpret_cast<const char *>(hash.data()), hash.size());
    QByteArray b64 = hash_as_byte_array.toBase64();

    // Authenticate hash with server.
    qInfo() << b64;
}

// Possible error: Output has not been tested against other sources.
std::vector<uint8_t> LoginWidget::computeHash(const std::string& password, const std::vector<uint8_t>& salt)
{
    uint8_t salt_as_array[kSaltLen] {0};
    std::copy(salt.begin(), salt.end(), salt_as_array);

    uint8_t hash[kHashLen] {0};

    int rc = argon2i_hash_raw(kTimeCost, kMemoryCost, kParallelism, password.c_str(), password.length(), salt_as_array, kSaltLen, hash, kHashLen);

    if (rc != ARGON2_OK) {
        throw std::runtime_error(argon2_error_message(rc));
    }

    return std::vector<uint8_t>(hash, hash + kHashLen);
}

void LoginWidget::connectSlots()
{
    connect(log_in_button_, &QPushButton::clicked, this, &LoginWidget::logInButtonClicked);
}

void LoginWidget::setUp()
{
    setUpUi();
    connectSlots();
}

void LoginWidget::setUpUi()
{
    setUpHBox();
    setUpLeftWidget();
    setUpLeftVBox();
    setUpImageLabel();
    setUpRightWidget();
    setUpRightVBox();
    setUpUsernameLineEdit();
    setUpPasswordLineEdit();
    setUpLogInButton();
}

void LoginWidget::setUpHBox()
{
    hbox_ = new QHBoxLayout(this);
}

void LoginWidget::setUpLeftWidget()
{
    left_widget_ = new QWidget();
    hbox_->addWidget(left_widget_);
}

void LoginWidget::setUpLeftVBox()
{
    left_vbox_ = new QVBoxLayout(left_widget_);
}

void LoginWidget::setUpImageLabel()
{
    image_label_ = new QLabel("Majestic");
    QPixmap pix = QPixmap(":/res/images/logo.png");
    image_label_->setPixmap(pix.scaled(200, 150, Qt::KeepAspectRatio));
    left_vbox_->addWidget(image_label_);
}

void LoginWidget::setUpRightWidget()
{
    right_widget_ = new QWidget();
    hbox_->addWidget(right_widget_);
}

void LoginWidget::setUpRightVBox()
{
    right_vbox_ = new QVBoxLayout(right_widget_);
}

void LoginWidget::setUpUsernameLineEdit()
{
    username_line_edit_ = new QLineEdit();
    username_line_edit_->setPlaceholderText("Username");
    right_vbox_->addWidget(username_line_edit_);
}

void LoginWidget::setUpPasswordLineEdit()
{
    password_line_edit_ = new QLineEdit();
    password_line_edit_->setPlaceholderText("Password");
    password_line_edit_->setEchoMode(QLineEdit::Password);
    right_vbox_->addWidget(password_line_edit_);
}

void LoginWidget::setUpLogInButton()
{
    log_in_button_ = new QPushButton("Log in");
    log_in_button_->setDefault(true);
    right_vbox_->addWidget(log_in_button_);
}
