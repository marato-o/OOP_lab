#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QMainWindow"
#include "QPushButton"
#include "collection.h"
#include "createtable.h"
#include "addnode.h"
#include "finddialog.h"
#include "readdialog.h"
#include "writedialog.h"
#include "gendialog.h"

#include "QListWidget"
#include "QKeySequence"
#include "QShortcut"

#include "stdlib.h"

#define DEF_AM 10

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddTableButton_clicked();
    void on_PopTableButton_clicked();
    void on_OpenTableButton_clicked();
    void on_DeleteTablesButton_clicked();
    void on_listWidget_itemClicked();
    void on_FindButton_clicked();
    void on_ClearTableButton_clicked();
    void on_AddNodeButton_clicked();
    void on_PopNodeButton_clicked();
    void on_QuitButton_clicked();
    void on_ReadButton_clicked();
    void on_WriteButton_clicked();
    void on_GenButton_clicked();
    //void Func();
    int CurrentItemChanged(int current);
    void Delay();

private:
    Ui::MainWindow *ui;
    Collection<std::string> tables [DEF_AM];

    CreateTable *dialog_table;
    AddNode *dialog_node;
    FindDialog *dialog_find;
    ReadDialog *dialog_read;
    WriteDialog *dialog_write;
    GenDialog *dialog_gen;

    int current;
    int amount;

    void UpdateList();
    void FillingTables();
    void FillingValues();
};
#endif // MAINWINDOW_H
