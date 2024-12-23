#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../DAO/iaccountsdao.h"
#include "../../Core/Entities/account.h"
#include "../../Core/LogFilesHandler/logfileshandler.h"
#include "qchartview.h"

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
    void onDescriptionBtnClicked();
    void onEditAccountBtnClicked();
    void onDeleteAccountBtnClicked();
    void onLoadBtnClicked();

private:
    Account _currentAccount;
    QScopedPointer<IAccountsDAO> _accountsDAO;
    QScopedPointer<LogFilesHandler> _logFilesHandler;
    QList<QString> _accountsNamesList;
    QChartView* chartView;

    Ui::MainWindow *_ui;

    void loadAccountsNames();
    void showAccountData(const Account& account);
    bool deleteAccount(const QString& accountName);

};
#endif
