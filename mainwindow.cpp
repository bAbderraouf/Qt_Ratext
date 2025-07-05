#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include "settingsinfodialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init setting info dialog
    init();

    setupSignalSlotsConnections();
}

QSize MainWindow::sizeHint() const
{
    return QSize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------
//             setupSignalSlotsConnections
//---------------------------------------------------
void MainWindow::setupSignalSlotsConnections()
{
    //open
    openFileAction();

    //save file
    saveFileAction();

    //export pdf file
    saveAsPdfAction();

    //quit
    quitAction();

    //copy
    copyAction();

    //cut
    cutAction();

    //paste
    pasteAction();

    //undo
    undoAction();

    //redo
    redoAction();

    //about
    aboutAction();

    //select all
    selectAllAction();

    //settings
    settingsAction();
}

//---------------------------------------------------
//             update TextEdit WrapMode (settings)
//---------------------------------------------------
void MainWindow::updateTextEditWrapMode()
{
    if(noWrapLines)
    {
        // pas de saut de lignes automatique
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }
    else
    {
        //saut automatique de lignes
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    }
}

//---------------------------------------------------
//             open file
//---------------------------------------------------
void MainWindow::openFileAction()
{
    connect(ui->actionOpen, &QAction::triggered, [=]()
            {

                QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home" , tr("Text (*.txt)"));

                QString text = readContentFromTextFile(fileName);

                if(!text.isEmpty())
                {
                    ui->textEdit->setText(text);
                }
            });}

//---------------------------------------------------
//             saveFileAction
//---------------------------------------------------
void MainWindow::saveFileAction()
{
    connect(ui->actionSave, &QAction::triggered, [=]()
            {

                // capture text from textEdit
                QString text = ui->textEdit->toPlainText();

                // get output file name
                QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/jana/untitled.txt", tr("Text (*.txt)"));

                if(!fileName.isEmpty())
                    saveTextToFile(fileName, text);
            });

}

//---------------------------------------------------
//             saveAsPdfAction
//---------------------------------------------------
void MainWindow::saveAsPdfAction()
{
    connect(ui->actionExport_as_PDF, &QAction::triggered, [=]()
            {

                // capture text from textEdit
                QString text = ui->textEdit->toPlainText();

                // get output file name
                QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/jana/untitled.pdf", tr("PDF (*.pdf)"));

                bool toPDF = true;

                if(!fileName.isEmpty())
                    saveTextToFile(fileName, text, toPDF);
            });
}

//---------------------------------------------------
//             quitAction
//---------------------------------------------------
void MainWindow::quitAction()
{
    connect(ui->actionQuit, &QAction::triggered, [=](){
        QApplication::quit();   });
}

//---------------------------------------------------
//             copyAction
//---------------------------------------------------
void MainWindow::copyAction()
{
    connect(ui->actionCopy, &QAction::triggered, [=](){
           ui->textEdit->copy();  });
}

//---------------------------------------------------
//             cutAction
//---------------------------------------------------
void MainWindow::cutAction()
{
    connect(ui->actionCut, &QAction::triggered, [=](){
        ui->textEdit->cut();  });
}

//---------------------------------------------------
//             pasteAction
//---------------------------------------------------
void MainWindow::pasteAction()
{
    connect(ui->actionPaste, &QAction::triggered, [=](){
        ui->textEdit->paste();  });

}

//---------------------------------------------------
//            undoAction
//---------------------------------------------------
void MainWindow::undoAction()
{
    connect(ui->actionUndo, &QAction::triggered, [=](){
        ui->textEdit->undo();  });

}

//---------------------------------------------------
//            redoAction
//---------------------------------------------------
void MainWindow::redoAction()
{
    connect(ui->actionRedo, &QAction::triggered, [=](){
        ui->textEdit->redo();  });
}

//---------------------------------------------------
//             aboutAction
//---------------------------------------------------
void MainWindow::aboutAction()
{
    connect(ui->actionAbout, &QAction::triggered, [=](){
        QString msg = "RateX is a small text editor.\n\n";
        msg.append( "Developer: Abderraouf Bousri\n");
        msg.append("Contact:\nabderraouf.bousri@gmail.com");
        QMessageBox::information(this, "About", msg , QMessageBox::Ok); });
}


//---------------------------------------------------
//             Seclect All action
//---------------------------------------------------
void MainWindow::selectAllAction()
{
    connect(ui->actionSelectAll, &QAction::triggered, [=](){
        ui->textEdit->selectAll();  });
}

void MainWindow::settingsAction()
{
    connect(ui->settingsAction, &QAction::triggered, [=](){

    int res = settings->exec();

    // accepted setting
    if(res == QDialog::Accepted)
    {
        pdfExportForamt = settings->getPdfExportForamt();
        noWrapLines = settings->getNoWrapLines();

        qDebug() << " pdf format : " << pdfExportForamt ;
        qDebug()  << "wrap mode : " << noWrapLines;

        // update textEdit settings
        updateTextEditWrapMode();
    }
    });
}

//---------------------------------------------------
//          saveTextToFile
//---------------------------------------------------
void MainWindow::saveTextToFile(QString const &filePath, QString const & text , bool toPDF )
{
    // define file full path
    QFile outputFile = filePath;

    if(toPDF) // save pdf file
    {
        // a formated object wich contains text
        QTextDocument doc;
        doc.setPlainText(text);

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);

        //-----------------------
        // apply pdfExportFormat from settings
        if(pdfExportForamt == "A1")
            printer.setPageSize(QPageSize(QPageSize::A1));
        else if(pdfExportForamt == "A2")
            printer.setPageSize(QPageSize(QPageSize::A2));
        else if(pdfExportForamt == "A3")
            printer.setPageSize(QPageSize(QPageSize::A3));
        else if(pdfExportForamt == "A4")
            printer.setPageSize(QPageSize(QPageSize::A4));

        //-----------------------
        printer.setOutputFileName(filePath);

        doc.print(&printer);

    }
    else  // save text file
    {
        //open the file and write it
        if(outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream outStream(&outputFile);
            outStream << text;
            outputFile.close();
        }
        else
        {
            qDebug() << "impossible d'ouvrir le fichier";
        }
    }


}

//---------------------------------------------------
//          readContentFromTextFile
//---------------------------------------------------
QString MainWindow::readContentFromTextFile(QString const &filePath)
{
    // define file full path
    QFile inputFile = filePath;
    QString text = "";

    //open the file and write it
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream inStream(&inputFile);
        text = inStream.readAll();
        inputFile.close();
    }
    else
    {
        qDebug() << "impossible d'ouvrir le fichier";
    }
    return text;
}

void MainWindow::init()
{
    // new settings QDialog form
    settings = new SettingsInfoDialog(this);

    // get default settings
    pdfExportForamt = settings->getPdfExportForamt();
    noWrapLines = settings->getNoWrapLines();

    updateTextEditWrapMode();

    // size hint
    this->sizeHint();
}

