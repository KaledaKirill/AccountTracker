#include "mainwindow.h"
#include "../../Views/Dialogs/addaccountdialog.h"
#include "../../Views/Dialogs/loginputdialog.h"
#include "ui_mainwindow.h"
#include "../../DAO/accountsdaosqlite.h"
#include "../../Entities/account.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _accountsDAO(new AccountsDAOSQLite())
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    loadAccountsNames();

    connect(_ui->addAccountBtn, SIGNAL(clicked(bool)), this, SLOT(onAddAccountBtnClicled()));
    connect(_ui->chooseAccountBtn, SIGNAL(clicked(bool)), this, SLOT(onChooseAccountBtnClicked()));
    connect(_ui->loadBtn, SIGNAL(clicked(bool)), this, SLOT(onLoadBtnClicked()));
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

void MainWindow::onLoadBtnClicked()
{
    LogInputDialog dialog(this);
    if (dialog.exec() == QDialog::Rejected)
        return;

    if (dialog.isFileInput())
    {
        QString filePath = dialog.getFilePath();
        if (!filePath.isEmpty())
            qDebug() << "file input";
        else
            QMessageBox::warning(this, "Error", "No file selected!");
    }
    else if (dialog.isTextInput())
    {
        QString textInput = dialog.getInputText();
        if (!textInput.isEmpty())
            qDebug() << "text input";
        else
            QMessageBox::warning(this, "Error", "No text entered!");
    }
}


