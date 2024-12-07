#include "Views/Forms/mainwindow.h"
#include "Utils/database.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBase* database = DataBase::getInstance();
    database->connect();
    MainWindow w;
    w.show();
    return a.exec();
}
