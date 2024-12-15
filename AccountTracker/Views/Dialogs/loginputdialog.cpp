#include "loginputdialog.h"
#include "ui_loginputdialog.h"
#include <QFileDialog>
#include <QMessageBox>

LogInputDialog::LogInputDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LogInputDialog)
{
    ui->setupUi(this);

    hideElements();

    connect(ui->textRadioBtn, &QRadioButton::toggled, this, &LogInputDialog::onTextRadioBtnToggled);
    connect(ui->fileRadioBtn, &QRadioButton::toggled, this, &LogInputDialog::onFileRadioBtnToggled);
    connect(ui->chooseFileBtn, &QPushButton::clicked, this, &LogInputDialog::onChooseFileBtnClicked);
    connect(ui->okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

LogInputDialog::~LogInputDialog()
{
    delete ui;
}

QString LogInputDialog::getInputText() const
{
    return ui->textEdit->toPlainText();
}

QString LogInputDialog::getFilePath() const
{
    return selectedFilePath;
}

bool LogInputDialog::isFileInput() const
{
    return ui->fileRadioBtn->isChecked();
}

bool LogInputDialog::isTextInput() const
{
    return ui->textRadioBtn->isChecked();
}

void LogInputDialog::onTextRadioBtnToggled(bool checked)
{
    if (checked) {
        ui->textEdit->setVisible(true);
        ui->fileLabel->setVisible(false);
        ui->chooseFileBtn->setVisible(false);
    }
}

void LogInputDialog::onFileRadioBtnToggled(bool checked)
{
    if (checked) {
        ui->textEdit->setVisible(false);
        ui->fileLabel->setVisible(true);
        ui->chooseFileBtn->setVisible(true);
    }
}

void LogInputDialog::onChooseFileBtnClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Choose Log File"), QString(), tr("Text Files (*.txt);;All Files (*)"));
    if (!filePath.isEmpty())
    {
        selectedFilePath = filePath;
        ui->fileLabel->setText(filePath);
    }
    else
    {
        selectedFilePath.clear();
        ui->fileLabel->setText("No file selected");
    }
}

void LogInputDialog::hideElements()
{
    ui->textRadioBtn->setChecked(false);
    ui->textEdit->setVisible(false);
    ui->fileLabel->setVisible(false);
    ui->chooseFileBtn->setVisible(false);
}
