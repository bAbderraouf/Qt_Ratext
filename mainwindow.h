#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "settingsinfodialog.h"

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <Qfile>
#include <QTextStream>
#include <QTextDocument>
#include <QPainter>
#include <QPdfWriter>
#include <QPrinter>
#include <QTextCursor>
#include <QList>


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

    void updatePdfExportFormatSetings(QPrinter &printer);

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

    void cursorPositionChanged(void); // not an aciton

    void updateCursorPosition(void);

    void writeCursorPosition(void);

private slots:


private:
    Ui::MainWindow *ui;

    //QList<QTextEdit*> textEditList;

    SettingsInfoDialog * settings;

    QString pdfExportForamt;

    bool noWrapLines;

    // cursor position

    QTextCursor  cursor;

    int idxLine;

    int idxColumn;
};
#endif // MAINWINDOW_H
