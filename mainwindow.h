#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "settingsinfodialog.h"

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
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

    void transparentAction(void);

    void showToolbarAction(void);

    void showStatusBarAction(void);

    void fontAction(void);

    void textColorAction(void);

    void cursorPositionChanged(void); // not an aciton

    void updateCursorPosition(void);

    void updateWindowOpacity(void);

    void writeCursorPosition(void);


private slots:


    void on_removeQuitFromToolbar_toggled(bool isSelected);

    void on_removeSettingsFromToolbar_toggled(bool isSelected);

    void on_removeAboutFromToolbar_toggled(bool isSelected);

    void on_removeActionZoomInFromTollbar_toggled(bool isSelected);

    void on_removeText_colorFromToolbar_toggled(bool isSelected);

    void on_removeActionFontFromToolbar_toggled(bool isSelected);

    void on_removeActionRedoFromToolbar_toggled(bool isSelected);

    void on_removeActionUndoFromToolbar_toggled(bool isSelected);

    void on_removeActionSelect_AllFromtoolbar_toggled(bool isSelected);

    void on_removeactionPasteFromToolbar_toggled(bool isSelected);

    void on_removeActionCutFromToolbar_toggled(bool isSelected);

    void on_removeActionCopyFromToolbar_toggled(bool isSelected);

    void on_removeExport_as_PDF_file_fromToolbar_toggled(bool isSelected);

    void on_removeOpenFileFromToolbar_toggled(bool isSelected);

    void on_removeSaveFileFromToolbar_toggled(bool isSelected);

    void on_removeTransparentModeFromToolbar_toggled(bool isSelected);

    void on_removeActionZoomOutFromTollbar_toggled(bool isSelected);

    void on_actionzoomIn_triggered();

    void on_actionzoom_out_triggered();

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

    QString defaultStyleSheet, transparentStyleSheet;

    bool flag_transparent,
        flag_showToolBar,
        flag_showMenuBar,
        flag_showStatusBar;

    double opacity;

    QColor bagroundColorInTranparentMode;

};
#endif // MAINWINDOW_H
