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

    CLexer* pLexer = new CLexer();
    pLexer->setExpression("32");



    QRegExp rx("\\n");

    ui->resultShow->clear();

   QString codesLines = ui->codeEditor->toPlainText();

   QStringList codesLinesList = codesLines.split(rx);

   QRegExp rxTab("(\\ )+");
   QStringList codesLinesParts;
   QRegExp rxVar("([abc])");
   QString temp;
   int pos=0;


     //       pLexer->setExpression(codesLinesParts[1]);
     //       CParser* pParser = new CParser(pLexer);
     //       double dValue = pParser->calculate();


   for(int i=0;i <codesLinesList.size();i++){
      codesLinesParts = codesLinesList[i].split("=");
      variablesMap.insert(codesLinesParts[0].trimmed(),codesLinesParts [1]);

   temp=codesLinesParts[1];

      while ((pos = rxVar.indexIn(temp, pos)) != -1) {
          qDebug()<<temp;

          qDebug()<<rxVar.cap(1);
          pos += rxVar.matchedLength();
       }


   pos = 0;
   }

//   while ((pos = rxVar.indexIn(codesLinesParts[1], pos)) != -1) {
//       qDebug()<<codesLinesParts[1];
//       qDebug()<<rxVar.cap(1);
//    codesLinesParts[1].replace(rxVar.cap(1),variablesMap.value(rxVar.cap(1)));

//    pos += rx.matchedLength();

//      variablesMap.insert(codesLinesParts[0].trimmed(),codesLinesParts [1]);
//    }



   QMapIterator<QString, QString> i(variablesMap);
    while (i.hasNext()) {
        i.next();
        ui->resultShow->append(i.key()+" : " + i.value());
    }



//

//  if(rxVar.exactMatch(codesLinesParts[0])){
//      ui->resultShow->setText("TRUE");
//  }
//  else{
//       ui->resultShow->setText("WRONG BITCH");
//  }
//for(int i=0;i != codesLinesList.size(); i++){
//    QStringList codesLinesParts = codesLinesList[i].split(rxTab);

////    if(rxVar.exactMatch(codesLinesParts[0])){
////        ui->resultShow->setText("TRUE at line " + String);
////    }
////    else{
////         ui->resultShow->setText("WRONG BITCH");
////    }

//}



}

void MainWindow::on_actionExit_2_triggered()
{
QApplication::quit();
}
