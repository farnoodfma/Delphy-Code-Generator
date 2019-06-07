#include "mainwindow.h"
#include <QApplication>
#include "parser.h"
#include "lexer.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QRegExp rxTab("(\\ )+");
    QStringList codesLinesParts;
    QRegExp rxVar("([ab])");
    // QRegExp rxVar("\\b([A-Da-d])\\b");


    QStringList list;
     int pos = 0;
     QString temp="a+b";


//         while ((pos = rxVar.indexIn(temp, pos)) != -1) {
//              qDebug()<<rxVar.cap(1);
//             pos += rxVar.matchedLength();
//          }



//    qDebug()<<list.size();





    return a.exec();
}
