#include "editaccountdialog.h"
#include "../../DAO/accountsdaosqlite.h"
#include "ui_editaccountdialog.h"

#include <QMessageBox>

EditAccountDialog::EditAccountDialog(const Account &account, QWidget *parent)
    : QDialog(parent)
    , _accountsDAO(new AccountsDAOSQLite)
    , _accountToEdit(account)
    , _ui(new Ui::EditAccountDialog)
{
    _ui->setupUi(this);
    fillLineEdits();

    connect(_ui->okButton, &QPushButton::clicked, this, &EditAccountDialog::onOkButtonClicked);
    connect(_ui->cancelButton, &QPushButton::clicked, this, &EditAccountDialog::onCancelButtonClicked);
}

EditAccountDialog::~EditAccountDialog()
{
    delete _ui;
}

void EditAccountDialog::onOkButtonClicked()
{
    QString name = _ui->nameLineEdit->text();
    QString sellerName = _ui->sellerNameLineEdit->text();
    QString purchaseDateString = _ui->purchaseLineEdit->text();
    QString description = _ui->textEdit->toPlainText();

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

    Account newAccount(name, sellerName, purchaseDate, 0, description);
    _accountsDAO->updateAccount(_accountToEdit, newAccount);

    accept();
}

void EditAccountDialog::onCancelButtonClicked()
{
    reject();
}

void EditAccountDialog::fillLineEdits()
{
    _ui->nameLineEdit->setText(_accountToEdit.getAccountName());
    _ui->sellerNameLineEdit->setText(_accountToEdit.getSellerName());
    _ui->purchaseLineEdit->setText(_accountToEdit.getPurchaseDate().toString("dd.MM.yyyy"));
    _ui->textEdit->setText(_accountToEdit.getDescription());
}
