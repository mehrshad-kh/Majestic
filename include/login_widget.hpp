#ifndef LOGIN_WIDGET_HPP
#define LOGIN_WIDGET_HPP

#include <memory>
#include <string>
#include <vector>

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

#include "client.hpp"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(const std::unique_ptr<Client>& client, QWidget *parent = nullptr);
    ~LoginWidget();

public slots:
    void logInButtonClicked(bool checked = false);

private:
    const std::unique_ptr<Client>& client_;

    Ui::LoginWidget *ui_;

    QHBoxLayout *hbox_;
    QLabel *image_label_;
    QLineEdit *password_line_edit_;
    QLineEdit *username_line_edit_;
    QPushButton *log_in_button_;
    QVBoxLayout *left_vbox_;
    QVBoxLayout *right_vbox_;
    QWidget *left_widget_;
    QWidget *right_widget_;

    std::vector<uint8_t> computeHash(const std::string& password, const std::vector<uint8_t>& salt);

    void setUp();
    void setUpUi();
    void connectSlots();

    void setUpHBox();
    void setUpLeftWidget();
    void setUpLeftVBox();
    void setUpImageLabel();
    void setUpRightWidget();
    void setUpRightVBox();
    void setUpUsernameLineEdit();
    void setUpPasswordLineEdit();
    void setUpLogInButton();
};

#endif // LOGIN_WIDGET_HPP
