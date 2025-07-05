#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsinfodialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QSize sizeHint() const;
    ~MainWindow();

    void saveTextToFile(QString const &filePath, QString const &  text , bool toPDF = false);

    QString readContentFromTextFile(QString const &filePath);

    void init();

    void setupSignalSlotsConnections(void);

    void updateTextEditWrapMode(void);

    void openFileAction(void);

    void saveFileAction(void);

    void saveAsPdfAction(void);

    void quitAction(void);

    void copyAction(void);

    void cutAction(void);

    void pasteAction(void);

    void undoAction(void);

    void redoAction(void);

    void aboutAction(void);

    void selectAllAction(void);

    void settingsAction(void);

private slots:


private:
    Ui::MainWindow *ui;

    SettingsInfoDialog * settings;

    QString pdfExportForamt;

    bool noWrapLines;
};
#endif // MAINWINDOW_H
