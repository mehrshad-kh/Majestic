#include <QPixmap>
#include <QVBoxLayout>

#include "about_dialog.hpp"
#include "ui_about_dialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::AboutDialog)
{
    ui_->setupUi(this);
    setUp();
}

AboutDialog::~AboutDialog()
{
    delete ui_;
}

void AboutDialog::setUp()
{
    setUpUi();
    setAttribute(Qt::WA_DeleteOnClose);
}

void AboutDialog::setUpUi()
{
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setObjectName("vBoxLayout");
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    image_label_ = new QLabel();
    image_label_->setObjectName("imageLabel");
    QPixmap pix = QPixmap(":/res/images/logo.png");
    image_label_->setPixmap(pix.scaled(200, 150, Qt::KeepAspectRatio));
    vBoxLayout->addWidget(image_label_, 0, Qt::AlignCenter);
    
    name_label_ = new QLabel();
    name_label_->setObjectName("nameLabel");
    name_label_->setText("<h1>Majestic</h1>");
    name_label_->setStyleSheet("font-weight: bold");
    vBoxLayout->addWidget(name_label_, 0, Qt::AlignCenter);
    
    explanation_label_ = new QLabel();
    explanation_label_->setObjectName("explanationLabel");
    explanation_label_->setText("A software program for use within the community.");
    vBoxLayout->addWidget(explanation_label_, 0, Qt::AlignCenter);

    version_label_ = new QLabel();
    version_label_->setObjectName("versionLabel");
    version_label_->setText("Majestic version 0.0.1");
    vBoxLayout->addWidget(version_label_, 0, Qt::AlignCenter);
    
    copyright_label_ = new QLabel();
    copyright_label_->setObjectName("copyrightLabel");
    copyright_label_->setText(u8"\u00A9 2023 Mehrshad Khansarian\nAll Rights Reserved.");
    copyright_label_->setAlignment(Qt::AlignCenter);
    vBoxLayout->addWidget(copyright_label_, 0, Qt::AlignCenter);
}
