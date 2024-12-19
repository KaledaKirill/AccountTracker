#include "../../Views/Dialogs/addaccountdialog.h"
#include "../../Views/Dialogs/editaccountdialog.h"
#include "../../Views/Dialogs/loginputdialog.h"
#include "../../DAO/accountsdaosqlite.h"
#include "../../Core/Entities/account.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _accountsDAO(new AccountsDAOSQLite())
    , _logFilesHandler(new LogFilesHandler)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    loadAccountsNames();

    connect(_ui->addAccountBtn, SIGNAL(clicked(bool)), this, SLOT(onAddAccountBtnClicled()));
    connect(_ui->chooseAccountBtn, SIGNAL(clicked(bool)), this, SLOT(onChooseAccountBtnClicked()));
    connect(_ui->loadBtn, SIGNAL(clicked(bool)), this, SLOT(onLoadBtnClicked()));
    connect(_ui->descriptionBtn, SIGNAL(clicked(bool)), this, SLOT(onDescriptionBtnClicked()));
    connect(_ui->editBtn, SIGNAL(clicked(bool)), this, SLOT(onEditAccountBtnClicked()));
    connect(_ui->deleteBtn, SIGNAL(clicked(bool)), this, SLOT(onDeleteAccountBtnClicked()));
}

MainWindow::~MainWindow()
{
    delete _ui;
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
    showAccountData(account);
    _currentAccount = account;
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

    qDebug() << "main window";
    for (const auto& inviteTime : account.getInvitesTime())
        qDebug() << inviteTime;
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
    {
        QString filePath = dialog.getFilePath();
        if (!filePath.isEmpty())
        {
            try
            {
                _logFilesHandler->handleFileLog(filePath);
            }
            catch(const std::runtime_error& e)
            {
                QMessageBox::warning(this, "Error", e.what());
            }
        }
        else
            QMessageBox::warning(this, "Error", "No file selected!");
    }
    else if (dialog.isTextInput())
    {
        QString textInput = dialog.getInputText();
        if (!textInput.isEmpty())
        {
            try
            {
                _logFilesHandler->handleTextLog(textInput);
            }
            catch(const std::runtime_error& e)
            {
                QMessageBox::warning(this, "Error", e.what());
            }
        }
        else
            QMessageBox::warning(this, "Error", "No text entered!");
    }
}
