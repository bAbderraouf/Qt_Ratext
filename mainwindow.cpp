#include "mainwindow.h"

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
    delete settings;
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

    // cursor position
    cursorPositionChanged();

    // transparent
    transparentAction();

    // toolbar
    showToolbarAction();

    //stausbar
    showStatusBarAction();

    //font
    fontAction();

    // text color
    textColorAction();
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
//          updatePdfExportFormatSetings
//---------------------------------------------------
void MainWindow::updatePdfExportFormatSetings(QPrinter &printer)
{
    // apply pdfExportFormat from settings
    if(pdfExportForamt == "A1")
        printer.setPageSize(QPageSize(QPageSize::A1));
    else if(pdfExportForamt == "A2")
        printer.setPageSize(QPageSize(QPageSize::A2));
    else if(pdfExportForamt == "A3")
        printer.setPageSize(QPageSize(QPageSize::A3));
    else if(pdfExportForamt == "A4")
        printer.setPageSize(QPageSize(QPageSize::A4));
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
                QString text = ui->textEdit->toHtml(); // toPlaintext() : text pure

                // get output file name
                QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/untitled.pdf", tr("PDF (*.pdf)"));

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

//---------------------------------------------------
//             Settings action
//---------------------------------------------------
void MainWindow::settingsAction()
{
    connect(ui->settingsAction, &QAction::triggered, [=]()
    {

        int res = settings->exec();

        // accepted setting
        if(res == QDialog::Accepted)
        {
            pdfExportForamt = settings->getPdfExportForamt();
            noWrapLines = settings->getNoWrapLines();
            opacity = settings->getOpacity();

            // update textEdit settings
            updateTextEditWrapMode();

            //update opacity
            updateWindowOpacity();

        }
    });
}

void MainWindow::transparentAction()
{
    connect(ui->actionTransparent , &QAction::toggled , [=](){

        flag_transparent = ! flag_transparent;

        if(flag_transparent)
        {
            ui->toolBar->update();

            //this->setAttribute(Qt::WA_TranslucentBackground);//transparent window
            this->setWindowFlags( Qt::Window);
            this->setWindowOpacity(opacity); // Réglage global de l’opacité


            // Rendre le fond du texte transparent
            ui->textEdit->setStyleSheet("background: black; color: yellow; border: none; ");

            this->hide();
            this->show();  // Très important sinon la fenêtre reste cachée
        }
        else
        {
            // Revenir au style normal (ex: bouton "Désactiver Style Custom")
            this->setAttribute(Qt::WA_TranslucentBackground, false);  // Désactive la transparence
            this->setWindowFlags( Qt::Window);            // Restaure les bordures
            this->setWindowOpacity(1.0);                  // Opaque

            // Restaure un style normal pour le QTextEdit
            ui->textEdit->setStyleSheet("background: white; color: black; border: 1px solid gray;");

            this->hide();
            this->show(); // Important pour réappliquer les flags
        }
    });
}

void MainWindow::showToolbarAction()
{
    connect(ui->actionShow_Tool_bar , &QAction::toggled , [=](){

         flag_showToolBar = !flag_showToolBar;

          // show/ hide toolbar
         for(QToolBar * bar: findChildren<QToolBar*>())
             flag_showToolBar ? bar->show() : bar->hide();
    });
}


void MainWindow::showStatusBarAction()
{
    connect(ui->actionShow_statusbar , &QAction::toggled , [=](){

        flag_showStatusBar = !flag_showStatusBar;

        // show / hide status bar
        flag_showStatusBar ?  ui->statusbar->show() : ui->statusbar->hide();
    });
}

void MainWindow::fontAction()
{

    connect(ui->actionFont , &QAction::triggered , [=]()
    {
        bool ok = false;
        // select a font
        QFont  textEditFont = QFontDialog::getFont(&ok, QFont("Select your font"));

        //set selected font
        if(ok)
        {
            ui->textEdit->setFont(textEditFont);
        }
    });
}

void MainWindow::textColorAction()
{
    connect(ui->actionColor , &QAction::triggered , [=]()
            {
               // capture color
                QPalette pal = ui->textEdit->palette();
                QColor initialTextColor = pal.color(QPalette::Text);

                //select color
                QColor const selectedColor = QColorDialog::getColor(initialTextColor,this, "Select a color");

                if(selectedColor.isValid())
                {
                    //set new text color
                    ui->textEdit->setTextColor(selectedColor);
                }
            });
}

//---------------------------------------------------
//          cursorPositionChanged
//---------------------------------------------------
void MainWindow::cursorPositionChanged()
{
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, [=](){
        updateCursorPosition();
    } );
}

//---------------------------------------------------
//          updateCursorPosition
//---------------------------------------------------
void MainWindow::updateCursorPosition()
{
    cursor = ui->textEdit->textCursor();
    idxLine = cursor.blockNumber() + 1;
    idxColumn = cursor.positionInBlock() + 1; // starts from 0

    writeCursorPosition();
}

void MainWindow::updateWindowOpacity()
{
    if(flag_transparent)
        this->setWindowOpacity(opacity);
}

//---------------------------------------------------
//          writeCursorPosition
//---------------------------------------------------
void MainWindow::writeCursorPosition()
{
    QString strCursorPos = "Line " + QString::number(idxLine) + ", Col " + QString::number(idxColumn) + ".";
    strCursorPos.append("           |  RaTex by : A.Bousri.");
    ui->statusbar->showMessage(strCursorPos);
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
         // doc.setPlainText(text);  // text pure
        doc.setHtml(text);

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);

        // apply pdfExportFormat from settings
        updatePdfExportFormatSetings(printer);

        printer.setOutputFileName(filePath);
        printer.setFontEmbeddingEnabled(true);

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
        QMessageBox::critical(this, "Import error!", "Could not open the file!", QMessageBox::Ok);
    }
    return text;
}

void MainWindow::init()
{
    // fenetre avec bg transparent
    this->setAttribute(Qt::WA_TranslucentBackground);

    // default background
    ui->toolBar->setStyleSheet("background: white;");
    ui->statusbar->setStyleSheet("background: white;");

    ui->toolBar->setMovable(true);

    // new settings QDialog form
    settings = new SettingsInfoDialog(this);

    // get default settings
    pdfExportForamt = settings->getPdfExportForamt();
    noWrapLines = settings->getNoWrapLines();

    updateTextEditWrapMode();
    this->setCentralWidget(ui->textEdit);

    // size hint
    this->sizeHint();

    // cursor position
    updateCursorPosition();

    // main tab (never deleted)
    //textEditList.append(ui->textEdit);


    defaultStyleSheet = this->styleSheet();

    transparentStyleSheet = "";
    flag_transparent = false;
    flag_showToolBar= true;
    flag_showStatusBar = true;
    flag_showMenuBar = true;

    opacity = settings->getOpacity();
    qDebug() << "opacity : " << opacity;
}






void MainWindow::on_removeQuitFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionQuit);
    else
        ui->toolBar->addAction(ui->actionQuit);
}


void MainWindow::on_removeSettingsFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->settingsAction);
    else
        ui->toolBar->addAction(ui->settingsAction);
}


void MainWindow::on_removeAboutFromToolbar_toggled(bool isSelected)
{
    if(isSelected)
        ui->toolBar->removeAction(ui->actionAbout);
    else
        ui->toolBar->addAction(ui->actionAbout);
}
