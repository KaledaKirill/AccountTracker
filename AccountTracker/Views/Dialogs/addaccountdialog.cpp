#include "AddAccountDialog.h"
#include "../../DAO/accountsdaosqlite.h"
#include "ui_addaccountdialog.h"

#include <QMessageBox>
#include <QDate>

AddAccountDialog::AddAccountDialog(QWidget *parent)
    : QDialog(parent)
    , _accountsDAO(new AccountsDAOSQLite())
    , _ui(new Ui::AddAccountDialog)
{
    _ui->setupUi(this);

    connect(_ui->pushButton, &QPushButton::clicked, this, &AddAccountDialog::onOkButtonClicked);
    connect(_ui->pushButton_2, &QPushButton::clicked, this, &AddAccountDialog::onCancelButtonClicked);
}

AddAccountDialog::~AddAccountDialog()
{
    delete _ui;
}

void AddAccountDialog::onOkButtonClicked()
{
    QString name = _ui->nameLineEdit->text();
    QString sellerName = _ui->sellerNameLineEdit->text();
    QString purchaseDateString = _ui->purchaseLineEdit->text();

    if (name.isEmpty() || sellerName.isEmpty() || purchaseDateString.isEmpty())
    {
        QMessageBox::warning(this, "Invalid Input", "Please fill in all fields!");
        return;
    }

    QDate purchaseDate = QDate::fromString(purchaseDateString, "dd.MM.yyyy");
    if (!purchaseDate.isValid())
    {
        QMessageBox::warning(this, "Invalid Date", "Please enter a valid date (dd.MM.yyyy)!");
        return;
    }

    Account newAccount(name, sellerName, purchaseDate, 0);
    _accountsDAO->addAccount(newAccount);

    accept();
}

void AddAccountDialog::onCancelButtonClicked()
{
    reject();
}
