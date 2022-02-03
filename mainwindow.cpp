#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMessageBox"
#include "QTime"
#include "QFileDialog"
#include "QDir"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateList();
    current = 0;
    amount = 0;

    ui->listWidget->clear();
}

MainWindow::~MainWindow()
{
    current = 0;
    for (int i = 0; i < DEF_AM; i++){
        tables[i].Clear();
    }
    delete ui;
}

void MainWindow::UpdateList(){
    connect(ui->listWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(on_listWidget_clicked(QModelIndex)));
    ui->PopTableButton->setDisabled(true);
    ui->OpenTableButton->setDisabled(true);
    ui->FindButton->setDisabled(true);
    ui->ClearTableButton->setDisabled(true);
    ui->DeleteTablesButton->setDisabled(true);
    ui->AddNodeButton->setDisabled(true);
    ui->PopNodeButton->setDisabled(true);
    ui->GenButton->setDisabled(true);
    ui->list->setDisabled(true);

    if (amount > 1)
         ui->GenButton->setDisabled(false);

    if (amount == DEF_AM){
         ui->AddTableButton->setDisabled(true);
         ui->ReadButton->setDisabled(true);
         ui->GenButton->setDisabled(true);
    }
    else {
        ui->AddTableButton->setDisabled(false);
        ui->ReadButton->setDisabled(false);
    }

    if (ui->listWidget->count()>0){
        ui->PopTableButton->setDisabled(false);
        ui->OpenTableButton->setDisabled(false);
        ui->FindButton->setDisabled(false);
        ui->ClearTableButton->setDisabled(false);
        ui->DeleteTablesButton->setDisabled(false);
    }
    else {
        ui->PopTableButton->setDisabled(true);
        ui->OpenTableButton->setDisabled(true);
        ui->FindButton->setDisabled(true);
        ui->ClearTableButton->setDisabled(true);
        ui->DeleteTablesButton->setDisabled(true);
        ui->GenButton->setDisabled(true);
    }
    ui->list->clear();
}

void MainWindow::FillingTables()
{
    if (amount > 0){
        for (int i = 0; i < amount; i++)
            ui->listWidget->addItem(QString::fromStdString(tables[i].GetName()));
    }
}

void MainWindow::on_AddTableButton_clicked()
{
    if (amount < DEF_AM){
        dialog_table = new CreateTable;
        dialog_table->setWindowTitle("Add table");

        dialog_table->show();

        if (dialog_table->exec()==QDialog::Accepted){
             ui->listWidget->addItem(dialog_table->GetName());
             tables[current].SetName((dialog_table->GetName()).toStdString());
             ++current;
             ++amount;
             UpdateList();
        }
        delete dialog_table;
    }
}

void MainWindow::on_listWidget_itemClicked()
{
    ui->list->setDisabled(false);
    ui->list->clear();
    ui->AddNodeButton->setDisabled(false);
    if (ui->list->count()>0) ui->PopNodeButton->setDisabled(false);
    if (tables[ui->listWidget->currentRow()].GetSize()>0)
     {
        ui->PopNodeButton->setDisabled(false);
        tables[ui->listWidget->currentRow()].Print(ui->list);
    }
}

void MainWindow::on_PopTableButton_clicked()
{
    if (ui->listWidget->currentRow()==-1) {
        QMessageBox::information(this,"Error","No choosed table for deleting") ;
        return ;
    }
    int del_index = ui->listWidget->currentRow();

    QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());
    delete it;
    tables[del_index].SetName("Just_a_table");

    if (del_index == DEF_AM) current = del_index;
    else {
        for (int i = del_index; i < DEF_AM - 1; i++){
            tables[i] = tables[i+1];
        }
        current = amount - 1;
    }
    --amount;
    UpdateList();

}

void MainWindow::Delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_OpenTableButton_clicked()
{
}


void MainWindow::on_DeleteTablesButton_clicked()
{
    ui->listWidget->clear();
    current = 0;
    amount = 0;
    for (int i = 0; i < DEF_AM; i++){
        tables[i].Clear();
    }
    UpdateList();
}


void MainWindow::on_FindButton_clicked()
{
    dialog_find = new FindDialog;
    dialog_find->setWindowTitle("Find it the table");

    dialog_find->show();

    if (dialog_find->exec()==QDialog::Accepted){
        if (tables[ui->listWidget->currentRow()].Find(dialog_find->GetValue().toStdString()))
            QMessageBox::information(this,"Result of operation","This node was found") ;
        else
            QMessageBox::information(this,"Result of operation","This node was not found") ;
    }
    delete dialog_find;
}


void MainWindow::on_ClearTableButton_clicked()
{
    if (ui->listWidget->currentItem()){
        tables[ui->listWidget->currentRow()].Clear();
        UpdateList();
    }
    else {
        QMessageBox::information(this,"Error","No choosed table for deleting") ;
        ui->listWidget->setCurrentRow(-1);
        return ;
    }
}


