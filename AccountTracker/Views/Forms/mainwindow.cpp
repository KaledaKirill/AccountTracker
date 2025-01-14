#include "../../Views/Dialogs/addaccountdialog.h"
#include "../../Views/Dialogs/editaccountdialog.h"
#include "../../Views/Dialogs/loginputdialog.h"
#include "../../DAO/accountsdaosqlite.h"
#include "../../Core/Entities/account.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _accountsDAO(new AccountsDAOSQLite())
    , _logFilesHandler(new LogFilesHandler)
    , _chartView(new QChartView)
    , _chartGenerator(new ChartGenerator)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    setupChartView();
    loadAccountsNames();

    connect(_ui->addAccountBtn, SIGNAL(clicked(bool)), this, SLOT(onAddAccountBtnClicled()));
    connect(_ui->chooseAccountBtn, SIGNAL(clicked(bool)), this, SLOT(onChooseAccountBtnClicked()));
    connect(_ui->loadBtn, SIGNAL(clicked(bool)), this, SLOT(onLoadBtnClicked()));
    connect(_ui->descriptionBtn, SIGNAL(clicked(bool)), this, SLOT(onDescriptionBtnClicked()));
    connect(_ui->editBtn, SIGNAL(clicked(bool)), this, SLOT(onEditAccountBtnClicked()));
    connect(_ui->deleteBtn, SIGNAL(clicked(bool)), this, SLOT(onDeleteAccountBtnClicked()));
    connect(_ui->chooseDataRangeBtn, SIGNAL(clicked(bool)), this, SLOT(onChooseDataRangeBtnClicked()));
}


MainWindow::~MainWindow()
{
    delete _ui;
    delete _chartView;
}

void MainWindow::setupChartView()
{
    _chartView->setRenderHint(QPainter::Antialiasing);
    _chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _ui->chartLayout->addWidget(_chartView);
}

void MainWindow::showAccountChart(const Account &account)
{
    const QMap<QDate, int> dailyInvitesCount = account.getDailyInvitesCount();
    QChart* chart = _chartGenerator->createInvitesChart(dailyInvitesCount);
    if(chart)
        _chartView->setChart(chart);
}

void MainWindow::showAccountChart(const Account &account, const QDate &startDate, const QDate &endDate)
{
    const QMap<QDate, int> dailyInvitesCount = account.getDailyInvitesCount(startDate, endDate);
    QChart* chart = _chartGenerator->createInvitesChart(dailyInvitesCount);
    if(chart)
        _chartView->setChart(chart);
}

void MainWindow::onAddAccountBtnClicled()
{
    auto addAccountDialog = new AddAccountDialog();

    if (addAccountDialog->exec() == QDialog::Accepted)
    {
        loadAccountsNames();
        QMessageBox::information(this, "Success", "Account successfully added.");
    }
    else
        QMessageBox::warning(this, "Error", "Failed to add the account.");

    delete addAccountDialog;
}

void MainWindow::onChooseAccountBtnClicked()
{
    const QString accountName = _ui->accountsCbx->currentText();
    if (accountName.isEmpty())
        return;

    Account account = _accountsDAO->getAccountByName(accountName);
    _currentAccount = account;
    showAccountData(account);
    showAccountChart(account);
}

void MainWindow::onDescriptionBtnClicked()
{
    if (_currentAccount.getAccountName().isEmpty())
    {
        QMessageBox::warning(this, "No Account Selected", "Please select an account first.");
        return;
    }

    QMessageBox::information(this, "Account Description", _currentAccount.getDescription());
}

void MainWindow::onEditAccountBtnClicked()
{
    if (_currentAccount.getAccountName().isEmpty())
    {
        QMessageBox::warning(this, "No Account Selected", "Please select an account first.");
        return;
    }

    auto editAccountDialog = new EditAccountDialog(_currentAccount);

    if (editAccountDialog->exec() == QDialog::Accepted)
    {
        loadAccountsNames();
        _currentAccount = Account();
        showAccountData(Account());
        QMessageBox::information(this, "Success", "Account successfully edit.");
    }
    else
        QMessageBox::warning(this, "Error", "Failed to edit the account.");

    delete editAccountDialog;
}

