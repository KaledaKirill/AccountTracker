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
    connect(ui->folderRadioBtn, &QRadioButton::toggled, this, &LogInputDialog::onFolderRadioBtnToggled);
    connect(ui->chooseFolderBtn, &QPushButton::clicked, this, &LogInputDialog::onChooseFolderBtnClicked);
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

QString LogInputDialog::getFolderPath() const
{
    return selectedFolderPath;
}

bool LogInputDialog::isFileInput() const
{
    return ui->fileRadioBtn->isChecked();
}

bool LogInputDialog::isTextInput() const
{
    return ui->textRadioBtn->isChecked();
}

bool LogInputDialog::isFolderInput() const
{
    return ui->folderRadioBtn->isChecked();
}

void LogInputDialog::onTextRadioBtnToggled(bool checked)
{
    if (checked)
    {
        ui->folderLabel->setVisible(false);
        ui->chooseFolderBtn->setVisible(false);
        ui->textEdit->setVisible(true);
        ui->fileLabel->setVisible(false);
        ui->chooseFileBtn->setVisible(false);
    }
}

void LogInputDialog::onFileRadioBtnToggled(bool checked)
{
    if (checked)
    {
        ui->folderLabel->setVisible(false);
        ui->chooseFolderBtn->setVisible(false);
        ui->textEdit->setVisible(false);
        ui->fileLabel->setVisible(true);
        ui->chooseFileBtn->setVisible(true);
    }
}

void LogInputDialog::onFolderRadioBtnToggled(bool checked)
{
    if (checked)
    {
        ui->textEdit->setVisible(false);
        ui->fileLabel->setVisible(false);
        ui->chooseFileBtn->setVisible(false);
        ui->folderLabel->setVisible(true);
        ui->chooseFolderBtn->setVisible(true);
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

void LogInputDialog::onChooseFolderBtnClicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Choose Folder"), QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!folderPath.isEmpty())
    {
        selectedFolderPath = folderPath;
        ui->folderLabel->setText(folderPath);
    }
    else
    {
        selectedFolderPath.clear();
        ui->folderLabel->setText("No folder selected");
    }
}

void LogInputDialog::hideElements()
{
    ui->textRadioBtn->setChecked(false);
    ui->textEdit->setVisible(false);
    ui->fileLabel->setVisible(false);
    ui->chooseFileBtn->setVisible(false);
    ui->chooseFolderBtn->setVisible(false);
    ui->folderLabel->setVisible(false);
}