void MainWindow::on_AddNodeButton_clicked()
{
    if (ui->listWidget->currentRow()==-1) {
        QMessageBox::information(this,"Error","No choosed table for adding") ;
        return ;
    }
    dialog_node= new AddNode;
    dialog_node->setWindowTitle("Add node");

    dialog_node->show();

    if (dialog_node->exec()==QDialog::Accepted){
         ui->list->addItem(dialog_node->GetValue());
         tables[ui->listWidget->currentRow()].Add(dialog_node->GetValue().toStdString());
         //tables[ui->listWidget->currentRow()].Export("/Users/Marat/Desktop/table.txt");
    }
}


void MainWindow::on_PopNodeButton_clicked()
{
    if (ui->list->currentRow()==-1) {
        QMessageBox::information(this,"Error","No choosed node for deleting") ;
        return ;
    }
    QListWidgetItem *it = ui->list->currentItem();
    QString node = it->text();
    tables[ui->listWidget->currentRow()].Remove(node.toStdString());
    delete it;
}


void MainWindow::on_QuitButton_clicked()
{
    qApp->QApplication::quit();
}


void MainWindow::on_ReadButton_clicked()
{
    /*
    dialog_read = new ReadDialog ;
    dialog_read->setWindowTitle("Read from file");

    dialog_read->show();

    if (dialog_read->exec()==QDialog::Accepted){
        tables[current].SetName((dialog_read->GetName()).toStdString());
        tables[current].Import((dialog_read->GetPath()).toStdString());
        ui->listWidget->addItem(dialog_read->GetName());
        ++current;
        ++amount;
        UpdateList();
    }
    */
    QString file_name = QFileDialog::getOpenFileName(this, "Open", QDir::currentPath(),"*.txt");
    if (file_name == "") return;

    tables[current].Import(file_name.toStdString());
    ui->listWidget->addItem(QString::fromStdString(tables[current].GetName()));
    ++current;
    ++amount;
    UpdateList();
}


void MainWindow::on_WriteButton_clicked()
{
    /*
    dialog_write = new WriteDialog ;
    dialog_write->setWindowTitle("Write to file");

    dialog_write->show();


    if (dialog_write->exec()==QDialog::Accepted){
        tables[ui->listWidget->currentRow()].Export(dialog_write->GetPath().toStdString());
    }
    */
    QString file_name = QFileDialog::getSaveFileName(this, "Save", QDir::currentPath(),"*.txt");
    if (file_name == "") return;

    tables[ui->listWidget->currentRow()].Export(file_name.toStdString());
}

int MainWindow::CurrentItemChanged(int current)
{
    int it = ui->listWidget->currentRow();
    while (current == it){
        Delay();
        it = ui->listWidget->currentRow();
    }
    ui->listWidget->setStyleSheet(
                "QListWidget::item:selected {"
                   "background-color: blue;"
                "}");
    return it;
}


void MainWindow::on_GenButton_clicked()
{
    /*
    dialog_gen = new GenDialog ;
    dialog_gen->setWindowTitle("Create a general table");

    QString first_table;
    QString second_table;
    QString new_table;
    dialog_gen->show();

    if (dialog_gen->exec()==QDialog::Accepted){
        first_table = dialog_gen->GetFirstName();
        second_table = dialog_gen->GetSecondName();
        new_table = dialog_gen->GetNewName();
    }
    int find_first = -1;
    int find_second = -1;
    for (int i = 0; i < amount; i++){
        ui->listWidget->setCurrentRow(i);
        if (ui->listWidget->currentItem()->text() == first_table)
            find_first = i;
    }
    for (int i = 0; i < amount; i++){
        ui->listWidget->setCurrentRow(i);
        if (ui->listWidget->currentItem()->text() == second_table)
            find_second = i;
    }
    if (find_first != -1 && find_second != -1)
    {
        ui->listWidget->addItem(new_table);
        ++amount;
        Collection<std::string> gen_t = tables[find_first] && tables[find_second];
        gen_t.SetName((new_table).toStdString());
        tables[current].CopyCol(gen_t);
        current++;
    }
    else
        QMessageBox::information(this,"Error","The specified items were not found");
    delete dialog_gen;
    */

    QMessageBox message;
    message.setWindowTitle("Clue");
    message.setText("Select two objects from the table list");
    message.exec();
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->listWidget->setCurrentRow(-1);
    ui->listWidget->setStyleSheet(
                "QListWidget::item {"
                   "background-color: black;"
                "}");
    int first_table = CurrentItemChanged(ui->listWidget->currentRow());
    //ui->listWidget->setCurrentRow(-1);
    int second_table = CurrentItemChanged(first_table);
    ui->listWidget->setStyleSheet("default");

    dialog_table = new CreateTable;
    dialog_table->setWindowTitle("Create a new table");

    //connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));
    dialog_table->show();

    if (dialog_table->exec()==QDialog::Accepted){
         ui->listWidget->addItem(dialog_table->GetName());
         ++amount;
         Collection<std::string> gen_t = tables[first_table] && tables[second_table];
         gen_t.SetName((dialog_table->GetName()).toStdString());
         tables[current].CopyCol(gen_t);
         current++;
    }
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    delete dialog_table;
}

