#include "main_window.hpp"
#include "ui_main_window.h"

#include <grpcpp/create_channel.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    setUp();
    client_ = std::make_unique<Client>(
        grpc::CreateChannel("localhost:8080", grpc::InsecureChannelCredentials()));
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::aboutActionTriggered(bool checked)
{
    about_dialog_ = new AboutDialog(this);
    about_dialog_->show();
}

void MainWindow::connectSlots()
{
    connect(about_action_, &QAction::triggered, this, &MainWindow::aboutActionTriggered);
}

void MainWindow::setUp()
{
    setUpUi();
    connectSlots();
}

void MainWindow::setUpLoginWidget()
{
    setAsCentralWidget<LoginWidget>(login_widget_);
}

void MainWindow::setUpMenuBar()
{
    menu_bar_ = new QMenuBar(this);
    menu_bar_->setObjectName("menuBar");
    setMenuBar(menu_bar_);

    app_menu_ = new QMenu("Majestic", menu_bar_);
    app_menu_->setObjectName("appMenu");
    menu_bar_->addMenu(app_menu_);

    about_action_ = new QAction("About Majestic", app_menu_);
    about_action_->setObjectName("aboutAction");
    about_action_->setMenuRole(QAction::AboutRole);
    app_menu_->addAction(about_action_);
}

void MainWindow::setUpUi()
{
    setUpMenuBar();
    setUpLoginWidget();
}

