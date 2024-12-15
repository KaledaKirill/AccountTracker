#ifndef LOGINPUTDIALOG_H
#define LOGINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class LogInputDialog;
}

class LogInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInputDialog(QWidget *parent = nullptr);
    ~LogInputDialog();

    QString getInputText() const;
    QString getFilePath() const;
    bool isFileInput() const;
    bool isTextInput() const;

private slots:
    void onTextRadioBtnToggled(bool checked);
    void onFileRadioBtnToggled(bool checked);
    void onChooseFileBtnClicked();

private:
    Ui::LogInputDialog *ui;
    QString selectedFilePath;

    void hideElements();

};

#endif
