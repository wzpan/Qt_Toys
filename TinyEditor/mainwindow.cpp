#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialization
    isUntitled = true;
    curFile = tr("untitled.txt");
    setWindowTitle(curFile);
    //ui->textEdit->setVisible(true);
    //updateEnable(true);

    // Impletement a find dialog
    findDialog = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateEnable(bool vi)
{
    for (int i = 0; i < ui->menuEdit->actions().count(); ++i){
        ui->menuEdit->actions().at(i)->setEnabled(vi);
    }
}


//----------------------
// File functions
//----------------------

// Do a file save check before close the application
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}


bool MainWindow::maybeSave()
{
    // if current file has been changed
    if (ui->textEdit->document()->isModified()) {
        // Create an warning dialog
        QMessageBox box;
        box.setWindowTitle(tr("Warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("The current file %1 has been changed. Save?").arg(curFile));
        
        QPushButton *yesBtn = box.addButton(tr("Yes(&Y)"),
                                            QMessageBox::YesRole);
        box.addButton(tr("No(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("Cancel(&C)"),
                                           QMessageBox::RejectRole);

        box.exec();
        if (box.clickedButton() == yesBtn)
            return save();
        if (box.clickedButton() == cancelBut)
            return false;
    }
    
    return true;
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        isUntitled = true;
        curFile = tr("Untitled.txt");
        setWindowTitle(tr("Unsaved.txt"));
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
        updateEnable(true);
    }
}

bool MainWindow::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}


bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save as"),
                                                    curFile);

    if (fileName.isEmpty()) return false;
    return saveFile(fileName);
}


bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Tiny Editor"),
                             tr("Enable to save %1: \n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);

    // Change cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();

    // Change cursor to original
    QApplication::restoreOverrideCursor();
    isUntitled = false;

    // Get the file's standard location
    curFile = QFileInfo(fileName).canonicalPath();
    setWindowTitle(curFile);
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Tiny Editor"),
                             tr("Unable to load file %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    // change the cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    // Load all the contents to the editor
    ui->textEdit->setPlainText(in.readAll());

    // restore the cursor
    QApplication::restoreOverrideCursor();

    // set the current file location
    curFile = QFileInfo(fileName).canonicalPath();
    setWindowTitle(curFile);
    return true;
}

// New file operation
void MainWindow::on_actionNew_triggered()
{
    newFile();
}

// Open file operation
void MainWindow::on_actionOpen_triggered()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);

        if(!fileName.isEmpty()) {
            loadFile(fileName);
            ui->textEdit->setVisible((true));
            updateEnable(true);
        }
    }
}

// Save file operation
void MainWindow::on_actionSave_triggered()
{
    save();
}

// Save as operation
void MainWindow::on_actionSave_As_triggered()
{
    saveAs();
}

// Close file operation
void MainWindow::on_actionClose_triggered()
{
    if (maybeSave()) {
        ui->textEdit->setVisible(false);
        updateEnable(false);
    }
}

// Quit operation
void MainWindow::on_actionQuit_triggered()
{
    // Execute the close operation before quit.
    on_actionClose_triggered();

    qApp->quit();
}

//-------------------
// Edit functions
//-------------------

// Cancel operation
void MainWindow::on_actionCancel_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

// Cut operation
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


// Copy operation
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

// Paste operation
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::find(const QString &str, QTextDocument::FindFlags flag)
{
    if(!ui->textEdit->find(str, flag)){
        QMessageBox::warning(this, tr("Find"), tr("Cannot find %1").arg(str));
    }
}

// Find operation
void MainWindow::on_actionFind_triggered()
{
    if (!findDialog) {
        findDialog = new FindDialog(this);
        // connect the findDialog's "find" signal to main window's "find" slot
        connect(findDialog, SIGNAL(find(const QString & , QTextDocument::FindFlags)),
                this, SLOT(find(const QString &, QTextDocument::FindFlags))
                );
    }

    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

//-------------------
// Help functions
//-------------------

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Tiny Editor"),
                       tr("<h2>Tiny Editor 1.1</h2>"
                          "<p>Copyright &copy; 2013 Software Inc.</p>"
                          "<p>Tiny Editor is a small application that "
                          "allows you to edit text.</p>"));
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionAbout_triggered()
{
    about();
}

