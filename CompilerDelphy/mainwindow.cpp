#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lexer.h"
#include "parser.h"
#include "QMap"



#include "QDebug"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->codeEditor->setText(QString());
    ui->resultShow->setText(QString());

}

void MainWindow::on_actionOpen_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this,"Open the new file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "Cannot open the file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->codeEditor->setText(text);
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save the file: " + file.errorString());
        return;
    }
    currentFile=fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->resultShow->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionRun_triggered()

{
    QMap<QString,QString> variablesMap;
    QMap<QString,QString> variablesMap2;
    CLexer* pLexer = new CLexer();




    QRegExp rx("\\n");

    ui->resultShow->clear();

   QString codesLines = ui->codeEditor->toPlainText();

   QStringList codesLinesList = codesLines.split(rx);

   QRegExp rxTab("(\\ )+");
   QStringList codesLinesParts;
   QRegExp rxVar("\\b([a-dA-D])\\b");

   int pos=0;





   for(int i=0;i <codesLinesList.size();i++){
      codesLinesParts = codesLinesList[i].split("=");
      variablesMap.insert(codesLinesParts[0].trimmed(),codesLinesParts [1]);



      while ((pos = rxVar.indexIn(codesLinesParts[1], pos)) != -1) {


         codesLinesParts[1].replace(rxVar.cap(1),variablesMap.value(rxVar.cap(1)));
          pos += rxVar.matchedLength();
       }
//      converting the string expression into a double
//      pLexer->setExpression(codesLinesParts[1]);
//      CParser* pParser = new CParser(pLexer);
//      double dValue = pParser->calculate();QString::number(dValue)

      variablesMap.insert(codesLinesParts[0].trimmed(), codesLinesParts[1].trimmed());

   pos = 0;
   }


   for(int i=0;i <codesLinesList.size();i++){
      codesLinesParts = codesLinesList[i].split("=");
      variablesMap2.insert(codesLinesParts[0].trimmed(),codesLinesParts [1]);

   }

   ui->resultShow->append("var");

   QMapIterator<QString, QString> i(variablesMap2);
    while (i.hasNext()) {
        i.next();
        ui->resultShow->append(i.key()+" : " + "Integer;");
    }

    ui->resultShow->append("begin");

    QMapIterator<QString, QString> j(variablesMap2);
     while (j.hasNext()) {
         j.next();
         ui->resultShow->append(j.key()+" := " + j.value() + ";");
     }

     ui->resultShow->append("WriteLn(C)");
     ui->resultShow->append("end.");



}

void MainWindow::on_actionExit_2_triggered()
{
QApplication::quit();
}
