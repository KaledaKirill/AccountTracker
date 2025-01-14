#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../DAO/iaccountsdao.h"
#include "../../Core/Entities/account.h"
#include "../../Core/LogFilesHandler/logfileshandler.h"
#include "../../Core/ChartGenerator/chartgenerator.h"
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
    void onChooseDataRangeBtnClicked();

private:
    Account _currentAccount;
    QScopedPointer<IAccountsDAO> _accountsDAO;
    QScopedPointer<LogFilesHandler> _logFilesHandler;
    QList<QString> _accountsNamesList;
    QChartView* _chartView;
    QScopedPointer<ChartGenerator> _chartGenerator;


    Ui::MainWindow *_ui;

    void loadAccountsNames();
    void showAccountData(const Account& account);
    bool deleteAccount(const QString& accountName);
    void setupChartView();
    void showAccountChart(const Account& account);
    void showAccountChart(const Account& account, const QDate& startDate, const QDate& endDate);

    void handleFileInput(const QString &filePath);
    void handleTextInput(const QString &textInput);
    void handleFolderInput(const QString &folderPath);

};
#endif