void MainWindow::onDeleteAccountBtnClicked()
{
    const QString accountName = _currentAccount.getAccountName();
    if (accountName.isEmpty())
    {
        QMessageBox::warning(this, "No Account Selected", "Please select an account first.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Deletion",
        QString("Are you sure you want to delete the account '%1'?").arg(accountName),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::No)
        return;

    if (deleteAccount(accountName))
    {
        QMessageBox::information(this, "Success", "Account successfully deleted.");

        _currentAccount = Account();
        showAccountData(Account());
    }
    else
        QMessageBox::warning(this, "Error", "Failed to delete the account. Please try again.");
}


void MainWindow::loadAccountsNames()
{
    _accountsNamesList.clear();
    _ui->accountsCbx->clear();
    _accountsNamesList = _accountsDAO->getAllAccountNames();
    _ui->accountsCbx->addItems(_accountsNamesList);
}

void MainWindow::showAccountData(const Account &account)
{
    _ui->nameLabel->setText("name: " + account.getAccountName());
    _ui->sellerNameLabel->setText("seller name: " + account.getSellerName());
    _ui->purchaseDateLabel->setText("purchase date: " + account.getPurchaseDate().toString());
    _ui->invitesCountLabel->setText("invites count: " + QString::number(account.getInvitesCount()));
}

bool MainWindow::deleteAccount(const QString &accountName)
{
    if (accountName.isEmpty())
        return false;
    _accountsDAO->deleteAccountByName(accountName);

    int index = _ui->accountsCbx->findText(accountName);
    if (index != -1)
    {
        _ui->accountsCbx->removeItem(index);
        return true;
    }

    return false;
}

void MainWindow::onLoadBtnClicked()
{
    LogInputDialog dialog(this);
    if (dialog.exec() == QDialog::Rejected)
        return;

    if (dialog.isFileInput())
        handleFileInput(dialog.getFilePath());
    else if (dialog.isTextInput())
        handleTextInput(dialog.getInputText());
    else if (dialog.isFolderInput())
        handleFolderInput(dialog.getFolderPath());
}

void MainWindow::handleFileInput(const QString& filePath)
{
    if (!filePath.isEmpty())
    {
        try
        {
            _logFilesHandler->handleFileLog(filePath);
        }
        catch (const std::runtime_error& e)
        {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    else
        QMessageBox::warning(this, "Error", "No file selected!");
}

void MainWindow::handleTextInput(const QString& textInput)
{
    if (!textInput.isEmpty())
    {
        try
        {
            _logFilesHandler->handleTextLog(textInput);
        }
        catch (const std::runtime_error& e)
        {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    else
        QMessageBox::warning(this, "Error", "No text entered!");
}

void MainWindow::handleFolderInput(const QString& folderPath)
{
    if (!folderPath.isEmpty())
    {
        try
        {
            _logFilesHandler->handleFolderWithLogs(folderPath);
        }
        catch (const std::runtime_error& e)
        {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    else
        QMessageBox::warning(this, "Error", "No folder selected!");
}


void MainWindow::onChooseDataRangeBtnClicked()
{
    const QString accountName = _currentAccount.getAccountName();
    if (accountName.isEmpty())
    {
        QMessageBox::warning(this, "No Account Selected", "Please select an account first");
        return;
    }

    QString startDateString = _ui->startDateLineEdit->text();
    QString endDateString = _ui->endDateLineEdit->text();
    if (startDateString.isEmpty() || endDateString.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please fill in both date fields");
        return;
    }

    QDate startDate = QDate::fromString(startDateString, "dd.MM.yyyy");
    QDate endDate = QDate::fromString(endDateString, "dd.MM.yyyy");
    if (!startDate.isValid() || !endDate.isValid())
    {
        QMessageBox::warning(this, "Error", "Please enter valid dates in the format dd.MM.yyyy");
        return;
    }

    if (startDate > endDate)
    {
        QMessageBox::warning(this, "Error", "Start date cannot be later than end date");
        return;
    }

    showAccountChart(_currentAccount, startDate, endDate);
    _ui->startDateLineEdit->clear();
    _ui->endDateLineEdit->clear();
}

