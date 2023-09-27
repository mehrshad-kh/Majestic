#ifndef ABOUT_DIALOG_HPP
#define ABOUT_DIALOG_HPP

#include <QDialog>
#include <QLabel>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui_;
    QLabel *image_label_;
    QLabel *name_label_;
    QLabel *explanation_label_;
    QLabel *version_label_;
    QLabel *copyright_label_;

    void setUp();
    void setUpUi();
};

#endif // ABOUT_DIALOG_HPP
