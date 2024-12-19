#ifndef EDITACCOUNTDIALOG_H
#define EDITACCOUNTDIALOG_H

#include "../../DAO/iaccountsdao.h"
#include "../../Core/Entities/account.h"

#include <QDialog>

namespace Ui {
class EditAccountDialog;
}

class EditAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAccountDialog(const Account& account, QWidget *parent = nullptr);
    ~EditAccountDialog();

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    QScopedPointer<IAccountsDAO> _accountsDAO;
    Account _accountToEdit;
    Ui::EditAccountDialog *_ui;

    void fillLineEdits();

};

#endif
