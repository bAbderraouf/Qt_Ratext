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
    ui->opacityDoubleSpinBox->setValue(0.5);

    // default values
    ui->pdfFormatComboBox->setCurrentText("A4");
    ui->noWrapCheckbox->setChecked(true);
    bagroundColorInTranparentMode = Qt::black;

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

float SettingsInfoDialog::getOpacity()
{
    return ui->opacityDoubleSpinBox->value();
}

QColor SettingsInfoDialog::getBagroundColorInTranparentMode()
{
    return bagroundColorInTranparentMode;
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


void SettingsInfoDialog::on_pushButton_clicked()
{
    //select color
    QColor const selectedColor = QColorDialog::getColor(Qt::black,this, "Select a color");

    qDebug() << "selected color " << selectedColor;

    if(selectedColor.isValid())
    {
        //set new color
        bagroundColorInTranparentMode = selectedColor;
    }

}

