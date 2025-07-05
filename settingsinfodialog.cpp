#include "settingsinfodialog.h"
#include "ui_settingsinfodialog.h"

SettingsInfoDialog::SettingsInfoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsInfoDialog)
{
    ui->setupUi(this);

    // init
    ui->pdfFormatComboBox->addItem("A1");
    ui->pdfFormatComboBox->addItem("A2");
    ui->pdfFormatComboBox->addItem("A3");
    ui->pdfFormatComboBox->addItem("A4");
    ui->pdfFormatComboBox->setEditable(false);

    // default values
    ui->pdfFormatComboBox->setCurrentText("A4");
    ui->noWrapCheckbox->setChecked(true);

    // init variables
    pdfExportForamt = ui->pdfFormatComboBox->currentText();
    noWrapLines = ui->noWrapCheckbox->isChecked();
}

SettingsInfoDialog::~SettingsInfoDialog()
{
    delete ui;
}

QString SettingsInfoDialog::getPdfExportForamt()
{
    pdfExportForamt = ui->pdfFormatComboBox->currentText();
    return pdfExportForamt;
}

bool SettingsInfoDialog::getNoWrapLines()
{
    noWrapLines = ui->noWrapCheckbox->isChecked();
    return noWrapLines;
}

void SettingsInfoDialog::on_cancelPushButton_2_clicked()
{
    this->reject();
}


void SettingsInfoDialog::on_okPushButton_clicked()
{
    noWrapLines = ui->noWrapCheckbox->isChecked();
    pdfExportForamt = ui->pdfFormatComboBox->currentText();

    this->accept();
}

