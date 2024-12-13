#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../DAO/iaccountsdao.h"
#include "../../Entities/account.h"

#include <QMainWindow>
#include <QList>
#include <QScopedPointer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddAccountBtnClicled();
    void onChooseAccountBtnClicked();

private:
    Account _currentAccount;
    QScopedPointer<IAccountsDAO> _accountsDAO;
    QList<QString> _accountsNamesList;

    Ui::MainWindow *_ui;

    void loadAccountsNames();
    void showAccountData(const Account& account);

};
#endif
