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
    QString getFolderPath() const;
    bool isFileInput() const;
    bool isTextInput() const;
    bool isFolderInput() const;

private slots:
    void onTextRadioBtnToggled(bool checked);
    void onFileRadioBtnToggled(bool checked);
    void onFolderRadioBtnToggled(bool checked);
    void onChooseFileBtnClicked();
    void onChooseFolderBtnClicked();

private:
    Ui::LogInputDialog *ui;
    QString selectedFilePath;
    QString selectedFolderPath;

    void hideElements();

};

#endif
