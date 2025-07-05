#ifndef SETTINGSINFODIALOG_H
#define SETTINGSINFODIALOG_H

#include <QDialog>

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

private slots:

    void on_cancelPushButton_2_clicked();

    void on_okPushButton_clicked();

private:
    Ui::SettingsInfoDialog *ui;

    QString pdfExportForamt;

    bool noWrapLines;
};

#endif // SETTINGSINFODIALOG_H
