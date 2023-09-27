#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <memory>
#include <type_traits>

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

#include "about_dialog.hpp"
#include "client.hpp"
#include "login_widget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void aboutActionTriggered(bool checked = false);

private:
    std::unique_ptr<Client> client_;

    Ui::MainWindow *ui_;

    LoginWidget *login_widget_;

    QAction *about_action_;
    QMenu *app_menu_;
    QMenuBar *menu_bar_;

    AboutDialog *about_dialog_;

    void connectSlots();
    template<typename T>
    requires(std::is_base_of<QWidget, T>::value)
    void setAsCentralWidget(T *central_widget)
    {
        // Delete current central widget.
        delete centralWidget();

        // Create new central widget.
        central_widget = new T(client_, this);
        setCentralWidget(central_widget);
    }
    void setUp();
    void setUpLoginWidget();
    void setUpMenuBar();
    void setUpUi();
};

#endif // MAIN_WINDOW_HPP
