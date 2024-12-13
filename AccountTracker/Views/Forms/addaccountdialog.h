#ifndef ADDACCOUNTDIALOG_H
#define ADDACCOUNTDIALOG_H

#include "../../DAO/iaccountsdao.h"

#include <QScopedPointer>
#include <QDialog>

namespace Ui {
class AddAccountDialog;
}

class AddAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAccountDialog(QWidget *parent = nullptr);
    ~AddAccountDialog();

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    QScopedPointer<IAccountsDAO> _accountsDAO;

    Ui::AddAccountDialog *_ui;

};

#endif
