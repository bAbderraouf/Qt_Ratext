#ifndef SETTINGSINFODIALOG_H
#define SETTINGSINFODIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class SettingsInfoDialog;
}

class SettingsInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsInfoDialog(QWidget *parent = nullptr);

    ~SettingsInfoDialog();

    QString getPdfExportForamt() ;

    bool getNoWrapLines() ;

    float getOpacity();

    QColor getBagroundColorInTranparentMode();

private slots:

    void on_cancelPushButton_2_clicked();

    void on_okPushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::SettingsInfoDialog *ui;

    QString pdfExportForamt;

    bool noWrapLines;

    QColor bagroundColorInTranparentMode;
};

#endif // SETTINGSINFODIALOG_H
