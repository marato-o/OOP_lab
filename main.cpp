#include "test.h"
#include "mainwindow.h"

#include "QApplication"

int main(int argc, char *argv[])
{

    ConstructorTest();
    AdditionTest();
    ClearTest();
    FindTest();
    RemoveTest();
    WriteReadTest();
    RehashTest();
    CreateTableTest();


    QApplication a(argc, argv);
    MainWindow window;
    window.setWindowTitle("Your hash tables");
    window.show();

    return a.exec();
}
